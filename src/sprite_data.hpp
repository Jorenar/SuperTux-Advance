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

#ifndef HEADER_SPRITE_DATA_HPP
#define HEADER_SPRITE_DATA_HPP

#include "types.hpp"

/** */
class SpriteData
{
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

#endif
