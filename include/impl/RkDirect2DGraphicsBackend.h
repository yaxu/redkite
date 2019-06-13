/**
 * File name: RkDirect2DGraphicsBackend.h
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

#ifndef RK_DIRECT2D_GRAPHICS_BACKEND_H
#define RK_DIRECT2D_GRAPHICS_BACKEND_H

#include "RkGraphicsBackend.h"

class RkDirect2DGraphicsBackend {
 public:
        RkCairoGraphicsBackend(RkCanvas* canvas);
        ~RkCairoGraphicsBackend();
        void drawText(const std::string &text, int x, int y) final;
        void drawImage(const std::string &file, int x, int y) final;
        void drawImage(const RkImage &image, int x, int y) final;
        void drawEllipse(const RkPoint& p, int width, int height) final;
        void drawLine(const RkPoint &p1, const RkPoint &p2) final;
        void drawRect(const RkRect &rect) final;
        void drawPolyLine(const std::vector<RkPoint> &points) final;
        void fillRect(const RkRect &rect, const RkColor &color) final;
        void setPen(const RkPen &pen) final;
        void setFont(const RkFont &font) final;
        int getTextWidth(const std::string &text) const final;
        void translate(const RkPoint &offset) final;
        void rotate(rk_real angle) final;
};

#endif // RK_DIRECT2D_GRAPHICS_BACKEND_H
