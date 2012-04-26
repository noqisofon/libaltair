#include "config.h"

#include "altair/altair_prefix.h"

#include "altair/OrderedCollection.hxx"
USING_NAMESPACE_ALTAIR;


OrderedCollection::OrderedCollection()
{
}
OrderedCollection::OrderedCollection(int an_integer)
{
}


Object* const OrderedCollection::first() const
{
    return NULL;
}


Collection* const& OrderedCollection::add(Object* const& new_object)
{

    return this;
}


bool OrderedCollection::tryRemove(Object* const& old_object)
{
    return false;
}


Iterator* const OrderedCollection::iterator() const
{
    return NULL;
}
// Local Variables:
//   coding: utf-8
// End:
