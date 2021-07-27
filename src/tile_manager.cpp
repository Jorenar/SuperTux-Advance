/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#include "tile_manager.hpp"

#include <gba_video.h>

#include "tileset.hpp"
#include "console.hpp"

#include "../build/font_img_bin.h"
#include "../build/antarctica_img_bin.h"

//#define ENABLE_DYNAMIC_TILE_ALLOCATION 1

TileManager::TileManager() :
    freelist(refcount), tileset(0)
{
    // Init refcount arrays and such
    for (uint16_t i = 0; i < MAX_TILE_ID; ++i) {
        rom2vram[i] = NO_TILE;
    }

    for (uint16_t i = 0; i < MAX_VRAM_ID; ++i) {
        freelist[i] = i + 1;
        vram2rom[i] = NO_TILE;
    }

    freelist[MAX_VRAM_ID-1] = 0;
    next_free = 1;

    // Upload letter tileset
    for (uint8_t rom_id = 0; rom_id < 95; ++rom_id) {
        for (int i = 0; i < 32; ++i) {
            ((uint16_t*)CHAR_BASE_ADR(0))[(MAX_VRAM_ID+rom_id)*32 + i] = ((uint16_t*)font_img_bin)[rom_id*32 + i];
        }
    }

#ifndef ENABLE_DYNAMIC_TILE_ALLOCATION
    for (uint16_t i = 0; i < MAX_VRAM_ID; ++i) {
        upload_tile(i, i);
    }
#endif
}

TileManager::~TileManager() {}

uint16_t TileManager::create_vram_tile(uint16_t rom_id)
{
#ifdef ENABLE_DYNAMIC_TILE_ALLOCATION
    if (rom_id == 0) {
        // Transparent tile is a special case, ignore
        return 0;
    }
    else if (rom2vram[rom_id] == NO_TILE) {
        // tile not allocated, so allocate it
        if (next_free == 0) {
            console << "Out of Tilespace for: " << rom_id << "\n";
            return 0;
        }
        else {
            uint16_t vram_id = next_free;

            rom2vram[rom_id]  = vram_id;
            vram2rom[vram_id] = rom_id;

            next_free = freelist[vram_id];

            refcount[vram_id] = 1;

            upload_tile(rom_id, vram_id);

            return rom2vram[rom_id];
        }
    }
    else {
        // tile already allocated, so increase the refcount
        refcount[rom_id] += 1;
        return rom2vram[rom_id];
    }
#else
    // Simple 1:1 mapping from rom to ram
    return rom_id % MAX_VRAM_ID;
#endif
}

void TileManager::delete_vram_tile(uint16_t vram_id)
{
#ifdef ENABLE_DYNAMIC_TILE_ALLOCATION
    if (vram_id != 0) {
        if (refcount[vram_id] <= 1) {
            refcount[vram_id] = next_free;
            next_free = vram_id;
            rom2vram[vram2rom[vram_id]] = NO_TILE;
            vram2rom[vram_id] = NO_TILE;
        }
        else {
            refcount[vram_id] -= 1;
        }
    }
#endif
}

void TileManager::upload_tile(uint16_t rom_id, uint16_t vram_id)
{
    const uint16_t* ptr = (const uint16_t*)(antarctica_img_bin); // tileset->get_tile(rom_id);
    for (int i = 0; i < 32; ++i) {
        ((uint16_t*)CHAR_BASE_ADR(0))[32*vram_id + i] = ptr[i + (32*rom_id)];
    }
}

void TileManager::set_tileset(Tileset* tileset_)
{
    tileset = tileset_;
}
