#ifndef altair_InvalidValueError_hxx
#define altair_InvalidValueError_hxx

#include "altair/Error.hxx"


BEGIN_NAMESPACE_ALTAIR


class InvalidValueError
{
 public:
    static Error* signalOn(const Object* const&, const char* const&);
};


END_NAMESPACE_ALTAIR


#endif  /* altair_InvalidValueError_hxx */
