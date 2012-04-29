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
    /*! \name accessing instences and variables
     */
    /*! @{ */
    /*!
     * 
     */
    virtual int instanceCount() const;


    /*!
     * 
     */
    virtual int indexOfInstVar(const String* const& a_string) const;
    /*! @} */


    /*! \name testing the form of the instances
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool isPointers() const;


    /*!
     * 
     */
    virtual bool isFixed() const { return !isVariable(); }


     /*!
     * 
     */
    virtual bool isVariable() const;
    /*! @} */


    /*! \name testing the class hierarchy
     */
    /*! @{ */
    /*!
     *
     */
    virtual size_t instanceSize() const;


    /*!
     * 
     */
    virtual bool inheritsFrom(const Class* const& a_class) const;


    /*!
     * 
     */
    virtual Symbol* getShape() const;
    /*! @} */


    /*! \name testing the method dictionary
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool canUnderstand(const Symbol* const& selector) const;
    /*! @} */
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Behavior_hxx */
// Local Variables:
//   coding: utf-8
// End:
