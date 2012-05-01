//  
//  SequenceableCollection.hxx
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
#ifndef altair_SequenceableCollection_hxx
#define altair_SequenceableCollection_hxx

#include "altair/Collection.hxx"


BEGIN_NAMESPACE_ALTAIR


/**
 * 
 */
class SequenceableCollection : public Collection
{
 public:/*! \name testing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool isSequenceable() const { return true; }


    /*!
     * 
     */
    virtual bool equals(const Collection* const& a_collection) const;


    /*!
     * 
     */
    virtual int hash() const;
    /*! @} */


    /*!
     \name comparing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool startsWith(const SequenceableCollection& other) const {
        return startsWith( &other );
    }
    /*!
     * 
     */
    virtual bool startsWith(const SequenceableCollection* const& other) const;


    /*!
     * 
     */
    virtual bool endsWith(const SequenceableCollection& other) const {
        return endsWith( &other );
    }
    /*!
     * 
     */
    virtual bool endsWith(const SequenceableCollection* const& other) const;
    /*! @} */


    /*!
     \name basic
     */
    /*! @{ */
    // /*!
    //  * 
    //  */
    // virtual Object* const checkIndexableBounds(int index) const;
    // /*!
    //  * 
    //  */
    // virtual Object* const checkIndexableBounds(int index, Object* const (*a_block)(const Object* const&)) const;


    // /*!
    //  * 
    //  */
    // virtual void checkIndexableBoundsPut(int index, Object* const& object);
    /*!
     * 
     */
    virtual Object* at(int an_index, Object* (*a_block)(const Object* const&, const Object* const&)) const;


    /*!
     * 
     */
    virtual Object* atRandom() const;


    /*!
     * 
     */
    virtual Collection* atAll(const Collection& key_collection) const {
        return atAll( &key_collection );
    }
    /*!
     * 
     */
    virtual Collection* atAll(const Collection* const& key_collection) const;


    /*!
     * 
     */
    virtual void putAll(const Collection* const& a_collection, Object* const& an_object);


    /*!
     * 
     */
    virtual const SequenceableCollection* const& atAllPut(Object* const& an_object);


    /*!
     * 
     */
    virtual Object* after(const Object* const& old_object) const;


    /*!
     * 
     */
    virtual Object* before(const Object* const& old_object) const;


    /*!
     * 
     */
    virtual SequenceableCollection* allButFirst() const;
    /*!
     * 
     */
    virtual SequenceableCollection* allButFirst(int n) const;


    /*!
     * 
     */
    virtual SequenceableCollection* allButLast() const;
    /*!
     * 
     */
    virtual SequenceableCollection* allButLast(int n) const;


    /*!
     * 
     */
    virtual Object* first() const;
    /*!
     * 
     */
    virtual SequenceableCollection* first(int n) const;


    /*!
     * 
     */
    virtual Object* second() const;


    /*!
     * 
     */
    virtual Object* third() const;


    /*!
     * 
     */
    virtual Object* fourth() const;



    /*!
     * 
     */
    virtual Object* last() const;
    /*!
     * 
     */
    virtual SequenceableCollection* last(int n) const;


    /*!
     * 
     */
    virtual bool includes(const Object* const& an_object) const;


    /*!
     * 
     */
    virtual bool identityIncludes(const Object* const& an_object) const;


    /*!
     * 
     */
    virtual int indexOf(const Object* const& an_element) const;
    /*!
     * 
     */
    virtual int indexOf(const Object* const& an_element, int an_index) const;
    /*!
     * 
     */
    virtual int indexOf(const Object* const& an_element, int (*exception_block)(const Object* const&, const Object* const&) ) const {
        return indexOf( an_element, 0, exception_block );
    }
    /*!
     * 
     */
    virtual int indexOf(const Object* const& an_element, int an_index, int (*exception_block)(const Object* const&, const Object* const&)) const;


    /*!
     * 
     */
    virtual int indexOfLast(const Object* const& an_element, int (*exception_block)(const Object* const&, const Object* const&)) const;


    /*!
     * 
     */
    virtual int identityIndexOf(const Object* const& an_element) const;
    /*!
     * 
     */
    virtual int identityIndexOf(const Object* const& an_element, int an_index) const;
    /*!
     * 
     */
    virtual int identityIndexOf(const Object* const& an_element, int an_index, int (*exception_block)(const Object* const&, const Object* const&) ) const;


    /*!
     * 
     */
    virtual int identityIndexOfLast(const Object* const& an_element, int (*exception_block)(const Object* const&, const Object* const&) ) const;


    /*!
     * 
     */
    virtual int indexOfSubCollection(const SequenceableCollection* const& a_sub_collection) const;
    /*!
     * 
     */
    virtual int indexOfSubCollection( const SequenceableCollection* const& a_sub_collection, int (*exception_block)(const Object* const&, const Object* const&) ) const {
        return indexOfSubCollection( a_sub_collection,
                                     0,
                                     exception_block );
    }
    /*!
     * 
     */
    virtual int indexOfSubCollection(const SequenceableCollection* const& a_sub_collection, int an_index) const;
    /*!
     * 
     */
    virtual int indexOfSubCollection( const SequenceableCollection* const& a_sub_collection,
                                      int an_index,
                                      int (*exception_block)(const Object* const&, const Object* const&) ) const;
    /*! @} */


    /*!
     \name replacing items
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void replaceAll(const Object* const& an_object, Object* const& another_object);


    /*!
     * 
     */
    virtual void replaceFrom(int start, int stop, const Collection* const& replacement_collection) {
        replaceFrom( start, stop, replacement_collection, 0 );
    }
    /*!
     * 
     */
    virtual void replaceFrom(int start, int stop, const Collection* const& replacement_collection, int rep_start);
    /*!
     * 
     */
    virtual void replaceFrom(int an_index, int stop_index, Object* const& an_object);
    /*! @} */


    /*!
     \name copying SequenceableCollections
     */
    /*! @{ */
    /*!
     * 
     */
    virtual SequenceableCollection* copyAfter(const Object* const& an_object) const;


    /*!
     * 
     */
    virtual SequenceableCollection* copyAfterLast(const Object* const& an_object) const;


    /*!
     * 
     */
    virtual SequenceableCollection* copyUpTo(const Object* const& an_object) const;


    /*!
     * 
     */
    virtual SequenceableCollection* copyUpToLast(const Object* const& an_object) const;

    
    /*!
     * 
     */
    virtual SequenceableCollection* copyReplaceFrom(int start, int stop, Object* const& an_object) const;


    /*!
     * 
     */
    virtual SequenceableCollection* copyWithFirst(Object* const& an_object) const;


    /*!
     * 
     */
    virtual SequenceableCollection* copyFrom(int start) const;
    /*!
     * 
     */
    virtual SequenceableCollection* copyFrom(int start, int stop) const;


    /*!
     * 
     */
    virtual SequenceableCollection* copyReplaceAll( const SequenceableCollection* const& old_sub_collection,
                                                    SequenceableCollection* const& new_sub_collection ) const;
    /*!
     * 
     */
    virtual SequenceableCollection* copyReplaceAll(int start, int stop, SequenceableCollection* const& replacement_collection) const;
    /*! @} */


    /*! \name concatenating
     */
    /*! @{ */
    /*! @} */


    /*!
     * 
     */
    virtual void nextPutAllOn(Stream* const& a_stream);


    /*! \name enumerating
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Stream* readStream() const;


    /*!
     * 
     */
    virtual Stream* writeStream();


    /*!
     * 
     */
    virtual Stream* readWriteStream();


    /*!
     * 
     */
    virtual Object* anyOne() const { return first(); }


    /*!
     * 
     */
    virtual SequenceableCollection* keys() const;


    /*!
     * 
     */
    virtual int findFirst(bool (*a_block)(const Object* const&, Object* const&)) const;


    /*!
     * 
     */
    virtual int findLast(bool (*a_block)(const Object* const&, Object* const&)) const;


    /*!
     * 
     */
    virtual SequenceableCollection* reverse() const;
    /*! @} */


    /*! \name private methods
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


    /*!
     * 
     */
    virtual void sort();
    /*!
     * 
     */
    virtual void sort(int (*a_block)(const Object* const&, const Object* const&));
    /*! @} */


    /*! \name private methods
     */
    /*! @{ */
    /*!
     *
     */
    virtual bool matchSubCollection(const SequenceableCollection* const& a_sub_collection, int an_index) const;


    /*!
     * 
     */
    virtual int countSubCollectionOccurrencesOf(const SequenceableCollection* const& a_subcollection) const;
    /*! @} */


    /*! \name testing collections
     */
    /*! @{ */
    /*!
     *
     */
    virtual size_t size() const = 0;
    /*! @} */


    /*! \name manipulation
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void swap(int an_index, int another_index);
    /*! @} */

 protected:
    /*! \name private methods
     */
    /*! @{ */
    /*!
     * 
     */
    virtual size_t growSize() const { return ALTAIR_MIN(size(), 8); }
    /*! @} */
};


END_NAMESPACE_ALTAIR


#endif  /* altair_SequenceableCollection_hxx */
// Local Variables:
//   coding: utf-8
// End:
