/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#pragma once

#include <stdint.h>

class Tileset;

/** */
class TileMap {
private:
    uint16_t width;
    uint16_t height;

    uint16_t* tilemap; //< Pointer to the tilemap in ROM

public:
    TileMap(uint16_t* raw_data);
    ~TileMap();

    inline uint16_t* get_data()   const { return tilemap; }
    inline uint16_t  get_width()  const { return width; }
    inline uint16_t  get_height() const { return height; }

    inline uint16_t get(int x, int y) const { return tilemap[y*width + x]; }

private:
    TileMap(const TileMap&);
    TileMap& operator =(const TileMap&);
};
