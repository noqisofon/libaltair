#ifndef altair_IndexOutOfRangeError_hxx
#define altair_IndexOutOfRangeError_hxx

#include "altair/Error.hxx"


BEGIN_NAMESPACE_ALTAIR


/*!
 * 
 */
class IndexOutOfRangeError : public Error
{
 public:
    static Error* signalOn(const Object* const&, int index);
};


END_NAMESPACE_ALTAIR


#endif  /* altair_IndexOutOfRangeError_hxx */
