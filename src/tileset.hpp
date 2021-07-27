/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#ifndef HEADER_TILESET_HPP
#define HEADER_TILESET_HPP

#include "types.hpp"

/** Handles a tileset in ROM */
class Tileset {
private:
    const uint16_t* data;
    const uint8_t*  colmap;
public:
    Tileset(const void* data, const void* colmap);
    ~Tileset();

    /** Returns a pointer to the start of tile \a id */
    const uint16_t* get_tile(uint16_t id) const;

    uint8_t get_colmap(uint16_t id) const;
};

#endif
