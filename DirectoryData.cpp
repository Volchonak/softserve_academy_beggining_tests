#include "DirectoryData.h"

DirectoryData::DirectoryData(const std::filesystem::path& directory)
{
	m_num_of_blank_lines = 0;
	m_num_of_comment_lines = 0;
	m_num_of_lines_with_code = 0;
	m_num_of_files = 0;
	m_directory = directory;
	DirectoryHandler dir(m_directory);
	m_files = dir.get_files();
	m_num_of_files = m_files.size();
	m_output.open("result.txt");
	if (!m_output.is_open())
	{
		throw std::exception("File to write output is not opened\n");
	}
	ProcessDirectory();
}
DirectoryData::~DirectoryData()
{
	if (m_output.is_open())
		m_output.close();
}
int DirectoryData::GetNumOfBlankLines()const
{
	return m_num_of_blank_lines;
}
int DirectoryData::GetNumOfCommentLines()const
{
	return m_num_of_comment_lines;
}
int DirectoryData::GetNumOfLinesWithCode()const
{
	return m_num_of_lines_with_code;
}
int DirectoryData::GetNumOfFiles()const
{
	return m_num_of_files;
}
void DirectoryData::UseCount(std::size_t begin, std::size_t end)
{
	Counter counter;
	for (; begin <= end && begin < m_files.size(); ++begin)
	{
		counter.ProcessFileAndCountLines(m_files[begin]);
		std::lock_guard<std::mutex> lock(m_data_mutex);
		m_num_of_blank_lines += counter.GetNumOfBlankLines();
		m_num_of_comment_lines += counter.GetNumOfCommentLines();
		m_num_of_lines_with_code += counter.GetNumOfLinesWithCode();
		m_output << m_files[begin] << "\nBlank lines: " << counter.GetNumOfBlankLines()
			<< "\nCommnet lines: " << counter.GetNumOfCommentLines()
			<< "\nCode lines: " << counter.GetNumOfLinesWithCode() << std::endl;
	}
}
void DirectoryData::ProcessDirectory()noexcept
{
	int num_of_concurrency = std::thread::hardware_concurrency() - 1;
	if (num_of_concurrency <= 0)
	{
		return;
	}

	std::vector<std::thread> threads;
	auto size_of_package = m_num_of_files / num_of_concurrency + 1;
	std::size_t begin = 0;
	for (auto i = 0; i < num_of_concurrency; ++i)
	{
		threads.emplace_back(std::thread(&DirectoryData::UseCount, std::ref(*this), begin, begin + size_of_package - 1));
		begin += size_of_package;
	}

	for (auto i = threads.begin(); i != threads.end(); ++i)
	{
		if (i->joinable())
			i->join();
	}
}