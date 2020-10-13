#include "Counter.h"

Counter::Counter() noexcept
{
	m_num_of_blank_lines = 0;
	m_num_of_comment_lines = 0;
	m_num_of_lines_with_code = 0;
}

Counter::Counter(const path& file_name) noexcept
{
	m_num_of_blank_lines = 0;
	m_num_of_comment_lines = 0;
	m_num_of_lines_with_code = 0;
	if (file_name.has_filename())
	{
		try
		{
			std::vector<std::string> data_of_file = ReadData(file_name);
			CountLines(data_of_file);
		}
		catch (std::ifstream::failure & exception)
		{
			std::cout << exception.what() << std::endl;
		}
	}
}
Counter::Counter(const Counter& copy) noexcept
{
	m_num_of_blank_lines = copy.m_num_of_blank_lines;
	m_num_of_comment_lines = copy.m_num_of_comment_lines;
	m_num_of_lines_with_code = copy.m_num_of_lines_with_code;
}
Counter::Counter(Counter&& copy) noexcept
{
	m_num_of_blank_lines = std::move(copy.m_num_of_blank_lines);
	m_num_of_comment_lines = std::move(copy.m_num_of_comment_lines);
	m_num_of_lines_with_code = std::move(copy.m_num_of_lines_with_code);
}
Counter& Counter::operator=(const path& file_name) noexcept
{
	if (file_name.has_filename())
	{
		try
		{
			std::vector<std::string> data_of_file = ReadData(file_name);
			CountLines(data_of_file);
		}
		catch (std::ifstream::failure & exception)
		{
			std::cout << exception.what() << std::endl;
		}
	}
	return *this;
}
void Counter::ProcessFileAndCountLines(const path& file_name) noexcept
{
	if (file_name.has_filename())
	{
		try
		{
			std::vector<std::string> data_of_file = ReadData(file_name);
			CountLines(data_of_file);
		}
		catch (std::ifstream::failure & exception)
		{
			std::cout << exception.what() << std::endl;
		}
	}
}

int Counter::GetNumOfBlankLines() const noexcept
{
	return m_num_of_blank_lines;
}
int Counter::GetNumOfCommentLines() const noexcept
{
	return m_num_of_comment_lines;
}
int Counter::GetNumOfLinesWithCode() const noexcept
{
	return m_num_of_lines_with_code;
}
void Counter::CountLines(const std::vector<std::string>& data_of_file) noexcept
{
	bool has_open_comment = false;
	m_num_of_blank_lines = 0;
	m_num_of_comment_lines = 0;
	m_num_of_lines_with_code = 0;
	const std::regex block_comment_begin(R"(\/\*)");
	const std::regex block_comment_end(R"(\*\/)");
	const std::regex line_comment(R"(//)");
	const std::regex code_before_comment("((\\w|\\s|[;,.=()])+(\\/\\*)(\\w|\\s|[;,.=()])+)");//look for code before /*
	const std::regex code_after_comment("((\\w|\\s|[;,.=()])+(\\*\\/)(\\w|\\s|[;,.=()])+)");//look for code after */
	const std::regex code_before_line_comment("(\\w|\\s|[(),;.])+\\/\\/(\\w|\\s|[(),;.])*");//look for code before //
	const std::regex regex_blank_line(R"(\t*\s*)");

	for (auto i : data_of_file)
	{
		if (std::regex_match(i, regex_blank_line))
		{
			++m_num_of_blank_lines;
			if (has_open_comment)
				++m_num_of_comment_lines;
			continue;
		}
		if (!has_open_comment)
		{
			if (std::regex_search(i, block_comment_begin))
			{
				if ((std::regex_match(i, code_before_comment)))
					++m_num_of_lines_with_code;
				has_open_comment = true;
				++m_num_of_comment_lines;
				if (std::regex_search(i, block_comment_end))
				{
					if (std::regex_match(i, code_after_comment))
						++m_num_of_lines_with_code;
					has_open_comment = false;
				}
			}
			else if (std::regex_search(i, line_comment))
			{
				++m_num_of_comment_lines;
				if (std::regex_match(i, code_before_line_comment))
					++m_num_of_lines_with_code;
				continue;
			}
			else
			{
				++m_num_of_lines_with_code;
			}
		}
		if (has_open_comment)
		{
			if (std::regex_search(i, block_comment_end))
			{
				if (std::regex_match(i, code_after_comment))
					++m_num_of_lines_with_code;

				++m_num_of_comment_lines;
				has_open_comment = false;
			}
		}
	}
}
std::vector<std::string> Counter::ReadData(const std::filesystem::path& file_name)
{
	try
	{
		std::ifstream file(file_name);
		if (file.is_open())
		{
			std::string str;
			std::vector<std::string> data;
			while (std::getline(file, str)) {
				data.push_back(str);
			}
			file.close();
			return data;
		}
		else
		{
			throw std::ifstream::failure("File is not opened\n");

		}
	}
	catch (std::ifstream::failure & exception)
	{
		throw exception;
	}
}