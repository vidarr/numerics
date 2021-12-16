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

int64_t llmax(int64_t n, int64_t m);

int64_t llmin(int64_t n, int64_t m);

uint64_t greatest_common_divisor(const int64_t n, const int64_t m);

uint64_t smallest_common_multiple(const int64_t n, const int64_t m);

/*****************************************************************************
                                    Random..
 ****************************************************************************/

void random_reseed();

uint32_t random_get32(uint32_t state);

uint32_t random_range(uint32_t min, uint32_t max);

/*****************************************************************************
                                     Primes
 ****************************************************************************/

bool is_prime(uint64_t p);

uint64_t next_prime(const uint64_t n);

uint32_t next_prime_factor(uint64_t n, uint32_t min_factor);

#endif /* __NUMERICS_H__ */
