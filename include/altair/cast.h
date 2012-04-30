//  
//  cast.h
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
/**
 * @file    cast.h
 * @breif   C++ 風のキャストを C 風のキャストとスイッチできるエクステンション
 */
#if !defined(__CSTYLE_CAST)
////////////////////////////////////////////////////////////////////////////////
// 
// C スタイルのキャストを行う関数型プリプロセッサ。
// 
#   define     __CSTYLE_CAST(_type_, _expression_)      ((_type_)_expression_)


#   ifdef __cplusplus
/* 
 * _ALTI_NON_STANDALONE_MODULE が定義されていなかったら、デフォルトとして
 * _ALTI_USE_CPPSTYLE_CAST を定義します。
 */
#       if !defined(_ALTI_NON_STANDALONE_MODULE)
#           define          _ALTI_USE_CPPSTYLE_CAST
#       else
/* 
 * 定義されており、_USE_CPPSTYLE_CAST が定義されていたら
 * _ALTI_USE_CPPSTYLE_CAST を定義します。
 */
#           if defined(_USE_CPPSTYLE_CAST)
#               define      _ALTI_USE_CPPSTYLE_CAST
#           endif  /* defined(_USE_CPPSTYLE_CAST) */

#       endif  /* !defined(_ALTI_NON_STANDALONE_MODULE) */
#   endif  /* def __cplusplus */


////////////////////////////////////////////////////////////////////////////////
// 
// C++ スタイルのキャストを行う関数型プリプロセッサ。
// 
#   if defined(_ALTI_USE_CPPSTYLE_CAST)
#       define      __DYNAMIC_CAST(_type_, _expression_)                  dynamic_cast<_type_>(_expression_)
#       define      __STATIC_CAST(_type_, _expression_)                    static_cast<_type_>(_expression_)
#       define      __REINTERPRET_CAST(_type_, _expression_)          reinterpret_cast<_type_>(_expression_)
#       define      __CONST_CAST(_type_, _expression_)                      const_cast<_type_>(_expression_)
#   else
#       define      __DYNAMIC_CAST(_type_, _expression_)                 __CSTYLE_CAST(_type_, _expression_)
#       define      __STATIC_CAST(_type_, _expression_)                  __CSTYLE_CAST(_type_, _expression_)
#       define      __REINTERPRET_CAST(_type_, _expression_)             __CSTYLE_CAST(_type_, _expression_)
#       define      __CONST_CAST(_type_, _expression_)                   __CSTYLE_CAST(_type_, _expression_)
#   endif  /* defined(_ALTI_USE_CPPSTYLE_CAST) */


#endif  /* !defined(__CSTYLE_CAST) */
