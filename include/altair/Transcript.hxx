#ifndef altair_Transcript_hxx
#define altair_Transcript_hxx


BEGIN_NAMESPACE_ALTAIR


class SequenceableCollection;


class Transcript
{
 public:
    static void print(const SequenceableCollection* const& a_sequence);
    static void nextPut(char ch);
    static void nextPutAll(const SequenceableCollection* const& a_sequence);
    static void nextPutAll(const String* const& a_string);
    static void nextPutAll(const char* const& cstring);
    static void nl();
    static void put(const Object* const& arg1, const Object* const& arg2);
};



END_NAMESPACE_ALTAIR


#endif  /* altair_Transcript_hxx */