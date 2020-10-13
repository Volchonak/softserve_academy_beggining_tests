#pragma once
#include <filesystem>
#include <fstream>
#include <regex>
#include <iostream>
#include <iterator>

using namespace std::filesystem;
class Counter
{
public:
	Counter() noexcept;
	Counter(const path& file_name) noexcept;
	Counter(const Counter& copy) noexcept;
	Counter(Counter&& copy) noexcept;
	Counter& operator=(const path& file_name) noexcept;
	void ProcessFileAndCountLines(const path& file_name) noexcept;
	int GetNumOfBlankLines() const noexcept;
	int GetNumOfCommentLines() const noexcept;
	int GetNumOfLinesWithCode() const noexcept;

private:
	void CountLines(const std::vector<std::string>& data_of_file) noexcept;
	std::vector<std::string> ReadData(const std::filesystem::path& file_name);

	int m_num_of_blank_lines;
	int m_num_of_comment_lines;
	int m_num_of_lines_with_code;
};