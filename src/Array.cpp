#include "config.h"

#include "altair/altair_prefix.h"
#include "altair/Character.hxx"
#include "altair/Stream.hxx"
#include "altair/String.hxx"

#include "altair/Array.hxx"
USING_NAMESPACE_ALTAIR;


Array* Array::with(Object* const& an_object)
{
    Array* ret = new Array( 1 );

    ret->put( 0, an_object );

    return ret;
}
Array* Array::with(Object* const& first_object, Object* const& second_object)
{
    Array* ret = new Array( 2 );

    ret->put( 0, first_object );
    ret->put( 1, second_object );

    return ret;

}
Array* Array::with(Object* const& first_object, Object* const& second_object, Object* const& third_object)
{
    Array* ret = new Array( 3 );

    ret->put( 0, first_object );
    ret->put( 1, second_object );
    ret->put( 2, third_object );

    return ret;
}
Array* Array::with( Object* const& first_object,
                    Object* const& second_object,
                    Object* const& third_object,
                    Object* const& fourth_object)
{
    Array* ret = new Array( 4 );

    ret->put( 0, first_object );
    ret->put( 1, second_object );
    ret->put( 2, third_object );
    ret->put( 3, fourth_object );

    return ret;
}
Array* Array::with( Object* const& first_object,
                    Object* const& second_object,
                    Object* const& third_object,
                    Object* const& fourth_object,
                    Object* const& fifth_object)
{
    Array* ret = new Array( 5 );

    ret->put( 0, first_object );
    ret->put( 1, second_object );
    ret->put( 2, third_object );
    ret->put( 3, fourth_object );
    ret->put( 4, fifth_object );

    return ret;
}


Array* Array::withAll(Collection* const& a_collection)
{
    Array* ret = new Array( a_collection->size() );

    int index = 0;
    Stream* it = a_collection->readStream();
    while ( it->atEnd() ) {
        Object* each = it->next();

        ret->put( index ++, each );
    }
    it->release();

    return ret;
}


Array::Array()
    : _Super(), content_(NULL)
{
}
Array::Array(size_t size, Object* const& an_object)
    : _Super(size, an_object), content_(NULL)
{
    if ( tally_ ) {
        content_ = new Object*[tally_];
        Object** sentinel = content_ + tally_;

        for ( Object** it = content_; it != sentinel; ++ it ) {
            *it = an_object;

            // if ( !*it )
            //     *it->retain();
        }
    }
}
Array::Array(const Array& other)
    : _Super(other.tally_), content_(NULL)
{
    if ( tally_ ) {
        content_ = new Object*[tally_];
        Object** sentinel = content_ + tally_;

        Object** other_it = other.content_;
        Object** other_sentinel = other.content_ + other.tally_;

        for ( Object** it = content_; it != sentinel; ++ it, ++ other_it ) {
            if ( other_it == other_sentinel )
                break;

            *it = *other_it;
            //*it->retain();
        }
    }
}
Array::Array(const Collection& other)
    : _Super(other), content_(NULL)
{
    if ( tally_ ) {
        content_ = new Object*[tally_];
        Object** sentinel = content_ + tally_;

        Stream* other_it = other.readStream();
        for ( Object** it = content_; it != sentinel; ++ it ) {
            if ( other_it->atEnd() )
                break;

            *it = other_it->next();
            //*it->retain();
        }
        other_it->release();
    }
}


Array::~Array()
{
    release();
}


Object* Array::at(int an_index) const
{
    return checkIndexableBounds( an_index );
}
Object* Array::at(int an_index, Object* (*a_block)(const Object* const&)) const
{
    return checkIndexableBounds( an_index, a_block );
}


void Array::replaceFrom(int start, int stop, ByteArray* const& byte_array, int replace_start)
{
    SequenceableCollection::replaceFrom( start,
                                         stop,
                                         __REINTERPRET_CAST(SequenceableCollection *, byte_array),
                                         replace_start );
}


void Array::printOn(Stream* const& a_stream) const
{
    a_stream->nextPut( '(' );

    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* elt = it->next();

        elt->printOn( a_stream );
        a_stream->space();
    }
    it->release();

    a_stream->nextPut( ')' );
}


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
void Array::storeLiteralOn(Stream* const& a_stream) const
{
    if ( !getClass()->identityEquals( Array::getClass() ) )
        return _Super::storeLiteralOn( a_stream );

    a_stream->nextPut( '#' );
    a_stream->nextPut( '(' );

    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* elt = it->next();

        elt->storeLiteralOn( a_stream );
        a_stream->space();
    }
    it->release();

    a_stream->nextPut( ')' );
}


void Array::storeOn(Stream* const& a_stream) const
{
    if ( !getClass()->identityEquals( Array::getClass() ) )
        return _Super::storeOn( a_stream );

    storeLiteralOn( a_stream );

    if ( !isReadOnly() )
        a_stream->nextPutAll( " copy" );
}
#endif  /*  defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


Object* Array::multiBecome(Array* const& an_array)
{
    int index = 0;

    Object** const sentinel = content_ + tally_;

    for ( Object** begin = content_; begin != sentinel; ++ begin, ++ index ) {
        Object* elt = *begin;

        elt->become( an_array->at( index ) );
    }
    return this;
}
// Local Variables:
//   coding: utf-8
// End:
