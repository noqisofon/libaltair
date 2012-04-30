//  
//  SortedCollection.hxx
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
#ifndef altair_SortedCollection_hxx
#define altair_SortedCollection_hxx

#include "altair/OrderedCollection.hxx"


BEGIN_NAMESPACE_ALTAIR


/*!
 *
 */
class SortedCollection : public OrderedCollection
{
 public:
    static SortedCollection* withSortBlock(int (*a_sort_block)(const Object* const&, const Object* const&));

 public:
    SortedCollection(size_t size, Object* const& an_object = NULL);

 public:
    virtual const SortedCollection* sortBlock(int (*a_sort_block)(const Object* const&, const Object* const&));
};


END_NAMESPACE_ALTAIR


#endif  /* altair_SortedCollection_hxx */
// Local Variables:
//   coding: utf-8
// End:
