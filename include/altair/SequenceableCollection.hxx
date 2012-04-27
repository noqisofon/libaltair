#ifndef altair_SequenceableCollection_hxx
#define altair_SequenceableCollection_hxx

#include "altair/Collection.hxx"


BEGIN_NAMESPACE_ALTAIR


/**
 * 
 */
class SequenceableCollection : public Collection
{
 public:
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
    virtual Object* const at(int an_index, Object* const (*a_block)(const Object* const&)) const;


    /*!
     * 
     */
    virtual Object* const atRandom() const;


    /*!
     * 
     */
    virtual Collection* const atAll(const Collection& key_collection) const {
        return atAll( &key_collection );
    }
    /*!
     * 
     */
    virtual Collection* const atAll(const Collection* const& key_collection) const;


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
    virtual Object* const after(const Object* const& old_object) const;


    /*!
     * 
     */
    virtual Object* const before(const Object* const& old_object) const;


    /*!
     * 
     */
    virtual SequenceableCollection* const allButFirst() const;
    /*!
     * 
     */
    virtual SequenceableCollection* const allButFirst(int n) const;


    /*!
     * 
     */
    virtual SequenceableCollection* const allButLast() const;
    /*!
     * 
     */
    virtual SequenceableCollection* const allButLast(int n) const;


    /*!
     * 
     */
    virtual Object* const first() const;
    /*!
     * 
     */
    virtual SequenceableCollection* const first(int n) const;


    /*!
     * 
     */
    virtual Object* const second() const;


    /*!
     * 
     */
    virtual Object* const third() const;


    /*!
     * 
     */
    virtual Object* const fourth() const;



    /*!
     * 
     */
    virtual Object* const last() const;
    /*!
     * 
     */
    virtual SequenceableCollection* const last(int n) const;


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
    virtual int indexOf(const Object* const& an_element, int (*exception_block)(const Object* const) ) const {
        return indexOf( an_element, 0, exception_block );
    }
    /*!
     * 
     */
    virtual int indexOf(const Object* const& an_element, int an_index, int (*exception_block)(const Object* const) ) const;


    /*!
     * 
     */
    virtual int indexOfLast(const Object* const& an_element, int (*exception_block)(const Object* const) ) const;


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
    virtual int identityIndexOf(const Object* const& an_element, int an_index, int (*exception_block)(const Object* const) ) const;


    /*!
     * 
     */
    virtual int identityIndexOfLast(const Object* const& an_element, int (*exception_block)(const Object* const) ) const;


    /*!
     * 
     */
    virtual int indexOfSubCollection(const SequenceableCollection* const& a_sub_collection) const;
    /*!
     * 
     */
    virtual int indexOfSubCollection( const SequenceableCollection* const& a_sub_collection, int (*exception_block)(const Object* const) ) const {
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
                                      int (*exception_block)(const Object* const) ) const;
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
     \name copying SequenceableCollections
     */
    /*! @{ */
    /*!
     * 
     */
    virtual SequenceableCollection* const copyAfter(const Object* const& an_object) const;


    /*!
     * 
     */
    virtual SequenceableCollection* const copyAfterLast(const Object* const& an_object) const;


    /*!
     * 
     */
    virtual SequenceableCollection* const copyFrom(int start) const;
    /*!
     * 
     */
    virtual SequenceableCollection* const copyFrom(int start, int stop) const;
    /*! @} */


    /*!
     \name testing
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


    /*! \name private methods
     */
    /*! @{ */
    /*!
     * 
     */
    virtual int countSubCollectionOccurrencesOf(const SequenceableCollection* const& a_subcollection) const;


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
