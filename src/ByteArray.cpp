#include "config.h"

#ifdef HAVE_MEMORY_H
#   include <memory.h>
#endif  /* def HAVE_MEMORY_H */
#ifdef HAVE_STRING_H
#   include <string.h>
#endif  /* def HAVE_STRING_H */

#include "altair/altair_prefix.h"
#include "altair/Class.hxx"
#include "altair/Number.hxx"
#include "altair/Integer.hxx"
#include "altair/String.hxx"
#include "altair/Stream.hxx"
//#include "altair/UnicodeString.hxx"
#include "altair/NotIndexableError.hxx"
#include "altair/IndexOutOfRangeError.hxx"

#include "altair/ByteArray.hxx"
USING_NAMESPACE_ALTAIR;


ByteArray::ByteArray(size_t size)
    : _Super(size), bytes_(NULL)
{
    if ( size ) {
        bytes_ = new ubyte[size];
        memset( bytes_, 0, tally_ );
    }
}
ByteArray::ByteArray(const ByteArray& other)
    : _Super(other), bytes_(NULL)
{
    if ( size() ) {
        bytes_ = new ubyte[size()];
        memcpy( bytes_, other.bytes_, size() );
    }
}


ByteArray::~ByteArray()
{
    release();
}


String* ByteArray::asString() const
{
    size_t self_size = size();
    String*  ret_string = new String( self_size );

    ret_string->replaceFrom( 0, self_size, this, 0 );

    return ret_string;
}


UnicodeString* ByteArray::asUnicodeString() const
{
    shouldNotImplement();

    return NULL;
}


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
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
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */



Object* ByteArray::at(int an_index, Object* (*a_block)(const Object* const&)) const
{
    return checkIndexableBounds( an_index, a_block );
}


ubyte ByteArray::byteAt(int index) const {
    return checkIndexableByteBounds( index );
}


void ByteArray::bytePut(int index, ubyte value)
{
    checkIndexableByteBoundsPut( index, value );
}


int ByteArray::hash() const
{
    return 0;
}


void ByteArray::replaceFrom(int start, int stop, const String* const& a_string, int replace_start)
{
    _Super::replaceFrom( start, stop, a_string, replace_start );
}


bool ByteArray::equals(const Collection* const&/* a_collection */) const
{
    return false;
}


void ByteArray::release()
{
    if ( size() ) {
        delete [] bytes_;
    }
}


static int null_exception_block(const Object* const&/* self */)
{
    return -1;
}


int ByteArray::indexOf(Object* const& an_element, int an_index) const
{
    // return an_index < 0 || an_index > ( __STATIC_CAST(int, size()) + 1)
    //     ? checkIndexableBounds( an_index )
    //     : -1;
    return indexOf( an_element,
                    an_index,
                    null_exception_block );
}
int ByteArray::indexOf(Object* const& an_element, int an_index, int (*a_exception_block)(const Object* const&)) const
{
    // return an_index < 0 || an_index > ( __STATIC_CAST(int, size()) + 1)
    //     ? checkIndexableBounds( an_index )
    //     : a_exception_block();
    int self_size = __STATIC_CAST(int, size());

    if ( an_index < 0 || self_size < an_index ) {
        if ( an_index == self_size + 1 )
            return a_exception_block( this );
        // else
        //     checkIndexableBounds( an_index );
    }

    int arrived = __STATIC_CAST(int, size());
    for ( int i = an_index; i < arrived; ++ i ) {
        if ( Object::at( i )->equals( an_element ) )
            return i;
    }
    return a_exception_block( this );
}


Object* ByteArray::checkIndexableBounds(int index) const
{
    Class* self_class = getClass();

    if ( self_class->isFixed() ) {
        self_class->release();
        NotIndexableError::signalOn( this );

        return NULL;
    }

    self_class->release();

    if ( index < 0 ) {
        IndexOutOfRangeError::signalOn( this, index );

        return NULL;
    }
    if ( index > __STATIC_CAST(int, basicSize()) ) {
        IndexOutOfRangeError::signalOn( this, index );

        return NULL;
    }
    return Integer::valueOf( bytes_[index] );
}
Object* ByteArray::checkIndexableBounds(int index, Object* (*a_block)(const Object* const&)) const
{
    Class* self_class = getClass();

    if ( self_class->isFixed() ) {
        self_class->release();
        NotIndexableError::signalOn( this );

        return NULL;
    }
    self_class->release();

    if ( index < 0 )
        return a_block( this );
    if ( index > __STATIC_CAST(int, basicSize()) )
        return a_block( this );

    return Integer::valueOf( bytes_[index] );
}


ubyte ByteArray::checkIndexableByteBounds(int index)  const
{
    if ( index < 0 ) {
        IndexOutOfRangeError::signalOn( this, index );

        return 0;
    }
    if ( index > __STATIC_CAST(int, basicSize()) ) {
        IndexOutOfRangeError::signalOn( this, index );

        return 0;
    }

    return bytes_[index];
}
ubyte ByteArray::checkIndexableByteBounds(int index, ubyte (*a_block)(const Object* const&)) const
{
    if ( index < 0 )
        return a_block( this );
    if ( index > __STATIC_CAST(int, basicSize()) )
        return a_block( this );

    return bytes_[index];
}


void ByteArray::checkIndexableByteBoundsPut(int index, ubyte value)
{
    if ( index < 0 ) {
        IndexOutOfRangeError::signalOn( this, index );

        return ;
    }
    if ( index > __STATIC_CAST(int, basicSize()) ) {
        IndexOutOfRangeError::signalOn( this, index );

        return ;
    }

    bytes_[index] = value;
}
// Local Variables:
//   coding: utf-8
// End:
