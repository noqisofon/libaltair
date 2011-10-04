#ifndef altair_Random_hxx
#define altair_Random_hxx

#include "Stream.hxx"


BEGIN_NAMESPACE_ALTAIR


/**
 * 乱数ジェネレーターストリームで、0 から 1 までの浮動小数点値を返します。
 */
class Random : public Stream
{
 public:
    typedef Stream  _Base;
    typedef Random  _This;

 public:
    /**
     * 
     */
    Random();
    /**
     * 
     */
    Random(int mt_size);

 public:
    /**
     * 
     */
    double chiSquare() { return chiSquare( 1000, 100 ); }
    /**
     * 
     */
    double chiSquare(int n, int range);


    /**
     * このストリームに終端はありません。常に false を返します。
     * \ingroup basic
     */
    virtual bool atEnd() const { return false; }


    /**
     * \var low と \var high の間のランダムな整数を返します。
     * \ingroup basic
     */
    int between(int low, int high);


    /**
     * 最大 32 bit の精度のランダムな整数を返します。
     * \ingroup basic
     */
    int next();


    /**
     * 0 と an_integer の間に分布するランダムな整数を返します。
     * \ingroup basic
     */
    int nextLimit(int an_integer);


    /**
     * 
     * \ingroup basic
     */
    virtual void nextPut(Object* const& value);


    /**
     * 
     */
    void setSeed(int an_integer);
    

 public:
    /**
     * MT19937 は 624 の大きさを持っています。
     */
    static int mtSize() { return 624; }


    /**
     * an_integer を乱数の種にした新しい乱数ジェネレーターを返します。
     */
    static Random* const seed(int an_integer);


    /**
     * 0 から 1(除外)のaidaの乱数を反します。
     */
    static double next();


    /**
     * 与えられた局地の間のランダムな整数を返します。
     */
    static int between(int low, int high);


    /**
     * 
     */
    

 private:
    static Random source_;
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Random_hxx */
