#ifndef altair_ReadStream_hxx
#define altair_ReadStream_hxx

#include "altair/PositionableStream.hxx"


BEGIN_NAMESPACE_ALTAIR


class Collection;
class String;


/*!
 * 
 */
class ReadStream : public PositionableStream
{
 public:
    /*!
     * 
     */
    static Stream* on(Collection* const& a_collection);


    /*!
     * 
     */
    static Stream* on(Collection* const& a_collection, int start, int stop);
};


END_NAMESPACE_ALTAIR


#endif  /* altair_ReadStream_hxx */
// Local Variables:
//   coding: utf-8
// End:
