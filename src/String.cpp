

Encoding* const String::encoding() const
{
    notYetImplemented();

    return nil;
}


ByteArray* const String::asByteArray()
{
    int self_bytesize = byteSize();
    ByteArray* byte_array = new ByteArray( self_bytesize );

    byte_array->replaceFrom( 0,                  // from:
                             self_bytesize - 1,  // to:
                             this,               // withString:
                             0 );                // startingAt

    return byte_array;
}


Symbol* const String::asSymbol() const
{
    return Symbol::intern( this );
}


void String::displayOn(Stream* const a_stream) const
{
    a_stream->nextPutAll( this );
}
// Local Variables:
//   coding: utf-8
// End:
