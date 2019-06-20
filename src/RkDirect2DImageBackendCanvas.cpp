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

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1 };

	canvasInfo = std::make_shared<RkCanvasInfo>();
	canvasInfo->window = 0;
	canvasInfo->size = size;

	auto hr = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG,
		featureLevels,
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		&canvasInfo->device3D,
		nullptr,
		nullptr);

	canvasInfo->device3D->QueryInterface(&canvasInfo->dxgiDevice);
	hr = rk_direct2d_factory()->CreateDevice(canvasInfo->dxgiDevice, &canvasInfo->device2D);
	
	RK_LOG_DEBUG(hr);
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
