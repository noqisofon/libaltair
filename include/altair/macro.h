#ifndef altair_macro_h
#define altair_macro_h


/**
 * \def ALTAIR_GET_CLASS
 */
//#define    ALTAIR_GET_CLASS(_symbol_)     _symbol_ ## _class::getInstance()
#define    ALTAIR_GET_CLASS(_symbol_)     _symbol_ ## ::getClass()


//#define    ALTA_CLASS_OF(_symbol_)


#define    ALTAIR_CLASS_INSTANCE_OF(_symbol_)


#endif  /* altair_macro_h */
