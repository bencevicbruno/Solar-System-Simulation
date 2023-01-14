#pragma once

#include "renderer/models/BaseModel.h"

class SkyboxModel : public BaseModel
{
public:
	SkyboxModel();
	SkyboxModel(float size);
	SkyboxModel(SkyboxModel&& other) noexcept;

	SkyboxModel& operator=(SkyboxModel&& other) noexcept;

	void render() const override;

	float getSize() const;

private:
	float size;
	VertexArray vertexArray;
	Buffer vertexBuffer, indexBuffer;

	void setupVertexBuffer();
	void setupIndexBuffer();

	SkyboxModel(const SkyboxModel& other) = delete;
	void operator=(const SkyboxModel& other) = delete;
};

