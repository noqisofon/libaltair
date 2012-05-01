//  
//  Collection.cpp
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
#include "altair/CompiledBlock.hxx"
#include "altair/OrderedCollection.hxx"
#include "altair/Array.hxx"
#include "altair/ByteArray.hxx"
#include "altair/Bag.hxx"
#include "altair/Iterator.hxx"
#include "altair/UnicodeString.hxx"
#include "altair/Set.hxx"
#include "altair/SortedCollection.hxx"
#include "altair/Stream.hxx"
#include "altair/String.hxx"

#include "altair/ElementNotFoundError.hxx"
#include "altair/EmptyCollectionError.hxx"

#include "altair/Collection.hxx"
USING_NAMESPACE_ALTAIR;


Collection* Collection::from(Array* const& an_array)
{
    return withAll( an_array );
}


Collection* Collection::with(Object* const& an_object)
{
    // return new OrderedCollection()
    //     ->add( an_object )
    //     ->yourself();
    Collection* ret = new OrderedCollection();

    ret->add( an_object );

    return ret;
}
Collection* Collection::with(Object* const& first_object, Object* const& second_object)
{
    Collection* ret = new OrderedCollection();

    // return ret
    //     ->add( first_object )
    //     ->add( second_object )
    //     ->yourself();
    ret
        ->add( first_object )
        ->add( second_object );

    return ret;

}
Collection* Collection::with(Object* const& first_object, Object* const& second_object, Object* const& third_object)
{
    Collection* ret = new OrderedCollection();
    // return new OrderedCollection()
    //     ->add( first_object )
    //     ->add( second_object )
    //     ->add( third_object )
    //     ->yourself();

    ret
        ->add( first_object )
        ->add( second_object )
        ->add( third_object );

    return ret;
}
Collection* Collection::with( Object* const& first_object,
                              Object* const& second_object,
                              Object* const& third_object,
                              Object* const& fourth_object)
{
    Collection* ret = new OrderedCollection();
    // return new OrderedCollection()
    //     ->add( first_object )
    //     ->add( second_object )
    //     ->add( third_object )
    //     ->add( fourth_object )
    //     ->yourself();
    ret
        ->add( first_object )
        ->add( second_object )
        ->add( third_object )
        ->add( fourth_object );

    return ret;
}
Collection* Collection::with( Object* const& first_object,
                              Object* const& second_object,
                              Object* const& third_object,
                              Object* const& fourth_object,
                              Object* const& fifth_object)
{
    Collection* ret = new OrderedCollection();
    // return new OrderedCollection()
    //     ->add( first_object )
    //     ->add( second_object )
    //     ->add( third_object )
    //     ->add( fourth_object )
    //     ->add( fifth_object )
    //     ->yourself();
    ret
        ->add( first_object )
        ->add( second_object )
        ->add( third_object )
        ->add( fourth_object )
        ->add( fifth_object );

    return ret;
}


Collection* Collection::withAll(Collection* const& an_collection)
{
    Collection* ret = new OrderedCollection();
    // return new OrderedCollection()
    //     ->addAll( an_collection );
    ret->addAll( an_collection );

    return ret;
}


#if defined(ALTAIR_USING_FUNCTOR)
static Object* binary_block_with_join(Object* const& size, Object* const& each)
{
    return size->plus( each->size() ); 
}


Collection* Collection::withJoin(Collection* const& a_collection)
{
    Collection* ret = a_collection->copyEmpty();

    a_collection->inject( Integer::valueOf( 0 ), binary_block_with_join );

    Iterator* it = a_collection->iterator();
    while ( it->atEnd() ) {
        
    }
}
#endif  /* defined(ALTAIR_USING_FUNCTOR) */


const Collection* Collection::addAll(const Collection* const& a_collection)
{
    Stream* it = a_collection->readStream();
    while ( it->atEnd() ) {
        add( it->next() );
    }
    it->release();

    return a_collection;
}


Collection* Collection::empty()
{
    //return __REINTERPRET_CAST(Collection* const, become( copyEmpty() ));
    become( copyEmpty() );

    return this;
}


Object* remove_exception_block(const Collection* const& self, Object* const& old_object)
{
    ElementNotFoundError::signalOn( old_object, new String( "object" ) );

    return NULL;
}


Object* Collection::remove(Object* const& old_object)
{
    return remove( old_object, remove_exception_block );
}
Object* Collection::remove(Object* const& old_object, Object* (*an_exception_block)(const Collection* const&, Object* const&))
{
    subclassResponsibility();

    return NULL;
}


const Collection* Collection::removeAll(const Collection* const& a_collection)
{
    Stream* it = a_collection->readStream();

    while ( it->atEnd() ) {
        remove( it->next() );
    }
    it->release();

    return a_collection;
}
const Collection* Collection::removeAll(const Collection* const& a_collection, Object* (*a_block)(const Collection* const&, Object* const&))
{
    Stream* it = a_collection->readStream();

    while ( it->atEnd() ) {
        remove( it->next(), a_block );
    }
    it->release();

    return a_collection;
}


size_t Collection::size() const
{
    size_t count = 0;
    Stream* it = readStream();

    while ( it->atEnd() ) {
        ++ count;
    }
    it->release();

    return count;
}


bool Collection::includes(const Object* const& an_object) const
{
    bool ret = false;
    Stream* it = readStream();

    while ( it->atEnd() ) {
        Object* element = it->next();

        if ( an_object->equals( element ) ) {
            ret = true;

            break;
        }
    }
    it->release();

    return ret;
}


bool Collection::identityIncludes(const Object* const& an_object) const
{
    bool ret = false;
    Stream* it = readStream();

    while ( it->atEnd() ) {
        Object* element = it->next();

        if ( an_object->identityEquals( element ) ) {
            ret = true;

            break;
        }
    }
    it->release();

    return ret;
}


bool Collection::includesAllOf(const Collection* const& a_collection) const
{
    int len = a_collection->size();
    int count = 0;

    Stream* it = readStream();

    while ( it->atEnd() ) {
        Object* element = it->next();

        if ( a_collection->includes( element ) )
            ++ count;
    }
    it->release();

    return len == count;
}


bool Collection::includesAnyOf(const Collection* const& a_collection) const
{
    //int len = a_collection->size();
    int count = 0;

    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* element = it->next();

        if ( a_collection->includes( element ) )
            ++ count;
    }
    it->release();

    return count > 0;
}


bool Collection::isEmpty() const
{
    return size() == 0;
}


bool Collection::notEmpty() const
{
    return size() > 0;
}


int Collection::occurencesOf(const Object* const& an_object) const
{
    int count = 0;

    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* element = it->next();

        if ( an_object->equals( element ) )
            ++ count;
    }
    it->release();

    return count;
}


Object* Collection::anyOne() const
{
    Object* ret;

    Stream* it = readStream();
    while ( it->atEnd() ) {
        ret = it->next();

        break;
    }

    it->release();

    if ( ret )
        return ret;

    EmptyCollectionError::signalOn( this );

    return NULL;
}


#if defined(ALTAIR_USING_FUNCTOR)
Collection* Collection::join() const
{
    if ( isEmpty() )
        return ALTAIR_ARRAY0;
    else {
        Class* anyone_species = anyOne()->species();
        Collection* ret = Collection::join( this );
    }
}
#endif  /* defined(ALTAIR_USING_FUNCTOR) */


Stream* Collection::readStream() const
{
    return Iterator::on( this );
}


Collection* Collection::select(bool (*a_block)(Object* const&)) const
{
    Collection* new_collection = copyEmpty();

    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* element = it->next();

        if ( a_block( element ) )
            new_collection->add( element );
    }
    it->release();

    return new_collection;
}


Collection* Collection::reject(bool (*a_block)(Object* const&)) const
{
    Collection* new_collection = copyEmpty();

    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* element = it->next();

        if ( a_block( element ) )
            new_collection->add( element );
    }
    it->release();

    return new_collection;
}


Collection* Collection::collect(Object* (*a_block)(Object* const&)) const
{
    Collection* new_collection = copyEmptyForCollect();

    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* element = it->next();

        new_collection->add( a_block( element ) );
    }
    it->release();

    return new_collection;
}


