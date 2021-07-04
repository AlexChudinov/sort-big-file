#include "sort-interface.hpp"
#include <fstream>
#include <algorithm>
#include <iterator>
#include <iostream>

SortInterface::SortInterface(
		const std::string &src_file,
		const std::string &dest_file)
	:
	  m_src_file(src_file),
	  m_dest_file(dest_file)
{
	std::cout << "Alphabet calculation started...\n";
	calc_alphabet();
	std::cout << "Alphabet of file: ";
	std::copy(m_alpabet.begin(), m_alpabet.end(), std::ostream_iterator<char>(std::cout));
	std::cout << std::endl;
}

void SortInterface::calc_alphabet()
{
	std::ifstream in(m_src_file);
	std::for_each(
				std::istream_iterator<std::string>(in),
				std::istream_iterator<std::string>(),
				[this](std::string s)
	{
		m_alpabet.insert(s.begin(), s.end());
	});
}
