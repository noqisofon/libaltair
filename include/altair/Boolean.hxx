#ifndef altair_Boolean_hxx
#define altair_Boolean_hxx

#include "altair/Magunitude.hxx"


BEGIN_NAMESPACE_ALTAIR


class Class;


class Boolean : public Magunitude
{
 public:
    static Boolean* valueOf(int value);
    static Class* getCurrentClass();
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Boolean_hxx */
