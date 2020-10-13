#pragma once
#include <filesystem>
#include <thread>
#include <mutex>
#include "DirectoryHandler.h"
#include "Counter.h"

class DirectoryData final
{
public:
	DirectoryData(const std::filesystem::path& directory);
	~DirectoryData();
	int GetNumOfBlankLines() const;
	int GetNumOfCommentLines() const;
	int GetNumOfLinesWithCode() const;
	int GetNumOfFiles() const;
private:

	void UseCount(std::size_t begin, std::size_t end);
	void ProcessDirectory() noexcept;

	std::ofstream m_output;
	std::filesystem::path m_directory;
	std::vector<std::filesystem::path> m_files;
	std::mutex m_data_mutex;
	int m_num_of_files;
	int m_num_of_blank_lines;
	int m_num_of_comment_lines;
	int m_num_of_lines_with_code;
};