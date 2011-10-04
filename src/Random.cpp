

Random* const Random::seed(int an_integer)
{
    Random* const self = new Random( mtSize() + 1 );

    self->setSeed( an_integer );

    return self;
}


double Random::next()
{
    if ( !source_ )
        source_ = new Random();

    return source_->next();
}


int Random::between(int low, int high)
{
    if ( !source_ )
        source_ = new Random();

    return source_->between( low, high );
}


Random::Random()
    : _Base( mtSize() + 1 ), source_(0)
{
}
Random::Random(int mt_size)
    : _Base( mt_size ), source_(0)
{
    setSeed();
}


double Random::chiSquare(int n, int range)
{
    int t;
    Array* f = new FloatArray( range, 0 );

    for ( int i = 0; i < n; ++ i ) {
        t = between( 1, r );
        f->put( t, f->at( t ) + 1 );
    }
    t = 0;

    for ( int i = 0; i < range; ++ i ) {
        int temp
        t += f->at( i )->squared();
    }
    f->release();

    return AS_FLOAT( r ) * t / n - n;
}


int Random::next()
{
    /// VM 内で実装されている。
}


int Random::nextLimit(int an_integer)
{
    /// VM 内で実装されている。
}


void Random::nextPut(Object* const& value)
{
    shouldNotImplement();
}


void Random::setSeed(int an_integer)
{
    int previous = an_integer | 1;

    for ( int i = 0; i < 624; ++ i ) {
        int value = 1812433253 * ( previous ^ ( previous >> 30 ) );

        put( i, value & 0xffffffff );

        previous = value;
    }
    put( size() - 1, 0 );
}
