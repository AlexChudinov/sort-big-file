#include "partial-quick-sort.hpp"
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <iostream>

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
	for (char c : m_alpabet)
	{
		std::cout << "Calculating sort for letter: " << c << std::endl;
		std::ifstream in(m_src_file);
		std::copy_if(
					std::istream_iterator<std::string>(in),
					std::istream_iterator<std::string>(),
					std::back_inserter(sort_array),
					[c](std::string s)
		{
			return s[0] == c;
		});
		std::sort(sort_array.begin(), sort_array.end());
		std::copy(sort_array.begin(), sort_array.end(), std::ostream_iterator<std::string>(out, "\n"));
		sort_array.clear();
	}
}
