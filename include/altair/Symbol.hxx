#ifndef altair_Symbol_hxx
#define altair_Symbol_hxx

#include "altair/String.hxx"


BEGIN_NAMESPACE_ALTAIR


/*!
 *
 */
class Symbol : public String
{
 public:
    static Symbol* intern(const char* const& cstring);
    static Symbol* intern(const String* const& a_string);
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Symbol_hxx */
// Local Variables:
//   coding: utf-8
// End:
