#ifndef altair_Array_hxx
#define altair_Array_hxx

#include "altair/ArrayedCollection.hxx"


BEGIN_NAMESPACE_ALTAIR


class Stream;


/**
 * 
 */
class Array : public ArrayedCollection
{
    typedef ArrayedCollection _Super;

 public:
    /*!
      \name instance creation
     */
    /*! @{ */
    /*!
     * 
     */
    static Array* const from(Array* const& an_array) {
        return an_array;
    }


    /**
     * 
     */
    static Array* with(Object* const& an_object);
    /**
     * 
     */
    static Array* with(Object* const& first_object, Object* const& second_object);
    /**
     * 
     */
    static Array* with(Object* const& first_object, Object* const& second_object, Object* const& third_object);
    /**
     * 
     */
    static Array* with(Object* const& first_object, Object* const& second_object, Object* const& third_object, Object* const& fourth_object);
    /**
     * 
     */
    static Array* with(Object* const& first_object, Object* const& second_object, Object* const& third_object, Object* const& fourth_object, Object* const& fifth_object);


    /**
     * 
     */
    static Array* withAll(Collection* const& an_collection);


#if defined(ALTAIR_USING_FUNCTOR)
    /**
     * 
     */
    static Array* withJoin(Collection* const& an_collection);
#endif  /* defined(ALTAIR_USING_FUNCTOR) */
    /*! @} */

 public:
    /*!
     * 
     */
    Array();
    /*!
     * 
     */
    Array(size_t size, Object* const& an_object = NULL);
    /*!
     * 
     */
    Array(const Array& other);
    /*!
     * 
     */
    Array(const Collection& other);


    /*!
     * 
     */
    virtual ~Array();

 public:
    /*!
      \name built ins
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* const at(int an_index) const;
    /*!
     * 
     */
    virtual Object* const at(int an_index, Object* const (*a_block)(const Object* const&)) const;


    /*!
     * 
     */
    virtual void replaceFrom(int start, int stop, ByteArray* const& byte_array, int replace_start);
    /*! @} */


    /*!
      \name printing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual void printOn(Stream* const& a_stream) const;


#if defined(ALTAIR_ENABLE_REDUNDANT_METHODS)
    /*!
     * 
     */
    virtual bool isLiteralObject() const { return !isReadOnly(); }


    /*!
     * 
     */
    virtual void storeLiteralOn(Stream* const& a_stream) const;


    /*!
     * 
     */
    virtual void storeOn(Stream* const& a_stream) const;
#endif  /*  defined(ALTAIR_ENABLE_REDUNDANT_METHODS) */
    /*! @} */


    /*!
      \name mutating objects
     */
    /*! @{ */
    /*!
     * 
     */
    virtual Object* const multiBecome(Array* const& an_array);
    /*! @} */


    /*!
      \name testing
     */
    /*! @{ */
    /*!
     * 
     */
    virtual bool isArray() const { return true; }
    /*! @} */

 private:
    Object** content_;
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Array_hxx */
// Local Variables:
//   coding: utf-8
// End:
