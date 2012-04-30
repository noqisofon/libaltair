//  
//  ArgumentOutOfRangeError.hxx
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
#ifndef altair_ArgumentOutOfRangeError_hxx
#define altair_ArgumentOutOfRangeError_hxx

#include "altair/ArgumentError.hxx"


BEGIN_NAMESPACE_ALTAIR


class String;
class Magunitude;


/*!
 * 
 */
class ArgumentOutOfRangeError : public ArgumentError
{
 public:
    /*!
     * 
     */
    static void signalOn(int n, int m, int k);
    /*!
     * 
     */
    static void signalOn(const Object* const& n, const Magunitude* const& m, const Magunitude* const& k);
};


END_NAMESPACE_ALTAIR


#endif  /* altair_ArgumentOutOfRangeError_hxx */
// Local Variables:
//   coding: utf-8
// End:
