#pragma once

#include <utils/logging/ILoggable.h>

class ILogger
{
public:
	virtual void log(const std::string& string) const = 0;
	virtual void log(const ILoggable& loggable) const = 0;
};