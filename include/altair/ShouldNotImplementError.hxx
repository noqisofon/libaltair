#ifndef altair_ShouldNotImplementError_hxx
#define altair_ShouldNotImplementError_hxx

#include "altair/Error.hxx"


BEGIN_NAMESPACE_ALTAIR


class String;


/*!
 * 
 */
class ShouldNotImplementError : public Error
{
 public:
    /*!
     * 
     */
    static void signal();
};


END_NAMESPACE_ALTAIR


#endif  /* altair_ShouldNotImplementError_hxx */
// Local Variables:
//   coding: utf-8
// End:
