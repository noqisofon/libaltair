#ifndef altair_SubclassResponsibilityError_hxx
#define altair_SubclassResponsibilityError_hxx

#include "altair/Error.hxx"


BEGIN_NAMESPACE_ALTAIR


class String;


/*!
 * 
 */
class SubclassResponsibilityError : public Error
{
 public:
    /*!
     * 
     */
    static void signal();
};


END_NAMESPACE_ALTAIR


#endif  /* altair_SubclassResponsibilityError_hxx */
// Local Variables:
//   coding: utf-8
// End:
