#include "config.h"

#include "altair/altair_prefix.h"
#include "altair/Array.hxx"
#include "altair/Collection.hxx"

#include "altair/Stream.hxx"
USING_NAMESPACE_ALTAIR;


Object* const Stream::next()
{
    subclassResponsibility();

    return NULL;
}
Collection* const Stream::next(int an_integer)
{
    Collection* answer = new Array( an_integer );

    nextInto( an_integer, answer, 0 );

    return answer;
}


Object* const Stream::nextInto(int an_integer, Object* const& answer, int starting_pos)
{
    int readen = 0;

    while ( !(readen == an_integer) ) {
        if ( atEnd() ) {
            NotEnoughElementsError::signalOn( an_integer - readen );

            return NULL;
        }
        readen += nextAvailable( an_integer - readen, answer, a_stream );
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


int Stream::nextAvailable(int an_integer)
{
    int n;
    Class* self_species = species();
    Collection* answer = self_species->createInstance( an_integer );

    n = nextAvailableInto( an_integer, answer, 0 );

    self_species->release();

    if ( n < an_integer ) {
        Collection* temp_answer = answer;

        answer = temp_answer->copyFrom( 0, n );

        temp_answer->release();
    }

    return answer;
}
int Stream::nextAvailable(int an_integer, Stream* const& a_stream)
{
    int n = ALTAIR_MIN(an_integer, 1024);
    Class* self_species = species();
    Collection* collection = self_species->createInstance( n );

    n = nextAvailableInto( n, collection, 0 );

    self_species->release();

    a_stream->nextPutAll( n, collection, 0 );

    collection->release();

    return n;
}


int Stream::nextAvailable(int an_integer, Collection* const& a_collection, int startint_pos)
{
    for ( int i = 0; i != an_integer; ++ i ) {
        if ( atEnd() )
            return i;

        a_collection->put( i + pos, next );
    }
    return an_integer;
}


bool Stream::nextMatchFor(const Object* const& an_object)
{
    return an_object->equals( next() );
}


OrderedCollection* const Stream::splitAt(const Object* const& an_object)
{
    OrderedCollection* result = new OrderedCollection( 10 );

    while ( !atEnd() ) {
        result->addLast( upTo( an_object ) );
    }
    return result;
}


Collection* const Stream::contents()
{
    Class* self_species = species();
    WriteStream* write_stream = WriteStream::on( self_species->createInstance( 8 ) );
    Collection* ret;

    nextPutAllOn( write_stream );

    self_species->release();

    ret = write_stream->contents();

    write_stream->release();

    return ret;
}


Collection* const Stream::nextLine()
{
    Class* self_species = species();
    WriteStream* write_stream = WriteStream::on( self_species->createInstance( 40 ) );
    Character* next;
    Collection* ret;

    while ( !atEnd() ) {
        next = __REINTERPRET_CAST(Character *, next());
        if ( ALTAIR_ISNIL( next ) )
            break;
        if ( next->identityEquals( Character::cr )
             || next->identityEquals( Character::nl ) )
            break;
        write_stream->nextPut( next );
    }

    self_species->release();

    if ( next->identityEquals( Character::cr ) )
        peekFor( Character::nl );

    ret = write_stream->contents();

    write_stream->release();

    return ret;
}


Collection* const Stream::upTo(const Object* const& an_object)
{
    Class* self_species = species();
    WriteStream* write_stream = WriteStream::on( self_species->createInstance( 8 ) );
    Collection* ret;
    Object* next;

    self_species->release();

    while ( atEnd() ) {
        next = next();

        if ( next->equals( an_object ) )
            break;

        write_stream->nextPut( next );
    }

    ret = write_stream->contents();

    write_stream->release();

    return ret;
}


Collection* const Stream::upToAll(const Collection* const& a_collection)
{
    Collection* ret;
    Class* self_species = species();

    if ( atEnd() ) {
        ret = self_species->createInstance();
        self_species->release();

        return ret;
    }
    if ( a_collection->isEmpty() ) {
        ret = self_species->createInstance();
        self_species->release();

        return ret;
    }
    WriteStream* result_write_stream = WriteStream::on( self_species->createInstance( 20 ) );

    self_species->release();

    Collection* prefix = prefixTableFor( a_collection );
    Object* ch = next();
    int j = 0;

    result_write_stream->nextPut( ch );

    while ( ch->equals( a_collection->at( j ) ) || ( j = prefix->at( j )->asInt32() ) == 0 ) {
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
Object* const Stream::nextPut(int an_integer, Object* const& an_object)
{
    for ( int i = 0; i < an_integer; ++ i ) {
        nextPut( an_object );
    }
    return an_object;
}


Collection* const Stream::nextPutAll(Collection* const& a_collection)
{
    a_collection->nextPutAllOn( self );

    return a_collection;
}
Collection* const Stream::nextPutAll(int n, Collection* const& a_collection, int start)
{
    Stream* it = a_collection->readSream();

    while ( it->atEnd() ) {
        Object* element = it->next();

        nextPut( element );
    }
    it->release();

    return a_collection;
}


void Stream::nextPutAllFlush(Collection* const& a_collection)
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
// Local Variables:
//   coding: utf-8
// End:
