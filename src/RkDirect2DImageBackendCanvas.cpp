#include "RkDirect2DImageBackendCanvas.h"
#include "RkCanvasInfo.h"
#include "RkLog.h"

RkDirect2DImageBackendCanvas::RkDirect2DImageBackendCanvas(const RkSize &size,
                                                     RkImage::Format format,
                                                     const unsigned char *data)
        : canvasInfo{nullptr}
        , imageSize{size}
{
}

RkDirect2DImageBackendCanvas::~RkDirect2DImageBackendCanvas()
{
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
