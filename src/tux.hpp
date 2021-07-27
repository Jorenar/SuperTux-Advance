/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#ifndef HEADER_TUX_HPP
#define HEADER_TUX_HPP

#include "contact.hpp"

class Sprite;

/** */
class Tux {
private:
    Sprite* sprite;

    // Contacts which handle Tuxs movement/collision detection on the
    // tilemap
    Contact*      contact;
    GroundContact ground_contact;
    AirContact air_contact;

    int x_pos;
    int y_pos;

    int16_t scroll_x;
    int16_t scroll_y;

public:
    Tux();
    ~Tux();

    void update();

private:
    Tux(const Tux&);
    Tux& operator =(const Tux&);
};

#endif
