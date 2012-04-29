#ifndef altair_NotYetImplementedError_hxx
#define altair_NotYetImplementedError_hxx

#include "altair/Error.hxx"


BEGIN_NAMESPACE_ALTAIR


class String;


/*!
 * 
 */
class NotYetImplementedError : public Error
{
 public:
    /*!
     * 
     */
    static void signal();
};


END_NAMESPACE_ALTAIR


#endif  /* altair_NotYetImplementedError_hxx */
// Local Variables:
//   coding: utf-8
// End:
