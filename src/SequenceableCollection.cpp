#include "config.h"

#include "altair/altair_prefix.h"
#include "altair/CompiledBlock.hxx"
#include "altair/Iterator.hxx"
#include "altair/Random.hxx"

#include "altair/SequenceableCollection.hxx"
USING_NAMESPACE_ALTAIR;


Object* const SequenceableCollection::at(int an_index, AbsentBlock& a_block) const
{
    size_t self_size = size();

    if ( 0 <= an_index &&  an_index < (int)self_size )
        return a_block();

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

    for ( ; it->finished(); it->next() ) {
        Object* each = it->current();
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

    for ( ; it->finished(); it->next() ) {
        Object* each = it->current();
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


static int null_exception_block(void)
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
int SequenceableCollection::indexOf(const Object* const& an_element, int an_index, ExceptionBlock& exception_block) const
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
    return exception_block();
}


int SequenceableCollection::indexOfLast(const Object* const& an_element, ExceptionBlock& exception_block) const
{
    size_t self_size = size();

    for ( int i = (int)self_size; i >= 0; -- i ) {
        if ( at( i )->equals( an_element ) )
            return i;
    }
    return exception_block();
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
int SequenceableCollection::identityIndexOf(const Object* const& an_element, int an_index, ExceptionBlock& exception_block) const
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
    return exception_block();
}


int SequenceableCollection::identityIndexOfLast(const Object* const& an_element, ExceptionBlock& exception_block) const
{
    size_t self_size = size();

    for ( int i = (int)self_size; i >= 0; -- i ) {
        if ( at( i )->identityEquals( an_element ) )
            return i;
    }
    return exception_block();
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
                                                  ExceptionBlock& exception_block ) const
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
    return exception_block();
}


bool SequenceableCollection::equals(const Collection* const& a_collection) const
{
    if ( !getClass()->equals( a_collection->getClass() ) )
        return false;
    if ( size() != a_collection->size() )
        return false;

    size_t len = size();
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

    Iterator* it = iterator();

    for ( ; it->finished(); it->next() ) {
        Object* element = it->current();

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
    Iterator* it = other->iterator();
    for ( int i = 0; it->finished(); it->next(), ++ i ) {
        Object* each = it->current();

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
    Iterator* it = other->iterator();
    for ( int i = 0; it->finished(); it->next(), ++ i ) {
        Object* each = it->current();

        if ( !at( i + delta )->equals( each ) ) {
            ret = false;

            break;
        }
    }
    it->release();

    return ret;
}


void SequenceableCollection::replaceAll(const Object* const& an_object, Object* const& another_object)
{
    int self_size = (int)size();

    for ( int i = 0; i < self_size; ++ i ) {
        if ( at( i )->equals( an_object ) )
            put( i, an_object );
    }
}


void SequenceableCollection::replaceFrom(int start, int stop, Collection* const& replacement_collection, int rep_start)
{
}
