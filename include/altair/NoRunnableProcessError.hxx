#ifndef altair_NoRunnableProcessError_hxx
#define altair_NoRunnableProcessError_hxx

#include "altair/Error.hxx"


BEGIN_NAMESPACE_ALTAIR


class String;


/*!
 * 
 */
class NoRunnableProcessError : public Error
{
 public:
    /*!
     * 
     */
    static void signal();
};


END_NAMESPACE_ALTAIR


#endif  /* altair_NoRunnableProcessError_hxx */
// Local Variables:
//   coding: utf-8
// End:
