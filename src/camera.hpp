/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#pragma once

/** Class for handling scrolling parameter */
class Camera {
public:
    Camera();
    ~Camera();

private:
    Camera(const Camera&);
    Camera& operator =(const Camera&);
};
