#ifndef altair_BadReturnError_hxx
#define altair_BadReturnError_hxx

#include "altair/Error.hxx"


BEGIN_NAMESPACE_ALTAIR


class String;


/*!
 * 
 */
class BadReturnError : public Error
{
 public:
    /*!
     * 
     */
    static void signal();
};


END_NAMESPACE_ALTAIR


#endif  /* altair_BadReturnError_hxx */
// Local Variables:
//   coding: utf-8
// End:
