/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#include "contact.hpp"

Contact::Contact() : x_pos(0), y_pos(0) {}

GroundContact::GroundContact() {}

void GroundContact::set_pos(int x, int y) {}

AirContact::AirContact() {}

void AirContact::set_pos(int x, int y) {}
