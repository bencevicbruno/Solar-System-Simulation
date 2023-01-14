#pragma once

#include <string>
#include <vector>

#include <utils/fileio/ISerializable.h>

class FileService
{
public:
	void saveFile(const std::string& fileName, const std::vector<std::string>& lines) const;

	template<typename T>
	void saveFile(const std::string& fileName, const ISerializable& serializable) const;

	std::vector<std::string> loadFile(const std::string& fileName) const;

	template<typename T, std::enable_if<std::is_base_of<ISerializable, T>>>
	T loadFile(const std::string& fileName) const;

	static FileService INSTANCE;
};