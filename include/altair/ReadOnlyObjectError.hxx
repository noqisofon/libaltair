#ifndef altair_ReadOnlyObjectError_hxx
#define altair_ReadOnlyObjectError_hxx

#include "altair/Error.hxx"


BEGIN_NAMESPACE_ALTAIR


/*!
 * 
 */
class ReadOnlyObjectError : public Error
{
 public:
    static Error* signalOn(const Object* const&);
    static Error* signal();
};


END_NAMESPACE_ALTAIR


#endif  /* altair_ReadOnlyObjectError_hxx */
