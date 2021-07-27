/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#include <math.h>
#include "math.hpp"

Math math;

Math::Math()
{
    for (uint16_t i = 0; i < 256; ++i) {
        sin_table[i] = (uint8_t)(::sin(i/8.0f) * 20);
    }
}

Math::~Math() {}

uint8_t Math::sin(uint8_t angle)
{
    return sin_table[angle];
}

uint8_t Math::cos(uint8_t angle)
{
    return sin_table[angle];
}
