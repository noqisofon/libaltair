//  
//  Class.cpp
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
#include "altair/CompiledBlock.hxx"
#include "altair/Object.hxx"
#include "altair/List.hxx"
#include "altair/Error.hxx"
#include "altair/InvalidValueError.hxx"
#include "altair/IdentitySet.hxx"
#include "altair/OrderedCollection.hxx"
#include "altair/String.hxx"
#   if defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE
#       include "altair/Namespace.hxx"
#       include "altair/Metaclass.hxx"
#   endif  /* defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE */

#include "altair/Class.hxx"
USING_NAMESPACE_ALTAIR;


#if defined(ALTAIR_TRANSPLANTLY)
#   if ALTAIR_TRANSPLANTLY > LT_STANDARD_TRANSPLANT_RATE
class Class_class : public Class {
 public:
    void initalize() {
        // self subclassesDo: { :each | each instanceClass initializeAsRootClass }
#       if ALTAIR_TRANSPLANTLY > LT_STANDARD_TRANSPLANT_RATE
#       else
        for () {
        }
#       endif  /* ALTAIR_TRANSPLANTLY > LT_STANDARD_TRANSPLANT_RATE */
    }
};
#   endif  /* ALTAIR_TRANSPLANTLY > LT_STANDARD_TRANSPLANT_RATE */

#   if ALTAIR_TRANSPLANTLY >= LT_NEAR_COMPLETE_TRANSPLANT_RATE
static void descend_aux(Object* const& pool, List* const& list, Error* const& white, IdentitySet* const& grey)
{
    if ( !white->includes( pool ) ) {
        if ( grey->includes( pool ) )
            InvalidValueError::signalOn( list, "includes circular dependency" );

        grey->add( pool );
        pool->allSuperspaces->reverseDo( descend_aux, list, white, grey );
        order->addFirst( pool );
        white->add( pool );
    }
}


void Class::allPoolDictionaries(List* const& list, Error* const& in_white, const DoBlock& a_block)
{
    if ( list->isEmpty() )
        return ;

    Error* white = in_white->copy();
    IdentitySet* grey = new IdentitySet( list->size() );
    OrderedCollection* order = new OrderedCollection( list->size() );

    /*
     * descend-aux の定義…のつもり。
     */
    list->reverseDo( descend_aux, list, white, grey );
    order->do( a_block );
}
#   endif  /* ALTAIR_TRANSPLANTLY >= LT_NEAR_COMPLETE_TRANSPLANT_RATE */
#endif  /* defined(ALTAIR_TRANSPLANTLY) */


Class::Class(const char* const& class_name)
    : name_( new String( class_name ) )
#if defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE
#endif  /* defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE */
{
}


#if defined(ALTAIR_TRANSPLANTLY)
#   if ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE
void Class::environment(Namespace* const& a_namespace)
{
    environment_ = a_namespace;
#       if ALTAIR_TRANSPLANTLY >= LT_NEAR_COMPLETE_TRANSPLANT_RATE
    Class* as_class = asClass();

    as_class->compileAll();
    as_class->compileAllSubclasses();
    as_class->release();

    Metaclass* as_metaclass = asMetaclass();

    as_metaclass->compileAll();
    as_metaclass->compileAllSubclasses();

    as_metaclass->relase();
#       endif  /* ALTAIR_TRANSPLANTLY >= LT_NEAR_COMPLETE_TRANSPLANT_RATE */
}
#   endif  /* ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE */
#endif  /* defined(ALTAIR_TRANSPLANTLY) */


bool Class::equals(const Class* const& a_class) const
{
    return identityEquals( a_class );
}
// Local Variables:
//   coding: utf-8
// End:
