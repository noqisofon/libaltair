#ifndef altair_Encoding_hxx
#define altair_Encoding_hxx


BEGIN_NAMESPACE_ALTAIR


class String;


/*!
 *
 */
class Encoding
{
 public:
    static Encoding* searchOf(const char* const& encoding_name);
    static Encoding* searchOf(const String* const& encoding_name);
};


END_NAMESPACE_ALTAIR


#endif  /* altair_Encoding_hxx */
