//  
//  PositionableStream.cpp
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
#include "altair/ReadStream.hxx"
#include "altair/Collection.hxx"
#include "altair/Transcript.hxx"
#include "altair/Character.hxx"
#include "altair/Integer.hxx"
#include "altair/SequenceableCollection.hxx"
#include "altair/IndexOutOfRangeError.hxx"

#include "altair/PositionableStream.hxx"
USING_NAMESPACE_ALTAIR;


void PositionableStream::close()
{
    flush();

    collection_->release();
    ptr_ = 0;
    end_ptr_ = 0;
    access_ = 0;
}


Object* PositionableStream::next()
{
    if ( ( access_ & 1 ) == 0 ) {
        shouldNotImplement();

        return NULL;
    }

    if ( ptr_ > end_ptr_  )
        return pastEnd();

    Object* element = collection_->Object::at( ptr_ ++ );

    return element;
}


void PositionableStream::nextPutAllOn(Stream* const& a_stream)
{
    if ( ( access_ & 1 ) == 0 ) {
        shouldNotImplement();

        return ;
    }

    int n = end_ptr_ - ptr_ + 1;

    a_stream->nextPutAll( n, collection_, ptr_ );

    ptr_ += n;
}


int PositionableStream::nextAvailable(int an_integer, Stream* const& a_stream)
{
    if ( ( access_ & 1 ) == 0 ) {
        shouldNotImplement();

        return 0;
    }

    int n = ALTAIR_MIN(an_integer, end_ptr_ - ptr_ + 1);

    a_stream->nextPutAll( n, collection_, ptr_ );

    ptr_ += n;

    return n;
}


int PositionableStream::nextAvailableInto(int an_integer, SequenceableCollection* const& a_collection, int starting_pos)
{
    if ( ( access_ & 1 ) == 0 ) {
        shouldNotImplement();

        return 0;
    }

    int n = ALTAIR_MIN(an_integer, end_ptr_ - ptr_ + 1);

    a_collection->replaceFrom( starting_pos,
                               starting_pos + n - 1,
                               collection_,
                               ptr_ );

    ptr_ += n;

    return n;
}


Object* PositionableStream::peek() const
{
    if ( ( access_ & 1 ) == 0 ) {
        shouldNotImplement();

        return NULL;
    }

    if ( ptr_ > end_ptr_ )
        return NULL;

    return collection_->Object::at( ptr_ );
}


bool PositionableStream::peekFor(const Object* const& an_object) const
{
    if ( atEnd() )
        return false;
    if ( peek()->equals( an_object ) )
        return true;
    return false;
}


SequenceableCollection* PositionableStream::copyFrom(int start, int end) const
{
    return collection_->copyFrom( start, end );
}


SequenceableCollection* PositionableStream::contents() const
{
    return collection_->copyFrom( 0, end_ptr_ );
}


Stream* PositionableStream::readStream() const
{
    return ReadStream::on( collection_, 0, end_ptr_ );
}


SequenceableCollection* PositionableStream::reverseContents() const
{
    SequenceableCollection* new_collection = __REINTERPRET_CAST(SequenceableCollection *, collection_->copyEmpty( end_ptr_ ));

    int arrived = end_ptr_;
    for ( int i = 0; i < arrived; ++ i ) {
        new_collection->put( i, collection_->Object::at( end_ptr_ - i ) );
    }
    return new_collection;
}


SequenceableCollection* PositionableStream::upToEnd()
{
    return _Super::next( end_ptr_ - ptr_ );
}


SequenceableCollection* PositionableStream::upTo(const Object* const& an_object)
{
    int r = collection_->indexOf( an_object, ptr_ );

    if ( r == -1 )
        return upToEnd();
    else {
        SequenceableCollection* result = _Super::next( r - ptr_ );

        next();

        return result;
    }
}


void PositionableStream::truncate()
{
    if ( ( access_ & 2 ) == 0 )
        shouldNotImplement();
    else
        end_ptr_ = ptr_ - 1;
}


void PositionableStream::position(int an_integer)
{
    if ( ALTAIR_BETWEEN_AND( an_integer, 0, size() ) )
        ptr_ = an_integer;
    else
        IndexOutOfRangeError::signalOn( this, an_integer );
}


void PositionableStream::basicPosition(int pos)
{
    if ( ALTAIR_BETWEEN_AND( pos, 0, size() ) )
        ptr_ = pos;
    else
        IndexOutOfRangeError::signalOn( this, pos );
}


void PositionableStream::status(String* const a_string) const
{
    Transcript::print( collection_->copyFrom( 0, end_ptr_ ) );
    Transcript::nextPutAll( "    " );
    Transcript::nextPutAll( a_string );
    Transcript::nl();
    Transcript::put( Integer::valueOf( position() ), Character::space() );
    Transcript::nextPut( '^' );
    Transcript::nl();
}


Class* PositionableStream::species() const
{
    return collection_->species();
}

// Local Variables:
//   coding: utf-8
// End:
