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
