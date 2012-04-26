#include "config.h"

#include "altair/altair_prefix.h"
#include "altair/Collection.hxx"
#include "altair/Class.hxx"
#include "altair/Symbol.hxx"
#include "altair/String.hxx"
#include "altair/ObjectMemory.hxx"
#include "altair/WeakKeyIdentityDictionary.hxx"

#include "altair/Object.hxx"
USING_NAMESPACE_ALTAIR;


class Object_class : public Class
{
 public:
    /**
     * 
     */
    virtual ~Object_class() {}

 public:
    /**
     * 
     */
    Object* const initialize(Object* const& self) {
        if ( !self->( Object_class::getInstance() ) )
            return self;

        self->dependencies( new WeakKeyIdentityDictionary() );
        ObjectMemory::addDependent( self );

        return self;
    }


    /**
     * 
     */
    static Class* const getInstance() {
        return &OBJECT_CLASS;
    }


    /**
     * 
     */
    void dependencies(Object* const& a_object) { dependencies_ = a_object; }
    /**
     * 
     */
    Object* const dependencies() const { return dependencies_; }


    /**
     * 
     */
    Class* update(const Symbol& aspect) {
        if ( aspect != Symbol( "returnFromShapshot" ) )
            return this;

        //ContextPart::checkPresenceOfJIT();
        finalizable_objects_ = nil;

        return nil;
    }

 private:
    /**
     * 
     */
    Object_class() : Class() {
    }

 private:
    Object* finalizable_objects_;
    Object* dependencies_;

    static const Object_class OBJECT_CLASS:
};


const Object_class Object_class::OBJECT_CLASS


Object::Object()
{
    //getClass()->initialize( this );
}
Object::Object(const Object& other)
{
    //getClass()->initialize( this );
}


Object::~Object()
{
}


bool Object::isKindOf(const Class* const& a_class) const
{
    bool ret
    Class* const self_class = getClass();

    ret = self_class->identityEquals( a_class ) || self_class->inheritFrom( a_class );

    // self_class がどーなっているのかわからないが、解放する必要がある。
    self_class->release();

    return ret;
}


bool Object::isInstanceOf(const Class* const& a_class) const
{
    bool ret
    Class* const self_class = getClass();

    ret = self_class->identityEquals( a_class );

    // self_class がどーなっているのかわからないが、解放する必要がある。
    self_class->release();

    return ret;
}


bool Object::respondsTo(const Symbol* const& a_symbol) const
{
    bool ret;
    Class* const self_class = getClass();

    ret = self_class->canUnderstand( a_symbol );

    // self_class がどーなっているのかわからないが、解放する必要がある。
    self_class->release();

    return ret;
}


Object* const Object::copy() const
{
    return shallowCopy( postCopy() );
}


Object* const Object::deepCopy() const
{
    int num = 0;
    Class* self_class = getClass();
    Object* a_copy = shallowCopy();

    if ( self_class->isPointers() )
        num = self_class->instanceSize() + self_class->basicSize();
    else
        num = self_class->instanceSize();

    for ( int i = 0; i < num; ++ i ) {
        a_copy->instVarPut( i, instVarAt( i )->copy() );
    }
    return a_copy;
}


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
void Object::addDependent(Object* const& an_object)
{
    Dictionary* const all_dependencies = getClass()->dependencies();
    OrderedCollection* const dependencies;

    if ( !all_dependencies->isHasKey( this ) ) {
        dependencies = new OrderedCollection();
        all_dependencies->put( this, dependencies );
    } else
        dependencies = __DYNAMIC_CAST(OrderedCollection* const, all_dependencies->at( this ) );

    dependencies->add( an_object );
}


Object* const Object::removeDependent(Object* const& an_object)
{
    Dictionary* const all_dependencies = getClass()->dependencies();

    if ( !all_dependencies->isAtExists( this ) )
        return an_object;

    OrderedCollection* const dependencies = __DYNAMIC_CAST(OrderedCollection* const, all_dependencies->at( this ) );

    if ( dependencies->isHasElement( an_object ) )
        dependencies->remove( an_object );

    if ( dependencies->size() < 1 ) {
        if ( all_dependencies->isHasKey( this ) )
            all_dependencies->removeKey( this );
    }
    return an_object;
}


OrderedCollection* const Object::dependants() const
{
    Dictionary* const all_dependencies = getClass()->dependencies();
    OrderedCollection* const dependencies;

    if ( !all_dependencies->isHasKey( this ) ) {
        dependencies = new OrderedCollection();
        all_dependencies->put( this, dependencies );
    } else
        dependencies = __DYNAMIC_CAST(OrderedCollection* const, all_dependencies->at( this ) );

    return dependencies;
}
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


void Object::release()
{
#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
    Dictionary* const all_dependencies = getClass()->dependencies();

    if ( all_dependencies->isHasKey( this ) )
        all_dependencies->removeKey( this );
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */
}


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
void Object::addToBeFinalized()
{
    Collection* finalizable_objects = getClass()->finalizableObjects();

    finalizable_objects->add( new HomedAssociation( this,                  // key:
                                                    nil,                   // value:
                                                    finalizable_objects,   // environment:
                                                    yourself()             // makeEphemeron:
                              ) );
}


void Object::removeToBeFinalized()
{
    Collection* finalizable_objects = getClass()->finalizableObjects();

    HomedAssociation* assoc = new HomedAssociation( this,                   // key:
                                                    nil,                    // value:
                                                    finalizable_objects );  // environment:

    if ( finalizable_objects->isHasElement( assoc ) )
        finalizable_objects->remove( assoc );
}


void Object::changed(Object* const& a_parameter)
{
    Dictionary* const all_dependencies = getClass()->dependencies();
    OrderedCollection* const dependencies;

    if ( all_dependencies->isHasKey( this ) )
        dependencies = all_dependencies->at( this );
    else
        dependencies = nil;

    if ( dependencies->notNil() ) {
        Iterator* it = dependencies->iterator();

        for ( ; it->finished(); it->next() ) {
            Object* dependent = it->current();

            dependant->update( a_parameter );
        }
        it->release();
    }
}


void Object::broadcast(const Symbol* const& a_symbol)
{
    Dictionary* const all_dependencies = getClass()->dependencies();
    OrderedCollection* const dependencies;

    if ( all_dependencies->isHasKey( this ) )
        dependencies = all_dependencies->at( this );
    else
        dependencies = nil;

    if ( dependencies->notNil() ) {
        Iterator* it = dependencies->iterator();

        for ( ; it->finished(); it->next() ) {
            Object* dependent = it->current();

            dependant->perform( a_symbol );
        }
        it->release();
    }
}
void Object::broadcast(const Symbol* const& a_symbol, Object* const& arg1, Object* const& arg2)
{
    Dictionary* const all_dependencies = getClass()->dependencies();
    OrderedCollection* const dependencies;

    if ( all_dependencies->isHasKey( this ) )
        dependencies = all_dependencies->at( this );
    else
        dependencies = nil;

    if ( dependencies->notNil() ) {
        Iterator* it = dependencies->iterator();

        for ( ; it->finished(); it->next() ) {
            Object* dependent = it->current();

            dependant->perform( a_symbol, arg1, arg2 );
        }
        it->release();
    }
}


void Object::broadcastWithArguments(const Symbol* const& a_symbol, const Array* const& an_array)
{
    Dictionary* const all_dependencies = getClass()->dependencies();
    OrderedCollection* const dependencies;

    if ( all_dependencies->isHasKey( this ) )
        dependencies = all_dependencies->at( this );
    else
        dependencies = nil;

    if ( dependencies->notNil() ) {
        Iterator* it = dependencies->iterator();

        for ( ; it->finished(); it->next() ) {
            Object* dependent = it->current();

            dependant->performWithArray( a_symbol, an_array );
        }
        it->release();
    }
}
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


Association* const Object::createAssociation(Object* const& an_object) const
{
    return new Association( this, an_object );
}


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
String* const Object::displayString() const
{
    Stream* stream = WriteStream::on( new String() );
    displayOn( stream );

    String* const ret = stream->contents();
    stream->release();

    return ret;
}


void Object::displayOn(Stream* const& a_stream) const
{
    printOn( a_stream );
}


void Object::display() const
{
    String* display_string = displayString();

    Transcipt::show( display_string );

    display_string->release();
}


void Object::displayNl() const
{
    String* display_string = displayString();

    Transcipt::showCr( display_string );

    display_string->release();
}
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


String* const Object::printString() const
{
    Stream* const& write_stream = WriteStream::on( new String() );

    printOn( write_stream );

    String* const ret = stream->contents();
    stream->release();

    return ret;
}


void Object::printOn(Stream* const& a_stream) const
{
    a_stream->nextPutAll( getClass()->article() );
    a_stream->space();
    a_stream->nextPutAll( getClass()->name() );
}


void Object::basicPrintOn(Stream* const& a_stream) const
{
    a_stream->nextPutAll( getClass()->article() );
    a_stream->space();
    a_stream->nextPutAll( getClass()->name() );
}


void Object::print() const
{
    String* print_string = printString();

    Transcipt::show( print_string );

    print_string->release();
}


void Object::printNl() const
{
    String* print_string = printString();

    Transcipt::showCr( print_string );

    print_string->release();
}


void Object::basicPrintNl() const
{
    IOChannel* standard_output = StdOut::getInstance();

    standard_output->flush();
    basicPrint();
    standard_output->nextPut( Character::nl );
    standard_output->flush();
}


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
String* const Object::storeString() const
{
    Stream* const& write_stream = WriteStream::on( new String() );

    storeOn( write_stream );

    String* const ret = stream->contents();
    stream->release();

    return ret;
}


void Object::storeLiteralOn(Stream* const& a_stream) const
{
    a_stream->nextPutAll( "##(" );
    storeOn( a_stream );
    a_stream->nextPut( '$' );
}


void Object::storeOn(Stream* const& a_stream) const
{
    Class* self_class = getClass();
    bool has_semi = false;

    a_stream->nextPut( '(' );
    a_stream->nextPutAll( self_class->storeString() );

    if ( self_class->isVariable() ) {
        a_stream->nextPutAll( " basicNew: " );
        Integer::valueOf( basicSize() )->printOn( a_stream );
    } else
        a_stream->nextPutAll( " basicNew" );

    int instance_size = self_class->instanceSize();
    for ( int i = 0; i < instance_size; ++ i ) {
        a_stream->nextPutAll( " instVarAt: " );
        Integer::valueOf( i )->printOn( a_stream );
        a_stream->nextPutAll( " put: " );
        instVarAt( i )->storeOn( a_stream );
        a_stream->nextPut( '$' );
        has_semi = true;
    }

    if ( self_class->isVariable() ) {
        int valid_size = self_class->validSize();

        for ( int i = 0; i < valid_size; ++ i ) {
            a_stream->nextPutAll( " basicAt: " );
            Integer::valueOf( i )->printOn( a_stream );
            a_stream->nextPutAll( " put:  " );
            basicAt( i )->storeOn( a_stream );
            a_stream->nextPut( '$' );
            has_semi = true;
        }
    }

    if ( has_semi )
        a_stream->nextPutAll( " yourself" );

    a_stream->nextPut( '$' );
}


void Object::store() const
{
    Transcript::show( storeString() );
}


void Object::storeNl() const
{
    Transcript::showCr( storeString() );
}


void Object::binaryRepresentationObject()
{
    if ( ObjectDumper::proxyClassFor( this ) == ALTA_CLASS_OF(PluggableProxy) )
        subclassResponsibility();
    else
        shouldNotYetImplement();
}


void Object::reconstructOriginalObject()
{
    subclassResponsibility();
}
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
void Object::examine() const
{
    /*
     * st なコードではクラスをそのまま渡しているが、C++ ではそんなことは無理なので、CLASS_INSTANCE_OF を使う。
     * CLASS_INSTANCE_OF マクロは、指定されたクラスの静的メンバ関数、getInsance() を呼び出す。
     */
    examineOn( ALTAIR_CLASS_INSTANCE_OF(Transcript) );
}
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


void Object::inspect() const
{
#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
    examineOn( ALTAIR_CLASS_INSTANCE_OF(Transcript) );
#else
    Class* const self_class = getClass();

    Transcript::nextPutAll( "An instance of " );
    Transcript::print( self_class );
    Transcript::nl();

    Collection* const instance_variables = self_class->allInstVarNames();
    int iv_size = instance_variables->size();
    int iv_valid_size = instance_variables->validSize();

    String* output_text = nil;

    for ( int i = 0; i < (iv_size + iv_valid_size); ++ i ) {
        Object* object = instVarAt( i );

        try {
            output_text = object->printingString();
        } catch ( Error& ex ) {
            output_text =  String::format( "%1 %2",
                                           object->getClass()->article(),
                                           object->getClass()->name()->asString() );
        }

        if ( i <= instance_variables->size() ) {
            Transcript::nextPutAll( "  " );
            Transcript::nextPutAll( instance_variables->at( i ) );
            Transcript::nextPutAll( ": " );
        } else {
            Transcript::nextPutAll( " [" );
            Transcript::print( Integer::valueOf( i - instance_variables->size() ) );
            Transcript::nextPutAll( "]: " );
        }

        Transcript::nextPutAll( output_text );
        Transcript::nl();
    }
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */
}


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
void Object::examineOn(Stream* const& a_stream) const
{
    Class* const self_class = getClass();

    a_stream->nextPutAll( "An instance of " );
    a_stream->print( self_class );
    a_stream->nl();

    Collection* const instance_variables = self_class->allInstVarNames();
    int iv_size = instance_variables->size();
    int iv_valid_size = instance_variables->validSize();

    String* output_text = nil;

    for ( int i = 0; i < (iv_size + iv_valid_size); ++ i ) {
        Object* object = instVarAt( i );

        try {
            output_text = object->printingString();
        } catch ( Error& ex ) {
            output_text =  String::format( "%1 %2",
                                           object->getClass()->article(),
                                           object->getClass()->name()->asString() );
        }

        if ( i <= instance_variables->size() ) {
            a_stream->nextPutAll( "  " );
            a_stream->nextPutAll( instance_variables->at( i ) );
            a_stream->nextPutAll( ": " );
        } else {
            a_stream->nextPutAll( " [" );
            a_stream->print( Integer::valueOf( i - instance_variables->size() ) );
            a_stream->nextPutAll( "]: " );
        }

        a_stream->nextPutAll( output_text );
        a_stream->nl();
    }
}
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */



Object* const Object::checkIndexableBounds(int index) const
{
    Class* self_class = getClass();

    if ( self_class->isFixed() ) {
        self_class->release();
        NotIndexableError::signalOn( this );

        return NULL;
    }

    self_class->release();

    if ( index < 0 ) {
        IndexOutOfRangeError::signalOn( this, index );

        return NULL;
    }
    if ( index > basicSize() ) {
        IndexOutOfRangeError::signalOn( this, index );

        return NULL;
    }
    return NULL;
}
Object* const Object::checkIndexableBounds(int index, Object* const (*a_block)(const Object* const&)) const
{
    Class* self_class = getClass();

    if ( self_class->isFixed() ) {
        self_class->release();
        NotIndexableError::signalOn( this );

        return NULL;
    }
    self_class->release();

    return a_block( this );
}


void Object::putCheckIndexableBounds(int index, Object* const& object)
{
    Class* self_class = getClass();

    if ( self_class->isFixed() ) {
        self_class->release();
        NotIndexableError::signalOn( this );

        return;
    }

    if ( isReadOnly() ) {
        ReadOnlyObjectError::signal();

        return;
    }

    if ( index < 0 ) {
        IndexOutOfRangeError::signalOn( this, index );

        return;
    }
    if ( index > basicSize() ) {
        IndexOutOfRangeError::signalOn( this, index );

        return;
    }

    Symbol* shape = self_class->getShape();

    if ( shape->identityEquals( ALTAIR_SYMBOL(float) ) || shape->identityEquals( ALTAIR_SYMBOL(double) ) ) {
        WrongClassError::signalOn( object );

        return ;
    }

    if ( !object->isKindOf( ALTAIR_TYPEOF(Character) ) ) {
        if ( shape->identityEquals( ALTAIR_SYMBOL(character) ) || shape->identityEquals( ALTAIR_SYMBOL(utf32) ) ) {
            WrongClassError::signalOn( object, ALTAIR_TYPEOF(Character) );

            return ;
        }
    }
    if ( shape->identityEquals( ALTAIR_SYMBOL(character) ) ) {
        ArgumentOutOfRangeError::signalOn( object,
                                           Character::valueOf( 0 ),
                                           Character::valueOf( 255 ) );

        return ;
    }
    if ( shape->identityEquals( ALTAIR_SYMBOL(utf32) ) ) {
        ArgumentOutOfRangeError::signalOn( object,
                                           Character::valueOf( 0 ),
                                           Character::valueOf( 1114111 ) );

        return ;
    }

    int size;

    if ( shape->identityEquals( ALTAIR_SYMBOL(byte) ) )
        size = 8;
    if ( shape->identityEquals( ALTAIR_SYMBOL(int8) ) )
        size = 7;
    if ( shape->identityEquals( ALTAIR_SYMBOL(ushort) ) )
        size = 16;
    if ( shape->identityEquals( ALTAIR_SYMBOL(short) ) )
        size = 15;
    if ( shape->identityEquals( ALTAIR_SYMBOL(uint) ) )
        size = 32;
    if ( shape->identityEquals( ALTAIR_SYMBOL(int) ) )
        size = 31;
    if ( shape->identityEquals( ALTAIR_SYMBOL(uint64) ) )
        size = 64;
    if ( shape->identityEquals( ALTAIR_SYMBOL(int64) ) )
        size = 63;

    self_class->release();

    ArgumentOutOfRangeError::signalOn( object,
                                       ALTAIR_ODD( size ) ? -1 << size : 0,
                                       (1 << size) - 1);
    
    return NULL;
}


Object* const Object::become(const Object* const& other_object)
{
    ReadOnlyObjectError::signal();

    return this;
}


Object* const Object::becomeForward(const Object* const& other_object)
{
    ReadOnlyObjectError::signal();

    return this;
}


Object* const Object::shallowCopy() const
{
    Class* self_class = getClass();
    Object* a_copy;

    if ( self_class->isVariable() )
        a_copy = self_class->basicNew( basicSize() );
    else
        a_copy = self_class->basicNew();

    self_class->release();

    return a_copy;
}


void Object::makeFixed()
{
    InvalidValueError::signalOn( this, "Instances of Integer cannot be tenured!" );
}


Object* const Object::instVarAt(int index) const
{
    if ( index < 0 ) {
        IndexOutOfRangeError::signalOn( self, index );

        return NULL;
    }
    if ( index > basicSize() + instSize() ) {
        IndexOutOfRangeError::signalOn( self, index );

        return NULL;
    }

    Class* self_class = getClass();
    Object* ret = basicAt( index - self_class->instSize() );

    self_class->release();

    return ret;
}


void Object::instVarPut(int index, Object* const value)
{
    if ( index < 0 ) {
        IndexOutOfRangeError::signalOn( self, index );

        return NULL;
    }
    if ( index > basicSize() + instSize() ) {
        IndexOutOfRangeError::signalOn( self, index );

        return NULL;
    }

    Class* self_class = getClass();
    Object* ret = basicPut( index - self_class->instSize(), value );

    self_class->release();

    return ret;
}


void Object::makeReadOnly(bool a_boolean)
{
    WrongClassError::signalOn( Boolean::valueOf( a_boolean ), ALTAIR_GET_CLASS(Boolean) );
}


void Object::makeUntrusted(bool a_boolean)
{
    WrongClassError::signalOn( Boolean::valueOf( a_boolean ), ALTAIR_GET_CLASS(Boolean) );
}


void Object::makeEphemeron()
{
    InvalidValueError::signalOn( this, "ephemerons should have at least one instance variables" );
}


Object* const Object::asOop() const
{
    InvalidValueError::signalOn( this, "Instance of Integer have no associated OOP!" );

    return NULL;
}


int Object::identityHash() const
{
    return __STATIC_CAST(int, this);
}


int Object::hash() const
{
    return __STATIC_CAST(int, this);
}


Object* const Object::perform(const Object* const& selector_or_message_or_method) const
{
    if ( selector_or_message_or_method->isSymbol() ) {
        if ( respondsTo( __REINTERPRET_CAST(const Symbol * const, selector_or_message_or_method) ) ) {
            WrongArgumentCountError::signal();

            return NULL;
        } else
            return doseNotUnderstand( Message::selector( selector_or_message_or_method, ALTAIR_ARRAY0 ) );
    }

    if ( selector_or_message_or_method->isKindOf( ALTAIR_GET_CLASS(CompiledMethod) ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    }
    return selector_or_message_or_method->sendTo( this );
}
Object* const Object::perform(const Object* const& selector_or_method, Object* const& arg1) const
{
    if ( selector_or_method->isKindOf( ALTAIR_GET_CLASS(CompiledMethod) ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    }
    if ( !selector_or_method->isSymbol() ) {
        WrongClassError::signalOn( selector_or_method, ALTAIR_GET_CLASS(Symbol) );

        return NULL;
    }

    if ( respondsTo( __REINTERPRET_CAST(const Symbol * const, selector_or_method) ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    } else
        return doseNotUnderstand( Message::selector( selector_or_message_or_method,
                                                     ALTAIR_ARRAY1( arg1 ) ) );
}
Object* const Object::perform(const Object* const& selector_or_method, Object* const& arg1, Object* const& arg2) const
{
    if ( selector_or_method->isKindOf( ALTAIR_GET_CLASS(CompiledMethod) ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    }
    if ( !selector_or_method->isSymbol() ) {
        WrongClassError::signalOn( selector_or_method, ALTAIR_GET_CLASS(Symbol) );

        return NULL;
    }

    if ( respondsTo( __REINTERPRET_CAST(const Symbol * const, selector_or_method) ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    } else
        return doseNotUnderstand( Message::selector( selector_or_message_or_method,
                                                     ALTAIR_ARRAY2( arg1, arg2 ) ) );
}
Object* const Object::perform(const Object* const& selector_or_method, Object* const& arg1, Object* const& arg2, Object* const& arg3) const
{
    if ( selector_or_method->isKindOf( ALTAIR_GET_CLASS(CompiledMethod) ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    }
    if ( !selector_or_method->isSymbol() ) {
        WrongClassError::signalOn( selector_or_method, ALTAIR_GET_CLASS(Symbol) );

        return NULL;
    }

    if ( respondsTo( __REINTERPRET_CAST(const Symbol * const, selector_or_method) ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    } else
        return doseNotUnderstand( Message::selector( selector_or_message_or_method,
                                                     ALTAIR_ARRAY3( arg1, arg2, arg3 ) ) );
}
Object* const Object::perform(const Object* const& selector_or_method, Object* const& arg1, Object* const& arg2, Object* const& arg3, Object* const& arg4) const
{
    if ( selector_or_method->isKindOf( ALTAIR_GET_CLASS(CompiledMethod) ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    }
    if ( !selector_or_method->isSymbol() ) {
        WrongClassError::signalOn( selector_or_method, ALTAIR_GET_CLASS(Symbol) );

        return NULL;
    }

    if ( respondsTo( __REINTERPRET_CAST(const Symbol * const, selector_or_method) ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    } else
        return doseNotUnderstand( Message::selector( selector_or_message_or_method,
                                                     ALTAIR_ARRAY4( arg1, arg2, arg3, arg4 ) ) );
}


Object* const Object::performWithArguments(const Object* const& selector_or_method, const Array* const& arguments_array) const
{
    if ( selector_or_method->isKindOf( ALTAIR_GET_CLASS(CompiledMethod) ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    }
    if ( !selector_or_method->isSymbol() ) {
        WrongClassError::signalOn( selector_or_method, ALTAIR_GET_CLASS(Symbol) );

        return NULL;
    }

    if ( respondsTo( __REINTERPRET_CAST(const Symbol * const, selector_or_method) ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    } else
        return doseNotUnderstand( Message::selector( selector_or_message_or_method, arguments_array ) );
}


bool Object::equals(const Object* const& arg) const
{
    return this == arg;
}


bool Object::identityEquals(const Object* const& arg) const
{
    return this == arg;
}


Class* const Object::getClass() const
{
    primitiveFailed();

    return NULL;
}


Object* const Object::error(const String* const& message) const
{
}


void Object::basicPrint() const
{
}


Object* const Object::halt()
{
    return halt( new String( "halt encountered" ) );
}
Object* const Object::halt(const String* const& a_string)
{
    return error( a_string );
}


Object* const Object::primitiveFailed() const
{
    PrimitiveFailed::signal();

    return this;
}


Object* const Object::shouldNotImplement() const
{
    ShouldNotImplementError::signal();

    return this;
}


Object* const subclassResponsibility() const
{
    SubclassResponsibilityError::signal();

    return this;
}


Object* const Object::notYetImplemented() const
{
    NotYetImplementedError::signal();

    return this;
}


Object* const Object::instVarNamed(const String* const& a_string) const
{
    Class* self_class = getClass();
    Object* ret;

    ret = instVarAt( self_class->indexOfInstVar( a_string ) );

    self_class->release();

    return ret;
}


void Object::instVarNamedPut(const String* const& a_string, Object* const& an_object)
{
    Class* self_class = getClass();

    instVarPut( self_class->indexOfInstVar( a_string ),
                an_object );

    self_class->release();
}


Object* const Object::doseNotUnderstand(const Message* const& message) const
{
    return this;
}


Object* const Object::badReturnError() const
{
    BadReturnError::signal();

    return this;
}


bool Object::mustBeBoolean() const
{
    bool result = MustBeBoolenError::signalOn( this );

    if ( result == false )
        result = true;

    return result;
}


Object* const Object::noRunnableProcess() const
{
    NoRunnableProcessError::signal();

    return this;
}


Object* const Object::userInterrupt() const
{
    UserInterruptError::signal();

    return this;
}


// Local Variables:
//   coding: utf-8
// End:
