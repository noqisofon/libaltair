//  
//  UndefinedObject.hxx
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
#ifndef altair_UndefinedObject_hxx
#define altair_UndefinedObject_hxx

#include "altair/Object.hxx"


BEGIN_NAMESPACE_ALTAIR


class Stream;


/*!
 * 
 */
class UndefinedObject : public Object
{
 public:
    /*!
     * 
     */
    static Object* getInstance();

 private:
    UndefinedObject() {}
    UndefinedObject(const UndefinedObject&);

 public:
    /*! \name basic
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* copy() const;


    /*!
     * 
     */
    virtual Object* shallowCopy() const;


    /*!
     * 
     */
    virtual Object* deepCopy() const;
    /*! @} */


    /*! \name testing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool isNil() const { return true; }


    /*!
     * 
     */
    virtual bool notNil() const { return false; }
    /*! @} */


    /*!
      \name dependents access
     */
    /*! @{ */
#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
    /*!
     * 
     */
    virtual void addDependent(Object* const& an_object);


    /*!
     * 
     */
    virtual Object* removeDependent(Object* const& an_object);


    /*!
     * 
     */
    virtual OrderedCollection* const dependants() const;
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


    /*!
     * 
     */
    virtual void release() {}
    /*! @} */


    /*!
      \name printing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void printOn(Stream* const& a_stream) const;


    /*!
     * 
     */
    virtual void basicPrintOn(Stream* const& a_stream) const;
    /*! @} */


    /*!
      \name storing
     */
    /*! @{ */
    /*!
     *
     */
    virtual bool isLiteralObject() const { return true; }

#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)    
    /*!
     *
     */
    virtual void storeLiteralOn(Stream* const& a_stream) const;


    /*!
     * 
     */
    virtual void storeOn(Stream* const& a_stream) const;
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */
    /*! @} */


    /*!
      \name class polymorphism
     */
    /*! @{ */
    /*!
     * 
     */
    virtual size_t instSize() const { return 0; }
    /*! @} */

 private:
    static UndefinedObject NIL;
};


END_NAMESPACE_ALTAIR


#endif  /* altair_UndefinedObject_hxx */
// Local Variables:
//   coding: utf-8
// End:
