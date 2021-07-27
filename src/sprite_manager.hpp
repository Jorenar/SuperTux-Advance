/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#pragma once

#include "types.hpp"

/** Class for handling sprite allocation, at the moment unused, all
    code is in SpriteRenderer and will be refactored into this one
    later on
 */
class SpriteManager {
private:
public:
    SpriteManager();
    ~SpriteManager();

private:
    SpriteManager(const SpriteManager&);
    SpriteManager& operator =(const SpriteManager&);
};
