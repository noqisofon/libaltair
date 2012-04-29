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
    virtual void key(Object* const& new_key);


    /*!
     *
     */
    virtual Object* value() const;
    /*!
     *
     */
    virtual void value(Object* const& new_value);
    /*! @} */
};


END_NAMESPACE_ALTAIR


#endif  /* altair_LookupKey_hxx */
// Local Variables:
//   coding: utf-8
// End:
