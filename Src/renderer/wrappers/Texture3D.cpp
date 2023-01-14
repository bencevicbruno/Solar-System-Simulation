#include "renderer/wrappers/Texture3D.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "utils/Image.h"

Texture3D::Texture3D():
	ID(0), name("")
{}

Texture3D::Texture3D(std::string name):
	name(name)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

	Image images[6] = {
		Image::Load(name + "/right.png", false),
		Image::Load(name + "/left.png", false),
		Image::Load(name + "/top.png", false),
		Image::Load(name + "/bottom.png", false),
		Image::Load(name + "/front.png", false),
		Image::Load(name + "/back.png", false)
	};

	for (int i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, 
			images[i].width, images[i].height, 0, GL_RGB, GL_UNSIGNED_BYTE, images[i].data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // DEFAULT GL_LINEAR
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // DEAFULT GL_CLAMPTOEDGE
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

Texture3D::Texture3D(Texture3D&& other) noexcept
{
	*this = std::move(other);
}

Texture3D& Texture3D::operator=(Texture3D&& other) noexcept
{
	if (this == &other) return *this;

	ID = std::exchange(other.ID, 0);
	name = std::move(other.name);

	return *this;
}

Texture3D::~Texture3D()
{
	glDeleteTextures(1, &ID);
}

void Texture3D::bind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}