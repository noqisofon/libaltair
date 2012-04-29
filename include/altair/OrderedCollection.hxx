#ifndef altair_OrderedCollection_hxx
#define altair_OrderedCollection_hxx

#include "altair/SequenceableCollection.hxx"


BEGIN_NAMESPACE_ALTAIR


/*!
 *
 */
class OrderedCollection : public SequenceableCollection
{
 public:
    /*!
     * 
     */
    OrderedCollection();
    /*!
     * 
     */
    OrderedCollection(int an_integer);


    /*!
     * 
     */
    virtual ~OrderedCollection();

 public:
    /*! \name accessing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* first() const;


    /*!
     * 
     */
    virtual Object* last() const;


    /*!
     * 
     */
    virtual Object* at(int an_index) const;


    /*!
     * 
     */
    virtual void put(int an_index, Object* const& an_object);


    /*!
     * 
     */
    virtual size_t size() const { return last_index_ - first_index_; }


    /*! \name adding
     */
    /*! @{ */
    /**
     * 
     */
    virtual Collection* const& add(Object* const& new_object);


    /**
     * 
     */
    virtual Collection* const& addAfter(Object* const& new_object, const Object* const& old_object);


    /**
     * 
     */
    virtual Collection* const& addBefore(Object* const& new_object, const Object* const& old_object);


    /**
     * 
     */
    virtual Collection* const& addAfterIndex(Object* const& new_object, int an_index);


    /**
     * 
     */
    virtual Collection* const& addBeforeIndex(Object* const& new_object, int an_index);


    /**
     * 
     */
    virtual const Collection* addAll(const Collection* const& a_collection);


    /**
     * 
     */
    virtual const Collection* addAllAfter(const Collection* const& a_collection, const Object* const& old_object);


    /**
     * 
     */
    virtual const Collection* addAllAfterIndex(const Collection* const& a_collection, int an_index);


    /**
     * 
     */
    virtual const Collection* addAllBefore(const Collection* const& a_collection, const Object* const& old_object);


    /**
     * 
     */
    virtual const Collection* addAllBeforeIndex(const Collection* const& a_collection, int an_index);


    /*!
     * 
     */
    virtual const Collection* addAllFirst(const Collection* const& a_collection);


    /*!
     * 
     */
    virtual const Collection* addAllLast(const Collection* const& a_collection);


    /*!
     * 
     */
    virtual void addFirst(Object* const& new_object);


    /*!
     * 
     */
    virtual void addLast(Object* const& new_object);
    /*! @} */


    /*! \name removing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* removeFirst();


    /*!
     * 
     */
    virtual Object* removeLast();


    /*!
     * 
     */
    virtual Object* identityRemove(const Object* const& old_object);
    /*!
     * 
     */
    virtual Object* identityRemove(const Object* const& old_object, int (*a_block)(const Object* const&, const Object* const&));


    /*!
     *
     */
    virtual Object* remove(const Object* const& an_object, int (*a_block)(const Object* const&, const Object* const&));


    /*!
     * 
     */
    virtual Object* removeAtIndex(int an_index);
    /*! @} */

 protected:
    /*! \name private methods
     */
    /*! @{ */
    /*!
     * 
     */
    Object* basicRemoveAtIndex(int an_index);


    /*!
     * 
     */
    void basicAddLast(Object* const& new_object);


    /*!
     * 
     */
    const Collection* basicAddAllLast(const Collection* const& a_collection);


    /*!
     * 
     */
    Object* basicRemoveFirst();


    /*!
     * 
     */
    Object* basicRemoveLast();


    /*!
     * 
     */
    void initIndices();


    /*!
     * 
     */
    void firstIndexAndLastIndex(int first_index, int last_index) {
        first_index_ = first_index;
        last_index_ = last_index;
    }


    /*!
     * 
     */
    void makeRoomFirstFor(int n);


    /*!
     * 
     */
    void makeRoomLastFor(int n);


    /*!
     *
     */
    virtual size_t shrinkSize() const { return basicSize() / 3; }


    /*!
     * 
     */
    virtual void shrink();


    /*!
     *
     */
    virtual void grow();


    /*!
     * 
     */
    virtual void growBy(int delta, int shift_count);


    /*!
     * 
     */
    void primReplaceFrom(int start, int stop, const SequenceableCollection* const& byte_array, int replace_start);
    /*! @} */

 private:
    int first_index_;
    int last_index_;
};


END_NAMESPACE_ALTAIR


#endif  /* altair_OrderedCollection_hxx */
// Local Variables:
//   coding: utf-8
// End:
