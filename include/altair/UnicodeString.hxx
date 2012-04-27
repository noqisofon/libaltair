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
    Encoding* const encoding() const;


    /**
     * 
     */
    virtual ByteArray* const asByteArray() const;


    /**
     * 
     */
    virtual Symbol* const asSymbol() const;


    /**
     * 
     */
    virtual bool isUnicodeString() const { return true; }


    /**
     * 
     */
    virtual const UnicodeString* const displayUnicodeString() const { return this; }


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
