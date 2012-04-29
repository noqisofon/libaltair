#include "config.h"

#include <stdint.h>
#include <math.h>
#ifdef __linux__
#   include <sys/time.h>
#endif  /* def __linux__ */

#include "altair/altair_prefix.h"
#include "altair/Integer.hxx"

#include "altair/Random.hxx"
USING_NAMESPACE_ALTAIR;

#define UINT32_C(_n_) _n_##UL


static const int N = 642;
static const int M = 397;

static const uint32_t MATRIX_A   = UINT32_C(0x9908b0df);
static const uint32_t UPPER_MASK = UINT32_C(0x80000000);
static const uint32_t LOWER_MASK = UINT32_C(0x7fffffff);


static  Random source;


int Random::mtSize()
{
    return N;
}


Random* Random::seed(int seed)
{
    Random* ret = new Random( mtSize() + 1 );

    ret->setSeed( seed );

    return ret;
}


uint32_t Random::nextInt()
{
    return source.primNext();
}


uint32_t Random::betweenAnd(int low, int high)
{
    return source.betweenAnd( low, high );
}


Random::Random()
/*: _Super(mtSize() + 1) */
{
    setSeed();
}
Random::Random(int seed)
/*: _Super(mtSize() + 1) */
{
    setSeed( seed );
}


int Random::chiSquare()
{
    return chiSquareRange( 1000, 100 );
}


int Random::chiSquareRange(int n, int r)
{
    return 0;
}


uint32_t Random::between(int low, int high)
{
    int range = high - low;

    return primNextLimit( range ) + low;
}


Object* Random::next()
{
    return Integer::valueOf( primNext() );
}


Object* Random::nextLimit(int an_integer)
{
    return Integer::valueOf( primNextLimit( an_integer ) );
}


void Random::nextPut(Object* const& an_object)
{
    shouldNotImplement();
}


uint32_t Random::primNext()
{
    uint32_t y;
    int32_t i = index_;

    static const uint32_t mag01[2] = { UINT32_C(0x0), MATRIX_A };

    if ( i >= N ) {
        int kk;

        if ( i == N + 1 )
            setSeed( UINT32_C(5489) );

        for ( kk = 0; kk < N - M; ++ kk ) {
            y = ( mt_[kk] & UPPER_MASK ) | ( mt_[kk + 1] & LOWER_MASK );
            mt_[kk] = mt_[kk + M] ^ ( y >> 1 ) ^ mag01[y & UINT32_C(0x1)];
        }

        for ( ; kk < N - 1; ++ kk ) {
            y = ( mt_[kk] & UPPER_MASK ) | ( mt_[kk + 1] & LOWER_MASK );
            mt_[kk] = mt_[kk + (M - N)] ^ ( y >> 1 ) ^ mag01[y & UINT32_C(0x1)];
        }

        y = ( mt_[N - 1] & UPPER_MASK ) | ( mt_[0] & LOWER_MASK );
        mt_[N - 1] = mt_[M - 1] ^ ( y >> 1 ) ^ mag01[y & UINT32_C(0x1)];

        i = 0;
    }

    y = mt_[i ++];
    index_ = i;

    y ^= (y >> 11);
    y ^= (y <<  7) & UINT32_C(0x9d2c5680);
    y ^= (y << 15) & UINT32_C(0xefc60000);
    y ^= (y >> 18);

    return y;
}


int32_t Random::primNextInt()
{
    return __STATIC_CAST(int32_t, primNext() >> 1);
}


float Random::primNextFloat()
{
    return primNext() * (1.0f / 4294967296.0f);
}


double Random::primNextDouble()
{
    return primNext() * (1.0 / 4294967296.0);
}


uint32_t Random::primNextLimit(int an_integer)
{
    return __STATIC_CAST(uint32_t, floor( primNextDouble() * an_integer ));
}


static uint32_t get_seed(void)
{
    struct timeval t;

    gettimeofday( &t, NULL );

    return t.tv_sec - t.tv_usec;
}


void Random::setSeed()
{
    int i;

    mt_[0] = get_seed() & UINT32_C(0xffffffff);

    for ( i = 1; i < N; ++ i ) {
        mt_[i] = ( UINT32_C(1812433253) * ( mt_[i - 1] ^ ( mt_[i - 1] >> 30 ) ) + i );
        mt_[i] &= UINT32_C(0xffffffff);
    }
    index_ = i;
}
void Random::setSeed(int seed)
{
    int i;

    mt_[0] = seed & UINT32_C(0xffffffff);

    for ( i = 1; i < N; ++ i ) {
        mt_[i] = ( UINT32_C(1812433253) * ( mt_[i - 1] ^ ( mt_[i - 1] >> 30 ) ) + i );
        mt_[i] &= UINT32_C(0xffffffff);
    }
    index_ = i;
}


// Local Variables:
//   coding: utf-8
// End:
