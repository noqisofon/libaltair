#include "config.h"

#include "altair/altair_prefix.h"
#include "altair/Encoding.hxx"
#include "altair/ByteArray.hxx"
#include "altair/Symbol.hxx"
#include "altair/Stream.hxx"

#include "altair/String.hxx"
USING_NAMESPACE_ALTAIR;


Encoding* String::encoding() const
{
    notYetImplemented();

    return nil;
}


ByteArray* String::asByteArray()
{
    int self_bytesize = byteSize();
    ByteArray* byte_array = new ByteArray( self_bytesize );

    byte_array->replaceFrom( 0,                  // from:
                             self_bytesize - 1,  // to:
                             this,               // withString:
                             0 );                // startingAt:

    return byte_array;
}


Symbol* String::asSymbol() const
{
    return Symbol::intern( this );
}


void String::displayOn(Stream* const& a_stream) const
{
    a_stream->nextPutAll( this );
}
// Local Variables:
//   coding: utf-8
// End:
