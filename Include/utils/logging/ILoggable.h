#pragma once

#include <string>

class ILoggable
{
public:
	virtual std::string toLoggable() const = 0;
};