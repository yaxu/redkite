/**
 * File name: RkCanvasInfo.h
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor (http://quamplex.com/redkite)
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

#ifndef RK_CANVAS_INFO_H
#define RK_CANVAS_INFO_H

#include "Rk.h"

#ifdef RK_GRAPHICS_BACKEND_CAIRO
#include <cairo/cairo.h>
struct RkCanvasInfo {
        cairo_surface_t* cairo_surface;
};
#elif RK_GRAPHICS_BACKEND_DIRECT2D
#include <d2d1_1.h>
#include <d3d11.h>
#include <dxgi1_2.h>
struct RkCanvasInfo {
	HWND window;
	ID3D11Device* device3D;
	ID2D1Device* device2D;
	IDXGIDevice1 *dxgiDevice;
};
#else
#error No graphics backend defined
#endif

#endif // RK_CANVAS_INFO_H
