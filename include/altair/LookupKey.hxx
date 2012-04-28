#ifndef altair_LookupKey_hxx
#define altair_LookupKey_hxx

#include "altair/Magunitude.hxx"


BEGIN_NAMESPACE_ALTAIR


class String;


/*!
 * 
 */
class LookupKey : public Magunitude
{
 public:
    /*! \name accessing
     */
    /*! @{ */
    /*!
     *
     */
    virtual Object* key() const;


    /*!
     *
     */
    virtual Object* value() const;
    /*! @} */
};


END_NAMESPACE_ALTAIR


#endif  /* altair_LookupKey_hxx */
// Local Variables:
//   coding: utf-8
// End:
