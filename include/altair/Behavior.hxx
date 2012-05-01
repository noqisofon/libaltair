//  
//  Behavior.hxx
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
#ifndef altair_Behavior_hxx
#define altair_Behavior_hxx

#include "altair/Object.hxx"


BEGIN_NAMESPACE_ALTAIR


class SequenceableCollection;
class String;


/*!
 * 
 */
class Behavior : public Object
{
 public:
    /*! \name instance variables
     */
    /*! @{ */
#if defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE
    /*!
     * 
     */
    virtual Object* addInstVarName(const String* const& a_string);


    /*!
     * 
     */
    virtual void removeInstVarName(const String* const& a_string);
#endif  /* defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE */
    /*! @} */


    /*! \name accessing instences and variables
     */
    /*! @{ */
#if defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE
    /*!
     * 
     */
    virtual int instanceCount() const;


    /*!
     * 
     */
    virtual int indexOfInstVar(const String* const& a_string) const;
    /*!
     * 
     */
    virtual int indexOfInstVar(const String* const& a_string, int (*exception_block)(const Object* const&, const Object* const&)) const;
#endif  /* defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE */
    /*! @} */


    /*! \name testing the form of the instances
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool isPointers() const;


    /*!
     * 
     */
    virtual bool isFixed() const { return !isVariable(); }


     /*!
     * 
     */
    virtual bool isVariable() const;
    /*! @} */


    /*! \name testing the class hierarchy
     */
    /*! @{ */
    /*!
     *
     */
    virtual size_t instanceSize() const;


    /*!
     * 
     */
    virtual bool inheritsFrom(const Class* const& a_class) const;


    /*!
     * 
     */
    virtual Symbol* getShape() const;
    /*! @} */


    /*! \name testing the method dictionary
     */
    /*! @{ */
#if defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE
    /*!
     * 
     */
    virtual bool canUnderstand(const Symbol* const& selector) const;
#endif  /* defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE */
    /*! @} */


    /*! \name built ins
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* someInstance() const { return nil; }
    /*! @} */

 protected:
    SequenceableCollection* instance_varialbes_;
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Behavior_hxx */
// Local Variables:
//   coding: utf-8
// End:
