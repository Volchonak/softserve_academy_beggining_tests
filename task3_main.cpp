#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include "DirectoryHandler.h"
#include "DirectoryData.h"
#include "Counter.h"

int main()
{

	int num_of_blank_lines = 0;
	int num_of_comment_lines = 0;
	int num_of_lines_with_code = 0;
	auto start = std::chrono::steady_clock::now();
	DirectoryData dir("C:\\Users\\roman\\source\\repos");
	num_of_blank_lines = dir.GetNumOfBlankLines();
	num_of_comment_lines = dir.GetNumOfCommentLines();
	num_of_lines_with_code = dir.GetNumOfLinesWithCode();
	auto end = std::chrono::steady_clock::now();
	auto func_time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
	std::ofstream output;
	output.open("result.txt", std::ios::app);
	if (!output.is_open())
	{
		return -1;
	}
	output << "Number of files = " << dir.GetNumOfFiles() << std::endl;
	output << "Time = " << func_time.count() << std::endl;
	output << "Total number of blank lines = " << num_of_blank_lines << std::endl;
	output << "Total number of comment lines  = " << num_of_comment_lines << std::endl;
	output << "Total number of lines with code = " << num_of_lines_with_code << std::endl;
	output.close();
	return 0;
}