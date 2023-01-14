#include <utils/logging/ConsoleLogger.h>

#include <iostream>

void ConsoleLogger::log(const std::string& string) const
{
	std::cout << string << std::endl;
}

void ConsoleLogger::log(const ILoggable& loggable) const
{
	std::cout << loggable.toLoggable() << std::endl;
}

ConsoleLogger ConsoleLogger::INSTANCE;