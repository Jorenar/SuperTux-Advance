/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#pragma once

/** */
class Contact {
protected:
    int x_pos;
    int y_pos;

public:
    Contact();
    virtual ~Contact() {}

    virtual void set_pos(int x, int y) = 0;
};

class GroundContact : public Contact {
public:
    GroundContact();
    void set_pos(int x, int y);
};

class AirContact : public Contact {
public:
    AirContact();
    void set_pos(int x, int y);
};
