//  
//  Transcript.hxx
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
#ifndef altair_Transcript_hxx
#define altair_Transcript_hxx


BEGIN_NAMESPACE_ALTAIR


class SequenceableCollection;


class Transcript
{
 public:
    static void print(const Object* const& an_object);
    static void nextPut(char ch);
    static void nextPutAll(const SequenceableCollection* const& a_sequence);
    static void nextPutAll(const String* const& a_string);
    static void nextPutAll(const char* const& cstring);
    static void nl();
    static void put(const Object* const& arg1, const Object* const& arg2);


    static void show(const String* const& a_string);
    static void showCr(const String* const& a_string);

    static Stream* instanceOf();
};



END_NAMESPACE_ALTAIR


#endif  /* altair_Transcript_hxx */
// Local Variables:
//   coding: utf-8
// End:
