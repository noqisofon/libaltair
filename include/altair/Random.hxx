#ifndef altair_Random_hxx
#define altair_Random_hxx

#include "Stream.hxx"


BEGIN_NAMESPACE_ALTAIR


/**
 * 乱数ジェネレーターストリームで、0 から 1 までの浮動小数点値を返します。
 */
class Random : public Stream
{
    typedef Stream _Super;

 public:
    /*!
     *
     */
    static int mtSize();


    /*! \name instance cration
     */
    /*! @{ */
    /*!
     *
     */
    static Random* seed(int seed);
    /*! @} */


    /*! \name shortcuts
     */
    /*! @{ */
    /*!
     * 
     */
    static uint32_t nextInt();


    /*!
     * 
     */
    static uint32_t betweenAnd(int low, int high);
    /*! @} */

 public:
    /*!
     *
     */
    Random();
    /*!
     *
     */
    Random(int seed);

 public:
    /*! /name testing
     */
    /*! @{ */
    /*!
     * 
     */
    int chiSquare();


    /*!
     * 
     */
    int chiSquareRange(int n, int r);
    /*! @} */


    /*! /name basic
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool atEnd() const { return false; }


    /*!
     * 
     */
    uint32_t between(int low, int high);


    /*!
     * 
     */
    virtual Object* next();


    /*!
     * 
     */
    Object* nextLimit(int an_integer);


    /*!
     * 
     */
    virtual void nextPut(Object* const& an_object);


    /*!
     * 
     */
    virtual uint32_t primNext();


    /*!
     * 
     */
    virtual int32_t primNextInt();


    /*!
     * 
     */
    virtual float primNextFloat();


    /*!
     * 
     */
    virtual double primNextDouble();


    /*!
     * 
     */
    virtual uint32_t primNextLimit(int an_integer);
    /*! @} */


    /*! /name basic
     */
    /*! @{ */
    /*!
     *
     */
    void setSeed(int seed);
    /*! @} */

 protected:
    /*!
     * 
     */
    void setSeed();

 private:
    uint32_t mt_[642];
    int32_t index_;
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Random_hxx */
// Local Variables:
//   coding: utf-8
// End:
