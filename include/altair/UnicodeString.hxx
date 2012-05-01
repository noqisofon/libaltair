//  
//  UnicodeString.hxx
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
#ifndef altair_UnicodeString_hxx
#define altair_UnicodeString_hxx

#include "altair/CharacterArray.hxx"


BEGIN_NAMESPACE_ALTAIR


class Encoding;
class ByteArray;
class Symbol;
class Stream;


/*!
 * 
 */
class UnicodeString : public CharacterArray
{
 public:
    /*!
     * 
     */
    UnicodeString(size_t size, char ch = '\0');
    /*!
     * 
     */
    UnicodeString(const char* const& cstring);
    /*!
     * 
     */
    UnicodeString(const UnicodeString& other);

 public:
    /**
     * 
     */
    Encoding* encoding() const;


    /**
     * 
     */
    virtual ByteArray* asByteArray() const;


    /**
     * 
     */
    virtual Symbol* asSymbol() const;


    /**
     * 
     */
    virtual bool isUnicodeString() const { return true; }


    /*!
      \name built ins
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* shallowCopy() const { return new UnicodeString( *this ); }
    /*! @} */


    /**
     * 
     */
    virtual const String* displayString() const;


    /**
     * 
     */
    virtual void displayOn(Stream* const a_stream) const;


#ifndef ALTAIR_TRANSPLANTLY
    /*!
      \name copying collections
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Collection* copyEmpty() const;
    /*!
     * 
     */
    virtual Collection* copyEmpty(int new_size) const;
    /*! @} */
#endif  /* ndef ALTAIR_TRANSPLANTLY */
};


END_NAMESPACE_ALTAIR


#endif  /* altair_UnicodeString_hxx */
// Local Variables:
//   coding: utf-8
// End:
