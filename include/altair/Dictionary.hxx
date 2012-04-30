//  
//  Dictionary.hxx
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
#ifndef altair_Dictionary_hxx
#define altair_Dictionary_hxx

#include "altair/HashedCollection.hxx"


BEGIN_NAMESPACE_ALTAIR


/*!
 *
 */
class Dictionary : public HashedCollection
{
    typedef HashedCollection _Super;

 public:
    /*!
     * 
     */
    Dictionary();
    /*!
     * 
     */
    explicit Dictionary(size_t size);

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
    virtual Object* at(const Object* const& key, Object* (*a_block)(const Object* const&, const Object* const&)) const;


    /*!
     * 
     */
    virtual Object* atIfAbsentPut(const Object* const& key, Object* (*a_block)(const Object* const&, const Object* const&));


    /*!
     * 
     */
    virtual Object* atIfPresent(const Object* const& key, Object* (*a_block)(const Object* const&, const Object* const&)) const;


    /*!
     * 
     */
    virtual Object* associationAt(const Object* const& key) const;
    /*!
     * 
     */
    virtual Object* associationAt(const Object* const& key, Object* (*a_block)(const Object* const&, const Object* const&)) const;


    /*!
     * 
     */
    virtual Object* put(const Object* const& key, Object* const& value);


    /*!
     * 
     */
    virtual Set* keys() const;
    /*! @} */


    /*! \name dictionary testing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool includes(const Object* const& an_object) const;
    
    /*!
     * 
     */
    virtual bool includesAssociation(const Association* const& an_association) const;


    /*!
     * 
     */
    virtual bool includesKey(const Object* const& key) const;


    /*!
     * 
     */
    virtual int occurrencesOf(const Object* const& a_value) const;
    /*! @} */


    /*! \name dictionary removing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* removeKey(Object* const& key);
    /*! @} */


    /*! \name dictionary enumerating
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Stream* keysAndValuesReadStream() const;
    /*! @} */


    /*! \name builtins
     */
    /*! @{ */
    /*!
     * 
     */
    virtual size_t primSize() const;
    /*! @} */
};


END_NAMESPACE_ALTAIR


#endif  /* altair_HashedCollection_hxx */
// Local Variables:
//   coding: utf-8
// End:
