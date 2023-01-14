#pragma once

#include <unordered_map>

#include "renderer/shader/ShaderProgram.h"

namespace ShaderRegistry
{
	namespace
	{
		std::unordered_map<std::string, ShaderProgram> registry;
	}

	const ShaderProgram& GetShader(const std::string& shaderName);
};

