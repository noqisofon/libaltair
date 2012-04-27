#ifndef altair_Number_hxx
#define altair_Number_hxx

#include "altair/Magunitude.hxx"


BEGIN_NAMESPACE_ALTAIR


/*!
 * 
 */
class Number : public Magunitude
{
 public:
    /*! \name converting
     */
    /*! @{ */
    /*!
     * 
     */
    virtual int asInt32() const;


    /*!
     * 
     */
    virtual long asLong() const;
    /*! @} */
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Number_hxx */
// Local Variables:
//   coding: utf-8
// End:
