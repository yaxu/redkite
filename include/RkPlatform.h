/**
 * File name: RkPlatform.h
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor <http://quamplex.com>
 *
 * This file is part of Redkite.
 *
 * Redkite is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef RK_PLATFORM_H
#define RK_PLATFORM_H

#include "Rk.h"
#include "RkLog.h"

#ifdef RK_OS_WIN
#include <windows.h>

struct RK_EXPORT RkWindowId {
    RkWindowId(HWND arg = nullptr) : id(arg) {}
    HWND id;
};

class ID2D1Factory1;
struct RK_EXPORT RkNativeWindowInfo {
        RkNativeWindowInfo(HWND arg = nullptr) : window(arg) {}
        HINSTANCE instance;
        std::string className;
        HWND window;
#ifdef RK_DIRECT2D_GRAPHICS_BACKEND
        ID2D1Factory1* factory;
#endif // RK_GRAPHICS_BACKEND_DIRECT2D
};

HINSTANCE RK_EXPORT rk_win_api_instance();
std::string RK_EXPORT rk_win_api_class_name();
RkNativeWindowInfo RK_EXPORT rk_from_native_win(HINSTANCE instance, LPCSTR className, HWND window);
RkWindowId RK_EXPORT rk_id_from_win(HWND window);
#ifdef RK_GRAPHICS_BACKEND_DIRECT2D
ID2D1Factory1* RK_EXPORT rk_direct2d_factory();
#endif // RK_DIRECT2D_GRAPHICS_BACKEND


#define RK_WIN_MESSAGE_PAINT (WM_USER + 0x0001)

#elif RK_OS_MAC
// to be defined
#else // X11
#include <X11/Xlib.h>

struct RK_EXPORT RkWindowId {
        Window id;
};

struct RK_EXPORT RkNativeWindowInfo
{
        Display* display;
        int screenNumber;
        Window window;
};

RkNativeWindowInfo RK_EXPORT rk_from_native_x11(Display* display, int screenNumber, Window window);
RkWindowId RK_EXPORT rk_id_from_x11(Window window);

#endif // X11

#endif // RK_PLATFORM_H
