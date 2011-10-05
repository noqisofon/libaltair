#include <altair/Object.hxx>
#include <altair/Processor.hxx>
#include <altair/Symbol.hxx>
#include <altair/Semaphone.hxx>
#include <altair/Fraction.hxx>
#include <altair/LargeInteger.hxx>
#include <altair/Date.hxx>
#include <altair/Time.hxx>
#include <altair/FileDescriptor.hxx>
#include <altair/Namespace.hxx>
#include <altair/SystemDirectory.hxx>

#include <altair/ObjectMemory.hxx>
USING_NAMESPACE_ALTAIR;


class ObjectMemory_class : public Class {
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
    ObjectMemory_class() : Class() {
    }
};
// Local Variables:
//   coding: utf-8
// End:
