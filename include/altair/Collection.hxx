#ifndef altair_Collection_hxx
#define altair_Collection_hxx

#include "altair/Iteratable.hxx"


BEGIN_NAMESPACE_ALTAIR


class Array;


/**
 * 
 */
class Collection : public Iteratable
{
 public:
    /**
     * 
     */
    static Collection* from(Array* const& an_array);


    /**
     * 
     */
    static Collection* with(Object* const& an_object);
    /**
     * 
     */
    static Collection* with(Object* const& first_object, Object* const& second_object);
    /**
     * 
     */
    static Collection* with(Object* const& first_object, Object* const& second_object, Object* const& third_object);
    /**
     * 
     */
    static Collection* with(Object* const& first_object, Object* const& second_object, Object* const& third_object, Object* const& fourth_object);
    /**
     * 
     */
    static Collection* with(Object* const& first_object, Object* const& second_object, Object* const& third_object, Object* const& fourth_object, Object* const& fifth_object);


    /**
     * 
     */
    static Collection* withAll(Collection* const& an_collection);


#if defined(ALTAIR_USING_FUNCTOR)
    /**
     * 
     */
    static Collection* withJoin(Collection* const& an_collection);
#endif  /* defined(ALTAIR_USING_FUNCTOR) */

 public:
    /**
     * 
     */
    virtual Collection* const add(Object* const& new_object) = 0;


    /**
     * 
     */
    virtual Collection* const addAll(const Collection* const& a_collection);


    /**
     * レシーバから全ての要素を取り除きます。
     * \ingroup removing
     */
    virtual Collection* const empty();


    /**
     * 
     */
    virtual bool tryRemove(Object* const& old_object) = 0;


    /**
     * レシーバから old_object を取り除きます。ない場合は ElementNotFoundException を返します。
     * \ingroup removing
     */
    virtual Object* const remove(Object* const& old_object);


    /**
     * レシーバから a_collection を取り除きます。
     * \ingroup removing
     */
    virtual Collection* const removeAll(const Collection* const& a_collection);


    /**
     * 
     * \ingroup testing collections
     */
    virtual bool isSequenceable() const { return false; }


    /**
     * レシーバがどれだけの要素を保持できるかを返します。
     * \ingroup testing collections
     */
    virtual int capacity() const { return basicSize(); }


    /**
     * レシーバに保持されている要素の数を返します。
     */
    virtual int size() const;


    /**
     *
     * \ingroup testing collections
     */
    virtual bool includes(const Object* const& an_object) const;


    /**
     *
     * \ingroup testing collections
     */
    virtual bool identityIncludes(const Object* const& an_object) const;


    /**
     * レシーバーに指定されたコレクションの要素が全て含まれていれば真を返します。
     * \ingroup testing collections
     */
    virtual bool includesAllOf(const Collection* const& a_collection) const;


    /**
     * レシーバーに指定されたコレクションの要素の何れかが含まれていれば真を返します。
     * \ingroup testing collections
     */
    virtual bool includesAnyOf(const Collection* const& a_collection) const;


    /**
     * レシーバに要素が含まれていない時に真を返します。
     * \ingroup testing collections
     */
    virtual bool isEmpty() const;


    /**
     * レシーバに要素が含まれている時に真を返します。
     * \ingroup testing collections
     */
    virtual bool notEmpty() const;


    /**
     * 
     */
    virtual bool occurencesOf(const Object* const& an_object) const;
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Collection_hxx */
// Local Variables:
//   coding: utf-8
// End:
