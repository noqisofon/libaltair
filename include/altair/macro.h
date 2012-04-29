#ifndef altair_macro_h
#define altair_macro_h


/**
 * \def ALTAIR_GET_CLASS(_symbol_)
 */
#define    ALTAIR_GET_CLASS(_symbol_)              _symbol_##_class::getInstance()


#define    ALTA_CLASS_OF(_symbol_)                 _symbol_##::getClassInstance()


#define    ALTAIR_CLASS_INSTANCE_OF(_symbol_)      _symbol_##::instanceOf()


#define    ALTAIR_SYMBOL(_symbol_)                 altair::Symbol::intern( #_symbol_ )


#include "altair/cast.h"


#define    ALTAIR_TYPED_MAX(_n_, _m_, _type_)   \
    ( { _type_ __a = (_n_), __b = (_m_); __a > __b ? __a : __b; } )

#define    ALTAIR_TYPED_MIN(_n_, _m_, _type_)   \
    ( { _type_ __a = (_n_), __b = (_m_); __a < __b ? __a : __b; } )

#define    ALTAIR_TYPED_BETWEEN_AND(_a_, _n_, _m_, _type_)  \
    ( { _type_ __a = _a_, __n = _n_, __m = _m_; __n <= __a && __a < __m; } )

#define    ALTAIR_TYPED_EVEN(_n_, _type_)       \
    ( { _type_ __a = (_n_); (__a % 2) == 0; } )

#define    ALTAIR_TYPED_ODD(_n_, _type_)        \
    ( { _type_ __a = (_n_); (__a % 2) == 1; } )

#define    ALTAIR_TYPED_NEGATED(_n_, _type_)     \
    ( { _type_ __n = (_n_); __n < 0 ? __n : -__n; } )


#define    ALTAIR_MAX(_n_, _m_)                ALTAIR_TYPED_MAX(_n_, _m_, int)
#define    ALTAIR_MIN(_n_, _m_)                ALTAIR_TYPED_MIN(_n_, _m_, int)

#define    ALTAIR_EVEN(_n_)                    ALTAIR_TYPED_EVEN(_n_, int)
#define    ALTAIR_ODD(_n_)                     ALTAIR_TYPED_ODD(_n_, int)

#define    ALTAIR_BETWEEN_AND(_a_, _n_, _m_)   ALTAIR_TYPED_BETWEEN_AND(_a_, _n_, _m_, int)

#define    ALTAIR_SCRAMBLE(_n_)                (_n_)
#define    ALTAIR_NEGATED(_n_)                 ALTAIR_TYPED_NEGATED(_n_, int)

#define    ALTAIR_ISNIL(_self_)                ((_self_) == NULL)
#define    ALTAIR_NOTNIL(_self_)               ((_self_) != NULL)


#endif  /* altair_macro_h */
