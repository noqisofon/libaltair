#ifndef altair_ArgumentOutOfRangeError_hxx
#define altair_ArgumentOutOfRangeError_hxx

#include "altair/ArgumentError.hxx"


BEGIN_NAMESPACE_ALTAIR


class String;
class Magunitude;


/*!
 * 
 */
class ArgumentOutOfRangeError : public ArgumentError
{
 public:
    /*!
     * 
     */
    static void signalOn(int n, int m, int k);
    /*!
     * 
     */
    static void signalOn(const Object* const& n, const Magunitude* const& m, const Magunitude* const& k);
};


END_NAMESPACE_ALTAIR


#endif  /* altair_ArgumentOutOfRangeError_hxx */
// Local Variables:
//   coding: utf-8
// End:
