//  
//  altair_prefix.h
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
#ifndef altair_altair_prefix_hxx
#define altair_altair_prefix_hxx

#define __STDC_CONSTANT_MACROS

#include <stdint.h>
#include <stddef.h>

#include "altair/platform.h"
#include "altair/transplant.h"
#include "altair/macro.h"


typedef   signed char sbyte;
typedef unsigned char ubyte;

typedef   signed int  sint;
typedef unsigned int  uint;



#define BEGIN_NAMESPACE_ALTAIR    namespace altair {
#define END_NAMESPACE_ALTAIR      }


#define USING_NAMESPACE_ALTAIR    using namespace altair


#endif  /* altair_altair_prefix_hxx */
