/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#include "sprite_data.hpp"

SpriteData::SpriteData() : data(0) {}

SpriteData::SpriteData(uint16_t* data_) : data(data_) {}

SpriteData::~SpriteData() {}

uint16_t SpriteData::get_char_addr(int frame) const
{
    uint16_t& x = data[6 + (2*frame)];
    uint16_t& y = data[6 + (2*frame) + 1];
    return 2*(16 * y + x);
}

uint16_t SpriteData::get_frames() const
{
    return data[5];
}

uint16_t SpriteData::get_fps() const
{
    return data[4];
}

uint16_t SpriteData::get_width()  const
{
    return data[0];
}

uint16_t SpriteData::get_height() const
{
    return data[1];
}

uint16_t SpriteData::get_x_align() const
{
    return data[2];
}

uint16_t SpriteData::get_y_align() const
{
    return data[3];
}
