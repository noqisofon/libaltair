#include "config.h"

#include "altair/altair_prefix.h"
#include "altair/Class.hxx"
#include "altair/Array.hxx"

#include "altair/Set.hxx"
USING_NAMESPACE_ALTAIR;


Set::Set()
    : _Super(32), content_(new Array(32))
{
}
Set::Set(size_t size, Object* const& an_object)
    : _Super(size), content_(new Array(size, an_object))
{
}
Set::Set(const Set& other)
    : _Super(other.primSize()), content_(__REINTERPRET_CAST(Array *, other.copyEmpty()))
{
}


Object* Set::at(const Object* const& key) const
{
    int index = findIndex( key );

    return primAt( index );
}


Object* Set::put(const Object* const& key, Object* const& value)
{
    int index = findIndex( key );

    Object* ret = primAt( index );
    primPut( index, value );

    return ret;
}


int Set::hashFor(const Object* const& an_object) const
{
    return an_object->hash();
}


int Set::findIndex(const Object* const& an_object) const
{
    int size = __STATIC_CAST(int, primSize());
    int index = (ALTAIR_SCRAMBLE(an_object->hash()) & size - 1) + 1;

    while ( true ) {
        Object* element = primAt( index );

        if ( ALTAIR_ISNIL(element) || element->equals( an_object ) )
            break;
        if ( index == size )
            index = 0;
        else
            ++ index;
    }
    return index;
}


size_t Set::primSize() const
{
    return content_->size();
}


// Local Variables:
//   coding: utf-8
// End:
