#ifndef altair_PositionableStream_hxx
#define altair_PositionableStream_hxx

#include "altair/Stream.hxx"


BEGIN_NAMESPACE_ALTAIR


class Collection;
class SequenceableCollection;
class String;


/*!
 * 
 */
class PositionableStream : public Stream
{
    typedef Stream _Super;

 public:
    /*! \name accessing-reading
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void close();


    /*!
     * 
     */
    virtual Object* next();


    /*!
     * 
     */
    virtual void nextPutAllOn(Stream* const& a_stream);


    /*!
     * 
     */
    virtual int nextAvailable(int an_integer, Stream* const& a_stream);


    /*!
     * 
     */
    virtual int nextAvailableInto(int an_integer, SequenceableCollection* const& a_collection, int starting_pos);


    /*!
     * 
     */
    virtual Object* peek() const;


    /*!
     * 
     */
    virtual bool peekFor(const Object* const& an_object) const;


    /*!
     * 
     */
    virtual SequenceableCollection* copyFrom(int start, int end) const;


    /*!
     * 
     */
    virtual SequenceableCollection* contents() const;


    /*!
     * 
     */
    virtual Stream* readStream() const;


    /*!
     * 
     */
    virtual SequenceableCollection* reverseContents() const;


    /*!
     * 
     */
    virtual SequenceableCollection* upToEnd();


    /*!
     * 
     */
    virtual SequenceableCollection* upTo(const Object* const& an_object);
    /*! @} */


    /*! \name testing
      オブジェクトの現在の状態を調べるカテゴリです。
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool atEnd() const { return ptr_ > end_ptr_; }


    /*!
     * 
     */
    virtual bool basicAtEnd() const { return ptr_ > end_ptr_; }


    /*!
     * 
     */
    virtual bool isEmpty() const { return end_ptr_ == 0; }
    /*! @} */


    /*! \name truncating
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void truncate();
    /*! @} */


    /*! \name positioning
     */
    /*! @{ */
    /*!
     * 
     */
    virtual int position() const { return ptr_; }


    /*!
     * 
     */
    virtual void position(int pos);


    /*!
     * 
     */
    virtual void basicPosition(int pos);


    /*!
     * 
     */
    virtual void reset() { position( 0 ); }


    /*!
     * 
     */
    virtual void setToEnd() { position( __STATIC_CAST(int, size()) ); }


    /*!
     * 
     */
    virtual size_t size() const { return __STATIC_CAST(size_t, end_ptr_); }


    /*!
     * 
     */
    virtual bool isPositionable() const { return true; }


    /*!
     * 
     */
    virtual void skip(int an_integer) {
        position( ALTAIR_MIN(ALTAIR_MAX(position() + an_integer, 0), end_ptr_) );
    }
    /*! @} */


    /*! \name private
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void beReadOnly() { access_ = 1; }


    /*!
     * 
     */
    virtual void beWriteOnly() { access_ = 2; }


    /*!
     * 
     */
    virtual void beReadWrite() { access_ = 1 | 2; }


    /*!
     * 
     */
    virtual const SequenceableCollection* collection() const { return collection_; }


    /*!
     * 
     */
    virtual void status(String* const a_string) const;
    /*! @} */


    /*! \name class type methods
     */
    /*! @{ */
    /*!
     *
     */
    virtual bool isExternalStream() const { return false; }


    /*!
     *
     */
    virtual Class* species() const;
    /*! @} */

 protected:
    SequenceableCollection* collection_;
    int ptr_;
    int end_ptr_;
    int access_;
};


END_NAMESPACE_ALTAIR


#endif  /* altair_PositionableStream_hxx */
// Local Variables:
//   coding: utf-8
// End:
