#ifndef altair_Object_hxx
#define altair_Object_hxx


BEGIN_NAMESPACE_ALTAIR


class Association;
class Array;
class Behavior;
class Class;
class Message;
class Collection;
class OrderedCollection;
class String;
class Stream;
class Symbol;


/**
 * 
 */
class Object
{
 public:
    /**
     * 
     */
    Object();
    /**
     * 
     */
    Object(const Object& other);


    /**
     * 
     */
    virtual ~Object();

 public:
    /*!
      \name relational operators
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool notEquals(const Object* const& an_object) const {
        return equals( an_object ) == false;
    }


    /*!
     * 
     */
    virtual bool notIdentityEquals(const Object* const& an_object) const {
        return identityEquals( an_object ) == false;
    }
    /*! @} */


    /*!
      \name testing functionality
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool isKindOf(const Class* const& a_class) const;


    /*!
     * 
     */
    virtual bool isInstanceOf(const Class* const& a_class) const;


    /*!
     * 
     */
    virtual bool respondsTo(const Symbol* const& a_symbol) const;


    /*!
     * 
     */
    virtual bool isNil() const { return false; }


    /*!
     * 
     */
    virtual bool notNil() const { return true; }


    /*!
     * 
     */
    virtual bool isCObject() const { return false; }


    /*!
     * 
     */
    virtual bool isString() const { return false; }


    /*!
     * 
     */
    virtual bool isCharacterArray() const { return false; }


    /*!
     * 
     */
    virtual bool isSymbol() const { return false; }


    /*!
     * 
     */
    virtual bool isCharacter() const { return false; }


    /*!
     * 
     */
    virtual bool isNumber() const { return false; }


    /*!
     * 
     */
    virtual bool isFloat() const { return false; }


    /*!
     * 
     */
    virtual bool isInteger() const { return false; }


    /*!
     * 
     */
    virtual bool isSmallInteger() const { return false; }


    /*!
     * 
     */
    virtual bool isNameSpace() const { return false; }


    /*!
     * 
     */
    virtual bool isClass() const { return false; }


    /*!
     * 
     */
    virtual bool isArray() const { return false; }


    /*!
     * 
     */
    virtual bool isBehavior() const { return false; }


    /*!
     * 
     */
    virtual bool isMeta() const { return isMetaClass(); }


    /*!
     * 
     */
    virtual bool isMetaClass() const { return false; }
    /*! @} */


    /*!
      \name copying
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* copy() const;


    /*!
     * 
     */
    virtual const Object& postCopy() const { return *this; }


    /*!
     * 
     */
    virtual Object* deepCopy() const;
    /*! @} */


    /*!
      \name class type methods
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Class* species() const {
        return getClass();
    }


    /*!
     * 
     */
    virtual const Object& yourself() const { return *this; }
    /*! @} */


    /*!
      \name dependents access
     */
    /*! @{ */
#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
    /*!
     * 
     */
    virtual void addDependent(Object* const& an_object);


    /*!
     * 
     */
    virtual Object* removeDependent(Object* const& an_object);


    /*!
     * 
     */
    virtual OrderedCollection* const dependants() const;
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


    /*!
     * 
     */
    virtual void release();
    /*! @} */


    /*!
      \name change and update
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void changed() {
        changed( this );
    }
    /*!
     * 
     */
    virtual void changed(Object* const& /* a_parameter */);


    /*!
     *
     */
    virtual void update(Object* const& /* a_parameter */) {}


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
    /*!
     * 
     */
    virtual void broadcast(const Symbol* const& a_symbol);
    /*!
     * 
     */
    virtual void broadcast(const Symbol* const& a_symbol, Object* const& an_object);
    /*!
     * 
     */
    virtual void broadcast(const Symbol* const& a_symbol, Object* const& arg1, Object* const& arg2);


    /*!
     * 
     */
    virtual void broadcastWithArguments(const Symbol* const& a_symbol, const Array* const& an_array);
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */
    /*! @} */


    /*!
      \name syntax shortcuts
     */
    /*! @{ */
    /*!
     * 
     */
    Association* createAssociation(Object* const& an_object) const;
    /*! @} */


    /*!
      \name printing
     */
    /*! @{ */
#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
    /*!
     * 
     */
    virtual String* const displayString() const;


    /*!
     * 
     */
    virtual void displayOn(Stream* const& a_stream) const;


    /*!
     * 
     */
    virtual void display() const;


    /*!
     * 
     */
    void displayNl() const;
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


    /*!
     * 
     */
    virtual String* printString() const;


    /*!
     * 
     */
    virtual void printOn(Stream* const& a_stream) const;


    /*!
     * 
     */
    virtual void basicPrintOn(Stream* const& a_stream) const;


    /*!
     * 
     */
    virtual void print() const;


    /*!
     * 
     */
    virtual void printNl() const;


    /*!
     * 
     */
    virtual void basicPrintNl() const;
    /*! @} */


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
    /*!
      \name storing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual String* storeString() const;


    /*!
     *
     */
    virtual void storeLiteralOn(Stream* const& a_stream) const;


    /*!
     * 
     */
    virtual void storeOn(Stream* const& a_stream) const;


    /*!
     * 
     */
    virtual void store() const;


    /*!
     * 
     */
    virtual void storeNl() const;
    /*! @} */


    /*!
      \name saving and loading
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void binaryRepresentationObject();


    /*!
     * 
     */
    virtual void postLoad() {}


    /*!
     * 
     */
    virtual void postStore() { postLoad(); }


    /*!
     * 
     */
    virtual void preLoad() {}


    /*!
     * 
     */
    virtual void reconstructOriginalObject();
    /*! @} */
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */



    /*!
      \name debugging
     */
    /*! @{ */
#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
    /*!
     * 
     */
    virtual void examine() const;
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


    /*!
     * 
     */
    virtual void inspect() const;


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
    /*!
     * 
     */
    virtual void examineOn(Stream* const& a_stream) const;
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


    /*!
     * 
     */
    virtual int validSize() const { return basicSize(); }
    /*! @} */


    /*!
      \name built ins
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Collection* allOwners() const { return NULL; }


#ifdef LT_NEAR_COMPLETE_TRANSPLANT_RATE
    /*!
     * 
     */
    virtual void changeClassTo(const Behavior* const& a_behavior);
#endif  /* def LT_NEAR_COMPLETE_TRANSPLANT_RATE */


    /*!
     * 
     */
    virtual Object* checkIndexableBounds(int index) const;
    /*!
     * 
     */
    virtual Object* checkIndexableBounds(int index, Object* (*a_block)(const Object* const&)) const;


    /*!
     * 
     */
    virtual void checkIndexableBoundsPut(int index, Object* const& object);


    /*!
     * 
     */
    virtual Object* at(int index) const {
        return checkIndexableBounds( index );
    }


    /*!
     * 
     */
    virtual Object* basicAt(int index) const {
        return checkIndexableBounds( index );
    }


    /*!
     * 
     */
    virtual void put(int index, Object* const& value) {
        checkIndexableBoundsPut( index, value );
    }


    /*!
     * 
     */
    virtual void basicPut(int index, Object* const& value) {
        checkIndexableBoundsPut( index, value );
    }


    /*!
     * 
     */
    virtual size_t size() const { return sizeof(*this); }


    /*!
     * 
     */
    virtual size_t basicSize() const { return sizeof(*this); }


    /*!
     * 
     */
    virtual Object* become(const Object* const& other_object);


    /*!
     * 
     */
    virtual Object* becomeForward(const Object* const& other_object);


    /*!
     * 
     */
    virtual Object* shallowCopy() const;


    /*!
     * 
     */
    virtual void makeFixed();


    /*!
     * 
     */
    virtual void tenure() {}


    /*!
     * 
     */
    virtual Object* instVarAt(int index) const;


    /*!
     * 
     */
    virtual void instVarPut(int index, Object* const value);


    /*!
     * 
     */
    virtual bool isReadOnly() const { return false; }


    /*!
     * 
     */
    virtual bool isUntrusted() const { return false; }


    /*!
     * 
     */
    virtual void makeReadOnly(bool a_boolean);


    /*!
     * 
     */
    virtual void makeUntrusted(bool a_boolean);


    /*!
     * 
     */
    virtual void makeWeak() {}


    /*!
     * 
     */
    virtual void makeEphemeron();


    /*!
     * 
     */
    virtual Object* asOop() const;


    /*!
     * 
     */
    int identityHash() const;


    /*!
     * 
     */
    virtual int hash() const;


    /*!
     * 
     */
    virtual Object* nextInstance() const { return NULL; }


    /*!
     * 
     */
    virtual Object* perform(const Object* const& selector_or_message_or_method) const;
    /*!
     * 
     */
    virtual Object* perform(const Object* const& selector_or_method, Object* const& arg1) const;
    /*!
     * 
     */
    virtual Object* perform(const Object* const& selector_or_method, Object* const& arg1, Object* const& arg2) const;
    /*!
     * 
     */
    virtual Object* perform(const Object* const& selector_or_method, Object* const& arg1, Object* const& arg2, Object* const& arg3) const;
    /*!
     * 
     */
    virtual Object* perform(const Object* const& selector_or_method, Object* const& arg1, Object* const& arg2, Object* const& arg3, Object* const& arg4) const;


    /*!
     * 
     */
    virtual Object* performWithArguments(const Object* const& selector_or_method, const Array* const& arguments_array) const;


    /*!
     * 
     */
    virtual bool equals(const Object* const& arg) const;


    /*!
     * 
     */
    virtual bool identityEquals(const Object* const& arg) const;


    /*!
     * 
     */
    virtual Class* getClass() const;


    /*!
     * 
     */
    virtual Object* error(const String* const& message) const;


    /*!
     * 
     */
    virtual void basicPrint() const;


    /*!
     * 
     */
    virtual Object* halt();
    /*!
     * 
     */
    virtual Object* halt(const String* const& a_string);


    /*!
     * 
     */
    virtual void mark(const Symbol* const&/* a_symbol */) {}


    /*!
     * 
     */
    virtual Object* primitiveFailed() const;


    /*!
     * 
     */
    virtual Object* shouldNotImplement() const;


    /*!
     * 
     */
    virtual Object* subclassResponsibility() const;


    /*!
     * 
     */
    virtual Object* notYetImplemented() const;
    /*! @} */


    /*!
      \name introspection
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* instVarNamed(const String* const& a_string) const;


    /*!
     * 
     */
    virtual void instVarNamedPut(const String* const& a_string, Object* const& an_object);
    /*! @} */


    /*!
      \name VM callbacks
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* doseNotUnderstand(const Message* const& message) const;


    /*!
     * 
     */
    virtual Object* badReturnError() const;


    /*!
     * 
     */
    virtual bool mustBeBoolean() const;


    /*!
     * 
     */
    virtual Object* noRunnableProcess() const;


    /*!
     * 
     */
    virtual Object* userInterrupt() const;
    /*! @} */

 protected:
    /*! \name finalization
     */
    /*! @{ */
#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
    /*!
     * 
     */
    virtual void addToBeFinalized();


    /*!
     * 
     */
    virtual void removeToBeFinalized();


    /*!
     * 
     */
    virtual void mourn() {}
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


    /*!
     * 
     */
    virtual void finalize() {}
    /*! @} */
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Object_hxx */
// Local Variables:
//   coding: utf-8
// End:
