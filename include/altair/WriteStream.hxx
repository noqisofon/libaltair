#ifndef altair_WriteStream_hxx
#define altair_WriteStream_hxx

#include "altair/PositionableStream.hxx"


BEGIN_NAMESPACE_ALTAIR


class Collection;
class String;


/*!
 * 
 */
class WriteStream : public PositionableStream
{
 public:
    /*!
     * 
     */
    static Stream* on(Collection* const& a_collection);
};


END_NAMESPACE_ALTAIR


#endif  /* altair_WriteStream_hxx */
// Local Variables:
//   coding: utf-8
// End:
