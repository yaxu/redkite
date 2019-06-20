#include "RkDirect2DImageBackendCanvas.h"
#include "RkCanvasInfo.h"
#include "RkLog.h"
#include "RkPlatform.h"

#include <d3d11.h>

RkDirect2DImageBackendCanvas::RkDirect2DImageBackendCanvas(const RkSize &size,
                                                     RkImage::Format format,
                                                     const unsigned char *data)
        : canvasInfo{nullptr}
        , imageSize{size}
        , device3D{nullptr}
        , context3D{nullptr}
        , offscreenTexture{nullptr}
{
	/*RK_LOG_INFO("h:1");
        if (imageSize.width() > 0 && imageSize.height() > 0) {
                canvasInfo = std::make_shared<RkCanvasInfo>();
                if (data == nullptr)
                        imageData = std::vector<unsigned char>(imageSize.width() * imageSize.height() * 4, 0);
                else
                        imageData.assign(data, data + imageSize.width() * imageSize.height() * 4);
        }

        if (canvasInfo) {
			RK_LOG_INFO("h:2");
                D3D_FEATURE_LEVEL featureLevels[] = {
                        D3D_FEATURE_LEVEL_11_1,
                        D3D_FEATURE_LEVEL_11_0,
                        D3D_FEATURE_LEVEL_10_1,
                        D3D_FEATURE_LEVEL_10_0,
                        D3D_FEATURE_LEVEL_9_3,
                        D3D_FEATURE_LEVEL_9_2,
                        D3D_FEATURE_LEVEL_9_1};

                auto hr = D3D11CreateDevice(
					              nullptr,
                                  D3D_DRIVER_TYPE_HARDWARE,
					              nullptr,
					              D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG,
                                  featureLevels,
                                  ARRAYSIZE(featureLevels),
                                  D3D11_SDK_VERSION,
                                  &device3D,
                                  nullptr,
                                  nullptr);

				if (!SUCCEEDED(hr)) {
					RK_LOG_ERROR("error on creating 3device");
				}
				RK_LOG_INFO("h:3");
                D3D11_TEXTURE2D_DESC texDesc;
                texDesc.ArraySize = 1;
                texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
                texDesc.CPUAccessFlags = 0;
                texDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
                texDesc.Height = size.width();
                texDesc.Width = size.height();
                texDesc.MipLevels = 1;
                texDesc.MiscFlags = 0;
                texDesc.SampleDesc.Count = 1;
                texDesc.SampleDesc.Quality = 0;
                texDesc.Usage = D3D11_USAGE_DEFAULT;
	
                hr = device3D->CreateTexture2D(&texDesc, nullptr, &offscreenTexture);
				if (!SUCCEEDED(hr)) {
					RK_LOG_ERROR("error on create texture");
				}
				RK_LOG_INFO("h:4");
                IDXGISurface *pDxgiSurface = nullptr;
                offscreenTexture->QueryInterface(&pDxgiSurface);
				DXGI_SURFACE_DESC desc;
				pDxgiSurface->GetDesc(&desc);
				auto props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), 96, 96);
				ID2D1RenderTarget *target;
                hr = rk_direct2d_factory()->CreateDxgiSurfaceRenderTarget(pDxgiSurface, &props, &target);
				ID2D1BitmapRenderTarget *bitmapRenderTarget;
				hr = target->CreateCompatibleRenderTarget(&bitmapRenderTarget);
				canvasInfo->renderTarget = static_cast<ID2D1RenderTarget*>(bitmapRenderTarget);
				if (!SUCCEEDED(hr))
					RK_LOG_ERROR("error on creating render target");
				RK_LOG_INFO("h:5");
        }*/
}

RkDirect2DImageBackendCanvas::~RkDirect2DImageBackendCanvas()
{
     /*   if (canvasInfo && canvasInfo->renderTarget)
                canvasInfo->renderTarget->Release();
        if (offscreenTexture)
                offscreenTexture->Release();
        if (context3D) 
                context3D->Release();
        if (device3D)
                device3D->Release();*/
}

int RkDirect2DImageBackendCanvas::pixelLength(RkImage::Format format) const
{
	// Implement.
	return 0;
}

const RkSize& RkDirect2DImageBackendCanvas::size() const
{
        return imageSize;
}

bool RkDirect2DImageBackendCanvas::isNull() const
{
        return canvasInfo == nullptr;
}

unsigned char* RkDirect2DImageBackendCanvas::data()
{
        return imageData.data();
}

std::vector<unsigned char> RkDirect2DImageBackendCanvas::dataCopy() const
{
        return imageData;
}

std::shared_ptr<RkCanvasInfo> RkDirect2DImageBackendCanvas::getCanvasInfo() const
{
        return canvasInfo;
}

void RkDirect2DImageBackendCanvas::fill(const RkColor &color)
{
}
