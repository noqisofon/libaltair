//  
//  HashedCollection.hxx
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
#ifndef altair_HashedCollection_hxx
#define altair_HashedCollection_hxx

#include "altair/Collection.hxx"


BEGIN_NAMESPACE_ALTAIR


/*!
 *
 */
class HashedCollection : public Collection
{
 public:
    /*! \name private-instance creation
     */
    /*! @{ */
    /*!
     * 
     */
    static HashedCollection* primNew(size_t real_size);
    /*! @} */


    /*! \name instance creation
     */
    /*! @{ */
    /*!
     * 
     */
    static HashedCollection* withAll(const Collection* const& a_collection);
    /*! @} */

 public:
    /*!
     * 
     */
    HashedCollection();
    /*!
     * 
     */
    explicit HashedCollection(size_t size);
    /*!
     * 
     */
    HashedCollection(const Collection& a_collection);

 public:
    /*! \name accessing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* at(int index) const;
    /*!
     * 
     */
    virtual Object* at(const Object* const& key) const = 0;


    /*!
     * 
     */
    virtual void put(int index, Object* const& value);
    /*!
     * 
     */
    virtual Object* put(const Object* const& key, Object* const& value) = 0;


    /**
     * 
     */
    virtual Collection* const& add(Object* const& new_object);
    /*! @} */


    /*! \name removing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* remove(Object* const& old_object, Object* (*an_exception_block)(const Collection* const&, Object* const&));
    /*! @} */


    /*! \name copying
     */
    /*! @{ */
    /*!
     *
     */
    virtual Object* shallowCopy() const;


    /*!
     *
     */
    virtual Object* deepCopy() const;
    /*! @} */


    /*! \name testing collections
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool includes(const Object* const& an_object) const;


    /*!
     * 
     */
    virtual bool isEmpty() const { return tally_ == 0; }


    /*!
     * 
     */
    virtual int occurrencesOf(const Object* const& an_object) const;


    /*!
     * 
     */
    virtual size_t capacity() const {
        return primSize() * 3 / 4;
    }


    /*!
     * 
     */
    virtual size_t size() const { return tally_; }


    /*!
     * 
     */
    virtual int hash() const;


    /*!
     * 
     */
    virtual bool equals(const Object* const& an_object) const;
    /*!
     * 
     */
    virtual bool equals(const HashedCollection* const& a_hashed_collection) const;
    /*! @} */


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
    /*! \name storing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void storeOn(Stream* const& a_stream) const;
    /*! } */
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


    /*! \name rehashing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void rehash();
    /*! } */


    /*! \name private methods
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* addWhileGrowing(Object* const& value);


    /*!
     * 
     */
    virtual void rehashObjectsAfter(int index);


    /*!
     * 
     */
    virtual int hashFor(const Object* const& an_object) const;


    /*!
     * 
     */
    virtual int findElementIndex(const Object* const& an_object) const;


    /*!
     * 
     */
    virtual int findIndex(const Object* const& an_object) const;


    /*!
     * 
     */
    virtual int findIndexOrNil(const Object* const& an_object) const;


    /*!
     * 
     */
    virtual Collection* copyEmpty() const;


    /*!
     * 
     */
    virtual HashedCollection* copyAllFrom(const HashedCollection* const& a_hashed_collection);
    /*! @} */


    /*! \name saving and loading
     */
    /*! @{ */
    /*!
     *
     */
    virtual void postLoad() { rehash(); }


    /*!
     * 
     */
    virtual void postStore() {}
    /*! @} */


    /*! \name builtins
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* primAt(int an_index) const;


    /*!
     * 
     */
    virtual void primPut(int an_index, Object* const& value);


    /*!
     * 
     */
    virtual size_t primSize() const = 0;
    /*! @} */

 protected:
    /*! \name private methods
     */
    /*! @{ */
    /*!
     *
     */
    virtual void initialize();


    /*!
     *
     */
    virtual void resetTally();


    /*!
     *
     */
    virtual bool incrementTally();


    /*!
     *
     */
    virtual bool decrementTally();


    /*!
     *
     */
    virtual void grow();


    /*!
     *
     */
    virtual void growBy(int delta);
    /*! @} */

 private:
    size_t tally_;
};


END_NAMESPACE_ALTAIR


#endif  /* altair_HashedCollection_hxx */
// Local Variables:
//   coding: utf-8
// End:
