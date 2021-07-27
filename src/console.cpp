/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2021 Jorengarenar <dev@joren.ga>
 * Copyright (C) 2005 Ingo Ruhnke  <grumbel@gmx.de>
 */

#include "console.hpp"

#include <gba_video.h>

Console console;

Console::Console() :
    screen((uint16_t*)MAP_BASE_ADR(28)),
    x_pos(0),
    y_pos(0),
    width(30),
    height(20)
{}

Console::~Console() {}

void Console::print(const char* buf)
{
    while (*buf) {
        putchar(*buf++);
    }
}

void Console::clear()
{
    for (uint16_t i = 0; i < 32*32; ++i) {
        screen[i] = char2tile(' ');
    }

    x_pos = 0;
    y_pos = 0;
}

void Console::scroll()
{
    for (uint8_t y = 0; y < height-1; ++y) {
        for (uint8_t x = 0; x < width; ++x) {
            screen[y * 32 + x] = screen[(y+1) * 32 + x];
        }
    }

    for (uint8_t x = 0; x < width; ++x) {
        screen[(height-1) * 32 + x] = char2tile(' ');
    }
}

void Console::putchar(char c)
{
    if (c == '\n') {
        x_pos = 0;
        y_pos += 1;

        if (y_pos == height) {
            scroll();
            y_pos = height - 1;
        }
    }
    else {
        screen[32 * y_pos + x_pos] = char2tile(c);

        x_pos += 1;
        if (x_pos == width) {
            x_pos = 0;
            y_pos += 1;

            if (y_pos == height) {
                scroll();
                y_pos = height - 1;
            }
        }
    }
}

void Console::moveto(uint8_t x, uint8_t y)
{
    x_pos = x % width;
    y_pos = y % height;
}

void Console::print(uint16_t num)
{
    char buf[6];
    char* ptr = buf;

    if (num == 0) {
        putchar('0');
    }
    else {
        while (num > 0) {
            *ptr++ = (num % 10) + '0';
            num /= 10;
        }
        ptr -= 1;
        while (ptr >= buf) {
            putchar(*ptr--);
        }
    }
}

Console& operator <<(Console& c, const char* buf)
{
    c.print(buf);
    return c;
}

Console& operator <<(Console& c, uint16_t num)
{
    c.print(num);
    return c;
}
