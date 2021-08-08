/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#include "tileset.hpp"
#include "console.hpp"

Tileset::Tileset(const void* data_) :
    data(static_cast<const uint16_t*>(data_))
{}

Tileset::~Tileset() {}

const uint16_t* Tileset::get_tile(uint16_t id) const
{
    return data + (32 * id);
}

uint8_t Tileset::get_colmap(uint16_t id) const
{
    return colmap[id];
}
