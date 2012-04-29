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
