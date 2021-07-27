/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#include "layer.hpp"

Layer::Layer(uint8_t number) {}

Layer::~Layer() {}

bool Layer::is_enabled()
{
    return false;
}

void Layer::enable(bool t) {}

void Layer::set_tileset(Tileset* tileset_)
{
    tileset = tileset_;
}

void Layer::set_tilemap(TileMap* tilemap_)
{
    tilemap = tilemap_;
}

void Layer::set_mosaic(bool t) {}
