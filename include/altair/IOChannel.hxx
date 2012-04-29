#ifndef altair_IOChannel_hxx
#define altair_IOChannel_hxx


BEGIN_NAMESPACE_ALTAIR


class Stream;


class IOChannel
{
 public:
    static Stream* getStandardOutput();
};


END_NAMESPACE_ALTAIR


#endif  /* altair_IOChannel_hxx */
// Local Variables:
//   coding: utf-8
// End:
