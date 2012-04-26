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
    String(size_t size);
    /*!
     * 
     */
    String(const char* const& cstring);

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
    virtual bool isString() const { return true; }


    /**
     * 
     */
    virtual const String* const displayString() const { return this; }


    /**
     * 
     */
    virtual void displayOn(Stream* const a_stream) const;
};


END_NAMESPACE_ALTAIR


#endif  /* altair_String_hxx */
// Local Variables:
//   coding: utf-8
// End:
