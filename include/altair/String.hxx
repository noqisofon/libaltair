//  
//  String.hxx
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
#ifndef altair_String_hxx
#define altair_String_hxx

#include "altair/CharacterArray.hxx"


BEGIN_NAMESPACE_ALTAIR


class Encoding;
class ByteArray;
class Symbol;
class Stream;


/*!
 * 
 */
class String : public CharacterArray
{
 public:
    /*!
     * 
     */
    String();
    /*!
     * 
     */
    String(size_t size, char ch = '\0');
    /*!
     * 
     */
    String(const char* const& cstring);

 public:
    /*! \name converting
     */
    /*! @{ */
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


    /*!
     * 
     */
    virtual String* asString() const;
    /*! @} */


    /**
     * 
     */
    virtual bool isString() const { return true; }


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
    /**
     * 
     */
    virtual const String* displayString() const { return this; }


    /**
     * 
     */
    virtual void displayOn(Stream* const a_stream) const;
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


    /*!
      \name built ins
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* shallowCopy() const;
    /*! @} */


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


#endif  /* altair_String_hxx */
// Local Variables:
//   coding: utf-8
// End:
