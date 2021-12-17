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
#ifndef __NUMERICS_H__
#define __NUMERICS_H__

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>

/*****************************************************************************
                                  Very Basics
 ****************************************************************************/

#define is_even(n) (0 == ((n) & 1))
#define is_odd(n) ( ! is_even(n))

int64_t llmax(int64_t n, int64_t m);

int64_t llmin(int64_t n, int64_t m);

uint64_t greatest_common_divisor(const int64_t n, const int64_t m);

uint64_t smallest_common_multiple(const int64_t n, const int64_t m);

/*****************************************************************************
                                    Random..
 ****************************************************************************/

void random_reseed();

/**
 * Returns a random number
 * If state is given, it is used as seed for the PRNG.
 * If it is not given, uses internal seed.
 *
 * For multithreaded environments, its best to use the seed.
 * Store the random number returned and use it as seed the next time you call
 * this function.
 */
uint32_t random_get32(uint32_t state);

/**
 * Returns a random number in the range of min <= rand <= max
 */
uint32_t random_range(uint32_t min, uint32_t max);

/*****************************************************************************
                                     Primes
 ****************************************************************************/

/**
 * Reliable prime test.
 * Albeit slow.
 */
bool is_prime(uint64_t p);

/**
 * Can be used for large numbers.
 * Will try to filter out non-primes by applying the rabin-miller test
 * several times on them.
 * For primes, will be actually slower than the is_prime test.
 *
 * Since the rabin miller test in here for primes up to at least 100000
 * is much slower than just brute force prime checking, it's more of
 * a demo.
 */
bool is_large_prime(uint64_t p);

/**
 * All primes must pass this test.
 * Albeit not all non-primes do not pass it.
 *
 * The test internally uses a randomly selected number to check.
 *
 * This function is not performant and merely a demo.
 *
 * But if it was performant, we could use it on large numbers to either
 *
 * (1) Check ahead of doing the actual full prime test whether we can rule the
 * number out in advance (2) If we only require a 'likely' prime, we can pass it
 * multiple times through this test
 */
bool passes_rabin_miller(uint64_t n);

/**
 * For a given n, returns the next prime greater than n
 */
uint64_t next_prime(const uint64_t n);

/**
 * Returns the next prime factor of n greater than min or 0 if something went
 * wrong
 */
uint32_t next_prime_factor(uint64_t n, uint32_t min_factor);

#endif /* __NUMERICS_H__ */
