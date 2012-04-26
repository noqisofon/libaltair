#ifndef altair_Iterator_hxx
#define altair_Iterator_hxx

#include "altair/Stream.hxx"


BEGIN_NAMESPACE_ALTAIR


/*!
 * 
 */
class Iterator : public Stream
{
 public:
    /*!
     * 
     */
    static Iterator* on(const Collection* const& a_collection);

 public:
    /*!
     * 
     */
    virtual ~Iterator() {}

 public:
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Iterator_hxx */
