#ifndef altair_UserInterruptError_hxx
#define altair_UserInterruptError_hxx

#include "altair/Error.hxx"


BEGIN_NAMESPACE_ALTAIR


class String;


/*!
 * 
 */
class UserInterruptError : public Error
{
 public:
    /*!
     * 
     */
    static void signal();
};


END_NAMESPACE_ALTAIR


#endif  /* altair_UserInterruptError_hxx */
// Local Variables:
//   coding: utf-8
// End:
