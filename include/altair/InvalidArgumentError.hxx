#ifndef altair_InvalidArgumentError_hxx
#define altair_InvalidArgumentError_hxx

#include "altair/ArgumentError.hxx"


BEGIN_NAMESPACE_ALTAIR


class String;


/*!
 * 
 */
class InvalidArgumentError : public ArgumentError
{
 public:
    /*!
     * 
     */
    static void signalOn(const Object* const&);
};


END_NAMESPACE_ALTAIR


#endif  /* altair_InvalidArgumentError_hxx */
// Local Variables:
//   coding: utf-8
// End:
