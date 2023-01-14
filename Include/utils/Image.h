#pragma once

#include <string>

class Image
{
public:
	int width, height;
	unsigned char* data;
	bool isRGBA;

	Image();
	Image(Image&& other) noexcept;

	Image& operator=(Image&& other) noexcept;

	~Image();

	static Image Load(const std::string& location, bool flipOnLoad);

private:
	Image(const Image& other) = delete;
	void operator=(const Image& other) = delete;
};

