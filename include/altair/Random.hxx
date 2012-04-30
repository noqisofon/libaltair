//  
//  Random.hxx
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
