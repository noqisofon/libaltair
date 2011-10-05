#ifndef altair_ObjectMemory_hxx
#define altair_ObjectMemory_hxx

#ifdef HAVE_CONFIG_H
#   include "config.h"
#endif  /* HAVE_CONFIG_H */


BEGIN_NAMESPACE_ALTAIR


class Symbol;


/**
 * 
 */
class ObjectMemory : public Object
{
 public:
    /**
     * 
     */
    static void changed(Symbol* const& a_symbol);


    /**
     * \ingroup initialization
     */
    static void initialize();


    /**
     * 
     */
    static ObjectMemory* const current();
};


END_NAMESPACE_ALTAIR


#endif  /* altair_ObjectMemory_hxx */
// Local Variables:
//   coding: utf-8
// End:
