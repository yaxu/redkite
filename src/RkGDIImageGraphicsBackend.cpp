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

#include "RkGDIGraphicsBackend.h"
#include "RkCanvas.h"
#include "RkCanvasInfo.h"
#include "RkLog.h"
#include "RkPlatform.h"

RkGDIGraphicsBackend::RkGDIGraphicsBackend(RkCanvas *canvas)
{
}

RkGDIGraphicsBackend::~RkGDIGraphicsBackend()
}

void RkGDIGraphicsBackend::drawText(const std::string &text, int x, int y)
{
}

void RkGDIGraphicsBackend::drawImage(const std::string &file, int x, int y)
{
}

void RkGDIGraphicsBackend::drawImage(const RkImage &image, int x, int y)
{
}

void RkGDIGraphicsBackend::drawEllipse(const RkPoint& p, int width, int height)
{
}

void RkGDIGraphicsBackend::drawLine(const RkPoint &p1, const RkPoint &p2)
{
}

void RkGDIGraphicsBackend::drawRect(const RkRect &rect)
{
}

void RkGDIGraphicsBackend::drawPolyLine(const std::vector<RkPoint> &points)
{
}

void RkGDIGraphicsBackend::fillRect(const RkRect &rect, const RkColor &color)
{
}

void RkGDIGraphicsBackend::setPen(const RkPen &pen)
{
}

void RkGDIGraphicsBackend::setFont(const RkFont &font)
{
        // TODO: implement
}

int RkGDIGraphicsBackend::getTextWidth(const std::string &text) const
{
	// TODO: impement
	return 0;
}

void RkGDIGraphicsBackend::translate(const RkPoint &offset)
{
        // TODO: impement
}

void RkGDIGraphicsBackend::rotate(rk_real angle)
{
        // TODO: impement
}
