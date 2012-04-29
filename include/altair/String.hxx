#ifndef altair_String_hxx
#define altair_String_hxx

#include "altair/CharacterArray.hxx"


BEGIN_NAMESPACE_ALTAIR


class Encoding;
class ByteArray;
class Symbol;
class Stream;


/*!
 * 
 */
class String : public CharacterArray
{
 public:
    /*!
     * 
     */
    String();
    /*!
     * 
     */
    String(size_t size, char ch = '\0');
    /*!
     * 
     */
    String(const char* const& cstring);

 public:
    /*! \name converting
     */
    /*! @{ */
    /**
     * 
     */
    Encoding* encoding() const;


    /**
     * 
     */
    virtual ByteArray* asByteArray() const;


    /**
     * 
     */
    virtual Symbol* asSymbol() const;


    /*!
     * 
     */
    virtual String* asString() const;
    /*! @} */


    /**
     * 
     */
    virtual bool isString() const { return true; }


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
    /**
     * 
     */
    virtual const String* displayString() const { return this; }


    /**
     * 
     */
    virtual void displayOn(Stream* const a_stream) const;
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */
};


END_NAMESPACE_ALTAIR


#endif  /* altair_String_hxx */
// Local Variables:
//   coding: utf-8
// End:
