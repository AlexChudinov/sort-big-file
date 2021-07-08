#include "partial-quick-sort.hpp"
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <iostream>
#include <boost/range/algorithm/equal.hpp>

PartialQuickSort::PartialQuickSort(
		const std::string &src_file,
		const std::string &dest_file)
	:
	  SortInterface(src_file, dest_file)
{

}

void PartialQuickSort::run()
{
	std::vector<std::string> sort_array;
	std::ofstream out(m_dest_file);
	for (const auto& freq_ref : m_frequency_table)
	{
		std::cout << "Calculating sort for freq. table entry: " << freq_ref.first << std::endl;
		std::ifstream in(m_src_file);
		std::copy_if(
					std::istream_iterator<std::string>(in),
					std::istream_iterator<std::string>(),
					std::back_inserter(sort_array),
					[freq_ref](std::string s)
		{
			return boost::range::equal(freq_ref.first, s.substr(0, freq_ref.first.size()));
		});
		std::sort(sort_array.begin(), sort_array.end());
		std::copy(sort_array.begin(), sort_array.end(), std::ostream_iterator<std::string>(out, "\n"));
		sort_array.clear();
	}
}
