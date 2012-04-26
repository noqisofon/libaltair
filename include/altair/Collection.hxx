#ifndef altair_Collection_hxx
#define altair_Collection_hxx

#include "altair/Iteratable.hxx"


BEGIN_NAMESPACE_ALTAIR


class Array;
class ByteArray;
class Bag;
class Set;
class String;
class UnicodeString;


/**
 * 
 */
class Collection : public Iteratable
{
 public:
    /*!
      \name instance creation
     */
    /*! @{ */
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
    /*! @} */

 public:
    /*!
      \name adding
     */
    /*! @{ */
    /**
     * 
     */
    virtual Collection* const& add(Object* const& new_object) = 0;


    /**
     * 
     */
    virtual Collection* const& addAll(const Collection* const& a_collection);
    /*! @} */


    /*!
      \name removing
     */
    /*! @{ */
    /**
     * レシーバから全ての要素を取り除きます。
     */
    virtual Collection* const empty();


    /**
     * レシーバから old_object を取り除きます。ない場合は ElementNotFoundException を返します。
     */
    virtual Object* const remove(Object* const& old_object);
    /*!
     * 
     */
    virtual Object* const remove(Object* const& old_object, Object* const (*an_exception_block)(const Collection* const&, Object* const&));


    /**
     * レシーバから a_collection を取り除きます。
     */
    virtual const Collection* const removeAll(const Collection* const& a_collection);
    /**
     * レシーバから a_collection を取り除きます。
     */
    virtual const Collection* const removeAll(const Collection* const& a_collection, Object* const (*a_block)(const Collection* const&, Object* const&));
    /*! @} */


    /*!
      \name testing collections
     */
    /*! @{ */
    /**
     * 
     */
    virtual bool isSequenceable() const { return false; }


    /**
     * レシーバがどれだけの要素を保持できるかを返します。
     */
    virtual size_t capacity() const { basicSize(); }


    /**
     * レシーバに保持されている要素の数を返します。
     */
    virtual size_t size() const;


    /**
     * 
     */
    virtual bool includes(const Object* const& an_object) const;


    /**
     * 
     */
    virtual bool identityIncludes(const Object* const& an_object) const;


    /**
     * レシーバーに指定されたコレクションの要素が全て含まれていれば真を返します。
     */
    virtual bool includesAllOf(const Collection* const& a_collection) const;


    /**
     * レシーバーに指定されたコレクションの要素の何れかが含まれていれば真を返します。
     */
    virtual bool includesAnyOf(const Collection* const& a_collection) const;


    /**
     * レシーバに要素が含まれていない時に真を返します。
     */
    virtual bool isEmpty() const;


    /**
     * レシーバに要素が含まれている時に真を返します。
     */
    virtual bool notEmpty() const;


    /**
     * 
     */
    virtual bool occurencesOf(const Object* const& an_object) const;
    /*! @} */


    /*!
      \name concatenating
     */
    /*! @{ */
#if defined(ALTAIR_USING_FUNCTOR)
    /*!
     * 
     */
    virtual Collection* const join() const;
#endif  /* defined(ALTAIR_USING_FUNCTOR) */
    /*! @} */


    /*!
      \name enumeration
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* const anyOne() const;


    /*!
     * 
     */
    virtual Stream* const readStream() const;


    /*!
     * 
     */
    virtual Collection* const select(bool (*a_block)(Object* const&)) const;


    /*!
     * 
     */
    virtual Collection* const reject(bool (*a_block)(Object* const&)) const;


    /*!
     * 
     */
    virtual Collection* const collect(Object* const (*a_block)(Object* const&)) const;


#if defined(ALTAIR_USING_FUNCTOR)
    /*!
     * 
     */
    virtual Collection* const gather(Object* const (*a_block)(Object* const&)) const;
#endif  /* defined(ALTAIR_USING_FUNCTOR) */
    /*! @} */


    /*!
      \name converting
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Array* const asArray() const;


    /*!
     * 
     */
    virtual ByteArray* const asByteArray() const;


    /*!
     * 
     */
    virtual Bag* const asBag() const;


    /*!
     * 
     */
    virtual Set* const asSet() const;


    /*!
     * 
     */
    virtual String* const asString() const;


    /*!
     * 
     */
    virtual UnicodeString* const asUnicodeString() const;


    /*!
     * 
     */
    virtual OrderedCollection* const asOrderedCollection() const;


    /*!
     * 
     */
    virtual Collection* const asSortedCollection() const;
    /*!
     * 
     */
    virtual Collection* const asSortedCollection(bool (*a_block)(const Object* const&)) const;
    /*! @} */


    /*!
      \name sorting
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Collection* const sorted() const;
    /*!
     * 
     */
    virtual Collection* const sorted(bool (*a_block)(const Object* const&)) const;
    /*! @} */


    /*!
      \name copying collections
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Collection* const copyReplacing(Object* const& target_object, Object* const& new_object) const;


    /*!
     * 
     */
    virtual Collection* const copyWith(Object* const& new_element) const;


    /*!
     * 
     */
    virtual Collection* const copyWithout(Object* const& old_element) const;
    /*! @} */

 protected:
    /*!
      \name copying collections
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Collection* const copyEmpty() const;
    /*!
     * 
     */
    virtual Collection* const copyEmpty(int new_size) const;


    /*!
     * 
     */
    virtual Collection* const copyEmptyForCollect() const;
    /*!
     * 
     */
    virtual Collection* const copyEmptyForCollect(int size) const;


    /*!
     * 
     */
    virtual void rehash() {}
    /*! @} */
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Collection_hxx */
// Local Variables:
//   coding: utf-8
// End:
