#ifndef altair_ElementNotFoundError_hxx
#define altair_ElementNotFoundError_hxx

#include "altair/NotFoundError.hxx"


BEGIN_NAMESPACE_ALTAIR


class String;


/*!
 * 
 */
class ElementNotFoundError : public NotFoundError
{
 public:
    /*!
     * 
     */
    static void signalOn(Object* const& element, const String* const& message);
};


END_NAMESPACE_ALTAIR


#endif  /* altair_ElementNotFoundError_hxx */
// Local Variables:
//   coding: utf-8
// End:
