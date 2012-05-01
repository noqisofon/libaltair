//  
//  SequenceableCollection.cpp
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
#include "altair/Number.hxx"
#include "altair/Integer.hxx"
#include "altair/Iterator.hxx"
#include "altair/ReadStream.hxx"
#include "altair/WriteStream.hxx"
#include "altair/ReadWriteStream.hxx"
#include "altair/Random.hxx"
#include "altair/NotFoundError.hxx"
#include "altair/ArgumentOutOfRangeError.hxx"

#include "altair/SequenceableCollection.hxx"
USING_NAMESPACE_ALTAIR;


bool SequenceableCollection::equals(const Collection* const& a_collection) const
{
    if ( !getClass()->equals( a_collection->getClass() ) )
        return false;
    if ( size() != a_collection->size() )
        return false;

    int len = __STATIC_CAST(int, size());
    for ( int i = 0; i < len; ++ i ) {
        if ( !Object::at( i )->equals( a_collection->at( i ) ) )
            return false;
    }
    return true;
}


int SequenceableCollection::hash() const
{
    int ret_hash = __STATIC_CAST(int, size());
    int carry = 0;

    Stream* it = readStream();

    while ( it->atEnd() ) {
        Object* element = it->next();

        carry = (ret_hash &   536870912) > 0;
        ret_hash = ret_hash & 536870911;
        ret_hash = ret_hash << 1;

        if ( carry ) ret_hash = ret_hash | 1;

        ret_hash = ret_hash ^ element->hash();
    }

    it->release();

    return ret_hash;
}


bool SequenceableCollection::startsWith(const SequenceableCollection* const& sequence) const
{
    if ( !( size() >= sequence->size() ) )
        return true;

    bool ret = true;
    Stream* it = sequence->readStream();
    for ( int i = 0; it->atEnd(); ++ i ) {
        Object* each = it->next();

        if ( !Object::at( i )->equals( each ) ) {
            ret = false;

            break;
        }
    }
    it->release();

    return ret;
}


bool SequenceableCollection::endsWith(const SequenceableCollection* const& sequence) const
{
    int delta = __STATIC_CAST(int, size()) - __STATIC_CAST(int, sequence->size());

    if ( !(delta >= 0) )
        return false;

    bool ret = true;
    Stream* it = sequence->readStream();
    for ( int i = 0; it->atEnd(); ++ i ) {
        Object* each = it->next();

        if ( !Object::at( i + delta )->equals( each ) ) {
            ret = false;

            break;
        }
    }
    it->release();

    return ret;
}


Object* SequenceableCollection::at(int an_index, Object* (*a_block)(const Object* const&, const Object* const&)) const
{
    size_t self_size = size();

    if ( 0 <= an_index &&  an_index < __STATIC_CAST(int, self_size) )
        return a_block( this, Integer::valueOf( an_index ) );

    return Object::at( an_index );
}


Object* SequenceableCollection::atRandom() const
{
    return Object::at( __STATIC_CAST(int, Random::betweenAnd( 0, size() )) );
}


Collection* SequenceableCollection::atAll(const Collection* const& key_collection) const
{
    Collection* result = copyEmptyForCollect( key_collection->size() );

    Stream* it = key_collection->readStream();

    while ( it->atEnd() ) {
        Object* each = it->next();
        int key = 0;

        if ( each->isNumber() )
            key = __REINTERPRET_CAST(Number *,each)->asInt32();

        result->add( Object::at( key ) );
    }

    it->release();

    return result;
}


void SequenceableCollection::putAll(const Collection* const& a_collection, Object* const& an_object)
{
    Stream* it = a_collection->readStream();

    while ( it->atEnd() ) {
        Object* each = it->next();
        int index = 0;

        if ( each->isNumber() )
            index = ((Number *)each)->asInt32();

        put( index, an_object );
    }
}


const SequenceableCollection* const& SequenceableCollection::atAllPut(Object* const& an_object)
{
    size_t self_size = size();
    size_t to;

    put( 0, an_object ); if ( self_size == 1 ) return this;
    put( 1, an_object ); if ( self_size == 2 ) return this;
    put( 2, an_object ); if ( self_size == 3 ) return this;
    put( 3, an_object ); if ( self_size == 4 ) to = 4;

    while ( self_size > to ) {
        replaceFrom/*ToWithStartingAt*/( to,
                                         ALTAIR_MIN(to += to, self_size),
                                         this,
                                         0 );
    }
}


Object* SequenceableCollection::after(const Object* const& old_object) const
{
    int i = indexOf( old_object );

    if ( i == 0 ) {
        NotFoundError::signalOn( old_object, "Object" );

        return NULL;
    }

    return Object::at( i + 1 );
}


Object* SequenceableCollection::before(const Object* const& old_object) const
{
    int i = indexOf( old_object );

    if ( i == 0 )
        NotFoundError::signalOn( old_object, "Object" );

    return Object::at( i - 1 );
}


SequenceableCollection* SequenceableCollection::allButFirst() const
{
    return __REINTERPRET_CAST(SequenceableCollection *, copyFrom( 1 ));
}
SequenceableCollection* SequenceableCollection::allButFirst(int n) const
{
    return __REINTERPRET_CAST(SequenceableCollection *, copyFrom( n ));
}


SequenceableCollection* SequenceableCollection::allButLast() const
{
    return __REINTERPRET_CAST(SequenceableCollection *, copyFrom( 0, size() - 1 ));
}
SequenceableCollection* SequenceableCollection::allButLast(int n) const
{
    return __REINTERPRET_CAST(SequenceableCollection *, copyFrom( 0, size() - (n - 1) ));
}


Object* SequenceableCollection::first() const
{
    return Object::at( 0 );
}
SequenceableCollection* SequenceableCollection::first(int n) const
{
    return __REINTERPRET_CAST(SequenceableCollection *, copyFrom( 0, n ));
}


Object* SequenceableCollection::second() const
{
    return Object::at( 1 );
}


Object* SequenceableCollection::third() const
{
    return Object::at( 2 );
}


Object* SequenceableCollection::fourth() const
{
    return Object::at( 3 );
}


Object* SequenceableCollection::last() const
{
    return Object::at( size() - 1 );
}
SequenceableCollection* SequenceableCollection::last(int n) const
{
    return __REINTERPRET_CAST(SequenceableCollection *, copyFrom( size() - n ));
}


bool SequenceableCollection::includes(const Object* const& an_object) const
{
    int self_size = size();

    for ( int i = 0; i < self_size; ++ i ) {
        if ( an_object->equals( Object::at( i ) ) )
            return true;
    }
    return false;
}


bool SequenceableCollection::identityIncludes(const Object* const& an_object) const
{
    int self_size = size();

    for ( int i = 0; i < self_size; ++ i ) {
        if ( an_object == Object::at( i ) )
            return true;
    }
    return false;
}


static int null_exception_block(const Object* const& self, const Object* const&)
{
    return -1;
}


int SequenceableCollection::indexOf(const Object* const& an_element) const
{
    return indexOf( an_element,
                    0,
                    null_exception_block );
}
int SequenceableCollection::indexOf(const Object* const& an_element, int an_index) const
{
    return indexOf( an_element,
                    an_index,
                    null_exception_block );
}
int SequenceableCollection::indexOf(const Object* const& an_element, int an_index, int (*exception_block)(const Object* const&, const Object* const&)) const
{
    size_t self_size = size();

    if ( an_index < 0 || self_size < an_index ) {
        if ( an_index == self_size + 1 )
            return exception_block( this, an_element );
        else
            checkIndexableBounds( an_index );
    }

    int arrived = __STATIC_CAST(int, size());

    for ( int i = an_index; i < arrived; ++ i ) {
        if ( Object::at( i )->equals( an_element ) )
            return i;
    }
    return exception_block( this, an_element );
}


int SequenceableCollection::indexOfLast(const Object* const& an_element, int (*exception_block)(const Object* const&, const Object* const&) ) const
{
    size_t self_size = size();

    for ( int i = __STATIC_CAST(int, self_size); i >= 0; -- i ) {
        if ( Object::at( i )->equals( an_element ) )
            return i;
    }
    return exception_block( this, an_element );
}


int SequenceableCollection::identityIndexOf(const Object* const& an_element) const
{
    return identityIndexOf( an_element,
                            0,
                            null_exception_block );
}
int SequenceableCollection::identityIndexOf(const Object* const& an_element, int an_index) const
{
    return identityIndexOf( an_element,
                            an_index,
                            null_exception_block );
}
int SequenceableCollection::identityIndexOf(const Object* const& an_element, int an_index, int (*exception_block)(const Object* const&, const Object* const&) ) const
{
    size_t self_size = size();

    if ( an_index < 0 || self_size < an_index ) {
        if ( an_index == self_size + 1 )
            return exception_block( this, an_element );
        else
            checkIndexableBounds( an_index );
    }

    int arrived = __STATIC_CAST(int, size());

    for ( int i = an_index; i < arrived; ++ i ) {
        if ( Object::at( i ) == an_element )
            return i;
    }
    return exception_block( this, an_element );
}


int SequenceableCollection::identityIndexOfLast(const Object* const& an_element, int (*exception_block)(const Object* const&, const Object* const&)) const
{
    size_t self_size = size();

    for ( int i = __STATIC_CAST(int, self_size); i >= 0; -- i ) {
        if ( Object::at( i )->identityEquals( an_element ) )
            return i;
    }
    return exception_block( this, an_element );
}


int SequenceableCollection::indexOfSubCollection(const SequenceableCollection* const& a_sub_collection) const
{
    return indexOfSubCollection( a_sub_collection,
                                 0,
                                 null_exception_block );
}
int SequenceableCollection::indexOfSubCollection(const SequenceableCollection* const& a_sub_collection, int an_index) const
{
    return indexOfSubCollection( a_sub_collection,
                                 an_index,
                                 null_exception_block );
}
int SequenceableCollection::indexOfSubCollection( const SequenceableCollection* const& a_sub_collection,
                                                  int an_index,
                                                  int (*exception_block)(const Object* const&, const Object* const&) ) const
{
    
    size_t sub_size = a_sub_collection->size();

    if ( sub_size == 0 )
        return an_index;

    size_t self_size = size();

    if ( (an_index + sub_size - 1) <= self_size ) {
        int arrived = an_index - sub_size + 1;

        for ( int i = an_index; i < arrived; ++ i ) {
            if ( Object::at( i )->equals( a_sub_collection->Object::at( 0 ) ) ) {
                if ( matchSubCollection( a_sub_collection, i ) )
                    return i;
            }
        }
    }
    return exception_block( this, a_sub_collection );
}


void SequenceableCollection::replaceFrom(int start, int stop, const Collection* const& replacement_collection, int rep_start)
{
    int min_stop = start - 1;
    int max_stop = ALTAIR_MIN(__STATIC_CAST(int, size()), min_stop + (int)replacement_collection->size());

    if ( !(min_stop <= stop && stop <= max_stop) ) {
        ArgumentOutOfRangeError::signalOn( stop,
                                           min_stop,
                                           max_stop );

        return ;
    }

    int delta = start - rep_start;

    if ( rep_start > start ) {
        for ( int i = start; i < stop; ++ i ) {
            put( i, replacement_collection->at( i - delta ) );
        }
    } else {
        for ( int i = stop; i >= start; -- i ) {
            put( i, replacement_collection->at( i - delta ) );
        }
    }
}
void SequenceableCollection::replaceFrom(int an_index, int stop_index, Object* const& replace_object)
{
    if ( an_index - stop_index < -1 ) {
        ArgumentOutOfRangeError::signalOn( stop_index,
                                           an_index,
                                           __STATIC_CAST(int, size()) );

        return ;
    }

    for ( int i = 0; i < stop_index; ++ i ) {
        put( i, replace_object );
    }
}


void SequenceableCollection::replaceAll(const Object* const& an_object, Object* const& another_object)
{
    int self_size = __STATIC_CAST(int, size());

    for ( int i = 0; i < self_size; ++ i ) {
        if ( Object::at( i )->equals( an_object ) )
            put( i, another_object );
    }
}


static int gain_self_size_exception_block(const Object* const& self, const Object* const& an_object)
{
    return __STATIC_CAST(int, self->size());
}


SequenceableCollection* SequenceableCollection::copyAfter(const Object* const& an_object) const
{
    return __REINTERPRET_CAST(SequenceableCollection *, copyFrom( indexOf( an_object,
                                                                           gain_self_size_exception_block ) + 1 ));
}


SequenceableCollection* SequenceableCollection::copyAfterLast(const Object* const& an_object) const
{
    return __REINTERPRET_CAST(SequenceableCollection *, copyFrom( indexOfLast( an_object,
                                                                               gain_self_size_exception_block ) + 1 ));
}


static int copy_up_to_exception_block(const Object* const& self, const Object* const& an_object)
{
    return __STATIC_CAST(int, __REINTERPRET_CAST(const SequenceableCollection * const, self)->size()) + 1;
}


SequenceableCollection* SequenceableCollection::copyUpTo(const Object* const& an_object) const
{
    return copyFrom( 0,
                     indexOf( an_object,
                              copy_up_to_exception_block ) - 1 );
}


SequenceableCollection* SequenceableCollection::copyUpToLast(const Object* const& an_object) const
{
    return copyFrom( 0,
                     indexOfLast( an_object,
                                  copy_up_to_exception_block ) - 1 );
}


