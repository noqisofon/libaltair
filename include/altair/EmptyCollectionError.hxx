#ifndef altair_EmptyCollectionError_hxx
#define altair_EmptyCollectionError_hxx

#include "altair/Error.hxx"


BEGIN_NAMESPACE_ALTAIR


class EmptyCollectionError : public Error
{
 public:
    /*!
     *
     */
    static void signalOn(const Object* const&);
};


END_NAMESPACE_ALTAIR


#endif  /* altair_EmptyCollectionError_hxx */
