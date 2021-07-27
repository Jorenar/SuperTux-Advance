/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#pragma once

#include <stdint.h>

/** */
class SpriteData {
private:
    uint16_t* data;

public:
    SpriteData();
    SpriteData(uint16_t* data_);
    ~SpriteData();

    uint16_t get_char_addr(int frame) const;

    uint16_t get_frames() const;

    uint16_t get_width()  const;
    uint16_t get_height() const;

    uint16_t get_fps() const;

    uint16_t get_x_align() const;
    uint16_t get_y_align() const;
};
