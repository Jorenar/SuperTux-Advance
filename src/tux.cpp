/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#include "gba_input.h"
#include "gba_video.h"
#include "globals.hpp"
#include "sprite_renderer.hpp"
#include "data.hpp"
#include "tile_renderer.hpp"
#include "tux.hpp"
#include "tile_map.hpp"
#include "console.hpp"

Tux::Tux() :
    sprite(sprite_renderer->create(tux_sprite_data)),
    contact(&air_contact)
{
    x_pos = 360;
    y_pos = 150;
}

Tux::~Tux() {}

void Tux::update()
{
    sprite->update();

    u16 keys = keysHeld();
    int speed = 2;

    int last_x = x_pos;
    int last_y = y_pos;

    uint8_t col = tilemap->get_colmap(x_pos/8, y_pos/8 + 1);

    if (keys & KEY_L) {
        if (keys & KEY_UP) {
            y_pos -= speed;
        }
        else if (keys & KEY_DOWN) {
            y_pos += speed;
        }
    }
    else {
        if (col == 0) {
            y_pos += 4;
        }
    }

    if (keys & KEY_B) {
        speed *= 2;
    }

    if (keys & KEY_A) {
        y_pos -= speed*4;
    }

    if (keys & KEY_LEFT) {
        x_pos -= speed;
        sprite->set_hflip(true);
    }
    else if (keys & KEY_RIGHT) {
        x_pos += speed;
        sprite->set_hflip(false);
    }

    if (tilemap->get_colmap(x_pos/8, y_pos/8 + 0) != 0) {
        x_pos = last_x;
        y_pos = last_y;
    }

    sprite->set_pos(x_pos, y_pos);

    scroll_x = sprite->get_x() - 120;
    scroll_y = sprite->get_y() - 100;

    tile_renderer->set_tilemap_offset(1, scroll_x, scroll_y);
    tile_renderer->set_tilemap_offset(2, scroll_x/2, scroll_y/2);
    tile_renderer->set_tilemap_offset(3, scroll_x/4, scroll_y/4);

    sprite_renderer->set_offset(scroll_x, scroll_y);
}