SequenceableCollection* SequenceableCollection::copyReplaceFrom(int start, int stop, Object* const& an_object) const
{
    if ( stop - start < -1 ) {
        ArgumentOutOfRangeError::signalOn( stop,
                                           start - 1,
                                           __STATIC_CAST(int, size()) );

        return NULL;
    }
    if ( stop >= start ) {
        SequenceableCollection* temp = __REINTERPRET_CAST(SequenceableCollection *, copy());
        SequenceableCollection* key_sequence;
        
        key_sequence = Integer::valueOf( start )->to( Integer::valueOf( stop ) );
        temp->putAll( key_sequence, an_object );
        key_sequence->release();

        return temp;
    }

    int new_size = __STATIC_CAST(int, size()) - (stop - start);
    SequenceableCollection* result = __REINTERPRET_CAST(SequenceableCollection *, copyEmpty( new_size ));

    if ( start > 0 ) {
        Stream* it = readStream();
        for ( int i = 0; i < start - 1 && !it->atEnd(); ++ i ) {
            Object* each = it->next();

            result->add( each );
        }
        it->release();
    }

    result->add( an_object );

    if ( stop < __STATIC_CAST(int, size()) ) {
        Stream* it = readStream();
        int arrived = __STATIC_CAST(int, size());
        for ( int i = stop + 1; i < arrived && !it->atEnd(); ++ i ) {
            Object* each = it->next();

            result->add( each );
        }
        it->release();
    }

    return result;
}


SequenceableCollection* SequenceableCollection::copyReplaceAll( const SequenceableCollection* const& old_sub_collection,
                                                                SequenceableCollection* const& new_sub_collection ) const
{
    int num_old = countSubCollectionOccurrencesOf( old_sub_collection );
    size_t new_sub_size = new_sub_collection->size();
    size_t old_sub_size = old_sub_collection->size();
    int size_difference = __STATIC_CAST(int, new_sub_size) - __STATIC_CAST(int, old_sub_size);

    int self_size = __STATIC_CAST(int, size());
    SequenceableCollection* new_collection = __REINTERPRET_CAST(SequenceableCollection *, copyEmpty( self_size + (size_difference * num_old) ));
    int old_start = 0;

    while ( true ) {
        int index = indexOfSubCollection( old_sub_collection, old_start );
        if ( index == -1 ) {
            Stream* it = readStream();

            it->skip( old_start );
            while ( !it->atEnd() ) {
                Object* each = it->next();

                new_collection->add( each );
            }
            it->release();

            return new_collection;
        }

        int copy_size = index - old_start;
        {
            Stream* it = readStream();

            it->skip( old_start );
            for ( int i = old_start; !it->atEnd() && i < old_start + copy_size; ++ i ) {
                Object* each = it->next();

                new_collection->add( each );
            }
            it->release();
        }
        new_collection->addAll( new_sub_collection );

        old_start += copy_size + __STATIC_CAST(int, old_sub_size);
    }
}
SequenceableCollection* SequenceableCollection::copyReplaceAll(int start, int stop, SequenceableCollection* const& replacement_collection) const
{
    int self_size = __STATIC_CAST(int, size());

    if ( stop - start < -1 ) {
        ArgumentOutOfRangeError::signalOn( stop,
                                           start - 1,
                                           self_size );

        return NULL;
    }

    int rep_size = __STATIC_CAST(int, replacement_collection->size());
    int new_size = self_size + rep_size - ( stop - start + 1 );
    SequenceableCollection* result = __REINTERPRET_CAST(SequenceableCollection *, copyEmpty( new_size ));

    if ( start > 0 ) {
        Stream* it = readStream();
        for ( int i = 0; !it->atEnd() && i < start; ++ i ) {
            Object* each = it->next();

            result->add( each );
        }
        it->release();
    }

    result->addAll( replacement_collection );

    if ( stop < self_size ) {
        Stream* it = readStream();

        it->skip( stop + 1 );
        for ( int i = 0; !it->atEnd() && i < start; ++ i ) {
            Object* each = it->next();

            result->add( each );
        }
        it->release();
    }

    return result;
}


SequenceableCollection* SequenceableCollection::copyWithFirst(Object* const& an_object) const
{
    return copyReplaceFrom( 0, -1, an_object );
}


