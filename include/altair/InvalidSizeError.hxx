#ifndef altair_InvalidSizeError_hxx
#define altair_InvalidSizeError_hxx

#include "altair/Error.hxx"


BEGIN_NAMESPACE_ALTAIR


class String;


/*!
 * 
 */
class InvalidSizeError : public Error
{
 public:
    /*!
     * 
     */
    static Error* signalOn(const Collection* const& a_collection);
};


END_NAMESPACE_ALTAIR


#endif  /* altair_InvalidSizeError_hxx */
// Local Variables:
//   coding: utf-8
// End:
