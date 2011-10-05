#ifndef altair_Object_hxx
#define altair_Object_hxx

#ifdef HAVE_CONFIG_H
#   include "config.h"
#endif  /* HAVE_CONFIG_H */


BEGIN_NAMESPACE_ALTAIR


class Association;
class Class;
class OrderedCollection;
class String;
class Symbol;


/**
 * 
 */
class Object
{
 public:
    /**
     * 
     */
    Object();
    /**
     * 
     */
    Object(const Object& other);


    /**
     * 
     */
    virtual ~Object();

 public:
    /**
     * 偽を返します。
     */
    virtual bool isNil() const { return false; }


    /**
     * 真を返します。
     */
    virtual bool notNil() const { return true; }


    /**
     * レシーバが指定されたクラスのインスタンスであるか、その派生クラスのインスタンスだった場合、真を返します。
     */
    virtual bool isKindOf(const Class* klass) const;


    /**
     * レシーバが指定されたクラスのインスタンスである場合、真を返します。
     */
    virtual bool isInstanceOf(const Class* klass) const;


    /**
     * 
     */
    virtual bool respondsTo(const Symbol* const& asymbol) const;


    /**
     * 
     */
    virtual bool isCObject() const { return false; }


    /**
     * 
     */
    virtual bool isString() const { return false; }


    /**
     * 
     */
    virtual bool isCharacterArray() const { return false; }


    /**
     * 
     */
    virtual bool isSymbol() const { return false; }


    /**
     * 
     */
    virtual bool isCharacter() const { return false; }


    /**
     * 
     */
    virtual bool isNumber() const { return false; }


    /**
     * 
     */
    virtual bool isFloat() const { return false; }


    /**
     * 
     */
    virtual bool isInteger() const { return false; }


    /**
     * 
     */
    virtual bool isSmallInteger() const { return false; }


    /**
     * 
     */
    virtual bool isNumespace() const { return false; }


    /**
     * 
     */
    virtual bool isClass() const { return false; }


    /**
     * 
     */
    virtual bool isArray() const { return false; }


    /**
     * 
     */
    virtual bool isBehavior() const { return false; }


    /**
     * 
     */
    virtual bool isMeta() const { return isMetaClass(); }


    /**
     * 
     */
    virtual bool isMetaClass() const { return false; }


    /**
     * 
     */
    virtual Object* const copy() const {
        return shallowCopy( postCopy() );
    }


    /**
     * 
     */
    virtual Object* const postCopy() const {
        return this;
    }


    /**
     * 
     */
    virtual Object* const deepCopy() const;


    /**
     * 
     */
    virtual Class* const species() const { return getClass(); }


    /**
     * レシーバーを返します。
     */
    virtual Object* yourself() const { return this; }


    /**
     * 依存関係を持つオブジェクトを追加します。
     */
    virtual void addDependent(Object* const& an_object);


    /**
     * 依存関係を持つオブジェクトの中から指定されたオブジェクトを削除します。
     */
    virtual Object* const removeDependent(Object* const& an_object);


    /**
     * 
     */
    virtual OrderedCollection* const dependants() const;


    /**
     * 
     */
    virtual void release();


    /**
     * 
     */
    virtual void addToBeFinalized();


    /**
     * 
     */
    virtual void removeToBeFinalized();


    /**
     * 何もしません。
     */
    virtual void mourn() {}


    /**
     * 
     */
    virtual void finalize() {}


    /**
     * 
     */
    virtual void changed() { changed( this ); }
    /**
     * 
     */
    virtual void changed(Object* const& a_parameter);


    /**
     * changed メンバ関数が呼び出されたときに呼び出されますが、Object では何もしません。
     */
    virtual void update(Object* const& a_parameter) {}


    /**
     * 
     */
    virtual void broadcast(const Symbol* const& a_symbol);
    /**
     * 
     */
    virtual void broadcast(const Symbol* const& a_symbol, Object* const& arg1, Object* const& arg2);


    /**
     * 
     */
    virtual void broadcastWithArray(const Symbol* const& a_symbol, const Array* const& an_array);


    /**
     * 
     */
    virtual Association* const createAssociation(Object* const& an_object) const;


    /**
     * 
     */
    virtual String* const displayString() const;


    /**
     * 
     */
    virtual void displayOn(Stream* const& a_stream) const;


    /**
     * 
     */
    virtual void display() const;


    /**
     * 
     */
    virtual void displayNl() const;


    /**
     * 
     */
    virtual String* const printString() const;


    /**
     * 
     */
    virtual void printOn(Stream* const& a_stream) const;


    /**
     * 
     */
    void basicPrintOn(Stream* const& a_stream) const;


    /**
     * 
     */
    virtual void print() const;


    /**
     * 
     */
    virtual void printNl() const;


    /**
     * 
     */
    void basicPrintNl() const;


    /**
     * \ingroup storing
     */
    virtual String* const storeString() const;


    /**
     * \ingroup storing
     */
    virtual void storeLiteralOn(Stream* const& a_stream) const;


    /**
     * \ingroup storing
     */
    virtual void storeOn(Stream* const& a_stream) const;


    /**
     * \ingroup storing
     */
    virtual void store() const;


    /**
     * \ingroup storing
     */
    virtual void storeNl() const;


    /**
     * \ingroup saving and loading
     */
    virtual void binaryRepresentationObject();


    /**
     * \ingroup saving and loading
     */
    virtual void postLoad() {}


    /**
     * デフォルトではメンバ関数 postLoad を呼び出すだけです。
     * \ingroup saving and loading
     */
    virtual void postStore() { postLoad(); }


    /**
     * オブジェクトをダンプする前に呼び出されます。デフォルトでは何もしません。
     * \ingroup saving and loading
     */
    virtual void preStore() {}


    /**
     * デフォルトでは例外を発生させます。
     * \ingroup saving and loading
     */
    virtual void reconstructOriginalObject();


    /**
     * トランスクリプトにレシーバの全てのインスタンス変数をプリントします。
     * \ingroup debugging
     */
    virtual void examine() const;


    /**
     * examine メンバ関数と同じです。
     * \ingroup debugging
     */
    virtual void inspect() const;


    /**
     *
     * \ingroup debugging
     */
    virtual void examineOn(Stream* const& a_stream) const;


    /**
     * レシーバの検査すべき要素の数を返します。
     * \ingroup debugging
     */
    virtual int validSize() const { return basicSize(); }


    /**
     * \ingroup built ins
     * レシーバを参照するオブジェクトの配列を返します。
     */
    Collection* const allOwnsers() const;


    /**
     * 
     */
    Object* const changeClassTo(Behavior* const& a_behavior);
    
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Object_hxx */
// Local Variables:
//   coding: utf-8
// End:
