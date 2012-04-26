#include "config.h"

#ifdef HAVE_MEMORY_H
#   include <memory.h>
#endif  /* def HAVE_MEMORY_H */
#ifdef HAVE_STRING_H
#   include <string.h>
#endif  /* def HAVE_STRING_H */

#include "altair/altair_prefix.h"
#include "altair/Class.hxx"
#include "altair/String.hxx"
#include "altair/Stream.hxx"
//#include "altair/UnicodeString.hxx"

#include "altair/ByteArray.hxx"
USING_NAMESPACE_ALTAIR;


ByteArray::ByteArray(size_t size)
    : bytes_(NULL), tally_(size)
{
    if ( size ) {
        bytes_ = new ubyte[size];
        memset( bytes_, 0, tally_ );
    }
}
ByteArray::ByteArray(const ByteArray& other)
    : bytes_(NULL), tally_(other.tally_)
{
    if ( tally_ ) {
        bytes_ = new ubyte[tally_];
        memcpy( bytes_, other.bytes_, tally_ );
    }
}


ByteArray::~ByteArray()
{
    if ( tally_ ) {
        delete [] bytes_;
        tally_ = 0;
    }
}


String* const ByteArray::asString() const
{
    size_t self_size = size();
    String*  ret_string = new String( size );

    ret_string->replaceFrom( 0, size, this, 0 );

    return ret_string;
}


UnicodeString* const ByteArray::asUnicodeString() const
{
    shouldNotImplement();

    return NULL;
}


void ByteArray::storeLiteralOn(Stream* const& a_stream)
{
    Class* self_class = getClass();

    if ( !self_class->identityEquals( ByteArray::getClass() ) ) {
        self_class->release();
        _Super::storeLiteralOn( a_stream );

        return ;
    }
    self_class->release();

    a_stream->nextPut( '#' );
    a_stream->nextPut( '[' );

    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* elt = it->next();

        a_stream->print();
        a_stream->space();
    }
    a_stream->nextPut( ']' );
}


void ByteArray::storeOn(Stream* const& a_stream)
{
    Class* self_class = getClass();

    if ( !self_class->identityEquals( ByteArray::getClass() ) ) {
        self_class->release();
        _Super::storeOn( a_stream );

        return ;
    }
    self_class->release();

    storeLiteralOn( a_stream );

    if ( !isReadOnly() )
        a_stream->nextPutAll( "copy" );
}



Object* const ByteArray::at(int an_index, Object* const (*a_block)(const Object* const&)) const
{
    return checkIndexableBounds( an_index, a_block );
}


ubyte ByteArray::byteAt(int index) const {
    return checkIndexableBounds( index );
}


ubyte ByteArray::bytePut(int index, ubyte value) const
{
    return putCheckIndexableBounds( index, value );
}


int ByteArray::hash() const
{
    return 0;
}


Collection* const ByteArray::replaceFrom(int start, int stop, const String* const& a_string, int replace_start)
{
    return _Super::replaceFrom( start, stop, a_string, replace_start );
}


bool ByteArray::equals(const Collection* const& a_collection) const
{
    return false;
}


int ByteArray::indexOf(Object* const& an_element, int an_index) const
{
    return an_index < 0 || an_index > ( __STATIC_CAST(int, size()) + 1)
        ? checkIndexableBounds( an_index )
        : -1;
}
int ByteArray::indexOf(Object* const& an_element, int an_index, int (*a_exception_block)(const Object* const&)) const
{
    return an_index < 0 || an_index > ( __STATIC_CAST(int, size()) + 1)
        ? checkIndexableBounds( an_index )
        : a_exception_block();
}
