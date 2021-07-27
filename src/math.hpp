/*  $Id$
**
**  SuperTux Portable
**  Copyright (C) 2005 Ingo Ruhnke <grumbel@gmx.de>
**
**  This program is free software; you can redistribute it and/or
**  modify it under the terms of the GNU General Public License
**  as published by the Free Software Foundation; either version 2
**  of the License, or (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
**  02111-1307, USA.
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
