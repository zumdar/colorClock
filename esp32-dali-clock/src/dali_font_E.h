/****************************************************************************
 *   DaliClock by (c) 2021 Marcio Teixeira                               *
 *                                                                          *
 *   This program is free software: you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by   *
 *   the Free Software Foundation, either version 3 of the License, or      *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   This program is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU General Public License for more details.                           *
 *                                                                          *
 *   To view a copy of the GNU General Public License, go to the following  *
 *   location: <http://www.gnu.org/licenses/>.                              *
 ****************************************************************************/

const PROGMEM uint8_t zeroE_rle[] = {
    17, 10, 21, 0,     15, 14, 19, 0,     13, 7, 4, 7,     12, 7, 6, 7,
    11, 7, 8, 7,     10, 7, 10, 7,     9, 8, 10, 8,     8, 9, 10, 9,
    8, 8, 12, 9,     7, 9, 12, 9,     6, 10, 12, 10,     6, 10, 12, 10,
    5, 11, 12, 11,     5, 11, 12, 11,     4, 12, 12, 12,     4, 12, 12, 12,
    4, 12, 12, 12,     3, 13, 12, 13,     3, 13, 13, 12,     3, 13, 13, 12,
    3, 13, 13, 12,     3, 13, 13, 13,     2, 14, 13, 13,     2, 14, 13, 13,
    2, 14, 13, 13,     2, 14, 13, 13,     2, 14, 13, 13,     2, 14, 13, 13,
    2, 14, 13, 13,     2, 14, 13, 13,     2, 14, 13, 13,     2, 14, 13, 13,
    2, 14, 13, 13,     2, 14, 13, 13,     2, 14, 13, 13,     2, 14, 13, 13,
    2, 14, 13, 13,     2, 14, 13, 13,     2, 14, 13, 13,     2, 14, 13, 13,
    2, 14, 13, 13,     2, 14, 13, 13,     3, 13, 13, 12,     3, 13, 13, 12,
    3, 13, 13, 12,     3, 13, 12, 13,     4, 12, 12, 12,     4, 12, 12, 12,
    4, 12, 12, 12,     5, 11, 12, 11,     5, 11, 12, 11,     6, 10, 12, 11,
    6, 10, 12, 10,     7, 9, 12, 10,     7, 9, 12, 9,     8, 9, 10, 9,
    9, 8, 10, 9,     10, 7, 10, 8,     10, 8, 8, 8,     11, 7, 8, 7,
    13, 6, 6, 7,     14, 7, 2, 7,     16, 12, 20, 0,     19, 6, 23, 0
};

constexpr PROGMEM dali_digit_t zeroE_info = {
    .height = 64,
    .width = 45,
    .linestride = 6,
    .packed_rle = zeroE_rle
};

const PROGMEM uint8_t oneE_rle[] = {
    26, 4, 18, 0,     24, 6, 18, 0,     22, 8, 18, 0,     19, 11, 18, 0,
    17, 13, 18, 0,     15, 15, 18, 0,     12, 18, 18, 0,     10, 20, 18, 0,
    8, 22, 18, 0,     5, 25, 18, 0,     5, 3, 7, 15,     16, 14, 18, 0,
    16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,
    16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,
    16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,
    16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,
    16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,
    16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,
    16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,
    16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,
    16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,
    16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,
    16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,     16, 14, 18, 0,
    16, 14, 18, 0,     16, 14, 18, 0,     15, 16, 17, 0,     15, 16, 17, 0,
    13, 19, 16, 0,     11, 23, 14, 0,     5, 35, 8, 0,     5, 35, 8, 0
};

constexpr PROGMEM dali_digit_t oneE_info = {
    .height = 64,
    .width = 45,
    .linestride = 6,
    .packed_rle = oneE_rle
};

const PROGMEM uint8_t twoE_rle[] = {
    17, 12, 19, 0,     15, 16, 17, 0,     13, 20, 15, 0,     12, 22, 14, 0,
    11, 24, 13, 0,     9, 27, 12, 0,     9, 28, 11, 0,     8, 30, 10, 0,
    7, 31, 10, 0,     6, 33, 9, 0,     6, 6, 8, 19,     5, 5, 12, 17,
    5, 4, 15, 16,     4, 4, 17, 15,     4, 3, 18, 15,     3, 3, 20, 14,
    3, 3, 20, 14,     3, 2, 22, 13,     27, 13, 8, 0,     27, 13, 8, 0,
    27, 13, 8, 0,     27, 13, 8, 0,     28, 11, 9, 0,     27, 12, 9, 0,
    27, 12, 9, 0,     27, 11, 10, 0,     27, 11, 10, 0,     27, 10, 11, 0,
    26, 10, 12, 0,     26, 10, 12, 0,     26, 9, 13, 0,     25, 9, 14, 0,
    25, 9, 14, 0,     24, 9, 15, 0,     24, 8, 16, 0,     23, 8, 17, 0,
    22, 8, 18, 0,     22, 7, 19, 0,     21, 7, 20, 0,     20, 7, 21, 0,
    20, 6, 22, 0,     19, 6, 23, 0,     18, 6, 24, 0,     17, 5, 26, 0,
    16, 5, 27, 0,     16, 4, 21, 3,     15, 4, 22, 2,     14, 4, 22, 3,
    13, 4, 23, 3,     12, 4, 23, 4,     11, 4, 23, 4,     10, 5, 19, 8,
    10, 32, 6, 0,     9, 33, 6, 0,     8, 34, 6, 0,     7, 34, 7, 0,
    6, 35, 7, 0,     5, 36, 7, 0,     4, 37, 7, 0,     3, 38, 7, 0,
    2, 38, 8, 0,     1, 39, 8, 0,     1, 39, 8, 0,     1, 39, 8, 0
};

constexpr PROGMEM dali_digit_t twoE_info = {
    .height = 64,
    .width = 45,
    .linestride = 6,
    .packed_rle = twoE_rle
};

const PROGMEM uint8_t threeE_rle[] = {
    18, 12, 18, 0,     15, 17, 16, 0,     13, 21, 14, 0,     12, 23, 13, 0,
    10, 26, 12, 0,     9, 28, 11, 0,     8, 30, 10, 0,     7, 5, 9, 17,
    6, 4, 12, 16,     6, 3, 15, 15,     5, 3, 16, 15,     4, 3, 18, 14,
    4, 2, 19, 14,     4, 2, 20, 13,     26, 13, 9, 0,     26, 13, 9, 0,
    26, 12, 10, 0,     26, 12, 10, 0,     26, 11, 11, 0,     26, 11, 11, 0,
    25, 11, 12, 0,     25, 10, 13, 0,     24, 9, 15, 0,     23, 9, 16, 0,
    22, 11, 15, 0,     21, 14, 13, 0,     19, 17, 12, 0,     17, 21, 10, 0,
    14, 25, 9, 0,     14, 25, 9, 0,     16, 24, 8, 0,     19, 22, 7, 0,
    21, 20, 7, 0,     23, 18, 7, 0,     24, 18, 6, 0,     26, 16, 6, 0,
    27, 15, 6, 0,     28, 14, 6, 0,     29, 14, 5, 0,     30, 13, 5, 0,
    30, 13, 5, 0,     31, 12, 5, 0,     31, 11, 6, 0,     32, 10, 6, 0,
    32, 10, 6, 0,     32, 10, 6, 0,     32, 10, 6, 0,     33, 8, 7, 0,
    33, 8, 7, 0,     33, 8, 7, 0,     5, 4, 23, 8,     3, 8, 21, 7,
    2, 11, 19, 7,     2, 12, 18, 6,     1, 14, 16, 6,     1, 15, 15, 5,
    1, 16, 13, 5,     2, 16, 11, 5,     2, 18, 8, 5,     3, 19, 3, 6,
    3, 27, 18, 0,     5, 23, 20, 0,     7, 18, 23, 0,     11, 9, 28, 0
};

constexpr PROGMEM dali_digit_t threeE_info = {
    .height = 64,
    .width = 45,
    .linestride = 6,
    .packed_rle = threeE_rle
};

const PROGMEM uint8_t fourE_rle[] = {
    30, 8, 10, 0,     29, 9, 10, 0,     28, 10, 10, 0,     27, 11, 10, 0,
    27, 11, 10, 0,     26, 12, 10, 0,     25, 13, 10, 0,     24, 14, 10, 0,
    24, 14, 10, 0,     23, 15, 10, 0,     22, 16, 10, 0,     21, 17, 10, 0,
    20, 18, 10, 0,     20, 18, 10, 0,     19, 19, 10, 0,     18, 5, 1, 14,
    17, 5, 2, 14,     17, 4, 3, 14,     16, 4, 4, 14,     15, 5, 4, 14,
    14, 5, 5, 14,     14, 4, 6, 14,     13, 5, 6, 14,     12, 5, 7, 14,
    12, 4, 8, 14,     11, 4, 9, 14,     10, 5, 9, 14,     9, 5, 10, 14,
    9, 4, 11, 14,     8, 4, 12, 14,     7, 5, 12, 14,     7, 4, 13, 14,
    6, 4, 14, 14,     5, 5, 14, 14,     5, 4, 15, 14,     4, 4, 16, 14,
    3, 4, 17, 14,     2, 5, 17, 14,     2, 4, 18, 14,     1, 4, 19, 14,
    1, 42, 5, 0,     1, 42, 5, 0,     1, 42, 5, 0,     1, 42, 5, 0,
    1, 42, 5, 0,     1, 42, 5, 0,     1, 42, 5, 0,     1, 42, 5, 0,
    1, 42, 5, 0,     1, 42, 5, 0,     24, 14, 10, 0,     24, 14, 10, 0,
    24, 14, 10, 0,     24, 14, 10, 0,     24, 14, 10, 0,     24, 14, 10, 0,
    24, 14, 10, 0,     24, 14, 10, 0,     24, 14, 10, 0,     24, 14, 10, 0,
    24, 14, 10, 0,     24, 14, 10, 0,     24, 14, 10, 0,     24, 14, 10, 0
};

constexpr PROGMEM dali_digit_t fourE_info = {
    .height = 64,
    .width = 45,
    .linestride = 6,
    .packed_rle = fourE_rle
};

const PROGMEM uint8_t fiveE_rle[] = {
    13, 30, 5, 0,     13, 30, 5, 0,     13, 30, 5, 0,     13, 29, 6, 0,
    12, 30, 6, 0,     12, 30, 6, 0,     12, 29, 7, 0,     11, 30, 7, 0,
    11, 30, 7, 0,     11, 29, 8, 0,     11, 29, 8, 0,     10, 4, 34, 0,
    10, 3, 35, 0,     10, 3, 35, 0,     10, 3, 35, 0,     9, 3, 36, 0,
    9, 3, 36, 0,     9, 3, 36, 0,     8, 4, 36, 0,     8, 7, 33, 0,
    8, 15, 25, 0,     8, 19, 21, 0,     7, 22, 19, 0,     7, 25, 16, 0,
    7, 26, 15, 0,     6, 29, 13, 0,     6, 30, 12, 0,     6, 31, 11, 0,
    6, 32, 10, 0,     5, 34, 9, 0,     5, 34, 9, 0,     5, 35, 8, 0,
    13, 27, 8, 0,     19, 22, 7, 0,     22, 19, 7, 0,     24, 17, 7, 0,
    26, 16, 6, 0,     28, 14, 6, 0,     29, 13, 6, 0,     31, 11, 6, 0,
    32, 10, 6, 0,     33, 9, 6, 0,     33, 9, 6, 0,     34, 8, 6, 0,
    34, 8, 6, 0,     35, 7, 6, 0,     35, 6, 7, 0,     35, 6, 7, 0,
    35, 6, 7, 0,     35, 5, 8, 0,     5, 5, 25, 5,     4, 8, 23, 4,
    3, 11, 20, 5,     2, 14, 18, 4,     2, 15, 16, 4,     2, 16, 14, 5,
    2, 18, 11, 5,     2, 20, 8, 4,     3, 30, 15, 0,     3, 29, 16, 0,
    4, 26, 18, 0,     6, 22, 20, 0,     8, 17, 23, 0,     11, 9, 28, 0
};

constexpr PROGMEM dali_digit_t fiveE_info = {
    .height = 64,
    .width = 45,
    .linestride = 6,
    .packed_rle = fiveE_rle
};

const PROGMEM uint8_t sixE_rle[] = {
    36, 7, 5, 0,     32, 10, 6, 0,     29, 10, 9, 0,     26, 10, 12, 0,
    24, 10, 14, 0,     22, 10, 16, 0,     20, 10, 18, 0,     19, 10, 19, 0,
    17, 11, 20, 0,     16, 11, 21, 0,     15, 11, 22, 0,     13, 12, 23, 0,
    12, 12, 24, 0,     11, 12, 25, 0,     11, 11, 26, 0,     10, 12, 26, 0,
    9, 12, 27, 0,     8, 13, 27, 0,     8, 12, 28, 0,     7, 13, 28, 0,
    6, 13, 29, 0,     6, 13, 29, 0,     5, 14, 29, 0,     5, 13, 30, 0,
    5, 13, 4, 8,     4, 29, 15, 0,     4, 31, 13, 0,     4, 33, 11, 0,
    3, 15, 6, 14,     3, 14, 9, 13,     3, 14, 9, 14,     3, 14, 10, 13,
    3, 14, 11, 13,     2, 14, 12, 13,     2, 14, 12, 14,     2, 14, 12, 14,
    2, 14, 13, 13,     2, 14, 13, 14,     2, 14, 13, 14,     2, 14, 13, 14,
    2, 14, 13, 14,     2, 14, 13, 14,     2, 14, 13, 14,     3, 13, 13, 14,
    3, 13, 13, 14,     3, 13, 13, 14,     3, 13, 13, 14,     3, 13, 13, 14,
    4, 12, 13, 13,     4, 13, 12, 13,     4, 13, 12, 13,     5, 12, 12, 12,
    5, 12, 12, 12,     6, 11, 12, 12,     6, 11, 12, 11,     7, 10, 12, 10,
    8, 10, 11, 10,     9, 9, 11, 9,     10, 9, 9, 9,     11, 8, 9, 8,
    12, 8, 7, 7,     14, 8, 3, 8,     16, 14, 18, 0,     19, 8, 21, 0
};

constexpr PROGMEM dali_digit_t sixE_info = {
    .height = 64,
    .width = 45,
    .linestride = 6,
    .packed_rle = sixE_rle
};

const PROGMEM uint8_t sevenE_rle[] = {
    5, 39, 4, 0,     4, 39, 5, 0,     4, 39, 5, 0,     4, 39, 5, 0,
    4, 38, 6, 0,     4, 38, 6, 0,     3, 39, 6, 0,     3, 38, 7, 0,
    3, 38, 7, 0,     3, 38, 7, 0,     3, 37, 8, 0,     2, 38, 8, 0,
    2, 8, 21, 8,     2, 5, 24, 8,     2, 3, 26, 8,     2, 3, 26, 7,
    1, 3, 26, 8,     1, 3, 26, 8,     1, 2, 27, 7,     1, 2, 26, 8,
    29, 8, 11, 0,     29, 7, 12, 0,     28, 8, 12, 0,     28, 8, 12, 0,
    27, 8, 13, 0,     27, 8, 13, 0,     27, 8, 13, 0,     26, 8, 14, 0,
    26, 8, 14, 0,     26, 8, 14, 0,     25, 8, 15, 0,     25, 8, 15, 0,
    25, 8, 15, 0,     24, 8, 16, 0,     24, 8, 16, 0,     23, 8, 17, 0,
    23, 8, 17, 0,     23, 8, 17, 0,     22, 8, 18, 0,     22, 8, 18, 0,
    22, 8, 18, 0,     21, 8, 19, 0,     21, 8, 19, 0,     20, 9, 19, 0,
    20, 8, 20, 0,     20, 8, 20, 0,     19, 9, 20, 0,     19, 8, 21, 0,
    19, 8, 21, 0,     18, 9, 21, 0,     18, 8, 22, 0,     18, 8, 22, 0,
    17, 9, 22, 0,     17, 8, 23, 0,     16, 9, 23, 0,     16, 9, 23, 0,
    16, 8, 24, 0,     15, 9, 24, 0,     15, 9, 24, 0,     15, 8, 25, 0,
    14, 9, 25, 0,     14, 8, 26, 0,     14, 8, 26, 0,     13, 9, 26, 0
};

constexpr PROGMEM dali_digit_t sevenE_info = {
    .height = 64,
    .width = 45,
    .linestride = 6,
    .packed_rle = sevenE_rle
};

const PROGMEM uint8_t eightE_rle[] = {
    16, 15, 17, 0,     13, 21, 14, 0,     11, 8, 7, 10,     10, 7, 10, 10,
    8, 8, 12, 10,     7, 9, 13, 10,     6, 9, 14, 11,     5, 10, 15, 10,
    5, 10, 15, 11,     4, 11, 15, 11,     4, 11, 15, 11,     4, 11, 16, 10,
    3, 12, 16, 10,     3, 12, 16, 10,     3, 13, 15, 10,     3, 13, 15, 10,
    3, 14, 13, 11,     3, 15, 12, 10,     3, 16, 11, 9,     3, 17, 10, 9,
    4, 17, 8, 9,     4, 18, 6, 9,     5, 19, 4, 7,     5, 21, 1, 6,
    6, 25, 17, 0,     7, 22, 19, 0,     7, 23, 18, 0,     8, 23, 17, 0,
    10, 23, 15, 0,     11, 23, 14, 0,     12, 23, 13, 0,     13, 23, 12, 0,
    15, 22, 11, 0,     15, 23, 10, 0,     12, 27, 9, 0,     10, 7, 2, 21,
    8, 8, 5, 19,     7, 9, 6, 19,     6, 9, 8, 18,     5, 9, 11, 17,
    4, 10, 12, 16,     4, 10, 13, 15,     3, 10, 14, 15,     3, 10, 15, 14,
    2, 11, 16, 13,     2, 11, 16, 13,     2, 11, 16, 13,     2, 11, 17, 12,
    2, 11, 17, 12,     2, 11, 17, 12,     2, 11, 17, 12,     2, 11, 17, 12,
    3, 10, 17, 11,     3, 10, 17, 11,     3, 11, 16, 10,     4, 10, 15, 11,
    4, 10, 15, 10,     5, 10, 14, 9,     6, 10, 12, 9,     7, 10, 10, 9,
    9, 9, 7, 9,     11, 21, 16, 0,     13, 17, 18, 0,     17, 9, 22, 0
};

constexpr PROGMEM dali_digit_t eightE_info = {
    .height = 64,
    .width = 45,
    .linestride = 6,
    .packed_rle = eightE_rle
};

const PROGMEM uint8_t nineE_rle[] = {
    16, 12, 20, 0,     13, 17, 18, 0,     11, 8, 5, 8,     10, 8, 7, 9,
    9, 8, 9, 9,     8, 9, 10, 9,     7, 9, 11, 10,     6, 10, 11, 10,
    5, 11, 12, 10,     5, 11, 12, 11,     4, 11, 13, 11,     4, 11, 13, 12,
    3, 12, 13, 12,     3, 12, 13, 13,     3, 12, 14, 12,     3, 12, 14, 12,
    2, 13, 14, 13,     2, 13, 14, 13,     2, 13, 14, 13,     2, 13, 14, 13,
    2, 13, 14, 13,     2, 14, 13, 14,     2, 14, 13, 14,     2, 14, 13, 14,
    2, 14, 13, 14,     3, 13, 13, 14,     3, 13, 13, 14,     3, 13, 13, 14,
    3, 14, 12, 14,     4, 13, 12, 14,     4, 13, 12, 13,     5, 13, 10, 14,
    5, 13, 10, 14,     6, 13, 9, 14,     7, 13, 8, 14,     8, 15, 1, 17,
    9, 32, 7, 0,     11, 30, 7, 0,     13, 11, 3, 14,     27, 13, 8, 0,
    26, 14, 8, 0,     26, 13, 9, 0,     26, 13, 9, 0,     25, 13, 10, 0,
    25, 13, 10, 0,     25, 12, 11, 0,     24, 12, 12, 0,     24, 12, 12, 0,
    23, 12, 13, 0,     22, 12, 14, 0,     22, 11, 15, 0,     21, 11, 16, 0,
    20, 11, 17, 0,     19, 11, 18, 0,     18, 10, 20, 0,     17, 10, 21, 0,
    16, 10, 22, 0,     14, 10, 24, 0,     12, 10, 26, 0,     10, 10, 28, 0,
    8, 10, 30, 0,     4, 11, 33, 0,     3, 8, 37, 0,     3, 3, 42, 0
};

constexpr PROGMEM dali_digit_t nineE_info = {
    .height = 64,
    .width = 45,
    .linestride = 6,
    .packed_rle = nineE_rle
};

const PROGMEM uint8_t colonE_rle[] = {
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     9, 7, 16, 0,
    8, 10, 14, 0,     7, 12, 13, 0,     6, 13, 13, 0,     6, 14, 12, 0,
    6, 14, 12, 0,     5, 15, 12, 0,     5, 15, 12, 0,     5, 15, 12, 0,
    6, 14, 12, 0,     6, 14, 12, 0,     6, 13, 13, 0,     7, 12, 13, 0,
    8, 10, 14, 0,     10, 6, 16, 0,     32, 0, 0, 0,     32, 0, 0, 0,
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,
    12, 2, 18, 0,     9, 8, 15, 0,     8, 10, 14, 0,     7, 12, 13, 0,
    6, 14, 12, 0,     6, 14, 12, 0,     5, 15, 12, 0,     5, 15, 12, 0,
    5, 15, 12, 0,     5, 15, 12, 0,     6, 14, 12, 0,     6, 14, 12, 0,
    7, 12, 13, 0,     7, 11, 14, 0,     9, 8, 15, 0,     11, 4, 17, 0
};

constexpr PROGMEM dali_digit_t colonE_info = {
    .height = 64,
    .width = 25,
    .linestride = 4,
    .packed_rle = colonE_rle
};

const PROGMEM uint8_t slashE_rle[] = {
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,
    2, 21, 9, 0,     2, 21, 9, 0,     2, 21, 9, 0,     2, 21, 9, 0,
    2, 21, 9, 0,     2, 21, 9, 0,     2, 21, 9, 0,     2, 21, 9, 0,
    2, 21, 9, 0,     2, 21, 9, 0,     2, 21, 9, 0,     32, 0, 0, 0,
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,
    32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0,     32, 0, 0, 0
};

constexpr PROGMEM dali_digit_t slashE_info = {
    .height = 64,
    .width = 25,
    .linestride = 4,
    .packed_rle = slashE_rle
};

#define DIGIT_INFO(digit) digit##E_info
