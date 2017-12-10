#pragma once

namespace Capture {

class CaptureInfo
{
public:
	CaptureInfo() = default;
	CaptureInfo(int w, int h, int f) : width(w), height(h), fps(f) {}
	~CaptureInfo() = default;

public:
	int width  = 0;
	int height = 0;
	int fps    = 0;
};

Q_DECLARE_METATYPE(Capture::CaptureInfo);

}
