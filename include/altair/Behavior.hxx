#ifndef altair_Behavior_hxx
#define altair_Behavior_hxx

#include "altair/Object.hxx"


BEGIN_NAMESPACE_ALTAIR


/*!
 * 
 */
class Behavior : public Object
{
 public:
    /*! \name testing the form of the instances
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool isFixed() const { return !isVariable(); }


     /*!
     * 
     */
    virtual bool isVariable() const;
    /*! @} */
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Behavior_hxx */
