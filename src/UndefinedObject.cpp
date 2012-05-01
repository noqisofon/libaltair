//  
//  UndefinedObject.cpp
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

#include "altair/UndefinedObject.hxx"
USING_NAMESPACE_ALTAIR;


static UndefinedObject UndefinedObject::NIL;


Object* UndefinedObject::getInstance()
{
    return &NIL;
}


Object* UndefinedObject::copy() const
{
    return __CONST_CAST(const UndefinedObject *, this);
}


Object* UndefinedObject::shallowCopy() const
{
    return __CONST_CAST(const UndefinedObject *, this);
}


Object* UndefinedObject::deepCopy() const
{
    return __CONST_CAST(const UndefinedObject *, this);
}


void UndefinedObject::printOn(Stream* const& a_stream) const
{
    a_stream->nextPutAll( "nil" );
}


void UndefinedObject::basicPrintOn(Stream* const& a_stream) const
{
    a_stream->nextPutAll( "nil" );
}


#if defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE    
void UndefinedObject::storeLiteralOn(Stream* const& a_stream) const
{
    storeOn( a_stream );
}


void UndefinedObject::storeOn(Stream* const& a_stream) const
{
    printOn( a_stream );
}
#endif  /* defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE */


// Local Variables:
//   coding: utf-8
// End:
