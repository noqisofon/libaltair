#include "config.h"

#include "altair/altair_prefix.h"
#include "altair/Character.hxx"
#include "altair/Stream.hxx"
#include "altair/String.hxx"

#include "altair/Bag.hxx"
USING_NAMESPACE_ALTAIR;


Bag::Bag()
{
    initContents( 31 );
}
Bag::Bag(size_t size)
{
    initContents( ALTAIR_MAX( 7, size ) );
}


Object* const Bag::add(Object* const new_object)
{
    addWithOccurrences( new_object, 1 );

    return new_object;
}


Object* const Bag::addWithOccurrences(Object* const new_object, int an_integer)
{
    if ( ALTAIR_ISNIL( new_object ) ) {
        InvalidArgumentError::signalOn( new_object );

        return NULL;
    }

    int new_occurrences = content_->put( new_object, occurrencesOf( new_object ) + an_integer );

    if ( new_occurrences <= 0 )
        contents_->removeKey( new_object );

    return new_object;
}


Object* const Bag::remove(Object* const& old_object, Object* const (*an_exception_block)(const Collection* const&, Object* const&))
{
    int count = occurencesOf( old_object );

    if ( count == 0 )
        return an_exception_block( this, NULL );
    if ( count == 1 )
        content_->removeKey( old_object );
    else
        content_->put( old_object, count - 1 );

    return old_object;
}


static int counts_sort_block(const Object* const& left, const Object* const& right)
{
    if ( left->isNumber() && right->isNumber() )
        return __REINTERPRET_CAST(Number *, left)->asInt32() >= __REINTERPRET_CAST(Number *, right)->asInt32();
    else
        return 1;
}


SequenceableCollection* const Bag::sortedByCount() const
{
    Array* result;
    SortedCollection* counts = SortedCollection::sortBlock( counts_sort_block );

    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* each = it->next();

        if ( pair->isAssociation() ) {
            Association* pair = __REINTERPRET_CAST(Association *, each);

            counts->add( new Association( pair->value(), pair->key() ) );
        }
    }
    it->release();

    result = counts->asArray();
    counts->release();

    return result;
}


static int occurrences_of_absent(const Object* const& an_object)
{
    return 0;
}


int Bag::occurrencesOf(const Object* const& an_object) const
{
    return content_->at( an_object, occurrences_of_absent );
}


bool Bag::includes(const Object* const& an_object) const
{
    return content_->includesKey( an_object );
}


size_t Bag::size() const
{
    size_t count = 0;

    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* element = it->next();

        if ( element->isNumber() )
            count += __REINTERPRET_CAST(Number *, element)->asInt32();
    }
    it->release();

    return count;
}


int Bag::hash() const
{
    return content_->hash();
}


bool Bag::equals(const Object* const& a_bag) const
{
    Class* self_class = getClass();
    Class* bag_class = a_bag->getClass();

    if ( !self_class->identityEquals( bag_class ) ) {
        self_class->release();
        bag_class->release();

        return false;
    }
    return contents_->equals( a_bag->contents_ );
}


Set* const Bag::asSet() const
{
    return contents_->keys();
}


void Bag::printOn(Stream* const& a_stream) const
{
    a_stream->nextPutAll(
#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
        getClass()->storeString()
#else
        getClass()->printString()
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */
    );

    a_stream->nextPut( '(' );

    Stream* it = contents_->keysAndValuesReadStream();
    while ( it->atEnd() ) {
        Association* pair = __REINTERPRET_CAST(Association *, it->next());

        a_stream->print( pair->key() );
        a_stream->nextPut( ':' );
        a_stream->print( pair->value() );
        a_stream->space();
    }
    it->release();

    a_stream->nextPut( ')' );
}
// Local Variables:
//   coding: utf-8
// End:

