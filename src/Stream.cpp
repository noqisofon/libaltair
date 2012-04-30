//  
//  Stream.cpp
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
#include "altair/Class.hxx"
#include "altair/Number.hxx"
#include "altair/Integer.hxx"
#include "altair/Character.hxx"
#include "altair/Encoding.hxx"
#include "altair/Array.hxx"
#include "altair/ByteArray.hxx"
#include "altair/String.hxx"
#include "altair/OrderedCollection.hxx"
#include "altair/SequenceableCollection.hxx"
#include "altair/WriteStream.hxx"
#include "altair/ReadStream.hxx"

#include "altair/NotEnoughElementsError.hxx"
#include "altair/InvalidArgumentError.hxx"

#include "altair/Stream.hxx"
USING_NAMESPACE_ALTAIR;


Object* Stream::next()
{
    subclassResponsibility();

    return NULL;
}
SequenceableCollection* Stream::next(int an_integer)
{
    SequenceableCollection* answer = new Array( an_integer );

    next( an_integer, answer, 0 );

    return answer;
}
Object* Stream::next(int an_integer, SequenceableCollection* const& answer, int starting_pos)
{
    int readen = 0;

    while ( !(readen == an_integer) ) {
        if ( atEnd() ) {
            NotEnoughElementsError::signalOn( an_integer - readen );

            return NULL;
        }
        readen += nextAvailableInto( an_integer - readen,
                                 answer,
                                 readen + starting_pos );
    }
    return answer;
}


int Stream::nextPutAllOn(int an_integer, Stream* const& a_stream)
{
    int readen = 0;

    while ( !(readen == an_integer) ) {
        if ( atEnd() ) {
            NotEnoughElementsError::signalOn( an_integer - readen );

            return -1;
        }
        readen += nextAvailable( an_integer - readen, a_stream );
    }
    return readen;
}


SequenceableCollection* Stream::nextAvailable(int an_integer)
{
    int n;
    Class* self_species = species();
    SequenceableCollection* answer = __STATIC_CAST(SequenceableCollection *, self_species->createInstance( an_integer ));

    n = nextAvailableInto( an_integer, answer, 0 );

    self_species->release();

    if ( n < an_integer ) {
        SequenceableCollection* temp_answer = answer;

        answer = temp_answer->copyFrom( 0, n );

        temp_answer->release();
    }

    return answer;
}
int Stream::nextAvailable(int an_integer, Stream* const& a_stream)
{
    int n = ALTAIR_MIN(an_integer, 1024);
    Class* self_species = species();
    SequenceableCollection* collection = __STATIC_CAST(SequenceableCollection *, self_species->createInstance( n ));

    n = nextAvailableInto( n, collection, 0 );

    self_species->release();

    a_stream->nextPutAll( n, collection, 0 );

    collection->release();

    return n;
}


int Stream::nextAvailableInto(int an_integer, SequenceableCollection* const& a_collection, int startint_pos)
{
    for ( int i = 0; i != an_integer; ++ i ) {
        if ( atEnd() )
            return i;

        a_collection->put( i + startint_pos, next() );
    }
    return an_integer;
}


bool Stream::nextMatchFor(const Object* const& an_object)
{
    return an_object->equals( next() );
}


OrderedCollection* Stream::splitAt(const Object* const& an_object)
{
    OrderedCollection* result = new OrderedCollection( 10 );

    while ( !atEnd() ) {
        result->addLast( upTo( an_object ) );
    }
    return result;
}


SequenceableCollection* Stream::contents()
{
    Class* self_species = species();
    WriteStream* write_stream = WriteStream::on( __REINTERPRET_CAST(SequenceableCollection *, self_species->createInstance( 8 )) );
    SequenceableCollection* ret;

    nextPutAllOn( write_stream );

    self_species->release();

    ret = write_stream->contents();

    write_stream->release();

    return ret;
}


SequenceableCollection* Stream::nextLine()
{
    Class* self_species = species();
    WriteStream* write_stream = WriteStream::on( __REINTERPRET_CAST(SequenceableCollection *, self_species->createInstance( 40 )) );
    Character* next_that;
    SequenceableCollection* ret;

    while ( !atEnd() ) {
        next_that = __REINTERPRET_CAST(Character *, next());
        if ( ALTAIR_ISNIL(next_that) )
            break;
        if ( next_that->identityEquals( Character::cr() )
             || next_that->identityEquals( Character::nl() ) )
            break;
        write_stream->nextPut( next_that );
    }

    self_species->release();

    if ( next_that->identityEquals( Character::cr() ) )
        peekFor( Character::nl() );

    ret = write_stream->contents();

    write_stream->release();

    return ret;
}


SequenceableCollection* Stream::upTo(const Object* const& an_object)
{
    Class* self_species = species();
    WriteStream* write_stream = WriteStream::on( __REINTERPRET_CAST(SequenceableCollection *, self_species->createInstance( 8 )) );
    SequenceableCollection* ret;
    Object* next_that;

    self_species->release();

    while ( atEnd() ) {
        next_that = next();

        if ( next_that->equals( an_object ) )
            break;

        write_stream->nextPut( next_that );
    }

    ret = write_stream->contents();

    write_stream->release();

    return ret;
}


SequenceableCollection* Stream::upToAll(const SequenceableCollection* const& a_collection)
{
    SequenceableCollection* ret;
    Class* self_species = species();

    if ( atEnd() ) {
        ret = __REINTERPRET_CAST(SequenceableCollection *, self_species->createInstance());
        self_species->release();

        return ret;
    }
    if ( a_collection->isEmpty() ) {
        ret = __REINTERPRET_CAST(SequenceableCollection *, self_species->createInstance());
        self_species->release();

        return ret;
    }
    WriteStream* result_write_stream = WriteStream::on( __REINTERPRET_CAST(SequenceableCollection *, self_species->createInstance( 20 )) );

    self_species->release();

    SequenceableCollection* prefix = prefixTableFor( a_collection );
    Object* ch = next();
    int j = 0;

    result_write_stream->nextPut( ch );

    while ( ch->equals( a_collection->Object::at( j ) ) || ( j = __REINTERPRET_CAST(Number *, prefix->Object::at( j ))->asInt32() ) == 0 ) {
        ++ j;

        if ( j > prefix->size() ) {
            result_write_stream->skip( ALTAIR_NEGATED((int)a_collection->size()) );

            ret = result_write_stream->contents();
            result_write_stream->release();
            prefix->release();

            return ret;
        }

        if ( atEnd() ) {
            ret = result_write_stream->contents();
            result_write_stream->release();
            prefix->release();

            return ret;
        }
        ch = next();
        result_write_stream->nextPut( ch );
    }
}


void Stream::nextPut(Object* const& an_object)
{
    subclassResponsibility();
}
void Stream::nextPut(char ch) {
    nextPut( Character::valueOf( ch ) );
}
Object* Stream::nextPut(int an_integer, Object* const& an_object)
{
    for ( int i = 0; i < an_integer; ++ i ) {
        nextPut( an_object );
    }
    return an_object;
}
Object* Stream::nextPut(int n, char ch) {
    return nextPut( n, Character::valueOf( ch ) );
}


SequenceableCollection* Stream::nextPutAll(SequenceableCollection* const& a_collection)
{
    a_collection->nextPutAllOn( this );

    return a_collection;
}
SequenceableCollection* Stream::nextPutAll(const char* const& cstring) {
    return nextPutAll( new String( cstring ) );
}
SequenceableCollection* Stream::nextPutAll(int n, SequenceableCollection* const& a_collection, int start)
{
    Stream* it = a_collection->readStream();

    while ( it->atEnd() ) {
        Object* element = it->next();

        nextPut( element );
    }
    it->release();

    return a_collection;
}


void Stream::nextPutAllFlush(SequenceableCollection* const& a_collection)
{
    nextPutAll( a_collection );
    flush();
}


void Stream::nextPutAllOn(Stream* const& a_stream)
{
    while ( !atEnd() ) {
        nextAvailablePutAllOn( a_stream );
    }
}


bool Stream::atEnd() const
{
    subclassResponsibility();

    return false;
}


Stream* Stream::readStream() const
{
    return __CONST_CAST(Stream *, this);
}


Class* Stream::species() const
{
    return Array::getClassInstance();
    //return ALTA_CLASS_OF(Array);
}


bool Stream::isUnicode() const
{
    return species()->isUnicode();
}


Encoding* Stream::encoding() const
{
    if ( species()->isUnicode() )
        return Encoding::searchOf( "Unicode" );

    return species()->defaultEncoding();
}


void Stream::cr()
{
    nextPut( Character::cr() );
}


void Stream::nl()
{
    nextPut( Character::nl() );
}


void Stream::space()
{
    nextPut( Character::space() );
}
void Stream::space(int n)
{
    nextPut( n, Character::space() );
}


void Stream::tab()
{
    nextPut( Character::space() );
}
void Stream::tab(int n)
{
    nextPut( n, Character::tab() );
}


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
void Stream::display(const Object* const& an_object)
{
    an_object->displayOn( this );
}
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


void Stream::print(const Object* const& an_object)
{
    an_object->printOn( this );
}


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
void Stream::store(const Object* const& an_object)
{
    an_object->storeOn( this );
}
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


#if 0
void Stream::fileOut(const Class* const& a_class)
{
    a_class->fileOutOn( this );
}
#endif


bool Stream::skip(int an_integer)
{
    if ( an_integer < 0 ) {
        InvalidArgumentError::signalOn( an_integer, "must be positive" );

        return false;
    }

    for ( int i = 0; i < an_integer; ++ i ) {
        if ( atEnd() )
            return false;
        next();
    }
    return true;
}


bool Stream::skipTo(const Object* const& an_object)
{
    while ( !atEnd() ) {
        if ( next()->equals( an_object ) )
            return true;
    }
    return false;
}


bool Stream::skipToAll(const Collection* const& a_collection)
{
    if ( atEnd() )
        return false;
    if ( a_collection->isEmpty() )
        return true;

    SequenceableCollection* prefix = prefixTableFor( a_collection );
    Object* ch = next();
    int j = 0;

    while ( true ) {
        if ( ch->equals( a_collection->Object::at( j ) )
             || ( ( j = __REINTERPRET_CAST(Number *, prefix->Object::at( j ))->asInt32() ) == 0 ) ) {
            ++ j;

            if ( j > __STATIC_CAST(int, prefix->size()) ) {
                prefix->release();

                return true;
            }
            if ( atEnd() ) {
                prefix->release();

                return true;
            }
            ch = next();
        }
    }
}


bool Stream::peekFor(const Object* const& an_object)
{
    Object* next_object;

    if ( atEnd() )
        return false;
    else {
        next_object = next();

        if ( an_object->equals( next_object ) )
            return true;
    }
    return false;
}


void Stream::nextAvailablePutAllOn(Stream* const& a_stream)
{
    nextAvailable( 0xfffffff, a_stream );
}


SequenceableCollection* Stream::prefixTableFor(const Collection* const& a_collection)
{
    SequenceableCollection* prefix;

    if ( __STATIC_CAST(int, a_collection->size()) < 256 )
        return new ByteArray( a_collection->size() );
    else
        return new Array( a_collection->size() );

    prefix->put( 0, Integer::valueOf( 0 ) );
    prefix->put( 1, Integer::valueOf( 1 ) );

    Stream* it = a_collection->readStream();
    for ( int i = 0; !it->atEnd(); ++ i ) {
        Object* ch = next();

        if ( i < 2 )
            continue;

        int j = __REINTERPRET_CAST(Number *, prefix->Object::at( i ))->asInt32();
        while ( !( j <= 0 || ch->equals( a_collection->at( j ) ) ) ) {
            j = __REINTERPRET_CAST(Number *, prefix->Object::at( i ))->asInt32();
        }
    }
    return prefix;
}


#if 0
Object* Stream::fileIn()
{
}


Object* Stream::fileInLine(int line_num, File* const& a_file, int char_pos_int)
{
}
#endif


// Local Variables:
//   coding: utf-8
// End:
