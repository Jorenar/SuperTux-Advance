/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#include "gba_sprites.h"
#include "gba_video.h"
#include "types.hpp"
#include "sprite_renderer.hpp"

SpriteRenderer::SpriteRenderer() : next_free(0) {}

SpriteRenderer::~SpriteRenderer() {}

void SpriteRenderer::set_palette(const void* pal)
{
    for (uint16_t i = 0; i < 256; ++i) {
        OBJ_COLORS[i] = ((u16*)pal)[i];
    }
}

void SpriteRenderer::update()
{
    for (int i = 0; i < 128; ++i) {
        // OAM[i].attr0 = OBJ_Y(80)  | OBJ_SHAPE(0) | OBJ_256_COLOR;
        // OAM[i].attr1 = OBJ_X(120) | OBJ_SIZE(2);
        // OAM[i].attr2 = OBJ_CHAR(8) | OBJ_PALETTE(0) | OBJ_PRIORITY(0);
        Sprite& sprite = sprites[i];
        if (sprite.is_enabled()) {
            OAM[i].attr0 = OBJ_Y((sprite.get_y() - sprite.get_data().get_y_align() - y_offset) & 0xFF) | OBJ_SHAPE(0) | OBJ_256_COLOR;
            OAM[i].attr1 =
                OBJ_X((sprite.get_x() - sprite.get_data().get_x_align() - x_offset) & 0xFF) |
                OBJ_SIZE(2) |
                (sprite.get_vflip() ? OBJ_VFLIP : 0) |
                (sprite.get_hflip() ? OBJ_HFLIP : 0);
            OAM[i].attr2 = OBJ_CHAR(sprite.get_data().get_char_addr(sprite.get_frame())) | OBJ_PALETTE(0) | OBJ_PRIORITY(0);
        }
        else {
            OAM[i].attr0 = OBJ_DISABLE; // OBJ_Y(80)  | OBJ_SHAPE(0) | OBJ_256_COLOR;
            OAM[i].attr1 = 0; // OBJ_X(120) | OBJ_SIZE(2);
            OAM[i].attr2 = 0; // OBJ_CHAR(8) | OBJ_PALETTE(0) | OBJ_PRIORITY(0);
        }
    }
}

void SpriteRenderer::upload(uint16_t* data)
{
    for (int i = 0; i < 32 * 512; ++i) {
        ((uint16_t*)OBJ_BASE_ADR)[i] = data[i];
    }

    //OAM[0].attr0 = OBJ_Y(80)  | OBJ_SHAPE(0) | OBJ_256_COLOR;
    //OAM[0].attr1 = OBJ_X(120) | OBJ_SIZE(2);
    //OAM[0].attr2 = OBJ_CHAR(8) | OBJ_PALETTE(0) | OBJ_PRIORITY(0);
}

void SpriteRenderer::set_offset(int x, int y)
{
    x_offset = x;
    y_offset = y;
}

Sprite* SpriteRenderer::create(const SpriteData& data)
{
    sprites[next_free] = Sprite(data);
    return &sprites[next_free++];
}
