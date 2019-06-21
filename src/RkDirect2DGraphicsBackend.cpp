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

#include <d2d1_1helper.h>

RkDirect2DGraphicsBackend::RkDirect2DGraphicsBackend(RkCanvas *canvas)
        : deviceContext{nullptr}
        , swapChain{nullptr};
        , d2dTargetBitmap{nullptr};
        , targetBrush{nullptr}
        , strokeWidth{1.0f}
        , strokeStyle{nullptr}
{
        if (validateCanvase(canvas)) {
                auto res = prepareContext();
                if (!res) {
                        auto hr = deviceContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &targetBrush);
                        if (!SUCCEEDED(hr)) {
                                RK_LOG_ERROR("can't create brush");
                                releaseContextResources();
                        } else {
                                deviceContext->BeginDraw();
                                deviceContext->Clear(D2D1::ColorF(D2D1::ColorF::White));
                        }
                }
        }
}

bool RkDirect2DGraphicsBackend::validateCanvase(RkCanvas *canvas)
{
        if (canvas->type() != RkCanvas::Type::Window) {
                RK_LOG_ERROR("unsuported canvase");
                return false;
        } else if (!canvas->getCanvasInfo() || !canvas->getCanvasInfo()->device2DInfo.device2D) {
                RK_LOG_ERROR("canvas is not ready for drawing");
                return false;
        }
        return true;
}

bool RkDirect2DGraphicsBackend::prepareContext()
{
        auto deviceInfo = canvas->getCanvasInfo()->device2DInfo;
        auto hr = deviceInfo.device2D->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &deviceContext);
        if (!SUCCEEDED(hr)) {
                RK_LOG_ERROR("can't create device context");
                return false;
        }

        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {0};
        swapChainDesc.Width = 0;
        swapChainDesc.Height = 0;
        swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        swapChainDesc.Stereo = false;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = 2;
        swapChainDesc.Scaling = DXGI_SCALING_NONE;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
        swapChainDesc.Flags = 0;

        IDXGIAdapter *dxgiAdapter = nullptr;
        deviceInfo.dxgiDevice->GetAdapter(&dxgiAdapter);
        if (!dxgiAdapter) {
                RK_LOG_ERROR("can't get DXGI adaptor");
                releaseContextResources();
                return false;
        }

        IDXGIFactory2 *dxgiFactory = nullptr;
        dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));
        if (!dxgiFactory) {
                RK_LOG_ERROR("can't get DXGI factory");
                releaseContextResources();
                return false;
        }
        hr = dxgiFactory->CreateSwapChainForHwnd(deviceInfo.device3D,
                                                 deviceInfo.window,
                                                 &swapChainDesc,
                                                 nullptr,
                                                 nullptr,
                                                 &swapChain);
        if (!SUCCEEDED(hr)) {
                RK_LOG_ERROR("can't get DXGI factory");
                releaseContextResources();
                return false;
        }

        deviceInfo.dxgiDevice->SetMaximumFrameLatency(1);
        ID3D11Texture2D *backBuffer= nullptr;
        swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
        if (!backBuffer) {
                RK_LOG_ERROR("can't get texture back buffer");
                releaseContextResources();
                return;
        }

        D2D1_PIXEL_FORMAT pixelFormat = {DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE};
        auto bitmapProperties = D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW, pixelFormat);
        IDXGISurface *dxgiBackBuffer = nullptr;
        swapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer));
        if (!dxgiBackBuffer) {
                RK_LOG_ERROR("can't get DXGI surface buffer");
                releaseContextResources();
                return false;
        }
        hr = deviceContext->CreateBitmapFromDxgiSurface(dxgiBackBuffer, &bitmapProperties, &d2dTargetBitmap);
        if (!SUCCEEDED(hr)) {
                RK_LOG_ERROR("can't create Bitmap from DXGI surface");
                releaseContextResources();
                return false;
        }

        deviceContext->SetTarget(d2dTargetBitmap);
        return true;
}

RkDirect2DGraphicsBackend::~RkDirect2DGraphicsBackend()
{
	if (deviceContext) {
		deviceContext->EndDraw();
                if (swapChain)
                        swapChain->Present(1, 0);
                releaseContextResources();
	}
}

void RkDirect2DGraphicsBackend::releaseContextResources()
{
        if (swapChain) {
                swapChain->Release();
                swapChain = nullptr;
        }
        if (d2dTargetBitmap) {
                d2dTargetBitmap->Release();
                d2dTargetBitmap = nullptr;
        }
        if (deviceContext) {
                deviceContext->Release();
                deviceContext = nullptr;
        }
        if (targetBrush) {
		targetBrush->Release();
                targetBrush = nullptr;
        }

        if (strokeStyle) {
                strokeStyle->Release();
                strokeStyle = nullptr;
        }
}

void RkDirect2DGraphicsBackend::drawText(const std::string &text, int x, int y)
{
        // TODO: impement
        /*        if (deviceContext) {
                deviceContext->DrawText(
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
        //	deviceContext->DrawBitmap(image.getCanvasInfo()->d2dTargetBitmap);
}

void RkDirect2DGraphicsBackend::drawEllipse(const RkPoint& p, int width, int height)
{
        if (deviceContext)
                deviceContext->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(p.x(), p.y()), width / 2, height / 2),
                                           targetBrush,
                                           strokeWidth,
                                           strokeStyle);
}

void RkDirect2DGraphicsBackend::drawLine(const RkPoint &p1, const RkPoint &p2)
{
	if (deviceContext) {
                deviceContext->DrawLine(D2D1::Point2F(static_cast<FLOAT>(p1.x()) + 0.5f,
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
        if (deviceContext) {
                auto rectF = D2D1::RectF(rect.left(), rect.top(), rect.right(), rect.bottom());
                deviceContext->DrawRectangle(rectF, targetBrush, strokeWidth, strokeStyle);
	}
}

void RkDirect2DGraphicsBackend::drawPolyLine(const std::vector<RkPoint> &points)
{
        if (deviceContext) {
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
        if (deviceContext)
                deviceContext->FillRectangle(D2D1::RectF(rect.left(), rect.top(), rect.right(), rect.bottom()),
                                             targetBrush);
}

void RkDirect2DGraphicsBackend::setPen(const RkPen &pen)
{
        strokeWidth = static_cast<FLOAT>(pen.width());
        if (targetBrush)
                targetBrush->SetColor(D2D1::ColorF(pen.color().rgb(), static_cast<FLOAT>(pen.color().alpha()) / 255));
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
