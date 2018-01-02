#pragma once

namespace Core {

struct FrameInfo
{
	FrameInfo() = default;
	FrameInfo(int w, int h) : width(w), height(h) {}

	int width, height;
};

}
