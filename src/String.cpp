//  
//  String.cpp
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
#include "altair/Encoding.hxx"
#include "altair/ByteArray.hxx"
#include "altair/Symbol.hxx"
#include "altair/Stream.hxx"

#include "altair/String.hxx"
USING_NAMESPACE_ALTAIR;


Encoding* String::encoding() const
{
    notYetImplemented();

    return NULL;
}


ByteArray* String::asByteArray() const
{
    int self_size = size();
    ByteArray* byte_array = new ByteArray( self_size );

    byte_array->replaceFrom( 0,                  // from:
                             self_size - 1,      // to:
                             this,               // withString:
                             0 );                // startingAt:

    return byte_array;
}


Symbol* String::asSymbol() const
{
    return Symbol::intern( this );
}


String* String::asString() const
{
    return __CONST_CAST(String *, this);
}


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
void String::displayOn(Stream* const& a_stream) const
{
    a_stream->nextPutAll( this );
}
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */
// Local Variables:
//   coding: utf-8
// End:
