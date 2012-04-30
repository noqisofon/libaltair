//  
//  Set.cpp
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
#include "altair/Class.hxx"
#include "altair/Array.hxx"

#include "altair/Set.hxx"
USING_NAMESPACE_ALTAIR;


Set::Set()
    : _Super(32), content_(new Array(32))
{
}
Set::Set(size_t size, Object* const& an_object)
    : _Super(size), content_(new Array(size, an_object))
{
}
Set::Set(const Set& other)
    : _Super(other.primSize()), content_(__REINTERPRET_CAST(Array *, other.copyEmpty()))
{
}


Object* Set::at(const Object* const& key) const
{
    int index = findIndex( key );

    return primAt( index );
}


Object* Set::put(const Object* const& key, Object* const& value)
{
    int index = findIndex( key );

    Object* ret = primAt( index );
    primPut( index, value );

    return ret;
}


int Set::hashFor(const Object* const& an_object) const
{
    return an_object->hash();
}


int Set::findIndex(const Object* const& an_object) const
{
    int size = __STATIC_CAST(int, primSize());
    int index = (ALTAIR_SCRAMBLE(an_object->hash()) & size - 1) + 1;

    while ( true ) {
        Object* element = primAt( index );

        if ( ALTAIR_ISNIL(element) || element->equals( an_object ) )
            break;
        if ( index == size )
            index = 0;
        else
            ++ index;
    }
    return index;
}


size_t Set::primSize() const
{
    return content_->size();
}


// Local Variables:
//   coding: utf-8
// End:
