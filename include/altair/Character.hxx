#ifndef altair_Character_hxx
#define altair_Character_hxx

#include "altair/Magunitude.hxx"


BEGIN_NAMESPACE_ALTAIR


/*!
 * 
 */
class Character : public Magunitude
{
 public:
    /*!
     * 
     */
    static Character* valueOf(int value);


    /*!
     * 
     */
    static Character* space();
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Character_hxx */
// Local Variables:
//   coding: utf-8
// End:
