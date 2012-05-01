//  
//  Bag.cpp
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
#include "altair/Association.hxx"
#include "altair/Number.hxx"
#include "altair/Integer.hxx"
#include "altair/Character.hxx"
#include "altair/Stream.hxx"
#include "altair/String.hxx"
#include "altair/Dictionary.hxx"
#include "altair/LookupTable.hxx"
#include "altair/SortedCollection.hxx"
#include "altair/HashedCollection.hxx"
#include "altair/InvalidArgumentError.hxx"

#include "altair/Bag.hxx"
USING_NAMESPACE_ALTAIR;


Bag::Bag()
{
    initContents( 31 );
}
Bag::Bag(size_t size)
{
    initContents( ALTAIR_MAX( 7, size ) );
}


Collection* const& Bag::add(Object* const& new_object)
{
    addWithOccurrences( new_object, 1 );

    return this;
}


Object* Bag::addWithOccurrences(Object* const new_object, int an_integer)
{
    if ( ALTAIR_ISNIL( new_object ) ) {
        InvalidArgumentError::signalOn( new_object );

        return NULL;
    }

    Number* temp = __REINTERPRET_CAST(Number *, contents_->put( new_object, Integer::valueOf( occurrencesOf( new_object ) + an_integer ) ));
    int new_occurrences = temp->asInt32();

    if ( new_occurrences <= 0 )
        contents_->removeKey( new_object );

    return new_object;
}


Object* Bag::remove(Object* const& old_object, Object* (*an_exception_block)(const Collection* const&, Object* const&))
{
    int count = occurencesOf( old_object );

    if ( count == 0 )
        return an_exception_block( this, old_object );
    if ( count == 1 )
        contents_->removeKey( old_object );
    else
        contents_->put( old_object, Integer::valueOf( count - 1 ) );

    return old_object;
}


static int counts_sort_block(const Object* const& left, const Object* const& right)
{
    if ( left->isNumber() && right->isNumber() )
        return __REINTERPRET_CAST(const Number * const, left)->asInt32() >= __REINTERPRET_CAST(const Number * const, right)->asInt32();
    else
        return 0;
}


SequenceableCollection* Bag::sortedByCount() const
{
    Array* result;
    SortedCollection* counts = SortedCollection::withSortBlock( counts_sort_block );

    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* each = it->next();

        if ( each->isAssociation() ) {
            Association* pair = __REINTERPRET_CAST(Association *, each);

            counts->add( new Association( pair->value(), pair->key() ) );
        }
    }
    it->release();

    result = counts->asArray();
    counts->release();

    return __REINTERPRET_CAST(SequenceableCollection *, result);
}


static Object* null_if_absent(const Object* const&/* self */, const Object* const&/* key */)
{
    return NULL;
}


int Bag::occurrencesOf(const Object* const& an_object) const
{
    Number* temp = __REINTERPRET_CAST(Number *, contents_->at( an_object, null_if_absent ));

    return temp->asInt32();
}


bool Bag::includes(const Object* const& an_object) const
{
    return contents_->includesKey( an_object );
}


size_t Bag::size() const
{
    size_t count = 0;

    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* element = it->next();

        if ( element->isNumber() )
            count += __REINTERPRET_CAST(Number *, element)->asInt32();
    }
    it->release();

    return count;
}


int Bag::hash() const
{
    return contents_->hash();
}


bool Bag::equals(const Object* const& an_object) const
{
    Class* self_class = getClass();
    Class* other_class = an_object->getClass();

    if ( !self_class->identityEquals( other_class ) ) {
        self_class->release();
        other_class->release();

        return false;
    }
    return equals( __REINTERPRET_CAST(const Bag* const, an_object) );
}
bool Bag::equals(const Bag* const& a_bag) const
{
    return contents_->equals( a_bag->contents_ );
}


Set* Bag::asSet() const
{
    return contents_->keys();
}


void Bag::printOn(Stream* const& a_stream) const
{
    a_stream->nextPutAll(
#if defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE
        getClass()->storeString()
#else
        getClass()->printString()
#endif  /* defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE */
    );

    a_stream->nextPut( '(' );

    Stream* it = contents_->keysAndValuesReadStream();
    while ( it->atEnd() ) {
        Association* pair = __REINTERPRET_CAST(Association *, it->next());

        a_stream->print( pair->key() );
        a_stream->nextPut( ':' );
        a_stream->print( pair->value() );
        a_stream->space();
    }
    it->release();

    a_stream->nextPut( ')' );
}


#if defined(ALTAIR_TRANSPLANTLY)
Class* Bag::dictionaryClass() const
{
    return LookupTable::getCurrentClass();
}
#endif  /* defined(ALTAIR_TRANSPLANTLY) */


Dictionary* Bag::valuesAndCounts() const
{
    return __REINTERPRET_CAST(Dictionary *, contents_->copy());
}


Dictionary* Bag::contents() const
{
    return contents_;
}


void Bag::initContents(size_t size)
{
#if defined(ALTAIR_TRANSPLANTLY)
    contents_ = __REINTERPRET_CAST(Dictionary *, dictionaryClass()->createInstance( size ));
#else
    contents_ = new LookupTable( size );
#endif  /* defined(ALTAIR_TRANSPLANTLY) */
}
// Local Variables:
//   coding: utf-8
// End:

