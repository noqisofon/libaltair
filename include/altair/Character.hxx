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
    static Class* getCurrentClass();


    /*!
     * 
     */
    static Character* valueOf(int value);


    /*!
     * 
     */
    static Character* cr();


    /*!
     * 
     */
    static Character* tab();


    /*!
     * 
     */
    static Character* space();


    /*!
     * 
     */
    static Character* nl();
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Character_hxx */
// Local Variables:
//   coding: utf-8
// End:
