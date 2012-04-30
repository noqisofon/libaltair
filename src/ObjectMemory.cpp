//  
//  ObjectMemory.cpp
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
#include "altair/Association.hxx"
#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
#   include "altair/Processor.hxx"
#   include "altair/Symbol.hxx"
#   include "altair/Semaphone.hxx"
#   include "altair/Fraction.hxx"
#   include "altair/LargeInteger.hxx"
#   include "altair/Date.hxx"
#   include "altair/Time.hxx"
#   include "altair/FileDescriptor.hxx"
#   include "altair/Namespace.hxx"
#   include "altair/SystemDirectory.hxx"
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */

#include "altair/ObjectMemory.hxx"
USING_NAMESPACE_ALTAIR;


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
class ObjectMemory_class : public Class
{
 public:
    typedef  Class _Super;

 public:
    virtual ~ObjectMemory_class() {}

 public:
    /**
     * 
     */
    void changed(Symbol* const& a_symbol) {
        Semaphone* semaphon;
        int priority;

        if ( a_symbol->equals( ALTAIR_SYMBOL(returnFromSnapShot) ) )
            priority = Processor::highIOPriority();
        else
            priority = Processor::userSchedulingPriority();

        if ( Processor::activePriority < priority ) {
            semaphon = new Semaphone();
            /*
             * 他に何かが起こる前のモジュールとライブラリが初期化されていることを確認します。
             */
            {
                DLD::update( a_symbol );
                _Base::changed( a_symbol );
                semaphon->signal();
            } semaphon->forkAt( priority );

            semaphon->wait();
        } else {
            DLD::update( a_symbol );
            _Base::changed( a_symbol );
        }

        if ( a_symbol->equals( ALTAIR_SYMBOL(aboutToQuit) ) ) {
            Processor::activeProcess()->priority( Processor::idlePriority() );
            Processor::yield();
        }
    }


    /**
     * 
     */
    void initialize() {
        Object::initialize();
        Class::initialize();
        Fraction::initialize();
        LargeInteger::initialize();
        Date::initialize();
        Time::initialize();
        FileDescriptor::initialize();
        Namespace::initialize();
        Processor::initialize();
        SystemDirectory::initialize();

        changed( ALTAIR_SYMBOL(returnFromSnapshot) );
    }

 private:
    /**
     * 
     */
    ObjectMemory_class()
        : _Super() {
    }
};
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */
// Local Variables:
//   coding: utf-8
// End:
