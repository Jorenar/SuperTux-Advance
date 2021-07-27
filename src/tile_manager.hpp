/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#pragma once

#include "types.hpp"

class Tileset;

/** The TileManager handles the allocation and deallocation of tiles
    in VRAM */
class TileManager {
private:
    static const uint16_t NO_TILE     = 0xFFFF;
    static const uint16_t MAX_TILE_ID = 1024;
    static const uint16_t MAX_VRAM_ID = 896 - 96; // we use 96 tiles for letters

    /** VRAM and ROM tile with id 0 is a special case, its the empty tile and always found at 0 */
    uint16_t rom2vram[MAX_TILE_ID];
    uint16_t vram2rom[MAX_VRAM_ID];

    /** This array holds the refcount for VRAM tiles as well as the list
        of freelist for tile entries in VRAM, since a tile entry is
        either used or free, which can be checked via vram2rom those two
        don't conflict */
    uint16_t refcount[MAX_VRAM_ID];

    /** pointer to refcount, see refcount */
    uint16_t* freelist;

    uint16_t next_free;

    Tileset* tileset;

public:
    TileManager();
    ~TileManager();

    /** Allocate a tile in VRAM and copy the ROM tile over to VRAM */
    uint16_t create_vram_tile(uint16_t rom_id);

    /** Decrements the refcount and deletes \a tile from VRAM if it is
        no longer used */
    void delete_vram_tile(uint16_t vram_id);

    /** Uploads a tile at location \a rom_id to location \a vram_id */
    void upload_tile(uint16_t rom_id, uint16_t vram_id);

    void set_tileset(Tileset* tileset_);

private:
    TileManager(const TileManager&);
    TileManager& operator =(const TileManager&);
};
