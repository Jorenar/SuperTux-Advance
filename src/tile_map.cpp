/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#include "tileset.hpp"
#include "tile_map.hpp"

TileMap::TileMap(Tileset* tileset_, uint16_t* raw_data) :
    tileset(tileset_),
    width(raw_data[0]), height(raw_data[1]), tilemap(raw_data + 2)
{}

TileMap::~TileMap() {}

uint8_t TileMap::get_colmap(int x, int y) const
{
    return tileset->get_colmap(tilemap[y*width + x]);
}
