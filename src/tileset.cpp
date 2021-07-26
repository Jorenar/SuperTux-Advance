/*  $Id$
**
**  SuperTux Portable
**  Copyright (C) 2005 Ingo Ruhnke <grumbel@gmx.de>
**
**  This program is free software; you can redistribute it and/or
**  modify it under the terms of the GNU General Public License
**  as published by the Free Software Foundation; either version 2
**  of the License, or (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
**  02111-1307, USA.
*/

#include "tileset.hpp"

Tileset::Tileset(const void* data_, const void* colmap_)
  : data(static_cast<const uint16_t*>(data_)),
    colmap(static_cast<const uint8_t*>(colmap_))
{
}

Tileset::~Tileset()
{
}

const uint16_t*
Tileset::get_tile(uint16_t id) const
{
  return data + (32 * id);
}

uint8_t
Tileset::get_colmap(uint16_t id) const
{
  return colmap[id];
}
