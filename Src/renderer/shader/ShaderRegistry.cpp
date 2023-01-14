#include "renderer/shader/ShaderRegistry.h"

#include <stdexcept>

const ShaderProgram& ShaderRegistry::GetShader(const std::string& name)
{
	ShaderProgram* shader = nullptr;

	try
	{
		shader = &registry.at(name);
	}
	catch (const std::out_of_range&)
	{
		registry[name] = ShaderProgram(name);
		shader = &registry[name];
	}

	return *shader;
}

