//  
//  ArrayedCollection.hxx
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
#ifndef altair_ArrayedCollection_hxx
#define altair_ArrayedCollection_hxx

#include "altair/SequenceableCollection.hxx"


BEGIN_NAMESPACE_ALTAIR


/**
 * 
 */
class ArrayedCollection : public SequenceableCollection
{
    typedef SequenceableCollection _Super;

 public:
    /*!
     * 
     */
    ArrayedCollection();
    /*!
     * 
     */
    ArrayedCollection(size_t size, Object* const& an_object = NULL);
    /*!
     * 
     */
    ArrayedCollection(const Collection& other);


    /*!
     * 
     */
    virtual ~ArrayedCollection();

 public:
    /*!
      \name built ins
     */
    /*! @{ */
    virtual size_t size() const { return tally_; }
    /*! @} */



    /*!
      \name basic
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Collection* const& add(Object* const& value);


    /*!
     * 
     */
    virtual Collection* addAll(Collection* const& key_collection);


    /*!
     * 
     */
    virtual SequenceableCollection* copyFrom(int start, int stop) const;


    /*!
     * 
     */
    virtual Collection* copyWithout(const Object* const old_element) const;


    /*!
     * 
     */
    virtual Collection* copyWith(Object* const& an_element) const;
    /*! @} */


    /*!
      \name enumerating the elements of a collection
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Collection* select(bool (*a_block)(const Object* const&)) const;


    /*!
     * 
     */
    virtual Collection* reject(bool (*a_block)(const Object* const&)) const;


    /*!
     * 
     */
    virtual Collection* collect(Object* (*a_block)(const Object* const&)) const;


    /*!
     * 
     */
    virtual Collection* withCollect(const SequenceableCollection* const& a_sequence, Object* (*a_block)(const Object* const&, const Object* const&)) const;
    /*! @} */


    /*!
      \name copying collections
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Collection* copyReplaceFrom(int start, int stop, Object* const& an_object) const;
    /*!
     * 
     */
    virtual Collection* copyReplaceFrom(int start, int stop, Collection* const& replacement_collection) const;


    /*!
     * 
     */
    virtual Collection* copyReplaceAll(const SequenceableCollection* const& old_subcollection, const SequenceableCollection* const& new_subcollection) const;


    /*!
     * 
     */
    virtual Collection* reverse() const;
    /*! @} */


    /*!
      \name sorting
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Collection* sorted() const;
    /*!
     * 
     */
    virtual Collection* sorted(int (*a_block)(const Object* const&, const Object* const&)) const;
    /*! @} */


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
    /*!
      \name storing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void storeOn(Stream* const& a_stream) const;
    /*! @} */
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


    /*!
      \name streams
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Stream* writeStream();
    /*! @} */


    /*!
      \name private
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Collection* copyEmpty() const;


    /*!
     * 
     */
    virtual Collection* copyGrowTo(int new_size) const;
    /*! @} */

 protected:
    /*!
      \name private
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void grow();


    /*!
     * 
     */
    virtual ArrayedCollection* growBy(int delta);


    /*!
     * 
     */
    virtual ArrayedCollection* growTo(int new_size);
    /*! @} */

 protected:
    size_t tally_;
};


END_NAMESPACE_ALTAIR


#endif  /* altair_ArrayedCollection_hxx */
// Local Variables:
//   coding: utf-8
// End:
