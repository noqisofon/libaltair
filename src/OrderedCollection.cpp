#include "config.h"

#include "altair/altair_prefix.h"
#include "altair/Iterator.hxx"
#include "altair/IndexOutOfRangeError.hxx"
#include "altair/NotFoundError.hxx"
#include "altair/EmptyCollectionError.hxx"

#include "altair/OrderedCollection.hxx"
USING_NAMESPACE_ALTAIR;


OrderedCollection::OrderedCollection()
{
}
OrderedCollection::OrderedCollection(int an_integer)
{
}


Object* OrderedCollection::first() const
{
    if ( last_index_ >= first_index_ )
        return basicAt( first_index_ );
    else
        IndexOutOfRangeError::signalOn( this, 0 );
    return NULL;
}


Object* OrderedCollection::last() const
{
    if ( last_index_ >= first_index_ )
        return basicAt( last_index_ );
    else
        IndexOutOfRangeError::signalOn( this, -1 );
    return NULL;
}


Object* OrderedCollection::at(int an_index) const
{
    int index = an_index + first_index_;

    if ( first_index_ <= index && index < last_index_ )
        return basicAt( index );
    else
        IndexOutOfRangeError::signalOn( this, an_index );
    return NULL;
}


void OrderedCollection::put(int an_index, Object* const& an_object)
{
    int index = an_index + first_index_;

    if ( first_index_ <= index && index < last_index_ )
        basicPut( index, an_object );
    else
        IndexOutOfRangeError::signalOn( this, an_index );
}


Collection* const& OrderedCollection::add(Object* const& new_object)
{
    if ( last_index_ == __STATIC_CAST(int, basicSize()) )
        growBy( growSize(), 0 );
    ++ last_index_;

    basicPut( last_index_, new_object );

    return this;
}


static int after_index_exception_block(const Object* const& self, const Object* const& old_object)
{
    NotFoundError::signalOn( old_object, "object" );

    return -1;
}


Collection* const& OrderedCollection::addAfter(Object* const& new_object, const Object* const& old_object)
{
    return addAfterIndex( new_object,
                          indexOf( old_object,
                                   after_index_exception_block ) );
}


Collection* const& OrderedCollection::addBefore(Object* const& new_object, const Object* const& old_object)
{
    return addBeforeIndex( new_object,
                           indexOf( old_object,
                                    after_index_exception_block ) );
}


Collection* const& OrderedCollection::addAfterIndex(Object* const& new_object, int an_index)
{
    if ( !ALTAIR_BETWEEN_AND(an_index, 0, size()) ) {
        IndexOutOfRangeError::signalOn( this, an_index );

        return this;
    }

    int index = an_index + first_index_;

    if ( last_index_ == __STATIC_CAST(int, basicSize()) )
        growBy( __STATIC_CAST(int, growSize()), 0 );

    for ( int i = last_index_; i > index; -- i ) {
        basicPut( i + 1, basicAt( i ) );
    }
    basicPut( index, new_object );

    return this;
}


Collection* const& OrderedCollection::addBeforeIndex(Object* const& new_object, int an_index)
{
    return addAfterIndex( new_object, an_index - 1 );
}


const Collection* OrderedCollection::addAll(const Collection* const& a_collection)
{
    makeRoomLastFor( a_collection->size() );

    int index = last_index_ + 1;

    last_index_ += __STATIC_CAST(int, a_collection->size());

    Stream* it = a_collection->readStream();
    while ( !it->atEnd() ) {
        Object* element = it->next();

        basicPut( index ++, element );
    }
    it->release();

    return a_collection;
}


const Collection* OrderedCollection::addAllAfter(const Collection* const& new_collection, const Object* const& old_object)
{
    return addAllAfterIndex( new_collection,
                             indexOf( old_object,
                                      after_index_exception_block ) );
}


const Collection* OrderedCollection::addAllAfterIndex(const Collection* const& new_collection, int an_index)
{
    if ( ALTAIR_BETWEEN_AND(an_index, 0, size()) ) {
        IndexOutOfRangeError::signalOn( this, an_index );

        return new_collection;
    }

    int index = an_index + first_index_;
    int new_size = __STATIC_CAST(int, new_collection->size());

    makeRoomLastFor( new_collection->size() );

    for ( int i = last_index_; i > index; -- i ) {
        basicPut( i + new_size, basicAt( i ) );
    }
    last_index_ += new_size;

    Stream* it = new_collection->readStream();
    for ( int i = 0; !it->atEnd(); ++ i ) {
        Object* each = it->next();

        basicPut( index + an_index, each );
    }
    it->release();

    return new_collection;
}


const Collection* OrderedCollection::addAllBefore(const Collection* const& new_collection, const Object* const& old_object)
{
    return addAllBeforeIndex( new_collection,
                              indexOf( old_object,
                                       after_index_exception_block ) );
}


const Collection* OrderedCollection::addAllBeforeIndex(const Collection* const& new_collection, int an_index)
{
    return addAllAfterIndex( new_collection, an_index - 1 );
}


const Collection* OrderedCollection::addAllFirst(const Collection* const& a_collection)
{
    makeRoomFirstFor( __STATIC_CAST(int, a_collection->size()) );

    int index = first_index_ = first_index_ - __STATIC_CAST(int, a_collection->size());

    Stream* it = a_collection->readStream();
    while ( !it->atEnd() ) {
        Object* element = it->next();

        basicPut( index ++, element );
    }
    it->release();

    return a_collection;
}


const Collection* OrderedCollection::addAllLast(const Collection* const& a_collection)
{
    makeRoomLastFor( __STATIC_CAST(int, a_collection->size()) );

    int index = last_index_ + 1;

    last_index_ = last_index_ + a_collection->size();

    Stream* it = a_collection->readStream();
    while ( !it->atEnd() ) {
        Object* element = it->next();

        basicPut( index ++, element );
    }
    it->release();

    return a_collection;
}


void OrderedCollection::addFirst(Object* const& new_object)
{
    if ( first_index_ <= 0 )
        growBy( growSize(), growSize() );
    -- first_index_;

    basicPut( first_index_, new_object );
}


void OrderedCollection::addLast(Object* const& new_object)
{
    if ( last_index_ == __STATIC_CAST(int, basicSize()) )
        growBy( growSize(), 0 );
    ++ last_index_;

    basicPut( last_index_, new_object );
}


Object* OrderedCollection::removeFirst()
{
    if ( last_index_ < first_index_ )  {
        EmptyCollectionError::signalOn( this );

        return NULL;
    }

    Object* answer = basicAt( first_index_ );
    basicPut( first_index_, NULL );

    if ( last_index_ == first_index_ )
        initIndices();
    else
        ++ first_index_;

    if ( size() < shrinkSize() )
        shrink();

    return answer;
}


Object* OrderedCollection::removeLast()
{
    if ( last_index_ < first_index_ )  {
        EmptyCollectionError::signalOn( this );

        return NULL;
    }

    Object* answer = basicAt( last_index_ );
    basicPut( last_index_, NULL );

    if ( last_index_ == first_index_ )
        initIndices();
    else
        ++ last_index_;

    if ( size() < shrinkSize() )
        shrink();

    return answer;
}


static int identity_remove_absent(const Object* const& self, const Object* const& old_object)
{
    NotFoundError::signalOn( old_object, "object" );

    return -1;
}


Object* OrderedCollection::identityRemove(const Object* const& old_object)
{
    return identityRemove( old_object, identity_remove_absent );
}
Object* OrderedCollection::identityRemove(const Object* const& old_object, int (*a_block)(const Object* const&, const Object* const&))
{
    return removeAtIndex( identityIndexOf( old_object, 0, a_block ) );
}


Object* OrderedCollection::remove(const Object* const& an_object, int (*a_block)(const Object* const&, const Object* const&))
{
    return removeAtIndex( indexOf( an_object, 0, a_block ) );
}


Object* OrderedCollection::removeAtIndex(int an_index)
{
    Object* answer = basicRemoveAtIndex( an_index );

    if ( size() < shrinkSize() )
        shrink();

    return answer;
}


Object* OrderedCollection::basicRemoveAtIndex(int an_index)
{
    if ( last_index_ < first_index_ ) {
        EmptyCollectionError::signalOn( this );

        return NULL;
    }
    if ( an_index < 0 || an_index < __STATIC_CAST(int, size()) ) {
        EmptyCollectionError::signalOn( this );

        return NULL;
    }

    Object* answer = basicAt( an_index + first_index_ - 1 );
    primReplaceFrom( an_index + first_index_,
                     last_index_ - 1,
                     this,
                     an_index + first_index_ );
    basicPut( last_index_, NULL );
    if ( last_index_ == first_index_ )
        initIndices();
    else
        -- last_index_;

    return answer;
}


void OrderedCollection::basicAddLast(Object* const& new_object)
{
    if ( last_index_ == __STATIC_CAST(int, basicSize()) )
        growBy( growSize(), 0 );
    ++ last_index_;

    basicPut( last_index_, new_object );
}


const Collection* OrderedCollection::basicAddAllLast(const Collection* const& a_collection)
{
    makeRoomLastFor( __STATIC_CAST(int, a_collection->size()) );

    int index = last_index_ + 1;

    last_index_ = last_index_ + a_collection->size();

    Stream* it = a_collection->readStream();
    while ( !it->atEnd() ) {
        Object* element = it->next();

        basicPut( index ++, element );
    }
    it->release();

    return a_collection;
}


Object* OrderedCollection::basicRemoveFirst()
{
    if ( last_index_ < first_index_ )  {
        EmptyCollectionError::signalOn( this );

        return NULL;
    }

    Object* answer = basicAt( first_index_ );
    basicPut( first_index_, NULL );

    if ( last_index_ == first_index_ )
        initIndices();
    else
        ++ first_index_;

    if ( size() < shrinkSize() )
        shrink();

    return answer;
}


Object* OrderedCollection::basicRemoveLast()
{
    if ( last_index_ < first_index_ )  {
        EmptyCollectionError::signalOn( this );

        return NULL;
    }

    Object* answer = basicAt( last_index_ );
    basicPut( last_index_, NULL );

    if ( last_index_ == first_index_ )
        initIndices();
    else
        ++ last_index_;

    if ( size() < shrinkSize() )
        shrink();

    return answer;
}


void OrderedCollection::initIndices()
{
    first_index_ = ALTAIR_MAX(basicSize() / 2, 1);
    last_index_ = first_index_ - 1;
}


void OrderedCollection::makeRoomFirstFor(int n)
{
    if ( first_index_ <= n )
        growBy( ALTAIR_MAX(n, growSize()), ALTAIR_MAX(n, growSize()) );
}


void OrderedCollection::makeRoomLastFor(int n)
{
    if ( last_index_ > n )
        growBy( ALTAIR_MAX(n, growSize()), 0 );
}


void OrderedCollection::shrink()
{
    int shrink = __STATIC_CAST(int, shrinkSize());
    int shift = ALTAIR_MIN(first_index_ - 1, shrink / 2);

    shrink = ALTAIR_MIN(shrink, basicSize() - (last_index_ - shift));

    growBy( ALTAIR_NEGATED(shrink), ALTAIR_NEGATED(shift) );
}


void OrderedCollection::grow()
{
    growBy( growSize(), first_index_ / 2 );
}


void OrderedCollection::growBy(int delta, int shift_count)
{
    OrderedCollection* new_ordered_collection = __REINTERPRET_CAST(OrderedCollection *,copyEmpty( basicSize() - delta ));

    new_ordered_collection->primReplaceFrom( first_index_ + shift_count,
                                             last_index_ + shift_count,
                                             this,
                                             first_index_ );
    new_ordered_collection->firstIndexAndLastIndex( first_index_ + shift_count,
                                                    last_index_ + shift_count );
    become( new_ordered_collection );
}


void OrderedCollection::primReplaceFrom(int start, int stop, const SequenceableCollection* const& byte_array, int replace_start)
{
    primitiveFailed();
}


// Local Variables:
//   coding: utf-8
// End:
