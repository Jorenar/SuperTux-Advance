/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#ifndef HEADER_MATH_HPP
#define HEADER_MATH_HPP

#include "types.hpp"

/** */
class Math {
private:
    uint8_t sin_table[256];

public:
    Math();
    ~Math();

    // FIXME: This is *NOT* real sin/cos at the moment, just something
    // to get the effect done
    uint8_t sin(uint8_t angle);
    uint8_t cos(uint8_t angle);

    template<class T>
    static T min (const T& a, const T& b)
    {
        if (a < b) {
            return a;
        }
        else {
            return b;
        }
    }

    template<class T>
    static T max (const T& a, const T& b)
    {
        if (a > b) {
            return a;
        }
        else {
            return b;
        }
    }

    template<class T>
    static T mid (const T& a, const T& b, const T& c)
    {
        return max<T>((a), min<T>((b), (c)));
    }

};

extern Math math;

#endif
