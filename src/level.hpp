/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 */

#pragma once

#include <stdint.h>

#include "tile_map.hpp"
#include "tileset.hpp"

class Level {
    uint8_t* colmap;

    TileMap interactive;
    TileMap background;
    TileMap skybox;

    static inline uint16_t* ptrToNextTileMap(TileMap& x)
    {
        return x.get_data() + x.get_width() * x.get_height();
    }

public:
    Level(uint16_t* raw, const uint16_t* pal, Tileset* tileset);
    ~Level();

    inline uint8_t get_colmap(int x, int y) const
    {
        return colmap[interactive.get(x,y)];
    }

private:
    Level(const Level&);
    Level& operator =(const Level&);
};
