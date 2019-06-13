/**
 * File name: RkWindowWin.cpp
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

#include "RkLog.h"
#include "RkWindowWin.h"
#include "RkCanvasInfo.h"

#include <cairo/cairo-win32.h>

RkWindowWin::RkWindowWin(const std::shared_ptr<RkNativeWindowInfo> &parent, Rk::WindowFlags flags)
        : parentWindowInfo{parent}
        , windowHandle{{nullptr}}
        , windowPosition{0, 0}
        , windowSize{250, 250}
        , winBorderWidth{1}
        , winBorderColor{255, 255, 255}
        , backgroundColor{255, 255, 255}
        , eventQueue{nullptr}
        , canvasInfo{nullptr}
        , windowFlags{flags}
{
}

RkWindowWin::RkWindowWin(const RkNativeWindowInfo &parent, Rk::WindowFlags flags)
        : parentWindowInfo{std::make_shared<RkNativeWindowInfo>()}
        , windowHandle{{nullptr}}
        , windowPosition{0, 0}
        , windowSize{250, 250}
        , winBorderWidth{1}
        , winBorderColor{255, 255, 255}
        , backgroundColor{255, 255, 255}
        , eventQueue{nullptr}
        , canvasInfo{nullptr}
        , windowFlags{flags}

{
        *parentWindowInfo.get() = parent;
}

RkWindowWin::~RkWindowWin()
{
}

bool RkWindowWin::hasParent() const
{
        return parentWindowInfo != nullptr;
}

bool RkWindowWin::init()
{
        windowHandle.id = CreateWindowExA(0,
                                          hasParent() ? parentWindowInfo->className.c_str() : rk_winApiClassName.c_str(),
                                          "RkWidget",
                                          !hasParent() ? WS_OVERLAPPEDWINDOW : WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE | WS_BORDER,
                                          windowPosition.x(),
                                          windowPosition.y(),
                                          windowSize.width(),
                                          windowSize.height(),
                                          !hasParent() ? nullptr : parentWindowInfo->window,
                                          nullptr,
                                          hasParent() ? parentWindowInfo->instance : rk_winApiInstance,
                                          nullptr);

        if (!windowHandle.id) {
                RK_LOG_ERROR("can't create window");
                return false;
        }

        if (eventQueue)
                SetWindowLongPtr(windowHandle.id, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(eventQueue));

        return true;
}

void RkWindowWin::show(bool b)
{
        if (isWindowCreated()) {
                ShowWindow(windowHandle.id, b ? SW_SHOW : SW_HIDE);
                UpdateWindow(windowHandle.id);
        }
}

std::shared_ptr<RkNativeWindowInfo> RkWindowWin::nativeWindowInfo()
{
        if (isWindowCreated()) {
                auto info = std::make_shared<RkNativeWindowInfo>();
                info->className = hasParent() ? parentWindowInfo->className : rk_winApiClassName;
                info->window    = windowHandle.id;
                info->instance  = hasParent() ? parentWindowInfo->instance : rk_winApiInstance;
                return info;
        }

        return nullptr;
}

void RkWindowWin::setTitle(const std::string &title)
{
        if (isWindowCreated() && !title.empty())
                SetWindowTextA(windowHandle.id, title.c_str());
}

bool RkWindowWin::isWindowCreated() const
{
        return windowHandle.id != nullptr;
}

const RkSize& RkWindowWin::size() const
{
        if (isWindowCreated()) {
                RECT rect;
                GetWindowRect(windowHandle.id, &rect);
				windowSize = {rect.right - rect.left, rect.bottom - rect.top};
        }
        return windowSize;
}

void RkWindowWin::setSize(const RkSize &size)
{
        if (size.width() > 0 && size.height() > 0) {
                windowSize = size;
                if (isWindowCreated())
                        SetWindowPos(windowHandle.id, 0, 0, 0, size.width(), size.height(), SWP_NOMOVE | SWP_NOZORDER);
        }
}

RkPoint& RkWindowWin::position() const
{
        if (isWindowCreated()) {
                RECT rect;
                GetWindowRect(windowHandle.id, &rect);
                if (hasParent())
                        MapWindowPoints(windowHandle.id, GetParent(windowHandle.id), reinterpret_cast<LPPOINT>(&rect), 2);
                windowPosition = {rect.left, rect.top};
        }
        return windowPosition;
}

void RkWindowWin::setPosition(const RkPoint &position)
{
        windowPosition = position;
        if (isWindowCreated())
                SetWindowPos(windowHandle.id, 0, position.x(), position.y(), 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void RkWindowWin::setBorderWidth(int width)
{
	// IMPLEMENT
		winBorderWidth = width;
}

int RkWindowWin::borderWidth() const
{
	//IMPLEMENT
	return winBorderWidth;
}

void RkWindowWin::setBorderColor(const RkColor &color)
{
        winBorderColor = color;
}

const RkColor& RkWindowWin::borderColor() const
{
	return winBorderColor;
}

void RkWindowWin::setBackgroundColor(const RkColor &background)
{
        backgroundColor = background;
}

RkWindowId RkWindowWin::id() const
{
        RkWindowId id;
        id.id = windowHandle.id;
        return id;
}

const RkColor& RkWindowWin::background() const
{
	// IMPLEMENT
	return backgroundColor;
}

std::shared_ptr<RkCanvasInfo> getCanvasInfo()
{
	// IMPLEMENT
	return nullptr;
}

void RkWindowWin::update()
{
}

#ifdef RK_DIRECT2D_GRAPHICS_BACKEND
void RkWindowWin::createCanvasInfo()
{
        canvasInfo = std::make_shared<RkCanvasInfo>();
        canvasInfo->windowHandle = windowHandle.id;
}

void RkWindowWin::resizeCanvas()
{
}

std::shared_ptr<RkCanvasInfo> RkWindowWin::getCanvasInfo()
{
        return canvasInfo;
}

void RkWindowWin::freeCanvasInfo()
{
        cairo_surface_destroy(canvasInfo->cairo_surface);
}
#else
#error No graphics backend defined
#endif // RK_GRAPHICS_CAIRO_BACKEND

void RkWindowWin::setFocus(bool b)
{
        // IMPLEMENT
}

bool RkWindowWin::hasFocus()
{
        // IMPLEMENT
		return false;
}

void RkWindowWin::setPointerShape(Rk::PointerShape shape)
{
        // IMPLEMENT
}

void RkWindowWin::setEventQueue(RkEventQueue *queue)
{
        eventQueue = queue;
        SetWindowLongPtr(windowHandle.id, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(eventQueue));
        InvalidateRect(windowHandle.id, nullptr, FALSE);
        UpdateWindow(windowHandle.id);
}
