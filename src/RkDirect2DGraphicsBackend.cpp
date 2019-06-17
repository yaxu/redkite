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
#include "RkPlatform.h"

RkDirect2DGraphicsBackend::RkDirect2DGraphicsBackend(RkCanvas *canvas)
        : renderTarget{canvas->getCanvasInfo()->renderTarget}
        , targetBrush{nullptr}
        , strokeWidth{1.0f}
        , strokeStyle{nullptr}
{
        if (renderTarget) {
                auto res = renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &targetBrush);
                if (!SUCCEEDED(res)) {
                        RK_LOG_ERROR("can't create brush");
                } else {
                        renderTarget->BeginDraw();
                        renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
                }
        }
}

RkDirect2DGraphicsBackend::~RkDirect2DGraphicsBackend()
{
	if (renderTarget)
		renderTarget->EndDraw();
	if (targetBrush)
		targetBrush->Release();
}

void RkDirect2DGraphicsBackend::drawText(const std::string &text, int x, int y)
{
        // TODO: impement
        /*        if (renderTarget) {
                renderTarget->DrawText(
                         static_cast<WCHAR*>(text.c_str()),
                         text.size() / sizeof(WCHAR),
                         IDWriteTextFormat      *textFormat,
                         D2D1::RectF(x, y, textFormat->FontSize())
                         targetBrush,
                         D2D1_DRAW_TEXT_OPTIONS_NONE,
                           DWRITE_MEASURING_MODE  measuringMode
                         );
                         }*/
}

void RkDirect2DGraphicsBackend::drawImage(const std::string &file, int x, int y)
{
        // TODO: impement
}

void RkDirect2DGraphicsBackend::drawImage(const RkImage &image, int x, int y)
{
        if (renderTarget) {
                ID2D1BitmapRenderTarget *bitmapRenderTarget = nullptr;
                auto target = image.getCanvasInfo()->renderTarget;
                /*                auto pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
                                                     D2D1_ALPHA_MODE_UNKNOWN);
                auto sf = D2D1::SizeF(image.width(), image.height());
                auto su = D2D1::SizeF(image.width(), image.height());*/
                target->CreateCompatibleRenderTarget(&bitmapRenderTarget);
                ID2D1Bitmap *bitmap;
                bitmapRenderTarget->GetBitmap(&bitmap);
                renderTarget->DrawBitmap(bitmap);
                bitmap->Release();
                bitmapRenderTarget->Release();
        }
}

void RkDirect2DGraphicsBackend::drawEllipse(const RkPoint& p, int width, int height)
{
        if (renderTarget) {
                renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(p.x(), p.y()), width / 2, height / 2),
                                          targetBrush,
                                          strokeWidth,
                                          strokeStyle);
        }
}

void RkDirect2DGraphicsBackend::drawLine(const RkPoint &p1, const RkPoint &p2)
{
	if (renderTarget) {
                renderTarget->DrawLine(D2D1::Point2F(static_cast<FLOAT>(p1.x()) + 0.5f,
                                                     static_cast<FLOAT>(p1.y()) + 0.5f),
                                       D2D1::Point2F(static_cast<FLOAT>(p2.x()) + 0.5f,
                                                     static_cast<FLOAT>(p2.y()) + 0.5f),
                                       targetBrush,
                                       strokeWidth,
                                       strokeStyle);
	}
}

void RkDirect2DGraphicsBackend::drawRect(const RkRect &rect)
{
        if (renderTarget) {
                auto rectF = D2D1::RectF(rect.left(), rect.top(), rect.right(), rect.bottom());
                renderTarget->DrawRectangle(rectF, targetBrush, strokeWidth, strokeStyle);
	}
}

void RkDirect2DGraphicsBackend::drawPolyLine(const std::vector<RkPoint> &points)
{
        if (renderTarget) {
                // TODO: use ID2D1PathGeometry instead drawLine().
                bool first = true;
                RkPoint currPoint;
                for (const auto &point: points) {
                        if (first) {
                                currPoint = point;
                                first = false;
                        } else if (currPoint != point) {
                                drawLine(currPoint, point);
                                currPoint = point;
                        }
                }
        }
}

void RkDirect2DGraphicsBackend::fillRect(const RkRect &rect, const RkColor &color)
{
        if (renderTarget)
                renderTarget->FillRectangle(D2D1::RectF(rect.left(), rect.top(), rect.right(), rect.bottom()),
                                            targetBrush);
}

void RkDirect2DGraphicsBackend::setPen(const RkPen &pen)
{
        strokeWidth = static_cast<FLOAT>(pen.width());
        if (targetBrush)
			targetBrush->SetColor(D2D1::ColorF(pen.color().rgb(),
                                                   static_cast<FLOAT>(pen.color().alpha()) / 255));
        FLOAT dashLine[] = {12.0f, 8.0f};
        FLOAT dotLine[] = {1.0f, 2.0f};

        if (strokeStyle) {
                strokeStyle->Release();
                strokeStyle = nullptr;
        }

        auto prop = D2D1::StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,
                                                D2D1_CAP_STYLE_FLAT,
                                                D2D1_CAP_STYLE_ROUND,
                                                D2D1_LINE_JOIN_MITER,
                                                10.0f,
                                                D2D1_DASH_STYLE_CUSTOM,
                                                0.0f);
        switch (pen.style())
        {
        case RkPen::PenStyle::DashLine:
                rk_direct2d_factory()->CreateStrokeStyle(prop, dashLine, ARRAYSIZE(dashLine), &strokeStyle);
                break;
        case RkPen::PenStyle::DotLine:
                rk_direct2d_factory()->CreateStrokeStyle(prop, dotLine, ARRAYSIZE(dotLine), &strokeStyle);
                break;
        case RkPen::PenStyle::NoLine:
        case RkPen::PenStyle::SolidLine:
        default:
                break;
        }
}

void RkDirect2DGraphicsBackend::setFont(const RkFont &font)
{
        // TODO: implement
}

int RkDirect2DGraphicsBackend::getTextWidth(const std::string &text) const
{
	// TODO: impement
	return 0;
}

void RkDirect2DGraphicsBackend::translate(const RkPoint &offset)
{
        // TODO: impement
}

void RkDirect2DGraphicsBackend::rotate(rk_real angle)
{
        // TODO: impement
}
