//  
//  Iteratable.cpp
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
#include "altair/Stream.hxx"

#include "altair/Iteratable.hxx"
USING_NAMESPACE_ALTAIR;


Object* Iteratable::inject(Object* const& this_value, Object* (*binary_block)(Object* const&, Object* const&))
{
    Object* result = this_value;

    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* element = it->next();

        result = binary_block( result, element );
    }
    it->release();

    return result;
}


Stream* Iteratable::readStream() const
{
    subclassResponsibility();

    return NULL;
}
// Local Variables:
//   coding: utf-8
// End:
