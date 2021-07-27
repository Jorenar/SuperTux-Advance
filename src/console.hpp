/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#ifndef HEADER_CONSOLE_HPP
#define HEADER_CONSOLE_HPP

#include <stdint.h>

/** */
class Console {
private:
    uint16_t* screen;
    uint8_t x_pos;
    uint8_t y_pos;
    uint8_t width;
    uint8_t height;

public:
    Console();
    ~Console();

    void print(const char* buf);
    void print(uint16_t num);

    void putchar(char c);
    void write(const char* buf, uint16_t len);

    void moveto(uint8_t x, uint8_t y);
    void clear();

    void scroll();

    inline uint16_t char2tile(char c) { return 800 - 32 + c; }

private:
    Console(const Console&);
    Console& operator =(const Console&);
};

Console& operator <<(Console& c, const char* buf);
Console& operator <<(Console& c, uint16_t num);

extern Console console;

#endif
