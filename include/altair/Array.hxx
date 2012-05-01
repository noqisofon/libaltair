//  
//  Array.hxx
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
#ifndef altair_Array_hxx
#define altair_Array_hxx

#include "altair/ArrayedCollection.hxx"


BEGIN_NAMESPACE_ALTAIR


class Class;
class Stream;


/**
 * 
 */
class Array : public ArrayedCollection
{
    typedef ArrayedCollection _Super;

 public:
    /*!
      \name instance creation
     */
    /*! @{ */
    /*!
     * 
     */
    static Array* from(Array* const& an_array) {
        return an_array;
    }


    /**
     * 
     */
    static Array* with(Object* const& an_object);
    /**
     * 
     */
    static Array* with(Object* const& first_object, Object* const& second_object);
    /**
     * 
     */
    static Array* with(Object* const& first_object, Object* const& second_object, Object* const& third_object);
    /**
     * 
     */
    static Array* with(Object* const& first_object, Object* const& second_object, Object* const& third_object, Object* const& fourth_object);
    /**
     * 
     */
    static Array* with(Object* const& first_object, Object* const& second_object, Object* const& third_object, Object* const& fourth_object, Object* const& fifth_object);


    /**
     * 
     */
    static Array* withAll(Collection* const& an_collection);


#if defined(ALTAIR_USING_FUNCTOR)
    /**
     * 
     */
    static Array* withJoin(Collection* const& an_collection);
#endif  /* defined(ALTAIR_USING_FUNCTOR) */
    /*! @} */


#if defined(ALTAIR_TRANSPLANTLY)
    /*!
     * 
     */
    static Class* getClassInstance();
#endif  /* defined(ALTAIR_TRANSPLANTLY) */

 public:
    /*!
     * 
     */
    Array();
    /*!
     * 
     */
    Array(size_t size, Object* const& an_object = NULL);
    /*!
     * 
     */
    Array(const Array& other);
    /*!
     * 
     */
    Array(const Collection& other);


    /*!
     * 
     */
    virtual ~Array();

 public:
    /*!
      \name built ins
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* at(int an_index) const;
    /*!
     * 
     */
    virtual Object* at(int an_index, Object* (*a_block)(const Object* const&)) const;


    /*!
     * 
     */
    virtual void replaceFrom(int start, int stop, ByteArray* const& byte_array, int replace_start);


    /*!
     * 
     */
    virtual Object* shallowCopy() const;
    /*! @} */


    /*!
      \name printing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void printOn(Stream* const& a_stream) const;


#if defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE
    /*!
     * 
     */
    virtual bool isLiteralObject() const { return !isReadOnly(); }


    /*!
     * 
     */
    virtual void storeLiteralOn(Stream* const& a_stream) const;


    /*!
     * 
     */
    virtual void storeOn(Stream* const& a_stream) const;
#endif  /*  defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE */
    /*! @} */


    /*!
      \name mutating objects
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* multiBecome(Array* const& an_array);
    /*! @} */


    /*!
      \name testing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool isArray() const { return true; }
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

 private:
    Object** content_;
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Array_hxx */
// Local Variables:
//   coding: utf-8
// End:
