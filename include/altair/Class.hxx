//  
//  Class.hxx
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
#ifndef altair_Class_hxx
#define altair_Class_hxx

#include "altair/ClassDescription.hxx"


BEGIN_NAMESPACE_ALTAIR


class CompiledBlock;
class Encoding;
class List;
class Error;


/**
 * 
 */
class Class : public ClassDescription
{
 public:
    /*! \name initialize
     */
    /*! @{ */
    /*!
     * 
     */
    static void initialize();
    /*! @{ */

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
    virtual String* name() const { return name_; }


#if defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE
    /**
     * 
     */
    virtual String* comment() const { return comment_; }


    /**
     * 
     */
    virtual Namespace* environment() const { return envinronment_; }
    /**
     * 
     */
    virtual void environment(Namespace* const& a_namespace);
#endif  /* defined(ALTAIR_TRANSPLANTLY) && ALTAIR_TRANSPLANTLY < LT_STANDARD_TRANSPLANT_RATE */


    /*! \name instance creation
     */
    /*! @{ */
    /*!
     *
     */
    virtual Object* createInstance() const;


    /*!
     *
     */
    virtual Object* createInstance(size_t size) const;


    /*!
     *
     */
    virtual Object* basicNew() const;


    /*!
     *
     */
    virtual Object* basicNew(size_t size) const;
    /*! @} */


    /*! \name printing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual String* article() const;
    /*! @} */


    /*! \name testing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool equals(const Class* const& a_class) const;
    /*! @} */


    /*! \name testing functionality
     */
    /*! @{ */
    /*!
     * 
     */
    virtual const Class* asClass() const { return this; }


    /*!
     * 
     */
    virtual bool isClass() const { return true; }
    /*! @} */


    /*!
     *
     */
    virtual bool isUnicode() const { return true; }


    /*!
     * 
     */
    virtual Encoding* defaultEncoding();

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
// Local Variables:
//   coding: utf-8
// End:
