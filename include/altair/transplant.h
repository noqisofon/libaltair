//  
//  transplant.h
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
#ifndef altair_transplant_h
#define altair_transplant_h


/**
 * \def LT_NEAR_COMPLETE_TRANSPLANT_RATE
 * 完全に近い移植率を表します。
 * <p>
 * Smalltalk に近い移植率を達成することはまず無理なので、ALTAIR_TRANSPLANTLY がこの値になることはまずありません。
 * 今はそこまで実装することもないと思います。
 * </p>
 */
#define    ALT_NEAR_COMPLETE_TRANSPLANT_RATE       10000
/**
 * \def LT_STANDARD_TRANSPLANT_RATE
 * 標準の移植率を表します。
 * <p>
 * 簡単なリフレクションやシリアライズなどが可能です。
 * </p>
 */
#define    ALT_STANDARD_TRANSPLANT_RATE             5000
/**
 * \def LT_MINIMUM_TRANSPLANT_RATE
 * 必要最低限の移植率を表します。
 * <p>
 * メソッドを数え上げるなどのリフレクションや、メンバ関数にブロックを渡すなどといったことはできません。
 * メンバ関数に関数ポインタを渡すということはできますが、かなりの制限があります。
 * また、定義されたメソッドの数も少なめです。
 * </p>
 */
#define    ALT_MINIMUM_TRANSPLANT_RATE              1000


#endif  /* altair_transplant_h */
