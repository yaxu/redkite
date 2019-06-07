/**
 * File name: RkWindowWin.h
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

#ifndef RK_WINDOW_WIN_H
#define RK_WINDOW_WIN_H

#include "Rk.h"
#include "RkPlatform.h"
#include "RkSize.h"
#include "RkPoint.h"
#include "RkColor.h"

class RkEventQueue;
struct RkCanvasInfo;

// TODO: define a common interface for window platform
class RkWindowWin {
 public:
        explicit RkWindowWin(const std::shared_ptr<RkNativeWindowInfo> &parent = nullptr,
                             Rk::WindowFlags flags = Rk::WindowFlags::Widget);
        explicit RkWindowWin(const RkNativeWindowInfo &parent,
                             Rk::WindowFlags flags = Rk::WindowFlags::Widget);
        ~RkWindowWin();
        RkWindowWin(const RkWindowWin &other) = delete;
        RkWindowWin& operator=(const RkWindowWin &other) = delete;
        RkWindowWin(RkWindowWin &&other) = delete;
        RkWindowWin& operator=(RkWindowWin &&other) = delete;
        bool init();
        void show();
        std::shared_ptr<RkNativeWindowInfo> nativeWindowInfo();
        void setTitle(const std::string &title);
        RkSize& size() const;
        void setSize(const RkSize &size);
        RkPoint& position() const;
        void setPosition(const std::pair<int, int> &position);
        RkWindowId id() const;
        void setBorderWidth(int width);
        int borderWidth() const;
        void setBorderColor(const RkColor &color);
        const RkColor& borderColor() const;
        void setBackgroundColor(const RkColor &color);
        const RkColor& background() const;
        void resizeCanvas();
        std::shared_ptr<RkCanvasInfo> getCanvasInfo();
        void update();
        void setFocus(bool b);
        bool hasFocus();
        void setPointerShape(Rk::PointerShape shape);
        void setEventQueue(RkEventQueue* queue);

 protected:
        bool isWindowCreated() const;
        bool hasParent() const;
        void createCanvasInfo();
        void freeCanvasInfo();

 private:
        std::shared_ptr<RkNativeWindowInfo> parentWindowInfo;
        RkWindowId windowHandle;
        mutable RkPoint windowPosition;
        mutable RkSize windowSize;
        int borderWidth;
        RkColor borderColor;
        RkColor backgroundColor;
        RkEventQueue* eventQueue;
        std::shared_ptr<RkCanvasInfo> canvasInfo;
        Rk::WindowFlags windowFlags;
};

#endif // RK_WIDGET_WIN_H
