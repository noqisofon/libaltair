#ifndef altair_OrderedCollection_hxx
#define altair_OrderedCollection_hxx

#include "altair/SequenceableCollection.hxx"


BEGIN_NAMESPACE_ALTAIR


/*!
 *
 */
class OrderedCollection : public SequenceableCollection
{
 public:
    /*!
     * 
     */
    OrderedCollection();
    /*!
     * 
     */
    OrderedCollection(int an_integer);


    /*!
     * 
     */
    virtual ~OrderedCollection();

 public:
    /*!
     * 
     */
    virtual Object* const first() const;


    /**
     * 
     */
    virtual Collection* const& add(Object* const& new_object);


    /*!
     *
     */
    virtual bool tryRemove(Object* const& old_object);
};


END_NAMESPACE_ALTAIR


#endif  /* altair_OrderedCollection_hxx */
// Local Variables:
//   coding: utf-8
// End:
