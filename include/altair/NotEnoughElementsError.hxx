#ifndef altair_NotEnoughElementsError_hxx
#define altair_NotEnoughElementsError_hxx

#include "altair/Error.hxx"


BEGIN_NAMESPACE_ALTAIR


class String;


/*!
 * 
 */
class NotEnoughElementsError : public Error
{
 public:
    static Error* signalOn(int);
};


END_NAMESPACE_ALTAIR


#endif  /* altair_NotEnoughElementsError_hxx */
// Local Variables:
//   coding: utf-8
// End:
