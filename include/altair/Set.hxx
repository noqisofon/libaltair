//  
//  Set.hxx
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
#ifndef altair_Set_hxx
#define altair_Set_hxx

#include "altair/HashedCollection.hxx"


BEGIN_NAMESPACE_ALTAIR


class Array;


/*!
 *
 */
class Set : public HashedCollection
{
    typedef HashedCollection _Super;

 public:
    /*!
     *
     */
    Set();
    /*!
     *
     */
    Set(size_t size, Object* const& an_object = NULL);
    /*!
     *
     */
    Set(const Set& other);


    /*!
     * 
     */
    virtual ~Set() {}

 public:
    /*! \name accessing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* at(const Object* const& key) const;


    /*!
     * 
     */
    virtual Object* put(const Object* const& key, Object* const& value);
    /*! @} */


    /*! \name private methods
     */
    /*! @{ */
    /*!
     * 
     */
    virtual int hashFor(const Object* const& an_object) const;


    /*!
     * 
     */
    virtual int findIndex(const Object* const& an_object) const;
    /*! @} */


    /*! \name builtins
     */
    /*! @{ */
    /*!
     * 
     */
    virtual size_t primSize() const;
    /*! @} */

 private:
    Array* content_;
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Set_hxx */
// Local Variables:
//   coding: utf-8
// End:
