#include "config.h"

#include "altair/altair_prefix.h"
#include "altair/Stream.hxx"

#include "altair/Iteratable.hxx"
USING_NAMESPACE_ALTAIR;


Object* Iteratable::inject(Object* const& this_value, Object* (*binary_block)(Object* const&, Object* const&))
{
    Object* result = this_value;

    Stream* it = readStream();
    while ( it->atEnd() ) {
        Object* element = it->next();

        result = binary_block( result, element );
    }
    it->release();

    return result;
}


Stream* Iteratable::readStream() const
{
    subclassResponsibility();

    return NULL;
}
// Local Variables:
//   coding: utf-8
// End:
