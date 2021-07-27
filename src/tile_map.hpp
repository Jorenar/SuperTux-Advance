/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#pragma once

#include "types.hpp"

class Tileset;

/** */
class TileMap {
private:
    Tileset* tileset;

    /** Width of the TileMap */
    uint16_t width;

    /** Height of the TileMap */
    uint16_t height;

    /** Pointer to the tilemap in ROM */
    uint16_t* tilemap;

public:
    TileMap(Tileset* tileset, uint16_t* raw_data);
    ~TileMap();

    inline uint16_t* get_data()   const { return tilemap; }

    inline uint16_t  get_width()  const { return width; }

    inline uint16_t  get_height() const { return height; }

    uint8_t get_colmap(int x, int y) const;

private:
    TileMap(const TileMap&);
    TileMap& operator =(const TileMap&);
};
