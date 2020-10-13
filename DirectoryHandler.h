#pragma once
#include <filesystem>
#include <vector>

using namespace std::filesystem;

class DirectoryHandler
{
public:
	DirectoryHandler() = default;
	DirectoryHandler(const path& directory);
	DirectoryHandler& operator=(const DirectoryHandler& obj);
	DirectoryHandler& operator=(const path& directory);
	const path& get_directory()const;
	const std::vector<path>& get_files()const;

private:
	bool has_specified_extension(const path& name_of_file)const;
	void FindAllFiles();
	path m_directory;
	std::vector<path> m_files;
};