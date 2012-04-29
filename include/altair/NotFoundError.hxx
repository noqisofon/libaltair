#ifndef altair_NotFoundError_hxx
#define altair_NotFoundError_hxx

#include "altair/Error.hxx"


BEGIN_NAMESPACE_ALTAIR


/*!
 *
 */
class NotFoundError : public Error
{
 public:
    static Error* signalOn(const Object* const&, const char* const&);
};


END_NAMESPACE_ALTAIR


#endif  /* altair_NotFoundError_hxx */
// Local Variables:
//   coding: utf-8
// End:
