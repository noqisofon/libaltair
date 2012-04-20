#ifndef altair_Class_hxx
#define altair_Class_hxx

#include "altair/ClassDescription.hxx"


BEGIN_NAMESPACE_ALTAIR


class CompiledBlock;
class List;
class Error;


/**
 * 
 */
class Class : public ClassDescription
{
 protected:
    /**
     * 
     */
    Class(const char* const& class_name);


    /**
     * 
     */
    virtual ~Class();

 public:
    /**
     * このクラスの名前を返します。
     */
    virtual String* const name() const { return name_; }


#if defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE
    /**
     * 
     */
    virtual String* const comment() const { return comment_; }


    /**
     * 
     */
    virtual Namespace* const environment() const { return envinronment_; }
    /**
     * 
     */
    virtual void environment(Namespace* const& a_namespace);
#endif  /* defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE */

 private:
    /**
     * \ingroup private
     */
    static void allPoolDictionaries(List* const& list, Error* const& in_white, const CompiledBlock& a_block);

 private:
    String* name_;
#if defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE
    String* category_;
    String* comment_;
    Namespace* encironment_;
    VariableCollection* class_variables_;
    Pool* shared_pools_;
    Handler* pragma_handlers_;
#endif  /* defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE */
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Class_hxx */
