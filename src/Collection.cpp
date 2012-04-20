#include "config.h"

#include "altair/altair_prefix.h"
#include "altair/Array.hxx"

#include "altair/Collection.hxx"
USING_NAMESPACE_ALTAIR;


Collection* Collection::from(Array* const& an_array)
{
    return withAll( an_array );
}


Collection* Collection::with(Object* const& an_object)
{
    return new Array()
        ->add( an_object )
        ->yourself();
}
Collection* Collection::with(Object* const& first_object, Object* const& second_object)
{
    Collection* ret = new Array();

    return ret
        ->add( first_object )
        ->add( second_object )
        ->yourself();

}
Collection* Collection::with(Object* const& first_object, Object* const& second_object, Object* const& third_object)
{
    return new Array()
        ->add( first_object )
        ->add( second_object )
        ->add( third_object )
        ->yourself();
}
Collection* Collection::with( Object* const& first_object,
                              Object* const& second_object,
                              Object* const& third_object,
                              Object* const& fourth_object)
{
    return new Array()
        ->add( first_object )
        ->add( second_object )
        ->add( third_object )
        ->add( fourth_object )
        ->yourself();
}
Collection* Collection::with( Object* const& first_object,
                              Object* const& second_object,
                              Object* const& third_object,
                              Object* const& fourth_object,
                              Object* const& fifth_object)
{
    return new Array()
        ->add( first_object )
        ->add( second_object )
        ->add( third_object )
        ->add( fourth_object )
        ->add( fifth_object )
        ->yourself();
}


Collection* Collection::withAll(Collection* const& an_collection)
{
    return new Array()
        ->addAll( an_collection );
}


#if defined(ALTAIR_USING_FUNCTOR)
static Object* binary_block_with_join(Object* const& size, Object* const& each)
{
    return size->plus( each->size() ); 
}


Collection* Collection::withJoin(Collection* const& a_collection)
{
    Collection* ret = a_collection->copyEmpty();

    a_collection->inject( Integer::valueOf( 0 ), binary_block_with_join );

    Iterator* it = a_collection->iterator();
    for ( ; it->finished(); it->next() ) {
        
    }
}
#endif  /* defined(ALTAIR_USING_FUNCTOR) */


Collection* const Collection::addAll(const Collection* const& a_collection)
{
    Iterator* it = a_collection->iterator();
    for ( ; it->finished(); it->next() ) {
        add( it->current() );
    }
    it->release();

    return a_collection;
}


Collection* const Collection::empty()
{
    return become( copyEmpty() );
}


Object* const Collection::remove(Object* const& old_object)
{
    if ( !tryRemove( old_object ) )
        ElementNotFoundException::signalOn( old_object, "object" );

    return old_object;
}


Collection* const Collection::removeAll(const Collection* const& a_collection)
{
    Iterator* it = a_collection->iterator();
    for ( ; it->finished(); it->next() ) {
        remove( it->current() );
    }
    it->release();

    return a_collection;
}


int Collection::size() const
{
    int count = 0;

    Iterator* it = iterator();
    for ( ; it->finished(); it->next() ) {
        ++ count;
    }
    it->release();

    return count;
}


bool Collection::includes(const Object* const& an_object) const
{
    bool ret = false;

    Iterator* it = iterator();
    for ( ; it->finished(); it->next() ) {
        Object* element = it->current();

        if ( an_object->equals( element ) ) {
            ret = true;

            break;
        }
    }
    it->release();

    return ret;
}


bool Collection::identityIncludes(const Object* const& an_object) const
{
    bool ret = false;

    Iterator* it = iterator();
    for ( ; it->finished(); it->next() ) {
        Object* element = it->current();

        if ( an_object->isIdentity( element ) ) {
            ret = true;

            break;
        }
    }
    it->release();

    return ret;
}


bool Collection::includesAllOf(const Collection* const& a_collection) const
{
    int len = a_collection->size();
    int count = 0;

    Iterator* it = iterator();
    for ( ; it->finished(); it->next() ) {
        Object* element = it->current();

        if ( a_collection->includes( element ) )
            ++ count;
    }
    it->release();

    return len == count;
}


bool Collection::includesAnyOf(const Collection* const& a_collection) const
{
    int len = a_collection->size();
    int count = 0;

    Iterator* it = iterator();
    for ( ; it->finished(); it->next() ) {
        Object* element = it->current();

        if ( a_collection->includes( element ) )
            ++ count;
    }
    it->release();

    return count > 0;
}


bool Collection::isEmpty() const
{
    return size() == 0;
}


bool Collection::notEmpty() const
{
    return size() > 0;
}


bool Collection::occurencesOf(const Object* const& an_object) const
{
    int count = 0;

    Iterator* it = iterator();
    for ( ; it->finished(); it->next() ) {
        Object* element = it->current();

        if ( an_object->equals( element ) )
            ++ count;
    }
    it->release();

    return count;
}
// Local Variables:
//   coding: utf-8
// End:
