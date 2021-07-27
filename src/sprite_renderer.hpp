/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#pragma once

#include <stdint.h>

#include "sprite.hpp"

/** */
class SpriteRenderer {
private:
    Sprite sprites[128];

    int next_free;
    int x_offset;
    int y_offset;

public:
    SpriteRenderer();
    ~SpriteRenderer();

    void set_palette(const void* pal);
    void update();

    Sprite* create(const SpriteData& data);

    /** Uploads a raw image of size 128x256 to the VRAM */
    void upload(uint16_t* data);

    void set_offset(int x, int y);

private:
    SpriteRenderer(const SpriteRenderer&);
    SpriteRenderer& operator =(const SpriteRenderer&);
};
