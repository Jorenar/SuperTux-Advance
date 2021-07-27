/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#include "data.hpp"

#include "sprite_data.hpp"

//                                         w, h, align, fps, frames, frames...
uint16_t tux_sprite_rawdata[]        = { 4, 4, 16,32,  6,     6,   0,0,  4,0,  8,0,  12,0,  0,4,  4,4  };
uint16_t mriceblock_sprite_rawdata[] = { 2, 2,  8,16,  6,     1,   0,0,  2,8,  4,8,  2,8 };

SpriteData tux_sprite_data(tux_sprite_rawdata);
SpriteData mriceblock_sprite_data(mriceblock_sprite_data);