#if defined(ALTAIR_USING_FUNCTOR)
Collection* Collection::gather(Object* (*a_block)(Object* const&)) const
{
    return collect( a_block )->join();
}
#endif  /* defined(ALTAIR_USING_FUNCTOR) */


Array* Collection::asArray() const
{
    Array* ret = new Array( size() );

    ret->SequenceableCollection::replaceFrom( 0, size(), this );

    return ret;
}


ByteArray* Collection::asByteArray() const
{
    ByteArray* ret = new ByteArray( size() );

    ret->SequenceableCollection::replaceFrom( 0, size(), this );

    return ret;
}


Bag* Collection::asBag() const
{
    Bag* ret = new Bag( size() );

    ret->addAll( this );

    return ret;
}


Set* Collection::asSet() const
{
    Set* ret = new Set( size() * 2 );

    ret->addAll( this );

    return ret;
}


String* Collection::asString() const
{
    String* ret = new String( __STATIC_CAST(int, size()) );

    ret->replaceFrom( 0, __STATIC_CAST(int, size()), this );

    return ret;
}


UnicodeString* Collection::asUnicodeString() const
{
    UnicodeString* ret = new UnicodeString( size() );

    ret->replaceFrom( 0, size(), this );

    return ret;
}


OrderedCollection* Collection::asOrderedCollection() const
{
    OrderedCollection* ret = new OrderedCollection( size() * 2 );

    ret->addAll( this );

    return ret;
}


SortedCollection* Collection::asSortedCollection() const
{
    SortedCollection* ret = new SortedCollection( size() + 10 );

    ret->addAll( this );

    return ret;
}
SortedCollection* Collection::asSortedCollection(int (*a_block)(const Object* const&, const Object* const&)) const
{
    SortedCollection* ret = asSortedCollection();

    ret->sortBlock( a_block );

    return ret;
}


Collection* Collection::sorted() const
{
    Array* ret = new Array( size() );

    ret->SequenceableCollection::replaceFrom( 0,
                                              size(),
                                              __REINTERPRET_CAST(SequenceableCollection *, asSortedCollection()),
                                              0 );

    return ret;
}
Collection* Collection::sorted(int (*sort_block)(const Object* const&, const Object* const&)) const
{
    Array* ret = new Array( size() );

    ret->SequenceableCollection::replaceFrom( 0,
                                              size(),
                                              __REINTERPRET_CAST(SequenceableCollection *, asSortedCollection( sort_block )),
                                              0 );

    return ret;
}


// static Object* const copy_replacing_block(Object* const& each)
// {
// }


Collection* Collection::copyReplacing(Object* const& target_object, Object* const& new_object) const
{
    //return collect(  );
    Collection* new_collection = copyEmptyForCollect();

    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* element = it->next();

        if ( element->equals( target_object ) )
            new_collection->add( element );
        else
            new_collection->add( new_object );
    }
    it->release();

    return new_collection;
}


Collection* Collection::copyWith(Object* const& new_element) const
{
    Collection* const a_copy = __REINTERPRET_CAST(Collection * const, copy());

    a_copy->add( new_element );

    return a_copy;
}


Collection* Collection::copyWithout(Object* const& old_element) const
{
    //return reject();
    Collection* new_collection = copyEmpty();

    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* element = it->next();

        if ( element->equals( old_element ) )
            new_collection->add( element );
    }
    it->release();

    return new_collection;
}


#if defined(ALTAIR_TRANSPLANTLY)
Collection* Collection::copyEmpty() const
{
    Collection* ret;
    Class* const self_species = species();

    ret = __REINTERPRET_CAST(Collection *, self_species->createInstance( basicSize() ));

    self_species->release();

    return ret;
}
Collection* Collection::copyEmpty(int new_size) const
{
    Collection* ret;
    Class* const self_species = species();

    ret = __REINTERPRET_CAST(Collection *, self_species->createInstance( new_size ));

    self_species->release();

    return ret;
}
#endif  /* defined(ALTAIR_TRANSPLANTLY) */


Collection* Collection::copyEmptyForCollect() const
{
    return copyEmpty();
}
Collection* Collection::copyEmptyForCollect(int size) const
{
    return copyEmpty( size );
}
// Local Variables:
//   coding: utf-8
// End:
