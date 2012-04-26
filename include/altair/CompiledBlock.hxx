#ifndef altair_CompiledBlock_hxx
#define altair_CompiledBlock_hxx


BEGIN_NAMESPACE_ALTAIR


class Object;


typedef int (*AbsentBlock)(const Object* const&);
typedef int (*ExceptionBlock)(const Object* const&);


END_NAMESPACE_ALTAIR


#endif  /* altair_CompiledBlock_hxx */
