#ifndef altair_Stream_hxx
#define altair_Stream_hxx

#include "altair/Iteratable.hxx"


BEGIN_NAMESPACE_ALTAIR


class SequenceableCollection;
class OrderedCollection;
class String;


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
    virtual SequenceableCollection* const next(int an_integer);


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
    virtual int nextAvailableInto(int an_integer, SequenceableCollection* const& a_collection, int startint_pos);


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
    virtual SequenceableCollection* const contents();


    /*!
     * 
     */
    virtual SequenceableCollection* const nextLine();


    /*!
     * 
     */
    virtual SequenceableCollection* const upTo(const Object* const& an_object);


    /*!
     * 
     */
    virtual SequenceableCollection* const upToAll(const SequenceableCollection* const& a_collection);
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
    virtual void nextPut(char ch);
    /*!
     * 
     */
    virtual Object* const nextPut(int n, Object* const& an_object);
    /*!
     * 
     */
    virtual Object* const  nextPut(int n, char ch);


    /*!
     * 
     */
    virtual SequenceableCollection* const nextPutAll(SequenceableCollection* const& a_collection);
    /*!
     * 
     */
    virtual SequenceableCollection* const nextPutAll(const char* const& cstring);
    /*!
     * 
     */
    virtual SequenceableCollection* const nextPutAll(int n, SequenceableCollection* const& a_collection, int start);


    /*!
     * 
     */
    virtual void nextPutAllFlush(SequenceableCollection* const& a_collection);


    /*!
     * 
     */
    virtual void nextPutAllOn(Stream* const& a_stream);
    /*! @} */


    /*! \name testing
      
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool atEnd() const;
    /*! @} */


    /*! \name character writing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void space();
    /*! @} */


    /*! \name polymorphism
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void close() {}


    /*!
     * 
     */
    virtual Object* const pastEnd();


    /*!
     * 
     */
    virtual void flush() {}
    /*! @} */
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Stream_hxx */
// Local Variables:
//   coding: utf-8
// End:
