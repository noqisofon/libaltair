//  
//  Object.cpp
//  altair
//  
//  Auther:
//       ned rihine <ned.rihine@gmail.com>
// 
//  Copyright (c) 2012 rihine All rights reserved.
// 
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
// 
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
// 
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include "config.h"

#include "altair/altair_prefix.h"
#include "altair/Collection.hxx"
#include "altair/Class.hxx"
#include "altair/Integer.hxx"
#include "altair/Character.hxx"
#include "altair/Boolean.hxx"
#include "altair/Symbol.hxx"
#include "altair/String.hxx"
#include "altair/IOChannel.hxx"
#include "altair/Association.hxx"
#include "altair/Transcript.hxx"
#include "altair/WriteStream.hxx"
#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
#   include "altair/ObjectMemory.hxx"
#   include "altair/WeakKeyIdentityDictionary.hxx"
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */
#include "altair/ArgumentOutOfRangeError.hxx"
#include "altair/NotIndexableError.hxx"
#include "altair/IndexOutOfRangeError.hxx"
#include "altair/ReadOnlyObjectError.hxx"
#include "altair/WrongClassError.hxx"
#include "altair/InvalidValueError.hxx"
#include "altair/BadReturnError.hxx"
#include "altair/UserInterruptError.hxx"
#include "altair/SubclassResponsibilityError.hxx"
#include "altair/NotYetImplementedError.hxx"
#include "altair/ShouldNotImplementError.hxx"
#include "altair/NoRunnableProcessError.hxx"
#include "altair/PrimitiveFailed.hxx"

#include "altair/Object.hxx"
USING_NAMESPACE_ALTAIR;


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
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
    virtual Object* const initialize(Object* const& self) {
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
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


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
    bool ret;
    Class* const self_class = getClass();

    ret = self_class->identityEquals( a_class ) || self_class->inheritsFrom( a_class );

    // self_class がどーなっているのかわからないが、解放する必要がある。
    self_class->release();

    return ret;
}


bool Object::isInstanceOf(const Class* const& a_class) const
{
    bool ret;
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


Object* Object::copy() const
{
    return shallowCopy( /* postCopy() */ );
}


Object* Object::deepCopy() const
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


Object* Object::removeDependent(Object* const& an_object)
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


Association* Object::createAssociation(Object* const& an_object) const
{
    return new Association( this, an_object );
}


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
String* Object::displayString() const
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

    Transcript::show( display_string );

    display_string->release();
}


void Object::displayNl() const
{
    String* display_string = displayString();

    Transcript::showCr( display_string );

    display_string->release();
}
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


String* Object::printString() const
{
    Stream* write_stream = WriteStream::on( new String() );

    printOn( write_stream );

    String* ret = __REINTERPRET_CAST(String *, write_stream->contents());

    write_stream->release();

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

    Transcript::show( print_string );

    print_string->release();
}


void Object::printNl() const
{
    String* print_string = printString();

    Transcript::showCr( print_string );

    print_string->release();
}


void Object::basicPrintNl() const
{
    Stream* standard_output = IOChannel::getStandardOutput();

    standard_output->flush();
    basicPrint();
    standard_output->nextPut( Character::nl() );
    standard_output->flush();

    standard_output->release();
}


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
String* Object::storeString() const
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
     * st なコードではクラスをそのまま渡しているが、C++ ではそんなことは無理なので、instanceOf を使う。
     * 
     */
    examineOn( Transcript::instanceOf() );
}
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


void Object::inspect() const
{
#if !defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
    printOn( Transcript::instanceOf() );
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
            output_text = object->printString();
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
#endif  /* !defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */
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



Object* Object::checkIndexableBounds(int index) const
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
    if ( index > __STATIC_CAST(int, basicSize()) ) {
        IndexOutOfRangeError::signalOn( this, index );

        return NULL;
    }
    return NULL;
}
Object* Object::checkIndexableBounds(int index, Object* (*a_block)(const Object* const&)) const
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


void Object::checkIndexableBoundsPut(int index, Object* const& object)
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
    if ( index > __STATIC_CAST(int, basicSize()) ) {
        IndexOutOfRangeError::signalOn( this, index );

        return;
    }

    Symbol* shape = self_class->getShape();

    if ( shape->identityEquals( ALTAIR_SYMBOL(float) ) || shape->identityEquals( ALTAIR_SYMBOL(double) ) ) {
        WrongClassError::signalOn( object );

        return ;
    }

    if ( !object->isKindOf( Character::getCurrentClass() ) ) {
        if ( shape->identityEquals( ALTAIR_SYMBOL(character) ) || shape->identityEquals( ALTAIR_SYMBOL(utf32) ) ) {
            WrongClassError::signalOn( object, Character::getCurrentClass() );

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
                                       Integer::valueOf( ALTAIR_ODD(size) ? -1 << size : 0 ),
                                       Integer::valueOf( ( 1 << size ) - 1 ) );
    
    return ;
}


Object* Object::become(const Object* const&/* other_object */)
{
    ReadOnlyObjectError::signal();

    return this;
}


Object* Object::becomeForward(const Object* const&/* other_object */)
{
    ReadOnlyObjectError::signal();

    return this;
}


Object* Object::shallowCopy() const
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


Object* Object::instVarAt(int index) const
{
    if ( index < 0 ) {
        IndexOutOfRangeError::signalOn( this, index );

        return NULL;
    }
    
    Class* self_class = getClass();
    if ( index > __STATIC_CAST(int, basicSize()) + __STATIC_CAST(int, self_class->instanceSize()) ) {
        IndexOutOfRangeError::signalOn( this, index );

        return NULL;
    }

    Object* ret = basicAt( index - self_class->instanceSize() );

    self_class->release();

    return ret;
}


void Object::instVarPut(int index, Object* const value)
{
    if ( index < 0 ) {
        IndexOutOfRangeError::signalOn( this, index );

        return ;
    }

    Class* self_class = getClass();

    if ( index > __STATIC_CAST(int, basicSize()) + __STATIC_CAST(int, self_class->instanceSize()) ) {
        IndexOutOfRangeError::signalOn( this, index );

        return ;
    }

    /* Object* ret = */basicPut( index - __STATIC_CAST(int, self_class->instanceSize()), value );

    self_class->release();

    //return ret;
}


void Object::makeReadOnly(bool a_boolean)
{
    WrongClassError::signalOn( Boolean::valueOf( a_boolean ),
                               Boolean::getCurrentClass() );
}


void Object::makeUntrusted(bool a_boolean)
{
    WrongClassError::signalOn( Boolean::valueOf( a_boolean ),
                               Boolean::getCurrentClass() );
}


void Object::makeEphemeron()
{
    InvalidValueError::signalOn( this, "ephemerons should have at least one instance variables" );
}


Object* Object::asOop() const
{
    InvalidValueError::signalOn( this, "Instance of Integer have no associated OOP!" );

    return NULL;
}


int Object::identityHash() const
{
    return *__REINTERPRET_CAST(const int *, this);
}


int Object::hash() const
{
    return *__REINTERPRET_CAST(const int *, this);
}


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
Object* Object::perform(const Object* const& selector_or_message_or_method) const
{
    if ( selector_or_message_or_method->isSymbol() ) {
        if ( respondsTo( __REINTERPRET_CAST(const Symbol * const, selector_or_message_or_method) ) ) {
            WrongArgumentCountError::signal();

            return NULL;
        } else
            return doseNotUnderstand( Message::selector( selector_or_message_or_method, ALTAIR_ARRAY0 ) );
    }

    if ( selector_or_message_or_method->isKindOf( CompiledMethod::getCurrentClass() ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    }
    return selector_or_message_or_method->sendTo( this );
}
Object* Object::perform(const Object* const& selector_or_method, Object* const& arg1) const
{
    if ( selector_or_method->isKindOf( CompiledMethod::getCurrentClass() ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    }
    if ( !selector_or_method->isSymbol() ) {
        WrongClassError::signalOn( selector_or_method, Symbol::getCurrentClass() );

        return NULL;
    }

    if ( respondsTo( __REINTERPRET_CAST(const Symbol * const, selector_or_method) ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    } else
        return doseNotUnderstand( Message::selector( selector_or_message_or_method,
                                                     ALTAIR_ARRAY1( arg1 ) ) );
}
Object* Object::perform(const Object* const& selector_or_method, Object* const& arg1, Object* const& arg2) const
{
    if ( selector_or_method->isKindOf( CompiledMethod::getCurrentClass() ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    }
    if ( !selector_or_method->isSymbol() ) {
        WrongClassError::signalOn( selector_or_method, Symbol::getCurrentClass() );

        return NULL;
    }

    if ( respondsTo( __REINTERPRET_CAST(const Symbol * const, selector_or_method) ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    } else
        return doseNotUnderstand( Message::selector( selector_or_message_or_method,
                                                     ALTAIR_ARRAY2( arg1, arg2 ) ) );
}
Object* Object::perform(const Object* const& selector_or_method, Object* const& arg1, Object* const& arg2, Object* const& arg3) const
{
    if ( selector_or_method->isKindOf( CompiledMethod::getCurrentClass() ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    }
    if ( !selector_or_method->isSymbol() ) {
        WrongClassError::signalOn( selector_or_method, Symbol::getCurrentClass() );

        return NULL;
    }

    if ( respondsTo( __REINTERPRET_CAST(const Symbol * const, selector_or_method) ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    } else
        return doseNotUnderstand( Message::selector( selector_or_message_or_method,
                                                     ALTAIR_ARRAY3( arg1, arg2, arg3 ) ) );
}
Object* Object::perform(const Object* const& selector_or_method, Object* const& arg1, Object* const& arg2, Object* const& arg3, Object* const& arg4) const
{
    if ( selector_or_method->isKindOf( CompiledMethod::getCurrentClass() ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    }
    if ( !selector_or_method->isSymbol() ) {
        WrongClassError::signalOn( selector_or_method, Symbol::getCurrentClass() );

        return NULL;
    }

    if ( respondsTo( __REINTERPRET_CAST(const Symbol * const, selector_or_method) ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    } else
        return doseNotUnderstand( Message::selector( selector_or_message_or_method,
                                                     ALTAIR_ARRAY4( arg1, arg2, arg3, arg4 ) ) );
}


Object* Object::performWithArguments(const Object* const& selector_or_method, const Array* const& arguments_array) const
{
    if ( selector_or_method->isKindOf( CompiledMethod::getCurrentClass() ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    }
    if ( !selector_or_method->isSymbol() ) {
        WrongClassError::signalOn( selector_or_method, Symbol::getCurrentClass() );

        return NULL;
    }

    if ( respondsTo( __REINTERPRET_CAST(const Symbol * const, selector_or_method) ) ) {
        WrongArgumentCountError::signal();

        return NULL;
    } else
        return doseNotUnderstand( Message::selector( selector_or_message_or_method, arguments_array ) );
}
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


bool Object::equals(const Object* const& arg) const
{
    return this == arg;
}


bool Object::identityEquals(const Object* const& arg) const
{
    return this == arg;
}


Class* Object::getClass() const
{
    primitiveFailed();

    return NULL;
}


Object* Object::error(const String* const& message) const
{
    return NULL;
}


void Object::basicPrint() const
{
}


Object* Object::halt()
{
    return halt( new String( "halt encountered" ) );
}
Object* Object::halt(const String* const& a_string)
{
    return error( a_string );
}


const Object* Object::primitiveFailed() const
{
    PrimitiveFailed::signal();

    return this;
}


const Object* Object::shouldNotImplement() const
{
    ShouldNotImplementError::signal();

    return this;
}


const Object* Object::subclassResponsibility() const
{
    SubclassResponsibilityError::signal();

    return this;
}


const Object* Object::notYetImplemented() const
{
    NotYetImplementedError::signal();

    return this;
}


Object* Object::instVarNamed(const String* const& a_string) const
{
    Object* ret;
    Class* self_class = getClass();

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


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
Object* Object::doseNotUnderstand(const Message* const& message) const
{
    return this;
}
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


const Object* Object::badReturnError() const
{
    BadReturnError::signal();

    return this;
}


bool Object::mustBeBoolean() const
{
    // bool result = MustBeBoolenError::signalOn( this );

    // if ( result == false )
    //     result = true;

    // return result;
    return false;
}


const Object* Object::noRunnableProcess() const
{
    NoRunnableProcessError::signal();

    return this;
}


const Object* Object::userInterrupt() const
{
    UserInterruptError::signal();

    return this;
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
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


// Local Variables:
//   coding: utf-8
// End:
