/*
 * (C) 2020 Michael J. Beer
 * All rights reserved.
 *
 * Redistribution  and use in source and binary forms, with or with‐
 * out modification, are permitted provided that the following  con‐
 * ditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above  copy‐
 * right  notice,  this  list  of  conditions and the following dis‐
 * claimer in the documentation and/or other materials provided with
 * the distribution.
 *
 * 3.  Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote  products  derived
 * from this software without specific prior written permission.
 *
 * THIS  SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBU‐
 * TORS "AS IS" AND ANY EXPRESS OR  IMPLIED  WARRANTIES,  INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE  ARE  DISCLAIMED.  IN  NO  EVENT
 * SHALL  THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DI‐
 * RECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR  CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS IN‐
 * TERRUPTION)  HOWEVER  CAUSED  AND  ON  ANY  THEORY  OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING  NEGLI‐
 * GENCE  OR  OTHERWISE)  ARISING  IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * @author Michael J. Beer <michael.josef.beer@gmail.com>
 *
 */
#include "numerics.h"

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/*---------------------------------------------------------------------------*/

int64_t llmax(int64_t n, int64_t m) {
    if (n > m) return n;
    return m;
}

/*---------------------------------------------------------------------------*/

int64_t llmin(int64_t n, int64_t m) {
    if (n < m) return n;
    return m;
}

/*----------------------------------------------------------------------------*/

uint64_t a_raised_to_d_mod_n(uint64_t a, uint64_t d, uint64_t n) {

    uint64_t m = a;

    while (n <= m) {
        m -= n;
    }

    for (uint64_t round = 1; round < d; ++round) {

        assert(m < n);

        m *= a;

        while (n <= m) {
            m -= n;
        }

        assert(m < n);
    }

    return m;
}

/*---------------------------------------------------------------------------*/

uint64_t greatest_common_divisor(const int64_t n, const int64_t m) {
    /* Simple algorithm:
     * Just split smaller number into prime factors and
     * collect all prime factors in common with bigger number */

    int64_t sfactor = llmin(n, m);
    int64_t ofactor = llmax(n, m);

    const int64_t max_divisor = 1 + sqrt(sfactor);

    int64_t gcd = 1;
    int64_t divisor = 2;
    int64_t sremainder = 1;
    int64_t oremainder = 1;

    /* Ok, here's the algorithm:
     *
     * We got n,m
     * Assume n < m, otherwise swap (if n == m, n is the gcd)
     *
     * There are primes N[i] such that  N[1] * N[2] ... * N[k] = n
     * There are primes M[i] such that  M[1] * M[2] ... * M[l] = m
     *
     * Let {(p[i],q[i])}  (i e [1,r]) the set of index pairs (p[i],q[i])
     * such that N[p[i]] == M[q[i]]    (p[i] and q[i] being unique).
     *
     * Then
     * gcd := 1 * N[p[1]] ... * N[p[r]]
     *
     * NB: r = 0 -> gcd = 1
     *
     * REMEMBER:
     *
     * If
     * a[1] * a[2] * ... * a[n] = c
     *
     * Then a[i] > sqrt(c) for one single i AT MOST.
     *
     * Apart from it being obvious, here's the reason:
     *
     * Assume a[I] > sqrt(c) for a particular I =>
     * c = a[I] * remainder
     * sqrt(c) * sqrt(c) = a[I] * remainder
     * =>
     * remainder = sqrt(c) * sqrt(c) / a[I]
     * =>
     * remainder < sqrt(c) * sqrt(c) / sqrt(c) = sqrt(c)
     *
     * The while loop will find all factors <= sqrt(n)     (Still assuming n <
     * m)
     *
     * Therefore, in the loop all factors of m <= sqrt(n) will be found.
     * The only 'edgy' case is n being its own single prime factor.
     *
     * We need to treat this case special after the loop.
     *
     */
    while (max_divisor >= divisor) {
        sremainder = sfactor / divisor;

        if (sfactor != divisor * sremainder) {
            /* divisor is not a real divisor of sfactor */
            ++divisor;
            continue;
        }

        sfactor = sremainder;
        oremainder = ofactor / divisor;

        if (ofactor == oremainder * divisor) {
            gcd *= divisor;
            ofactor = oremainder;
        }

        if (1 == sremainder) break;
    }

    if (sfactor <= max_divisor) {
        return gcd;
    }

    oremainder = ofactor / sfactor;

    if (ofactor == oremainder * sfactor) {
        gcd *= sfactor;
    }

    return gcd;
}

/*---------------------------------------------------------------------------*/

uint64_t smallest_common_multiple(const int64_t n, const int64_t m) {
    return n * m / greatest_common_divisor(n, m);
}

/*----------------------------------------------------------------------------*/

bool is_prime(uint64_t p) {
    if (2 == p) {
        return true;
    }

    if (is_even(p)) {
        return false;
    }

    uint64_t last_factor_to_check = sqrt(p) + 1;

    for (uint64_t factor = 2; factor < last_factor_to_check; ++factor) {
        uint64_t share = p / factor;

        if (p == share * factor) {
            return false;
        }
    }

    return true;
}

/*----------------------------------------------------------------------------*/

bool is_large_prime(uint64_t p) {

    if (!passes_rabin_miller(p)) {
        return false;
    }

    return is_prime(p);
}

/*----------------------------------------------------------------------------*/

bool passes_rabin_miller(uint64_t n) {
    if (2 == n) {
        return true;
    }

    if (is_even(n)) {
        return false;
    }

    uint64_t n_minus_1 = n - 1;

    uint64_t twos_exponent = 0;
    uint64_t twos_factor = 1;
    uint64_t d = n_minus_1;

    assert(is_even(d));

    for (twos_exponent = 0; is_even(d); ++twos_exponent) {
        twos_factor *= 2;
        d /= 2;
    }

    uint64_t a = random_range(2, n_minus_1);
    assert(2 <= a);
    assert(a <= n_minus_1);

    uint64_t m = a_raised_to_d_mod_n(a, d, n);

    if (1 == m) return true;

    // Now we got our special case:

    uint64_t last_m = m;

    for (uint64_t r = 0; r < twos_exponent; ++r) {
        last_m = m;
        m = a_raised_to_d_mod_n(m, 2, n);
        if (1 == m) break;
    }

    return (m == 1) && (n - 1 == last_m);
}

/*----------------------------------------------------------------------------*/

uint64_t next_prime(const uint64_t n) {
    for (uint64_t num_to_check = 1 + n; num_to_check < UINT64_MAX;
         ++num_to_check) {
        if (is_prime(num_to_check)) {
            return num_to_check;
        }
    }

    return 0;
}

/*----------------------------------------------------------------------------*/

uint32_t next_prime_factor(uint64_t n, uint32_t min_factor) {
    uint64_t last_factor_to_check = sqrt(n) + 1;

    assert(UINT32_MAX >= last_factor_to_check);

    for (uint32_t factor = min_factor; factor < last_factor_to_check;
         factor = next_prime(factor)) {
        uint64_t share = n / factor;

        if (n == share * factor) {
            return (uint32_t)factor;
        }
    }

    return 0;
}

/*****************************************************************************
                                 RANDOM NUMBERS
 ****************************************************************************/

/*
 * As the library function random(3) is not guaranteed to produce more than
 * 16 bit random numbers, we need to rely on our own prng - it is not that hard
 * if we do not want cryptographically safe rngs...
 *
 * However, this manually implemented PRNG (with a little help by
 * Mr Donald Knuth) performs better than the currently available
 * glibc implementation of random(3) under linux
 *
 * The Monte Carlo calculation of PI yields results closer to PI by
 * 1/100, and plotting the points shows an EVEN distribution.
 *
 * A better PRNG would be e.g. the Mersenne Twister:
 *
 * https://web.archive.org/web/20070918014705/http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/MT2002/CODES/mt19937ar.c
 *
 */

static uint32_t g_random_number = 144312;
static bool g_random_seeded = false;

/*----------------------------------------------------------------------------*/

static void genrand_init(uint32_t s) { g_random_number = s; }

/*----------------------------------------------------------------------------*/

#include <time.h>

static void genrand_reseed() {
    if (g_random_seeded) return;

    genrand_init(time(0));
    g_random_seeded = true;
}

/*----------------------------------------------------------------------------*/

static uint32_t genrand_int32(uint32_t state) {
    // This is the general form of a linear congruental method -
    // with reasonable values for A, B, M
    // static uint64_t a = ...;
    // static uint64_t c = ...;
    // static uint64_t m = ...;
    // g_random_number = (a * g_random_number + c) % m;

    // We choose m to be 0xffffffff == UINT32_MAX + 1, then
    // r mod m is calculated easily by r overflowing on 32 bit
    // (See Knuth, TAOCP Vol2, 12pp)

    // m = 2^32, hence its only prime factor is '2'
    // thus, according to TAOCP, 3.2.1.2, Theorem A,
    // a - 1 should be a multiple of 2
    // Since m is a multiple of 4, a - 1 should also be a multiple of 4
    static uint64_t a = 0xea5f3f01;

    uint64_t r = state;

    if (0 == state) {
        r = g_random_number;
    }

    r *= a;

    // This new random number does not really alternate much in the lower order
    // bits
    // Thus, we do it once more, then combine the 2 higher order 16 bit chunks
    // into our 'real' number
    // Does not add randomness, but our PRNG is just for basics
    // like choosing arbitrary ports...

    uint32_t r1 = (uint32_t)r;

    uint64_t r2 = r1;
    r *= a;

    uint32_t random_number = r1 + (r2 >> 16);

    if (0 == state) {
        g_random_number = random_number;
    }

    return random_number;
}

/*----------------------------------------------------------------------------*/

void random_reseed() { genrand_reseed(); }

/*----------------------------------------------------------------------------*/

uint32_t random_get32(uint32_t state) { return genrand_int32(state); }

/*----------------------------------------------------------------------------*/

uint32_t random_range(uint32_t min, uint32_t max) {
    if (max == 0) {
        max = INT_MAX;
    }

    if (min > max) {
        return -1;
    }

    double r = random_get32(0);

    r *= max - min;
    r /= UINT32_MAX;

    return min + (uint32_t)r;
}

/*----------------------------------------------------------------------------*/
