//  
//  Dictionary.cpp
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
#include "altair/Association.hxx"
#include "altair/Number.hxx"
#include "altair/Integer.hxx"
#include "altair/Character.hxx"
#include "altair/Stream.hxx"
#include "altair/String.hxx"
#include "altair/SortedCollection.hxx"
#include "altair/HashedCollection.hxx"
#include "altair/InvalidArgumentError.hxx"
#include "altair/NotFoundError.hxx"

#include "altair/Dictionary.hxx"
USING_NAMESPACE_ALTAIR;


Dictionary::Dictionary()
    : _Super(24)
{
}
Dictionary::Dictionary(size_t size)
    : _Super(size)
{
}


static Object* at_if_absent(const Object* const& self, const Object* const& key)
{
    NotFoundError::signalOn( key, "key" );

    return NULL;
}


Object* Dictionary::at(const Object* const& key) const
{
    return at( key, at_if_absent );
}
Object* Dictionary::at(const Object* const& key, Object* (*a_block)(const Object* const&, const Object* const&)) const
{
    int index = findIndexOrNil( key );

    if ( index == -1 )
        return a_block( this, key );
    else
        return __REINTERPRET_CAST(Association *, _Super::primAt( index ))->value();
}



static Object* at_if_absent_put(const Object* const& self, const Object* const& key)
{
    return NULL;
}


Object* Dictionary::atIfAbsentPut(const Object* const& key, Object* (*a_block)(const Object* const&, const Object* const&))
{
    Object* ret = at( key, at_if_absent_put );

    if ( ALTAIR_ISNIL(ret) ) {
        ret = a_block( this, key );
        put( key, ret );
    }

    return ret;
}


Object* Dictionary::atIfPresent(const Object* const& key, Object* (*a_block)(const Object* const&, const Object* const&)) const
{
    int index = findIndexOrNil( key );

    if ( index == -1 )
        return NULL;
    else
        return a_block( this, __REINTERPRET_CAST(Association *, primAt( index ))->value() );
}


static Object* association_at_if_absent(const Object* const&, const Object* const& key)
{
    NotFoundError::signalOn( key, "key" );

    return NULL;
}


Object* Dictionary::associationAt(const Object* const& key) const
{
    return associationAt( key, association_at_if_absent );
}
Object* Dictionary::associationAt(const Object* const& key, Object* (*a_block)(const Object* const&, const Object* const&)) const
{
    int index = findIndexOrNil( key );

    if ( index == -1 )
        return a_block( this, key );
    else
        return primAt( index );
}


Object* Dictionary::put(const Object* const& key, Object* const& value)
{
    int index = findIndex( key );
    Association* assoc = __REINTERPRET_CAST(Association *, primAt( index ));

    if ( ALTAIR_ISNIL(assoc) ) {
        if ( incrementTally() )
            index = findIndex( key );

        primPut( index, new Association( key, value ) );
    } else
        assoc->value( value );

    return value;
}


// Local Variables:
//   coding: utf-8
// End:
