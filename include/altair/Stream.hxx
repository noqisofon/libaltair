#ifndef altair_Stream_hxx
#define altair_Stream_hxx

#include "altair/Iteratable.hxx"


BEGIN_NAMESPACE_ALTAIR


/*!
 *
 */
class Stream : public Iteratable
{
 public:
    /*!
     \name accessing-reading
     */
    /*! @{ */
    /*!
     * 
     */
    virtual const String* const file() const { return NULL; }


    /*!
     * 
     */
    virtual const String* const name() const { return NULL; }


    /*!
     * 
     */
    virtual Object* const next();
    /*!
     * 
     */
    virtual Collection* const next(int an_integer);


    /*!
     * 
     */
    virtual Object* const nextInto(int an_integer, Object* const& answer, int starting_pos);


    /*!
     * 
     */
    virtual int nextPutAllOn(int an_integer, Stream* const& a_stream);


    /*!
     * 
     */
    virtual int nextAvailable(int an_integer);
    /*!
     * 
     */
    virtual int nextAvailable(int an_integer, Stream* const& a_stream);


    /*!
     * 
     */
    virtual int nextAvailable(int an_integer, Collection* const& a_collection, int startint_pos);


    /*!
     * 
     */
    virtual bool nextMatchFor(const Object* const& an_object);


    /*!
     * 
     */
    virtual OrderedCollection* const splitAt(const Object* const& an_object);


    /*!
     * 
     */
    virtual Collection* const contents();


    /*!
     * 
     */
    virtual Collection* const nextLine();


    /*!
     * 
     */
    virtual Collection* const upTo(const Object* const& an_object);


    /*!
     * 
     */
    virtual Collection* const upToAll(const Collection* const& a_collection);
    /*! @} */


    /*!
     \name accessing-writing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void nextPut(Object* const& an_object);
    /*!
     * 
     */
    virtual Object* const nextPut(int n, Object* const& an_object);


    /*!
     * 
     */
    virtual Collection* const nextPutAll(Collection* const& a_collection);


    /*!
     * 
     */
    virtual Collection* const nextPutAll(int n, Collection* const& a_collection, int start);


    /*!
     * 
     */
    virtual void nextPutAllFlush(Collection* const& a_collection);


    /*!
     * 
     */
    virtual void nextPutAllOn(Stream* const& a_stream);
    /*! @} */


    /*!
     \name testing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool atEnd() const;
    /*! @} */
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Stream_hxx */
// Local Variables:
//   coding: utf-8
// End:
