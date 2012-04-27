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


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
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
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


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
    virtual void put(int index, Object* const& value) {
        checkIndexableBoundsPut( index, value );
    }


    /*!
     * 
     */
    ubyte byteAt(int index) const;


    /*!
     * 
     */
    void bytePut(int index, ubyte value);


    /*!
     * 
     */
    virtual int hash() const;


    /*!
     * 
     */
    virtual void release();


    /*!
     * 
     */
    virtual void replaceFrom(int start, int stop, const String* const& a_string, int replace_start);
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

 protected:
    /*!
      \name private
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* const checkIndexableBounds(int index) const;
    /*!
     * 
     */
    virtual Object* const checkIndexableBounds(int index, Object* const (*a_block)(const Object* const&)) const;


    /*!
     * 
     */
    virtual void checkIndexableBoundsPut(int index, Object* const& object);


    /*!
     * 
     */
    virtual ubyte checkIndexableByteBounds(int index) const;
    /*!
     * 
     */
    virtual ubyte checkIndexableByteBounds(int index, ubyte (*a_block)(const Object* const&)) const;


    /*!
     * 
     */
    virtual void checkIndexableByteBoundsPut(int index, ubyte value);
    /*! @} */

 private:
    /*!
      \name private
     */
    /*! @{ */
    virtual size_t growSize() const { return size(); }
    /*! @} */

 private:
    ubyte* bytes_;
};


END_NAMESPACE_ALTAIR


#endif  /* altair_ByteArray_hxx */
// Local Variables:
//   coding: utf-8
// End:
