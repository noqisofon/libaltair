//  
//  ReadStream.hxx
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
#ifndef altair_ReadStream_hxx
#define altair_ReadStream_hxx

#include "altair/PositionableStream.hxx"


BEGIN_NAMESPACE_ALTAIR


class Collection;
class String;


/*!
 * 
 */
class ReadStream : public PositionableStream
{
 public:
    /*!
     * 
     */
    static Stream* on(const Collection* const& a_collection);


    /*!
     * 
     */
    static Stream* on(const Collection* const& a_collection, int start, int stop);
};


END_NAMESPACE_ALTAIR


#endif  /* altair_ReadStream_hxx */
// Local Variables:
//   coding: utf-8
// End:
