/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#ifndef HEADER_CAMERA_HPP
#define HEADER_CAMERA_HPP

/** Class for handling scrolling parameter */
class Camera {
public:
    Camera();
    ~Camera();

private:
    Camera(const Camera&);
    Camera& operator =(const Camera&);
};

#endif
