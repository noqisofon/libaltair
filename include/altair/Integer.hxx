#ifndef altair_Integer_hxx
#define altair_Integer_hxx

#include "altair/Number.hxx"


BEGIN_NAMESPACE_ALTAIR


/*!
 * 
 */
class Integer : public Number
{
 public:
    static Integer* valueOf(int value);
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Integer_hxx */
// Local Variables:
//   coding: utf-8
// End:
