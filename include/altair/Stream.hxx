//  
//  Stream.hxx
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
#ifndef altair_Stream_hxx
#define altair_Stream_hxx

#include "altair/Iteratable.hxx"


BEGIN_NAMESPACE_ALTAIR


class SequenceableCollection;
class OrderedCollection;
class String;
class Encoding;


/*!
 *
 */
class Stream : public Iteratable
{
 public:
    /*!
     \name accessing-reading
     */
    /*! @{ */
    /*!
     * 
     */
    virtual const String* file() const { return NULL; }


    /*!
     * 
     */
    virtual const String* name() const { return NULL; }


    /*!
     * 
     */
    virtual Object* next();
    /*!
     * 
     */
    virtual SequenceableCollection* next(int an_integer);
    /*!
     * 
     */
    virtual Object* next(int an_integer, SequenceableCollection* const& answer, int starting_pos);


    /*!
     * 
     */
    virtual int nextPutAllOn(int an_integer, Stream* const& a_stream);


    /*!
     * 
     */
    virtual SequenceableCollection* nextAvailable(int an_integer);
    /*!
     * 
     */
    virtual int nextAvailable(int an_integer, Stream* const& a_stream);


    /*!
     * 
     */
    virtual int nextAvailableInto(int an_integer, SequenceableCollection* const& a_collection, int startint_pos);


    /*!
     * 
     */
    virtual bool nextMatchFor(const Object* const& an_object);


    /*!
     * 
     */
    virtual OrderedCollection* splitAt(const Object* const& an_object);


    /*!
     * 
     */
    virtual SequenceableCollection* contents();


    /*!
     * 
     */
    virtual SequenceableCollection* nextLine();


    /*!
     * 
     */
    virtual SequenceableCollection* upTo(const Object* const& an_object);


    /*!
     * 
     */
    virtual SequenceableCollection* upToAll(const SequenceableCollection* const& a_collection);
    /*! @} */


    /*!
     \name accessing-writing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void nextPut(Object* const& an_object);
    /*!
     * 
     */
    virtual void nextPut(char ch);
    /*!
     * 
     */
    virtual Object* nextPut(int n, Object* const& an_object);
    /*!
     * 
     */
    virtual Object*  nextPut(int n, char ch);


    /*!
     * 
     */
    virtual SequenceableCollection* nextPutAll(SequenceableCollection* const& a_collection);
    /*!
     * 
     */
    virtual SequenceableCollection* nextPutAll(const char* const& cstring);
    /*!
     * 
     */
    virtual SequenceableCollection* nextPutAll(int n, SequenceableCollection* const& a_collection, int start);


    /*!
     * 
     */
    virtual void nextPutAllFlush(SequenceableCollection* const& a_collection);


    /*!
     * 
     */
    virtual void nextPutAllOn(Stream* const& a_stream);
    /*! @} */


    /*! \name testing
      
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool atEnd() const;


    /*!
     * 
     */
    virtual Stream* readStream() const;


    /*!
     * 
     */
    virtual bool isSequenceable() const { return false; }


    /*!
     * 
     */
    virtual bool isExternalStream() const { return false; }
    /*! @} */


    /*! \name basic
      
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Class* species() const;
    /*! @} */


    /*! \name character writing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool isUnicode() const;


    /*!
     *
     */
    virtual Encoding* encoding() const;


    /*!
     * 
     */
    virtual void cr();


    /*!
     * 
     */
    virtual void nl();


    /*!
     * 
     */
    virtual void crTab() {
        cr();
        tab();
    }


    /*!
     * 
     */
    virtual void nlTab() {
        nl();
        tab();
    }


    /*!
     * 
     */
    virtual void space();
    /*!
     * 
     */
    virtual void space(int n);


    /*!
     * 
     */
    virtual void tab();
    /*!
     * 
     */
    virtual void tab(int n);
    /*! @} */


    /*! \name polymorphism
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void close() {}


    /*!
     * 
     */
    virtual Object* pastEnd();


    /*!
     * 
     */
    virtual void flush() {}
    /*! @} */


    /*! \name printing
      
     */
    /*! @{ */
#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
    /*!
     * 
     */
    virtual void display(const Object* const& an_object);
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


    /*!
     * 
     */
    virtual void print(const Object* const& an_object);
    /*! @} */


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
    /*! \name storing
      
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void store(const Object* const& an_object);
    /*! @} */
#endif  /* defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */


#if 0
    /*! \name filing out
      
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void fileOut(const Class* const& a_class);
    /*! @} */
#endif


    /*! \name positioning
      
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool isPositionable() const { return false; }


    /*!
     * 
     */
    virtual bool skip(int an_integer);


    /*!
     * 
     */
    virtual bool skipTo(const Object* const& an_object);


    /*!
     * 
     */
    virtual bool skipToAll(const Collection* const& a_collection);


    /*!
     * 
     */
    virtual bool peekFor(const Object* const& an_object);
    /*! @} */


    /*! \name streaming protocol
      
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void nextAvailablePutAllOn(Stream* const& a_stream);
    /*! @} */


    /*! \name private
      
     */
    /*! @{ */
    /*!
     * 
     */
    virtual SequenceableCollection* prefixTableFor(const Collection* const& a_collection);
    /*! @} */


    /*! \name built ins
      
     */
    /*! @{ */
#if 0
    /*!
     * 
     */
    virtual Object* fileIn();


    /*!
     * 
     */
    virtual Object* fileInLine(int line_num, File* const& a_file, int char_pos_int);
#endif
    /*! @} */
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Stream_hxx */
// Local Variables:
//   coding: utf-8
// End:
