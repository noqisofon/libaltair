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
    /*!
      \name accessing
     */
    /*! @{ */
    /**
     * 
     */
    virtual Collection* const& add(Object* const& new_object);
    /*! @} */
};


END_NAMESPACE_ALTAIR


#endif  /* altair_HashedCollection_hxx */
// Local Variables:
//   coding: utf-8
// End:
