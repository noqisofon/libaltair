#ifndef altair_UnicodeString_hxx
#define altair_UnicodeString_hxx

#include "altair/CharacterArray.hxx"


BEGIN_NAMESPACE_ALTAIR


class Encoding;
class ByteArray;
class Symbol;
class Stream;


/*!
 * 
 */
class UnicodeString : public CharacterArray
{
 public:
    /*!
     * 
     */
    UnicodeString(size_t size, char ch = '\0');
    /*!
     * 
     */
    UnicodeString(const char* const& cstring);

 public:
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


    /**
     * 
     */
    virtual bool isUnicodeString() const { return true; }


    /**
     * 
     */
    virtual const String* displayString() const;


    /**
     * 
     */
    virtual void displayOn(Stream* const a_stream) const;
};


END_NAMESPACE_ALTAIR


#endif  /* altair_UnicodeString_hxx */
// Local Variables:
//   coding: utf-8
// End:
