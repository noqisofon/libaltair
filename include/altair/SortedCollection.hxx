#ifndef altair_SortedCollection_hxx
#define altair_SortedCollection_hxx

#include "altair/OrderedCollection.hxx"


BEGIN_NAMESPACE_ALTAIR


/*!
 *
 */
class SortedCollection : public OrderedCollection
{
 public:
    static SortedCollection* withSortBlock(int (*a_sort_block)(const Object* const&, const Object* const&));

 public:
    SortedCollection(size_t size, Object* const& an_object = NULL);

 public:
    virtual const SortedCollection* sortBlock(int (*a_sort_block)(const Object* const&, const Object* const&));
};


END_NAMESPACE_ALTAIR


#endif  /* altair_SortedCollection_hxx */
// Local Variables:
//   coding: utf-8
// End:
