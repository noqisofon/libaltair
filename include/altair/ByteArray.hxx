//  
//  ByteArray.hxx
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
#ifndef altair_ByteArray_hxx
#define altair_ByteArray_hxx

#include "altair/ArrayedCollection.hxx"


BEGIN_NAMESPACE_ALTAIR


class String;
class UnicodeString;


/*!
 * 
 */
class ByteArray : public ArrayedCollection
{
    typedef ArrayedCollection _Super;

 public:
    /*!
     * 
     */
    explicit ByteArray(size_t size = 4);
    /*!
     * 
     */
    ByteArray(const ByteArray& other);


    /*!
     * 
     */
    virtual ~ByteArray();

 public:
    /*!
      \name converting
     */
    /*! @{ */
    /*!
     * 
     */
    virtual String* asString() const;


    /*!
     * 
     */
    virtual UnicodeString* asUnicodeString() const;
    /*! @} */


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
    /*!
      \name storing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool isLiteralObject() const {
        return !isReadOnly();
    }


    /*!
     * 
     */
    virtual void storeLiteralOn(Stream* const& a_stream);


    /*!
     * 
     */
    virtual void storeOn(Stream* const& a_stream);
    /*! @} */
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


    /*!
      \name built ins
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* at(int an_index, Object* (*a_block)(const Object* const&)) const;


    /*!
     * 
     */
    virtual void put(int index, Object* const& value) {
        checkIndexableBoundsPut( index, value );
    }


    /*!
     * 
     */
    ubyte byteAt(int index) const;


    /*!
     * 
     */
    void bytePut(int index, ubyte value);


    /*!
     * 
     */
    virtual int hash() const;


    /*!
     * 
     */
    virtual void release();


    /*!
     * 
     */
    virtual void replaceFrom(int start, int stop, const String* const& a_string, int replace_start);
    /*! @} */


    /*!
      \name basic
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool equals(const Collection* const& a_collection) const;


    /*!
     * 
     */
    virtual int indexOf(Object* const& an_element, int an_index) const;
    /*!
     * 
     */
    virtual int indexOf(Object* const& an_element, int an_index, int (*a_block)(const Object* const&)) const;
    /*! @} */

 protected:
    /*!
      \name private
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* checkIndexableBounds(int index) const;
    /*!
     * 
     */
    virtual Object* checkIndexableBounds(int index, Object* (*a_block)(const Object* const&)) const;


    /*!
     * 
     */
    virtual void checkIndexableBoundsPut(int index, Object* const& object);


    /*!
     * 
     */
    virtual ubyte checkIndexableByteBounds(int index) const;
    /*!
     * 
     */
    virtual ubyte checkIndexableByteBounds(int index, ubyte (*a_block)(const Object* const&)) const;


    /*!
     * 
     */
    virtual void checkIndexableByteBoundsPut(int index, ubyte value);
    /*! @} */

 private:
    /*!
      \name private
     */
    /*! @{ */
    virtual size_t growSize() const { return size(); }
    /*! @} */

 private:
    ubyte* bytes_;
};


END_NAMESPACE_ALTAIR


#endif  /* altair_ByteArray_hxx */
// Local Variables:
//   coding: utf-8
// End:
