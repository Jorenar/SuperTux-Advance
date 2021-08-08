/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#pragma once

class TileManager;
class TileRenderer;

class SpriteManager;
class SpriteRenderer;

class Level;

extern TileManager*  tile_manager;
extern TileRenderer* tile_renderer;

extern SpriteManager*  sprite_manager;
extern SpriteRenderer* sprite_renderer;

extern Level* level;
