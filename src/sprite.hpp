/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#pragma once

#include "sprite_data.hpp"

/** */
class Sprite {
private:
    bool enabled;
    SpriteData data;
    int x;
    int y;
    bool world_co;
    int frame;
    bool hflip;
    bool vflip;

public:
    Sprite();
    Sprite(const SpriteData& data_);

    void set_pos(int x, int y);

    void set_x(int x_) { x = x_; }

    void set_y(int y_) { y = y_; }

    int  get_x() const { return x; }

    int  get_y() const { return y; }

    bool is_enabled() const { return enabled; }

    const SpriteData& get_data() const { return data; }

    /** If true use world coordinates, else use screen coordinates */
    bool use_world_co() const { return world_co; }

    int get_frame() const { return frame; }

    void set_hflip(bool t) { hflip = t; }

    void set_vflip(bool t) { vflip = t; }

    bool get_hflip() const { return hflip; }

    bool get_vflip() const { return vflip; }

    void update();
};
