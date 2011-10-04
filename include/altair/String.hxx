

class String : public CharacterArray
{
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
    virtual String* const displayString() const { return this; }


    /**
     * 
     */
    virtual void displayOn(Stream* const a_stream) const;
};
// Local Variables:
//   coding: utf-8
// End:
