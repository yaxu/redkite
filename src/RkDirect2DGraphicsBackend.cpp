/**
 * File name: RkDirect2DGraphicsBackend.cpp
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

#include "RkDirect2DGraphicsBackend.h"
#include "RkCanvas.h"
#include "RkCanvasInfo.h"
#include "RkLog.h"

#include <math.h>

RkDirect2DGraphicsBackend::RkDirect2DGraphicsBackend(RkCanvas *canvas)
        : renderTarget{nullptr}
{
        
}

void RkDirect2DGraphicsBackend::drawText(const std::string &text, int x, int y)
{
}

void RkDirect2DGraphicsBackend::drawImage(const std::string &file, int x, int y)
{
}

void RkDirect2DGraphicsBackend::drawImage(const RkImage &image, int x, int y)
{
}

void RkDirect2DGraphicsBackend::drawEllipse(const RkPoint& p, int width, int height)
{
}

void RkDirect2DGraphicsBackend::drawLine(const RkPoint &p1, const RkPoint &p2)
{
}

void RkDirect2DGraphicsBackend::drawRect(const RkRect &rect)
{
}

void RkDirect2DGraphicsBackend::drawPolyLine(const std::vector<RkPoint> &points)
{
}

void RkDirect2DGraphicsBackend::fillRect(const RkRect &rect, const RkColor &color)
{
}

void RkDirect2DGraphicsBackend::setPen(const RkPen &pen)
{
}

void RkDirect2DGraphicsBackend::setFont(const RkFont &font)
{
}

int RkDirect2DGraphicsBackend::getTextWidth(const std::string &text) const
{
}

void RkDirect2DGraphicsBackend::translate(const RkPoint &offset)
{
}

void RkDirect2DGraphicsBackend::rotate(rk_real angle)
{
}
