#include "config.h"

#include "altair/altair_prefix.h"
#include "altair/Number.hxx"
#include "altair/Character.hxx"
#include "altair/Stream.hxx"
#include "altair/WriteStream.hxx"
#include "altair/String.hxx"
#include "altair/InvalidSizeError.hxx"
#include "altair/ArgumentOutOfRangeError.hxx"

#include "altair/ArrayedCollection.hxx"
USING_NAMESPACE_ALTAIR;


ArrayedCollection::ArrayedCollection()
    : tally_(32)
{
}
ArrayedCollection::ArrayedCollection(size_t size, Object* const& an_object)
    : tally_(size)
{
    //grow( size );
    //atAllPut( an_object );
}
ArrayedCollection::ArrayedCollection(const Collection& other)
    : tally_(other.size())
{
}


ArrayedCollection::~ArrayedCollection()
{
}


Collection* const& ArrayedCollection::add(Object* const& value)
{
    shouldNotImplement();

    return this;
}


Collection* ArrayedCollection::addAll(Collection* const& key_collection)
{
    int i = 0;
    Collection* result = copyEmptyForCollect( __STATIC_CAST(int, key_collection->size()) );

    Stream* it = key_collection->readStream();
    while ( it->atEnd() ) {
        Object* key = it->next();

        if ( key->isNumber() )
            result->put( i ++, Object::at( __REINTERPRET_CAST(Number *, key)->asInt32() ) );
    }
    it->release();

    return result;
}


SequenceableCollection* ArrayedCollection::copyFrom(int start, int stop) const
{
    if ( stop < start ) {
        if ( stop == start - 1 )
            return __REINTERPRET_CAST(SequenceableCollection *, _Super::copyEmpty( 0 ));

        ArgumentOutOfRangeError::signalOn( stop,
                                           start - 1,
                                           __STATIC_CAST(int, size()) );

        return NULL;
    }
    
    int len = stop - start;
    SequenceableCollection* result = __REINTERPRET_CAST(SequenceableCollection *, _Super::copyEmpty( len ));

    result->replaceFrom( 0, len, this, start );

    return result;
}


Collection* ArrayedCollection::copyWithout(const Object* const old_element) const
{
    SequenceableCollection* new_collection;
    int num_occurrences = 0;

    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* element = it->next();

        if ( element->equals( old_element ) )
            ++ num_occurrences;
    }
    it->release();

    new_collection = __REINTERPRET_CAST(SequenceableCollection *, _Super::copyEmpty( __STATIC_CAST(int, size()) - num_occurrences ));

    int i = 0;
    it = readStream();
    while ( it->atEnd() ) {
        Object* element = it->next();

        if ( !element->equals( old_element ) )
            new_collection->put( i ++, element );
    }
    return new_collection;
}


Collection* ArrayedCollection::copyWith(Object* const& an_element) const
{
    SequenceableCollection* new_collection = __REINTERPRET_CAST(SequenceableCollection *, _Super::copyEmpty( size() + 1 ));
}


Collection* ArrayedCollection::select(bool (*a_block)(const Object* const&)) const
{
    Stream* write_stream = WriteStream::on( _Super::copyEmpty() );
    Collection* new_collection;

    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* element = it->next();

        if ( a_block( element ) )
            write_stream->nextPut( element );
    }
    it->release();

    new_collection = write_stream->contents();
    write_stream->release();

    return new_collection;
}


Collection* ArrayedCollection::reject(bool (*a_block)(const Object* const&)) const
{
    Stream* write_stream = WriteStream::on( copyEmpty() );
    Collection* new_collection;

    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* element = it->next();

        if ( !a_block( element ) )
            write_stream->nextPut( element );
    }
    it->release();

    new_collection = write_stream->contents();
    write_stream->release();

    return new_collection;
}


Collection* ArrayedCollection::collect(Object* (*a_block)(const Object* const&)) const
{
    SequenceableCollection* new_collection = __REINTERPRET_CAST(SequenceableCollection *, copyEmptyForCollect());

    int arrived = __STATIC_CAST(int, size());
    for ( int i = 0; i < arrived; ++ i ) {
        new_collection->put( i, a_block( Object::at( i ) ) );
    }

    return __REINTERPRET_CAST(Collection *, new_collection);
}


Collection* ArrayedCollection::withCollect( const SequenceableCollection* const& a_sequence,
                                            Object* (*a_block)(const Object* const&, const Object* const&)) const
{
    if ( size() != a_sequence->size() ) {
        InvalidSizeError::signalOn( a_sequence );

        return NULL;
    }

    SequenceableCollection* new_collection = __REINTERPRET_CAST(SequenceableCollection *, copyEmptyForCollect());

    int arrived = __STATIC_CAST(int, size());
    for ( int i = 0; i < arrived; ++ i ) {
        new_collection->put( i,
                             a_block( Object::at( i ),
                                      a_sequence->Object::at( i ) ) );
    }

    return new_collection;
}


Collection* ArrayedCollection::copyReplaceFrom(int start, int stop, Object* const& an_object) const
{
    if ( ( stop - start ) < 0 ) {
        ArgumentOutOfRangeError::signalOn( stop,
                                           start - 1,
                                           __STATIC_CAST(int, size()) );

        return NULL;
    }

    int end = stop >= start ? stop : start;
    int new_size = end + __STATIC_CAST(int, size()) - stop;

    SequenceableCollection* new_collection = __REINTERPRET_CAST(SequenceableCollection *, _Super::copyEmpty( new_size ));

    new_collection->replaceFrom( 0, start - 1, this, 0 );
    new_collection->replaceFrom( start, end, an_object );
    new_collection->replaceFrom( end + 1, new_size, this, stop );

    return new_collection;
}
Collection* ArrayedCollection::copyReplaceFrom(int start, int stop, Collection* const& replacement_collection) const
{
    if ( ( stop - start ) < 0 ) {
        ArgumentOutOfRangeError::signalOn( stop,
                                           start - 1,
                                           __STATIC_CAST(int, size()) );

        return NULL;
    }

    int rep_size = __STATIC_CAST(int, replacement_collection->size());
    int new_size = __STATIC_CAST(int, size()) + rep_size - (stop - start);

    SequenceableCollection* new_collection = __REINTERPRET_CAST(SequenceableCollection *, _Super::copyEmpty( new_size ));

    new_collection->replaceFrom( 0,
                                 start,
                                 this,
                                 0 );
    new_collection->replaceFrom( start,
                                 start + rep_size,
                                 replacement_collection );
    new_collection->replaceFrom( start + rep_size + 1,
                                 new_size,
                                 this,
                                 0 );

    return new_collection;
}


Collection* ArrayedCollection::copyReplaceAll(const SequenceableCollection* const& old_subcollection, const SequenceableCollection* const& new_subcollection) const
{
    int num_old = _Super::countSubCollectionOccurrencesOf( old_subcollection );

    size_t new_subsize = new_subcollection->size();
    size_t old_subsize = old_subcollection->size();

    int size_diffreence = new_subsize - old_subsize;

    SequenceableCollection* new_collection = __REINTERPRET_CAST(SequenceableCollection *, _Super::copyEmpty( size() + ( size_diffreence * num_old ) ));

    int old_start = 0,
        new_start = 0 ;

    while ( 1 ) {
        int index = _Super::indexOfSubCollection( old_subcollection, old_start );

        if ( index == -1 ) {
            new_collection->replaceFrom( new_start,
                                         __STATIC_CAST(int, new_collection->size()),
                                         this,
                                         old_start );

            break;
        }

        int copy_size = index - old_start;
        new_collection->replaceFrom( new_start,
                                     new_start + copy_size - 1,
                                     this,
                                     old_start );
        new_start += copy_size;
        new_collection->replaceFrom( new_start,
                                     new_start + new_subsize - 1,
                                     new_subcollection,
                                     0 );

        old_start = old_start + copy_size + old_subsize;
        new_start += new_subsize;
    }
    return new_collection;
}


Collection* ArrayedCollection::reverse() const
{
    SequenceableCollection* result = __REINTERPRET_CAST(SequenceableCollection *, copyEmpty());
    int complement = __STATIC_CAST(int, size()) + 1;

    int arrived = __STATIC_CAST(int, size());
    for ( int i = 0; i < arrived; ++ i ) {
        result->Object::put( i, Object::at( complement - i ) );
    }
    return result;
}


Collection* ArrayedCollection::sorted() const
{
    SequenceableCollection* new_collection = __REINTERPRET_CAST(SequenceableCollection *, copyEmpty());

    new_collection->replaceFrom( 0,
                                 __STATIC_CAST(int, size()),
                                 __REINTERPRET_CAST(Collection *, asSortedCollection()),
                                 0 );

    return __REINTERPRET_CAST(Collection *, new_collection);
}
Collection* ArrayedCollection::sorted(int (*a_block)(const Object* const&, const Object* const&)) const
{
    SequenceableCollection* new_collection = __REINTERPRET_CAST(SequenceableCollection *, copyEmpty());

    new_collection->replaceFrom( 0,
                                 __STATIC_CAST(int, size()),
                                 __REINTERPRET_CAST(Collection *, asSortedCollection( a_block )),
                                 0 );

    return __REINTERPRET_CAST(Collection *, new_collection);
}


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
void ArrayedCollection::storeOn(Stream* const& a_stream) const
{
    a_stream->nextPutAll( "((" );
    a_stream->nextPutAll( getClass()->storeString() );
    a_stream->nextPutAll( " basicNew: " );

    Integer::valueOf( basicSize() )->printOn( a_stream );

    a_stream->nextPut( ')' );

    int index = 0;
    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* element = it->next();

        a_stream->nextPutAll( " at: " );
        Integer::valueOf( i )->printOn( a_stream );
        a_stream->nextPutAll( " put: " );
        element->storeOn( a_stream );
        a_stream->nextPut( '$' );

        ++ index;
    }
    it->release();

    if ( index > 0 )
        a_stream->nextPutAll( " yourself" );

    a_stream->nextPut( ')' );
}
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


Stream* ArrayedCollection::writeStream()
{
    return WriteStream::on( this );
}


Collection* ArrayedCollection::copyEmpty() const
{
    return _Super::copyEmpty( size() );
}


Collection* ArrayedCollection::copyGrowTo(int new_size) const
{
    SequenceableCollection* new_collection = __REINTERPRET_CAST(SequenceableCollection *,_Super::copyEmpty( new_size ));

    new_collection->replaceFrom( 0,
                                 __STATIC_CAST(int, size()),
                                 this,
                                 0 );

    return new_collection;
}



void ArrayedCollection::grow()
{
    growBy( growSize() );
}


ArrayedCollection* ArrayedCollection::growBy(int delta)
{
    return __REINTERPRET_CAST(ArrayedCollection* const, become( copyGrowTo( __STATIC_CAST(int, basicSize()) + delta ) ));
}


ArrayedCollection* ArrayedCollection::growTo(int new_size)
{
    return __REINTERPRET_CAST(ArrayedCollection* const, become( copyGrowTo( new_size ) ));
}
// Local Variables:
//   coding: utf-8
// End:
