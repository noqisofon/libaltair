//  
//  HashedCollection.cpp
//  altair
//  
//  Auther:
//       ned rihine <ned.rihine@gmail.com>
// 
//  Copyright (c) 2012 rihine All rights reserved.
// 
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
// 
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
// 
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include "config.h"

#include "altair/altair_prefix.h"
#include "altair/Class.hxx"
#include "altair/Stream.hxx"
#include "altair/Array.hxx"
#include "altair/Dictionary.hxx"

#include "altair/HashedCollection.hxx"
USING_NAMESPACE_ALTAIR;


HashedCollection* HashedCollection::primNew(size_t real_size)
{
    return new Dictionary( real_size );
}


HashedCollection* HashedCollection::withAll(const Collection* const& a_collection)
{
    HashedCollection* ret = new Dictionary( a_collection->size() * 2 );

    ret->addAll( a_collection );

    return ret;
}


HashedCollection::HashedCollection()
    : tally_(0)
{
}
HashedCollection::HashedCollection(size_t size)
    : tally_(size)
{
}
HashedCollection::HashedCollection(const Collection& a_collection)
    : tally_(a_collection.size())
{
}


Object* HashedCollection::at(int index) const
{
    shouldNotImplement();

    return NULL;
}


void HashedCollection::put(int index, Object* const& value)
{
    shouldNotImplement();
}


Collection* const& HashedCollection::add(Object* const& new_object)
{
    if ( ALTAIR_ISNIL(new_object) )
        return this;

    int index = findIndex( new_object );
    if ( ALTAIR_ISNIL(primAt( index )) ) {
        if ( incrementTally() )
            index = findIndex( new_object );

        primPut( index, new_object );
    }
    return this;
}


Object* HashedCollection::remove(Object* const& old_object, Object* (*an_exception_block)(const Collection* const&, Object* const&))
{
    int index = findIndex( old_object );

    if ( index == -1 )
        return an_exception_block( this, old_object );

    primPut( index, NULL );
    decrementTally();
    rehashObjectsAfter( index );

    return old_object;
}


Object* HashedCollection::shallowCopy() const
{
    HashedCollection* a_copy = __REINTERPRET_CAST(HashedCollection *, Collection::copyEmpty( capacity() ));

    a_copy->copyAllFrom( this );

    return a_copy;
}


Object* HashedCollection::deepCopy() const
{
    HashedCollection* new_hashed_collection = __REINTERPRET_CAST(HashedCollection *, Collection::copyEmpty( capacity() ));

    Stream* it = readStream();
    while ( !it->atEnd() ) {
        Object* each = it->next();

        new_hashed_collection->addWhileGrowing( each->copy() );
    }
    it->release();

    return new_hashed_collection;
}


bool HashedCollection::includes(const Object* const& an_object) const
{
    return findIndexOrNil( an_object ) != -1;
}


int HashedCollection::occurrencesOf(const Object* const& an_object) const
{
    if ( ALTAIR_ISNIL(an_object) )
        return 1;
    if ( includes( an_object ) )
        return 1;
    else
        return 0;
}


int HashedCollection::hash() const
{
    int hash_value = __STATIC_CAST(int, tally_);

    Stream* it = readStream();
    while ( !it->atEnd() ) {
        Object* member = it->next();

        hash_value ^= ALTAIR_SCRAMBLE(hashFor( member ));
    }
    it->release();

    return hash_value;
}


bool HashedCollection::equals(const Object* const& an_object) const
{
    Class* self_class = getClass();
    Class* other_class = an_object->getClass();

    if ( !self_class->identityEquals( other_class ) ) {
        self_class->release();
        other_class->release();

        return false;
    }
    self_class->release();
    other_class->release();

    return equals( __REINTERPRET_CAST(const HashedCollection* const, an_object) );
}
bool HashedCollection::equals(const HashedCollection* const& a_hashed_collection) const
{
    if ( identityEquals( a_hashed_collection ) )
        return true;
    if ( tally_ != a_hashed_collection->size() )
        return false;

    Stream* it = readStream();
    while ( !it->atEnd() ) {
        Object* element = it->next();

        if ( !a_hashed_collection->includes( element ) ) {
            it->release();

            return false;
        }
    }
    it->release();

    return true;
}


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
void HashedCollection::storeOn(Stream* const& a_stream) const
{
    a_stream->nextPut( '(' );
    a_stream->nextPutAll( getClass()->storeString() );
    a_stream->nextPutAll( " new" );

    bool has_elements = false;

    Stream* it = readStream();
    while ( !it->atEnd() ) {
        Object* element = it->next();

        a_stream->nextPutAll( " add: " );
        element->storeOn( a_stream );
        a_stream->nextPut( '$' );

        has_elements = true;
    }
    it->release();

    if ( has_elements )
        a_stream->nextPutAll( " yourself" );
    
    a_stream->nextPut( ')' );
}
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


void HashedCollection::rehash()
{
    Array* a_copy = new Array( size() );

    resetTally();

    int n = 0;
    int self_prim_size = __STATIC_CAST(int, primSize());
    for ( int i = 0; i < self_prim_size; ++ i ) {
        Object* obj = primAt( i );

        if ( !ALTAIR_ISNIL(obj) ) {
            a_copy->put( n ++, obj );
            primPut( i, NULL );
        }
    }

    Stream* it = a_copy->readStream();
    while ( !it->atEnd() ) {
        Object* each = it->next();

        addWhileGrowing( each );
    }
    it->release();

    a_copy->release();
}


Object* HashedCollection::addWhileGrowing(Object* const& value)
{
    primPut( findElementIndex( value ), value );
    ++ tally_;

    return value;
}


void HashedCollection::rehashObjectsAfter(int index)
{
    int i = index, j;
    int size = __STATIC_CAST(int, primSize());

    Object* element;
    while ( ALTAIR_NOTNIL(element) ) {
        if ( i == size )
            i = 0;
        else
            ++ i;
        element = primAt( i );

        primPut( i, NULL );
        j = findElementIndex( element );
        primPut( j, element );
    }
}


int HashedCollection::hashFor(const Object* const& an_object) const
{
    subclassResponsibility();

    return -1;
}


int HashedCollection::findElementIndex(const Object* const& an_object) const
{
    int size = __STATIC_CAST(int, primSize());
    int index = (ALTAIR_SCRAMBLE(an_object->hash()) & size - 1) + 1;

    while ( true ) {
        Object* element = primAt( index );

        if ( ALTAIR_ISNIL(element) )
            break;
        if ( index == size )
            index = 0;
        else
            ++ index;
    }
    return index;
}


int HashedCollection::findIndex(const Object* const& an_object) const
{
    subclassResponsibility();

    return -1;
}


int HashedCollection::findIndexOrNil(const Object* const& an_object) const
{
    //Object* temp;
    int index = findIndex( an_object );

    //temp = primAt( index );
    if ( ALTAIR_ISNIL(primAt( index )) )
        return -1;
    return index;
}


Collection* HashedCollection::copyEmpty() const
{
    return Collection::copyEmpty( __STATIC_CAST(int, capacity()) );
}


HashedCollection* HashedCollection::copyAllFrom(const HashedCollection* const& a_hashed_collection)
{
    int prim_size = __STATIC_CAST(int, a_hashed_collection->primSize());

    for ( int i = 0; i < prim_size; ++ i ) {
        Object* value = a_hashed_collection->at( i );

        if ( ALTAIR_ISNIL(value) )
            addWhileGrowing( value );
    }
    return this;
}


Object* HashedCollection::primAt(int an_index) const
{
    return checkIndexableBounds( an_index );
}


void HashedCollection::primPut(int an_index, Object* const& value)
{
    checkIndexableBoundsPut( an_index, value );
}


void HashedCollection::initialize()
{
    resetTally();
}


void HashedCollection::resetTally()
{
    tally_ = 0;
}


bool HashedCollection::incrementTally()
{
    bool grown = tally_ >= (primSize() * 3 / 4);

    if ( grown )
        growBy( capacity() );

    ++ tally_;

    return grown;
}


bool HashedCollection::decrementTally()
{
    -- tally_;

    return false;
}


void HashedCollection::grow()
{
    growBy( capacity() );
}


void HashedCollection::growBy(int delta)
{
    HashedCollection* new_hashed_collection;
    size_t new_size = primSize() + delta;

    new_hashed_collection = __REINTERPRET_CAST(HashedCollection *, Collection::copyEmpty( capacity() + delta ));
    new_hashed_collection->copyAllFrom( this );

    become( new_hashed_collection );
}


// Local Variables:
//   coding: utf-8
// End:
