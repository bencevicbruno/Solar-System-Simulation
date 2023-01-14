#include "utils/Image.h"

#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#pragma warning(push) 
#pragma warning( disable : 6308 28182 6262 6011)
#include <stb_image.h>
#pragma warning(pop)

#include "utils/Utils.h"

Image Image::Load(const std::string& location, bool flipOnLoad)
{
	Image image;
	int channelCount;

	stbi_set_flip_vertically_on_load(flipOnLoad);

	const std::string imageLocation = "Res/textures/" + location;
	image.data = stbi_load(imageLocation.c_str(), &image.width, &image.height, &channelCount, 0);
	image.isRGBA = channelCount >= 4;

	if (image.data == NULL)
	{
		std::stringstream stream;

		stream << "Unable to load image " << imageLocation << "\n";
		Utils::CrashWithLog(stream.str());
	}

	return image;
}

Image::Image() :
	width(0), height(0), data(0), isRGBA(false)
{}

Image::Image(Image&& other) noexcept
{
	*this = std::move(other);
}

Image& Image::operator=(Image&& other) noexcept
{
	if (this == &other) return *this;

	width = std::exchange(other.width, 0);
	height = std::exchange(other.height, 0);
	data = std::exchange(other.data, nullptr);
	isRGBA = std::exchange(other.isRGBA, false);

	return *this;
}

Image::~Image()
{
	delete data;
}

