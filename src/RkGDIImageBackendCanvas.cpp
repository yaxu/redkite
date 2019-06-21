#include "RkGDIImageBackendCanvas.h"
#include "RkCanvasInfo.h"
#include "RkLog.h"
#include "RkPlatform.h"

RkGDIImageBackendCanvas::RkGDIImageBackendCanvas(const RkSize &size,
                                                     RkImage::Format format,
                                                     const unsigned char *data)
        : canvasInfo{nullptr}
        , imageSize{size}
{
}

RkGDIImageBackendCanvas::~RkGDIImageBackendCanvas()
{
}

int RkGDIImageBackendCanvas::pixelLength(RkImage::Format format) const
{
	// Implement.
	return 0;
}

const RkSize& RkGDIImageBackendCanvas::size() const
{
        return imageSize;
}

bool RkGDIImageBackendCanvas::isNull() const
{
        return canvasInfo == nullptr;
}

unsigned char* RkGDIImageBackendCanvas::data()
{
        return imageData.data();
}

std::vector<unsigned char> RkGDIImageBackendCanvas::dataCopy() const
{
        return imageData;
}

std::shared_ptr<RkCanvasInfo> RkGDIImageBackendCanvas::getCanvasInfo() const
{
        return canvasInfo;
}

void RkGDIImageBackendCanvas::fill(const RkColor &color)
{
}
