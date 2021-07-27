/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#include "sprite.hpp"

Sprite::Sprite() : enabled(false) {}

Sprite::Sprite(const SpriteData& data_) :
    enabled(true), data(data_), x(0), y(0), world_co(true), hflip(false), vflip(false)
{}

void Sprite::set_pos(int x_, int y_)
{
    x = x_;
    y = y_;
}

void Sprite::update()
{
    frame += 1;
    frame %= data.get_frames();
}
