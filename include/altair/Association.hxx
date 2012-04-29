#ifndef altair_Association_hxx
#define altair_Association_hxx

#include "altair/LookupKey.hxx"


BEGIN_NAMESPACE_ALTAIR


class String;


/*!
 * 
 */
class Association : public LookupKey
{
 public:
    Association(const altair::Object* const, altair::Object* const&);
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Association_hxx */
// Local Variables:
//   coding: utf-8
// End:
