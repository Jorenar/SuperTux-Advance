/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#include <math.h>
#include <stdlib.h>

#include <gba_input.h>
#include <gba_interrupt.h>
#include <gba_video.h>
#include <fade.h>

#include "globals.hpp"
#include "math.hpp"

// Data for use in the game
#include "../build/sprites_img_bin.h"
#include "../build/sprites_pal_bin.h"

#include "../build/antarctica_img_bin.h"
#include "../build/antarctica_pal_bin.h"
#include "../build/interactive_bin.h"
#include "../build/colmap_bin.h"
#include "../build/background_bin.h"
#include "../build/skybox_bin.h"

#include "console.hpp"
#include "sprite_manager.hpp"
#include "sprite_renderer.hpp"
#include "tile_map.hpp"
#include "tile_renderer.hpp"
#include "tileset.hpp"
#include "tux.hpp"

unsigned int frame;

void VblankInterrupt()
{
    frame += 1;
}

void vid_vsync()
{
    while (REG_VCOUNT >= 160) {  // wait till VDraw
    }
    while (REG_VCOUNT < 160) {   // wait till VBlank
    }
}

int main(void)
{
    // Set up the interrupt handlers
    irqInit();

    // irqSet( Int_Vblank, VblankInterrupt);

    // Enable Vblank Interrupt to allow VblankIntrWait
    // irqEnable(Int_Vblank);

    // Allow Interrupts
    REG_IME = 1;

    SetMode( MODE_0 | BG0_ON | BG1_ON | BG2_ON | BG3_ON | OBJ_ON );             // screen mode & background to display

    // console layer
    BGCTRL[0] = BG_PRIORITY(0) | CHAR_BASE(0) | BG_MOSAIC | BG_256_COLOR | SCREEN_BASE(28) | BG_SIZE_0;
    BGCTRL[1] = BG_PRIORITY(0) | CHAR_BASE(0) | BG_MOSAIC | BG_256_COLOR | SCREEN_BASE(29) | BG_SIZE_0;
    BGCTRL[2] = BG_PRIORITY(0) | CHAR_BASE(0) | BG_MOSAIC | BG_256_COLOR | SCREEN_BASE(30) | BG_SIZE_0;
    BGCTRL[3] = BG_PRIORITY(0) | CHAR_BASE(0) | BG_MOSAIC | BG_256_COLOR | SCREEN_BASE(31) | BG_SIZE_0;

    TileManager stack_tile_manager;
    TileRenderer stack_tile_renderer;

    SpriteManager stack_sprite_manager;
    SpriteRenderer stack_sprite_renderer;

    tile_manager  = &stack_tile_manager;
    tile_renderer = &stack_tile_renderer;

    sprite_renderer = &stack_sprite_renderer;
    sprite_manager  = &stack_sprite_manager;

    Tileset tileset(antarctica_img_bin, colmap_bin);

    TileMap interactive(&tileset, (uint16_t*)interactive_bin);
    TileMap background(&tileset, (uint16_t*)background_bin);
    TileMap skybox(&tileset, (uint16_t*)skybox_bin);

    tilemap = &interactive;

    tile_manager->set_tileset(&tileset);
    tile_renderer->set_tilemap(1, &interactive);
    tile_renderer->set_tilemap(2, &background);
    tile_renderer->set_tilemap(3, &skybox);
    tile_renderer->set_palette(antarctica_pal_bin);
    tile_renderer->done();

    sprite_renderer->set_palette(sprites_pal_bin);
    sprite_renderer->upload((uint16_t*)sprites_img_bin);

    if (0) {
        console.print("SupeTux Portable Version 0.0.0\n");
        console.print("==============================\n");
        console.print("\nThis program is free software;"
                      "you can redistribute it and/or"
                      "modify it under the terms of\n"
                      "the GNU General Public License"
                      "as published by the Free\n"
                      "Software Foundation; either\n"
                      "version 2 of the License, or\n"
                      "(at your option) any later\n"
                      "version. Version 0.0.0\n");
    }
    else {
        console.print("SuperTux Portable Version 0.0.0\n");
    }

    Tux tux;

    scanKeys();

    while (1) {
        tux.update();
        sprite_renderer->update();
        scanKeys();
        //VBlankIntrWait();
        vid_vsync();
    }
}
