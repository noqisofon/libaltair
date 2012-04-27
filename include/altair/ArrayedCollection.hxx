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
    virtual Collection* const addAll(Collection* const& key_collection);


    /*!
     * 
     */
    virtual SequenceableCollection* const copyFrom(int start, int stop) const;


    /*!
     * 
     */
    virtual Collection* const copyWithout(const Object* const old_element) const;


    /*!
     * 
     */
    virtual Collection* const copyWith(Object* const& an_element) const;
    /*! @} */


    /*!
      \name enumerating the elements of a collection
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Collection* const select(bool (*a_block)(const Object* const&)) const;


    /*!
     * 
     */
    virtual Collection* const reject(bool (*a_block)(const Object* const&)) const;


    /*!
     * 
     */
    virtual Collection* const collect(Object* const (*a_block)(const Object* const&)) const;


    /*!
     * 
     */
    virtual Collection* const withCollect(const SequenceableCollection* const& a_sequence, Object* const (*a_block)(const Object* const&, const Object* const&)) const;
    /*! @} */


    /*!
      \name copying collections
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Collection* const copyReplaceFrom(int start, int stop, Object* const& an_object) const;
    /*!
     * 
     */
    virtual Collection* const copyReplaceFrom(int start, int stop, Collection* const& replacement_collection) const;


    /*!
     * 
     */
    virtual Collection* const copyReplaceAll(const SequenceableCollection* const& old_subcollection, const SequenceableCollection* const& new_subcollection) const;


    /*!
     * 
     */
    virtual Collection* const reverse() const;
    /*! @} */


    /*!
      \name sorting
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Collection* const sorted() const;
    /*!
     * 
     */
    virtual Collection* const sorted(bool (*a_block)(const Object* const&, const Object* const&)) const;
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
    virtual Stream* const writeStream();
    /*! @} */


    /*!
      \name private
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Collection* const copyEmpty() const;


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
    virtual ArrayedCollection* const growBy(int delta);


    /*!
     * 
     */
    virtual ArrayedCollection* const growTo(int new_size);
    /*! @} */

 protected:
    size_t tally_;
};


END_NAMESPACE_ALTAIR


#endif  /* altair_ArrayedCollection_hxx */
// Local Variables:
//   coding: utf-8
// End:
