/**
 * File name: RkImageImpl.cpp
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

#include "RkImageImpl.h"
#ifdef RK_GRAPHICS_BACKEND_CAIRO
#include "RkCairoImageBackendCanvas.h"
#elif RK_GRAPHICS_BACKEND_DIRECT2D
#include "RkGDIImageBackendCanvas.h"
#else
#error No graphics backend defined.
#endif

RkImage::RkImageImpl::RkImageImpl(RkImage *interface,
                                  int width,
                                  int height,
                                  const unsigned char *data,
                                  RkImage::Format format)
        : inf_ptr{interface}
        , imageFormat{format}
#ifdef RK_GRAPHICS_BACKEND_CAIRO
        , imageBackendCanvas{std::make_unique<RkCairoImageBackendCanvas>(RkSize(width, height), imageFormat, data)}
#elif RK_GRAPHICS_BACKEND_DIRECT2D
          // USE GDI+ for in memory rendering instead of Direct2D.
          // Direct2D is only for Windows.
        , imageBackendCanvas{std::make_unique<RkGDIImageBackendCanvas>(RkSize(width, height), imageFormat, data)}
#else
#error No graphics backend defined
#endif
        , backgroundColor{0, 0, 0}
{
}

RkImage::RkImageImpl::~RkImageImpl()
{
}

std::shared_ptr<RkCanvasInfo> RkImage::RkImageImpl::getCanvasInfo() const
{
        if (imageBackendCanvas)
                return imageBackendCanvas->getCanvasInfo();
        return nullptr;
}

unsigned char* RkImage::RkImageImpl::data() const
{
        return imageBackendCanvas->data();
}

std::vector<unsigned char> RkImage::RkImageImpl::dataCopy() const
{
        if (imageBackendCanvas)
                return imageBackendCanvas->dataCopy();
        return std::vector<unsigned char>();
}

RkImage::Format RkImage::RkImageImpl::format() const
{
        return imageFormat;
}

int RkImage::RkImageImpl::width() const
{
        if (imageBackendCanvas)
                return imageBackendCanvas->size().width();
        return 0;
}

int RkImage::RkImageImpl::height() const
{
        if (imageBackendCanvas)
                return imageBackendCanvas->size().height();
        return 0;
}

bool RkImage::RkImageImpl::isNull() const
{
        return !imageBackendCanvas || imageBackendCanvas->isNull();
}

void RkImage::RkImageImpl::createImage(const RkSize &size,
                                       RkImage::Format format,
                                       const unsigned char *data)
{
        imageFormat = format;
#ifdef RK_GRAPHICS_CAIRO_BACKEND
        imageBackendCanvas = std::make_unique<RkCairoImageBackendCanvas>(size, format, data);
#elif RK_GRAPHICS_BACKEND_DIRECT2D
        imageBackendCanvas = std::make_unique<RkGDIImageBackendCanvas>(size, format, data);
#else
#error No graphics backend defined
#endif
}

void RkImage::RkImageImpl::fill(const RkColor &color)
{
        if (imageBackendCanvas)
                imageBackendCanvas->fill(color);
}

const RkColor& RkImage::RkImageImpl::background() const
{
	return backgroundColor;
}
