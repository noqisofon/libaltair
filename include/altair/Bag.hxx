#ifndef altair_Bag_hxx
#define altair_Bag_hxx

#include "altair/Collection.hxx"


BEGIN_NAMESPACE_ALTAIR


class HashedCollection;
class SequenceableCollection;
class Stream;


/*!
 *
 */
class Bag : public Collection
{
 public:
    /*!
     * 
     */
    Bag();
    /*!
     * 
     */
    explicit Bag(size_t size);

 public:
    /*! \name adding
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Collection* const& add(Object* const& new_object);


    /*!
     * 
     */
    virtual Object* addWithOccurrences(Object* const new_object, int an_integer);
    /*! @} */


    /*! \name removing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* remove(Object* const& old_object, Object* (*an_exception_block)(const Collection* const&, Object* const&));
    /*! @} */


    /*! \name extracting items
     */
    /*! @{ */
    /*!
     * 
     */
    virtual SequenceableCollection* sortedByCount() const;
    /*! @} */


    /*! \name testing collections
     */
    /*! @{ */
    /*!
     * 
     */
    virtual int occurrencesOf(const Object* const& an_object) const;


    /*!
     * 
     */
    virtual bool includes(const Object* const& an_object) const;


    /*!
     * 
     */
    virtual size_t size() const;


    /*!
     * 
     */
    virtual int hash() const;


    /*!
     * 
     */
    virtual bool equals(const Object* const& a_bag) const;
    /*! @} */


    /*! \name enumerating the elements of a collection
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Set* asSet() const;
    /*! @} */


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
    /*! \name storing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void storeOn(Stream* const& a_stream) const;
    /*! @} */
#endif  /*  defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


    /*! \name printing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void printOn(Stream* const& a_stream) const;
    /*! @} */


    /*! \name private
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Class* dictionaryClass() const;


    /*!
     * 
     */
    virtual HashedCollection* valuesAndCounts() const;


    /*!
     * 
     */
    virtual HashedCollection* contents() const;
    /*! @} */

 protected:
    /*! \name private
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void initContents(size_t size);
    /*! @} */

 private:
    HashedCollection* contents_;
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Bag_hxx */
// Local Variables:
//   coding: utf-8
// End:
