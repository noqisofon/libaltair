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
    virtual const String* file() const { return NULL; }


    /*!
     * 
     */
    virtual const String* name() const { return NULL; }


    /*!
     * 
     */
    virtual Object* next();
    /*!
     * 
     */
    virtual SequenceableCollection* next(int an_integer);


    /*!
     * 
     */
    virtual Object* nextInto(int an_integer, Object* const& answer, int starting_pos);


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
    virtual OrderedCollection* splitAt(const Object* const& an_object);


    /*!
     * 
     */
    virtual SequenceableCollection* contents();


    /*!
     * 
     */
    virtual SequenceableCollection* nextLine();


    /*!
     * 
     */
    virtual SequenceableCollection* upTo(const Object* const& an_object);


    /*!
     * 
     */
    virtual SequenceableCollection* upToAll(const SequenceableCollection* const& a_collection);
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
    virtual Object* nextPut(int n, Object* const& an_object);
    /*!
     * 
     */
    virtual Object*  nextPut(int n, char ch);


    /*!
     * 
     */
    virtual SequenceableCollection* nextPutAll(SequenceableCollection* const& a_collection);
    /*!
     * 
     */
    virtual SequenceableCollection* nextPutAll(const char* const& cstring);
    /*!
     * 
     */
    virtual SequenceableCollection* nextPutAll(int n, SequenceableCollection* const& a_collection, int start);


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
    virtual Object* pastEnd();


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
