


Object* const Iterable::inject(Object* const& this_value, BinaryBlock& binary_block)
{
    Object* result = this_value;

    Iterator* it = iterator();
    for ( ; it->finished(); it->next() ) {
        Object* element = it->current();

        result = binary_block( result, element );
    }
    it->release();

    return result;
}
