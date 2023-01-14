#pragma once

#include <utils/logging/ILogger.h>

class ConsoleLogger : ILogger
{
public:
	void log(const std::string& string) const override;
	void log(const ILoggable& loggable) const override;

	static ConsoleLogger INSTANCE;
};