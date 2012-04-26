#include "config.h"

#include "altair/altair_prefix.h"
#include "altair/CompiledBlock.hxx"
#include "altair/Iterator.hxx"
#include "altair/Random.hxx"

#include "altair/SequenceableCollection.hxx"
USING_NAMESPACE_ALTAIR;


Object* const SequenceableCollection::at(int an_index, Object* const (*a_block)(const Object* const&)) const
{
    size_t self_size = size();

    if ( 0 <= an_index &&  an_index < (int)self_size )
        return a_block( this );

    return at( an_index );
}


Object* const SequenceableCollection::atRandom() const
{
    return at( Random::betweenAnd( 0, size() ) );
}


Collection* const SequenceableCollection::atAll(const Collection* const& key_collection) const
{
    Collection* result = copyEmptyForCollect( key_collection->size() );

    Iterator* it = key_collection->iterator();

    while ( it->atEnd() ) {
        Object* each = it->next();
        int key = 0;

        if ( each->isNumber() )
            key = ((Number *)each)->asInt32();

        result->add( at( key ) );
    }

    it->release();

    return result;
}


void SequenceableCollection::putAll(const Collection* const& a_collection, Object* const& an_object)
{
    Iterator* it = a_collection->iterator();

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

    atPut( 0, an_object ); if ( self_size == 1 ) return this;
    atPut( 1, an_object ); if ( self_size == 2 ) return this;
    atPut( 2, an_object ); if ( self_size == 3 ) return this;
    atPut( 3, an_object ); if ( self_size == 4 ) to = 4;

    while ( self_size > to ) {
        replaceFrom/*ToWithStartingAt*/( to,
                                         ALTAIR_MIN(to += to, self_size),
                                         this,
                                         0 );
    }
}


Object* const SequenceableCollection::after(const Object* const& old_object) const
{
    int i = indexOf( old_object );

    if ( i == 0 )
        NotFoundError::signalOn( old_object, "Object" );

    return at( i + 1 );
}


Object* const SequenceableCollection::before(const Object* const& old_object) const
{
    int i = indexOf( old_object );

    if ( i == 0 )
        NotFoundError::signalOn( old_object, "Object" );

    return at( i - 1 );
}


SequenceableCollection* const SequenceableCollection::allButFirst() const
{
    return (SequenceableCollection *)copyFrom( 1 );
}
SequenceableCollection* const SequenceableCollection::allButFirst(int n) const
{
    return (SequenceableCollection *)copyFrom( n );
}


SequenceableCollection* const SequenceableCollection::allButLast() const
{
    return (SequenceableCollection *)copyFrom( 0, size() - 1 );
}
SequenceableCollection* const SequenceableCollection::allButLast(int n) const
{
    return (SequenceableCollection *)copyFrom( 0, size() - (n - 1) );
}


Object* const SequenceableCollection::first() const
{
    return at( 0 );
}
SequenceableCollection* const SequenceableCollection::first(int n) const
{
    return (SequenceableCollection *)copyFrom( 0, n );
}


Object* const SequenceableCollection::second() const
{
    return at( 1 );
}


Object* const SequenceableCollection::third() const
{
    return at( 2 );
}


Object* const SequenceableCollection::fourth() const
{
    return at( 3 );
}


Object* const SequenceableCollection::last() const
{
    return at( size() - 1 );
}
SequenceableCollection* const SequenceableCollection::last(int n) const
{
    return (SequenceableCollection *)copyFrom( size() - n );
}


bool SequenceableCollection::includes(const Object* const& an_object) const
{
    int self_size = size();

    for ( int i = 0; i < self_size; ++ i ) {
        if ( a_object->equals( at( i ) ) )
            return true;
    }
    return false;
}


bool SequenceableCollection::identityIncludes(const Object* const& an_object) const
{
    int self_size = size();

    for ( int i = 0; i < self_size; ++ i ) {
        if ( a_object == at( i ) )
            return true;
    }
    return false;
}


static int null_exception_block(const Object* const& self)
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
int SequenceableCollection::indexOf(const Object* const& an_element, int an_index, int (*exception_block)(const Object* const) ) const
{
    size_t self_size = size();

    if ( an_index < 0 || self_size < an_index ) {
        if ( an_index == self_size + 1 )
            return exception_block();
        else
            checkIndexableBounds( an_index );
    }

    int arrived = (int)size();

    for ( int i = an_index; i < arrived; ++ i ) {
        if ( at( i )->equals( an_element ) )
            return i;
    }
    return exception_block( this );
}


int SequenceableCollection::indexOfLast(const Object* const& an_element, int (*exception_block)(const Object* const) ) const
{
    size_t self_size = size();

    for ( int i = (int)self_size; i >= 0; -- i ) {
        if ( at( i )->equals( an_element ) )
            return i;
    }
    return exception_block( this );
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
int SequenceableCollection::identityIndexOf(const Object* const& an_element, int an_index, int (*exception_block)(const Object* const) ) const
{
    size_t self_size = size();

    if ( an_index < 0 || self_size < an_index ) {
        if ( an_index == self_size + 1 )
            return exception_block();
        else
            checkIndexableBounds( an_index );
    }

    int arrived = (int)size();

    for ( int i = an_index; i < arrived; ++ i ) {
        if ( at( i ) == an_element )
            return i;
    }
    return exception_block( this );
}


int SequenceableCollection::identityIndexOfLast(const Object* const& an_element, int (*exception_block)(const Object* const)) const
{
    size_t self_size = size();

    for ( int i = (int)self_size; i >= 0; -- i ) {
        if ( at( i )->identityEquals( an_element ) )
            return i;
    }
    return exception_block( this );
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
                                                  int (*exception_block)(const Object* const) ) const
{
    
    size_t sub_size = a_sub_collection->size();
    if ( sub_size == 0 )
        return an_index;
    size_t self_size = size();

    if ( (an_index + sub_size - 1) <= self_size ) {
        int arrived = an_index - sub_size + 1;

        for ( int i = an_index; i < arrived; ++ i ) {
            if ( at( i )->equals( a_sub_collection->at( 0 ) ) ) {
                if ( matchSubCollection( a_sub_collection, i ) )
                    return i;
            }
        }
    }
    return exception_block( this );
}


bool SequenceableCollection::equals(const Collection* const& a_collection) const
{
    if ( !getClass()->equals( a_collection->getClass() ) )
        return false;
    if ( size() != a_collection->size() )
        return false;

    int len = (int)size();
    for ( int i = 0; i < len; ++ i ) {
        if ( !at( i )->equals( a_collection->at( i ) ) )
            return false;
    }
    return true;
}


int SequenceableCollection::hash() const
{
    int ret_hash = (int)size();
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
    Stream* it = other->readStream();
    for ( int i = 0; it->atEnd(); ++ i ) {
        Object* each = it->next();

        if ( !at( i )->equals( each ) ) {
            ret = false;

            break;
        }
    }
    it->release();

    return ret;
}


bool SequenceableCollection::endsWith(const SequenceableCollection* const& other) const
{
    int delpha  = size() - other->size();

    if ( !(delta >= 0) )
        return false;

    bool ret = true;
    Stream* it = other->readStream();
    for ( int i = 0; it->atEnd(); ++ i ) {
        Object* each = it->next();

        if ( !at( i + delta )->equals( each ) ) {
            ret = false;

            break;
        }
    }
    it->release();

    return ret;
}


static int gain_self_size_exception_block(const Object* const& self)
{
    return (int)self->size();
}


SequenceableCollection const* SequenceableCollection::copyAfter(const Object* const& an_object) const
{
    return copyFrom( indexOf( an_object,
                              gain_self_size_exception_block( this ) ) );
}


SequenceableCollection const* SequenceableCollection::copyAfterLast(const Object* const& an_object) const
{
    return copyFrom( indexOfLast( an_object,
                                  gain_self_size_exception_block( this ) ) );
}


void SequenceableCollection::replaceAll(const Object* const& an_object, Object* const& another_object)
{
    int self_size = (int)size();

    for ( int i = 0; i < self_size; ++ i ) {
        if ( at( i )->equals( an_object ) )
            put( i, an_object );
    }
}


void SequenceableCollection::replaceFrom(int start, int stop, const Collection* const& replacement_collection, int rep_start)
{
    int min_stop = start - 1;
    int max_stop = ALTAIR_MIN((int)size(), min_stop + (int)replacement_collection->size());

    if ( !(min_stop <= stop && stop <= max_stop) ) {
        ArgumentOutOfRangeError::signalOn( stop,
                                           min_stop,
                                           max_stop );
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
                                           (int)size() );
    }

    if ( int i = 0; i < stop_index; ++ i ) {
        put( i, replace_object );
    }
}
// Local Variables:
//   coding: utf-8
// End:
