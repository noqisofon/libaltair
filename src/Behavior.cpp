//  
//  Behavior.cpp
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
#include "altair/SequenceableCollection.hxx"
#include "altair/String.hxx"
#include "altair/Symbol.hxx"

#include "altair/Behavior.hxx"
USING_NAMESPACE_ALTAIR;


#if defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE
Object* Behavior::addInstVarName(const String* const& a_string)
{
    validateIndentifier( a_string );

    Symbol* symbol = a_string->asSymbol();

    SequenceableCollection* new_instance_variables;
    if ( ALTAIR_ISNIL(instance_varialbes_) )
        new_instance_variables = ALTAIR_ARRAY1(symbol);
    else
        new_instance_variables = __REINTERPRET_CAST(SequenceableCollection *, instance_varialbes_->copyWith( symbol ));

    bool duplicated = superclass()->allInstVarNames()->includes( symbol );

    updateInstanceVars( new_instance_variables, getShape() );
#   if defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_COMPLETE_TRANSPLANT_RATE
    if ( duplicated )
        compileAll();
    compileAllSubclasses();
#   endif  /* defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_COMPLETE_TRANSPLANT_RATE */
}


static bool remove_inst_var_name_find_last_block(const Object* const& self, Object* const& each)
// {
//     ContextPart* context = self->context();

//     Symbol* symbol = __REINTERPRET_CAST(Symbol *, context->holderAt( context->indexOfClass( Symbol::getCurrentClass() ) ));

     return each->equals( symbol );
}


void Behavior::removeInstVarName(const String* const& a_string)
{
    //ContextPart* method_context = ContextPart::thisContext( "removeInstVarName" );
    Symbol* symbol;
    int index;

    symbol = a_string->asSymbol();
    //method_context->holderAdd( symbol );
    index = instance_varialbes_->findLast( this, remove_inst_var_name_find_last_block );
}
#endif  /* defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE */


#if defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE
int Behavior::instanceCount() const
{
    int count = 0;
    Object* an_instance = someInstance();

    while ( ALTAIR_NOTNIL(an_instance) ) {
        ++ count;

        an_instance = an_instance->nextInstance();
    }
    return count;
}


static int null_exception_block(const Object* const&, const Object* const&)
{
    return 0;
}


int Behavior::indexOfInstVar(const String* const& a_string) const
{
    SequenceableCollection* temp = allInstVarNames();

    int ret = temp->indexOfLast( a_string->asSymbol(), null_exception_block );
    temp->release();

    return ret;
}
int Behavior::indexOfInstVar(const String* const& a_string, int (*a_block)(const Object* const&, const Object* const&)) const
{
    SequenceableCollection* temp = allInstVarNames();

    int ret = temp->indexOfLast( a_string->asSymbol(), a_block );
    temp->release();

    return ret;
}
#endif  /* defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE */


bool Behavior::isPointers() const
{
    return false;
}


bool Behavior::isVariable() const
{
    return false;
}


Symbol* Behavior::getShape() const
{
    return NULL;
}


// Local Variables:
//   coding: utf-8
// End:
