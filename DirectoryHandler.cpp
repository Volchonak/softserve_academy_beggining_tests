#include "DirectoryHandler.h"

DirectoryHandler::DirectoryHandler(const path & directory)
{
	if (is_directory(directory))
	{
		m_directory = directory;
		FindAllFiles();
	}
}

DirectoryHandler& DirectoryHandler::operator=(const DirectoryHandler & obj)
{
	m_directory = obj.m_directory;
	m_files = obj.m_files;
	return *this;
}

DirectoryHandler& DirectoryHandler::operator=(const path & directory)
{
	if (is_directory(directory))
	{
		m_directory = directory;
		FindAllFiles();
	}
	return *this;
}
const path& DirectoryHandler::get_directory()const
{
	return m_directory;
}

const std::vector<path>& DirectoryHandler::get_files()const
{
	return m_files;
}
bool DirectoryHandler::has_specified_extension(const path& name_of_file)const
{
	if (name_of_file.has_extension())
	{
		auto file_extention = name_of_file.extension().string();
		if (file_extention == ".cpp" ||
			file_extention == ".c" ||
			file_extention == ".hpp" ||
			file_extention == ".h")
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}
void DirectoryHandler::FindAllFiles()
{
	if (m_directory.empty())
		return;
	for (auto i : recursive_directory_iterator(m_directory))
	{
		if (has_specified_extension(i))
		{
			m_files.push_back(i.path());
		}
	}
}