SequenceableCollection* SequenceableCollection::copyFrom(int start) const
{
    return __REINTERPRET_CAST(SequenceableCollection *, copyFrom( start, __STATIC_CAST(int, size()) ));
}
SequenceableCollection* SequenceableCollection::copyFrom(int start, int stop) const
{
    if ( stop < start ) {
        if ( stop == start - 1 )
            return __REINTERPRET_CAST(SequenceableCollection *, Collection::copyEmpty( 0 ));

        ArgumentOutOfRangeError::signalOn( stop,
                                           start - 1,
                                           __STATIC_CAST(int, size()) );

        return NULL;
    }

    int len = stop - start + 1;
    SequenceableCollection* sequence = __REINTERPRET_CAST(SequenceableCollection *, copyEmpty( len + 10 ));

    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* each = it->next();

        sequence->add( each );
    }
    it->release();

    return sequence;
}


Stream* SequenceableCollection::readStream() const
{
    return ReadStream::on( this );
}


Stream* SequenceableCollection::writeStream()
{
    return WriteStream::on( this );
}


Stream* SequenceableCollection::readWriteStream()
{
    return ReadWriteStream::on( this );
}


SequenceableCollection* SequenceableCollection::keys() const
{
    return Integer::valueOf( 0 )->to( Integer::valueOf( __STATIC_CAST(int, size()) ) );
}


int SequenceableCollection::findFirst(bool (*a_block)(const Object* const&, Object* const&)) const
{
    int found_index = -1;
    int arrived = __STATIC_CAST(int, size());
    Stream* it = readStream();

    for ( int i = 0; !it->atEnd() && i < arrived; ++ i ) {
        Object* each = it->next();

        if ( a_block( this, each ) ) {
            found_index = i;

            break;
        }
    }
    it->release();

    return found_index;
}


int SequenceableCollection::findLast(bool (*a_block)(const Object* const&, Object* const&)) const
{
    int found_index = -1;
    int arrived = __STATIC_CAST(int, size());
    Stream* it = readStream();

    for ( int i = 0; !it->atEnd() && i < arrived; ++ i ) {
        Object* each = it->next();

        if ( a_block( this, each ) )
            found_index = i;
    }
    it->release();

    return found_index;
}


SequenceableCollection* SequenceableCollection::reverse() const
{
    SequenceableCollection* result = __REINTERPRET_CAST(SequenceableCollection *, copyEmptyForCollect());

    for ( int i = __STATIC_CAST(int, size()); i >= 0; -- i ) {
        result->add( Object::at( i ) );
    }

    return result;
}


Collection* SequenceableCollection::sorted() const
{
    Collection* result = copyEmptyForCollect();

    result->addAll( __REINTERPRET_CAST(Collection *, asSortedCollection()) );

    return result;
}
Collection* SequenceableCollection::sorted(int (*a_block)(const Object* const&, const Object* const&)) const
{
    Collection* result = copyEmptyForCollect();

    result->addAll( __REINTERPRET_CAST(Collection *, asSortedCollection( a_block )) );

    return result;
}


void SequenceableCollection::sort()
{
    replaceFrom( 0,
                 __STATIC_CAST(int, size()),
                 __REINTERPRET_CAST(SequenceableCollection *, asSortedCollection()),
                 0 );
}
void SequenceableCollection::sort(int (*a_block)(const Object* const&, const Object* const&))
{
    replaceFrom( 0,
                 __STATIC_CAST(int, size()),
                 __REINTERPRET_CAST(SequenceableCollection *, asSortedCollection( a_block )),
                 0 );
}


bool SequenceableCollection::matchSubCollection(const SequenceableCollection* const& a_sub_collection, int an_index) const
{
    int our_index = an_index;
    int subcol_size = __STATIC_CAST(int, a_sub_collection->size());

    for ( int i = 1; i < subcol_size; ++ i ) {
        ++ our_index;

        if ( !Object::at( our_index )->equals( a_sub_collection->Object::at( i ) ) )
            return false;
    }
    return true;
}


int SequenceableCollection::countSubCollectionOccurrencesOf(const SequenceableCollection* const& a_subcollection) const
{
    int coll_index = 0;
    int count = 0;
    int subcoll_index;

    while ( ( subcoll_index = indexOfSubCollection( a_subcollection ) ) > 0 ) {
        ++ count;

        coll_index = subcoll_index + __STATIC_CAST(int, a_subcollection->size());
    }
    return count;
}


void SequenceableCollection::swap(int an_index, int another_index)
{
    Object* saved = Object::at( an_index );

    Object::put( an_index, Object::at( another_index ) );
    Object::put( another_index, saved );
}


// Object* SequenceableCollection::checkIndexableBounds(int index) const
// {
// }
// Object* SequenceableCollection::checkIndexableBounds(int index, Object* const (*a_block)(const Object* const&)) const
// {
// }


// void SequenceableCollection::checkIndexableBoundsPut(int index, Object* const& object)
// {
// }


// Local Variables:
//   coding: utf-8
// End:
