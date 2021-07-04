#include "merge-sort.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <memory>

constexpr size_t BUFFER_ARRAY_SIZE = 10000000;

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
	std::ofstream out(m_dest_file);
	std::vector<std::shared_ptr<std::ifstream>> in_streams;
	std::vector<std::istream_iterator<std::string>> in_stream_iterators;
	std::for_each(
				file_names.begin(),
				file_names.end(),
				[&in_streams, &in_stream_iterators](const std::string& file_name)
	{
		in_streams.emplace_back(new std::ifstream(file_name));
		in_stream_iterators.emplace_back(*in_streams.back());
	});
	while (std::any_of(
			   in_stream_iterators.begin(),
			   in_stream_iterators.end(),
			   [](std::istream_iterator<std::string> it){ return it != std::istream_iterator<std::string>(); }))
	{
		for (std::istream_iterator<std::string> it : in_stream_iterators)
			if (it != std::istream_iterator<std::string>())
				sort_array.push_back(* it);
		std::sort(sort_array.begin(), sort_array.end());
		std::copy(sort_array.begin(), sort_array.end(), std::ostream_iterator<std::string>(out));
		sort_array.clear();
	}
}
