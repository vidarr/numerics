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
#include <stdio.h>
#include <stdlib.h>

/*---------------------------------------------------------------------------*/

static int greatest_common_divisor_test() {
    assert(1 == greatest_common_divisor(2, 3));
    assert(3 == greatest_common_divisor(2 * 2 * 3, 3));
    assert(2 == greatest_common_divisor(2 * 2 * 3, 2));
    assert(1 == greatest_common_divisor(3 * 3 * 3, 2));
    assert(2 == greatest_common_divisor(2 * 3 * 3, 2));
    assert(5 * 7 == greatest_common_divisor(2 * 3 * 5 * 7, 5 * 7));
    assert(5 * 5 * 7 == greatest_common_divisor(2 * 3 * 5 * 5 * 7, 5 * 5 * 7));
    assert(5 * 5 * 7 ==
           greatest_common_divisor(2 * 3 * 5 * 5 * 7 * 13, 5 * 5 * 7 * 11));
    assert(7 * 13 ==
           greatest_common_divisor(2 * 3 * 5 * 5 * 7 * 7 * 13 * 13, 7 * 13));
    assert(2 * 7 * 13 == greatest_common_divisor(
                             2 * 3 * 5 * 5 * 7 * 7 * 13 * 13, 2 * 7 * 13));
    assert(2 * 7 * 13 ==
           greatest_common_divisor(2 * 3 * 5 * 5 * 7 * 13, 2 * 7 * 7 * 13));
    assert(2 * 97 == greatest_common_divisor(2 * 3 * 5 * 5 * 97, 2 * 97));
    assert(2 * 97 == greatest_common_divisor(2 * 3 * 5 * 5 * 97, 2 * 7 * 97));

    return EXIT_SUCCESS;
}

/*---------------------------------------------------------------------------*/

static int smallest_common_multiple_test() {
    assert(6 == smallest_common_multiple(2, 3));
    assert(2 * 2 * 3 == smallest_common_multiple(2 * 2 * 3, 3));
    assert(2 * 2 * 3 == smallest_common_multiple(2 * 2 * 3, 2));
    assert(2 * 3 * 3 * 3 == smallest_common_multiple(3 * 3 * 3, 2));
    assert(2 * 3 * 3 == smallest_common_multiple(2 * 3 * 3, 2));
    assert(2 * 3 * 5 * 7 == smallest_common_multiple(2 * 3 * 5 * 7, 5 * 7));
    assert(2 * 3 * 5 * 5 * 7 ==
           smallest_common_multiple(2 * 3 * 5 * 5 * 7, 5 * 5 * 7));
    assert(2 * 3 * 5 * 5 * 7 * 13 * 11 ==
           smallest_common_multiple(2 * 3 * 5 * 5 * 7 * 13, 5 * 5 * 7 * 11));

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------------*/

static int is_prime_test() {
    assert(!is_prime(4));
    assert(!is_prime(6));
    assert(!is_prime(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 *
                     2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2));
    assert(!is_prime(23 * 1288 * 17));

    assert(!is_prime(7919 * 7907));

    assert(is_prime(2));
    assert(is_prime(3));
    assert(is_prime(5));
    assert(is_prime(7));
    assert(is_prime(11));
    assert(is_prime(13));
    assert(is_prime(7919));

    assert(!is_prime(7919 - 1));
    assert(!is_prime(7919 + 1));

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------------*/

static int next_prime_test() {
    assert(101 == next_prime(100));
    assert(239 == next_prime(200));
    assert(7817 == next_prime(7700));

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------------*/

static int next_prime_factor_test() {
    uint64_t number = 101 * 239 * 757;

    uint32_t factor = next_prime_factor(number, 1);
    assert(1 == factor);

    factor = next_prime_factor(number, 1 + 1);
    assert(101 == factor);

    factor = next_prime_factor(number, factor + 1);
    assert(239 == factor);

    factor = next_prime_factor(number, factor + 1);
    assert(757 == factor);

    return EXIT_SUCCESS;
}

/*---------------------------------------------------------------------------*/

static int random_range_test() {
    long r = random_range(10, 20);
    assert((10 <= r) && (20 >= r));

    r = random_range(0, 32000);
    assert((0 <= r) && (32000 >= r));

    // random_range(0, 0) will give rands between 0 and RAND_MAX, since
    // random_range(*, 0) indicates 'all possible values'
    for (long i = 1; i < RAND_MAX; ++i) {
        r = random_range(0, i);
        assert((0 <= r) && (i >= r));
    }

    long max = 21191;

    for (long i = 0; i < max; ++i) {
        r = random_range(i, max);
        assert((i <= r) && (max >= r));
    }

    for (long i = max; i < 2 * max; ++i) {
        long r = random_range(i, 2 * max);

        assert(r <= 2 * max);
        assert(r >= i);
    }

    long min = RAND_MAX - 1;
    max = RAND_MAX;

    r = random_range(min, max);
    assert((min <= r) && (max >= r));

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------------*/

int main(int argc, char** argv) {
    greatest_common_divisor_test();
    smallest_common_multiple_test();
    is_prime_test();
    next_prime_factor_test();
    random_range_test();
}

/*---------------------------------------------------------------------------*/
