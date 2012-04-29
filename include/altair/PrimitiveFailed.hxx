#ifndef altair_PrimitiveFailed_hxx
#define altair_PrimitiveFailed_hxx

#include "altair/Error.hxx"


BEGIN_NAMESPACE_ALTAIR


class String;


/*!
 * 
 */
class PrimitiveFailed : public Error
{
 public:
    /*!
     * 
     */
    static void signal();
};


END_NAMESPACE_ALTAIR


#endif  /* altair_PrimitiveFailed_hxx */
// Local Variables:
//   coding: utf-8
// End:
