#ifndef altair_ByteArray_hxx
#define altair_ByteArray_hxx

#include "altair/ArrayedCollection.hxx"


BEGIN_NAMESPACE_ALTAIR


class String;
class UnicodeString;


/*!
 * 
 */
class ByteArray : public ArrayedCollection
{
    typedef ArrayedCollection _Super;

 public:
    /*!
     * 
     */
    explicit ByteArray(size_t size = 4);
    /*!
     * 
     */
    ByteArray(const ByteArray& other);


    /*!
     * 
     */
    virtual ~ByteArray();

 public:
    /*!
      \name converting
     */
    /*! @{ */
    /*!
     * 
     */
    virtual String* const asString() const;


    /*!
     * 
     */
    virtual UnicodeString* const asUnicodeString() const;
    /*! @} */


    /*!
      \name storing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool isLiteralObject() const {
        return !isReadOnly();
    }


    /*!
     * 
     */
    virtual void storeLiteralOn(Stream* const& a_stream);


    /*!
     * 
     */
    virtual void storeOn(Stream* const& a_stream);
    /*! @} */


    /*!
      \name built ins
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* const at(int an_index, Object* const (*a_block)(const Object* const&)) const;


    /*!
     * 
     */
    ubyte byteAt(int index) const;


    /*!
     * 
     */
    ubyte bytePut(int index, ubyte value) const;


    /*!
     * 
     */
    virtual int hash() const;


    /*!
     * 
     */
    virtual Collection* const replaceFrom(int start, int stop, const String* const& a_string, int replace_start);
    /*! @} */


    /*!
      \name basic
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool equals(const Collection* const& a_collection) const;


    /*!
     * 
     */
    virtual int indexOf(Object* const& an_element, int an_index) const;
    /*!
     * 
     */
    virtual int indexOf(Object* const& an_element, int an_index, int (*a_block)(const Object* const&)) const;
    /*! @} */

 private:
    /*!
      \name private
     */
    /*! @{ */
    size_t growSize() const { return size(); }
    /*! @} */

 private:
    ubyte* bytes_;
    size_t tally_;
};


END_NAMESPACE_ALTAIR


#endif  /* altair_ByteArray_hxx */
