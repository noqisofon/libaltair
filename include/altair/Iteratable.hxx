#ifndef altair_Iteratable_hxx
#define altair_Iteratable_hxx

#include "altair/Object.hxx"


BEGIN_NAMESPACE_ALTAIR


/**
 * 
 */
class Iteratable : public Object
{
 public:
    /*! \name enumeration
     */
    /*! @{ */
    /*!
     *
     */
    virtual Object* inject(Object* const& this_value, Object* (*binary_block)(Object* const&, Object* const&));
    /*! @} */


    /*! \name streaming
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Stream* readStream() const;
    /*! @} */
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Iteratable_hxx */
// Local Variables:
//   coding: utf-8
// End:
