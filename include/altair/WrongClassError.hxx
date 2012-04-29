#ifndef altair_WrongClassError_hxx
#define altair_WrongClassError_hxx

#include "altair/Error.hxx"


BEGIN_NAMESPACE_ALTAIR


/*!
 * 
 */
class WrongClassError : public Error
{
 public:
    static Error* signalOn(const Object* const&);
    static Error* signalOn(const Object* const&, const Class* const&);
};


END_NAMESPACE_ALTAIR


#endif  /* altair_WrongClassError_hxx */
