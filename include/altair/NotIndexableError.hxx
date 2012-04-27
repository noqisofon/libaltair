#ifndef altair_NotIndexableError_hxx
#define altair_NotIndexableError_hxx

#include "altair/Error.hxx"


BEGIN_NAMESPACE_ALTAIR


/*!
 * 
 */
class NotIndexableError : public Error
{
 public:
    static Error* signalOn(const Object* const&);
};


END_NAMESPACE_ALTAIR


#endif  /* altair_NotIndexableError_hxx */
