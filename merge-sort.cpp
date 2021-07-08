#include "merge-sort.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <memory>

MergeSort::MergeSort(const std::string &src_file, const std::string &dest_file)
	:
	  SortInterface(src_file, dest_file)
{

}

void MergeSort::run()
{
	size_t i = 0;
	std::vector<std::string> file_names;
	std::vector<std::string> sort_array;
	sort_array.reserve(BUFFER_ARRAY_SIZE);
	std::ifstream in(m_src_file);
	for(
		std::istream_iterator<std::string> it(in);
		it != std::istream_iterator<std::string>();
		++it)
	{
		sort_array.push_back(*it);
		if (sort_array.size() == BUFFER_ARRAY_SIZE)
		{
			std::ofstream out(std::to_string(i));
			std::sort(sort_array.begin(), sort_array.end());
			std::copy(sort_array.begin(), sort_array.end(), std::ostream_iterator<std::string>(out));
			file_names.push_back(std::to_string(i++));
			sort_array.clear();
		}
	}
	for (
		 std::vector<std::string>::const_iterator it = file_names.begin();
		 it != std::prev(file_names.end());
		 ++it)
	{
		std::ifstream in;
		in.open(*std::next(it));
		std::copy(
					std::istream_iterator<std::string>(in),
					std::istream_iterator<std::string>(),
					std::back_inserter(sort_array));
		in.close();
		std::ofstream out(*std::next(it));
		in.open(*it);
		std::merge(
					sort_array.begin(), sort_array.end(),
					std::istream_iterator<std::string>(in), std::istream_iterator<std::string>(),
					std::ostream_iterator<std::string>(out));
	}
	std::ofstream out(m_dest_file);
	in.close();
	in.open(file_names.back());
	std::copy(
				std::istream_iterator<std::string>(in),
				std::istream_iterator<std::string>(),
				std::ostream_iterator<std::string>(out));
}
