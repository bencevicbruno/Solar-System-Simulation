#pragma once

#include <string>
#include <vector>

class ISerializable
{
public:
	std::vector<std::string> serialize() const;
};