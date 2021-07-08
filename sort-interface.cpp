#include "sort-interface.hpp"
#include <fstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <boost/range/algorithm/equal.hpp>

constexpr size_t SortInterface::BUFFER_ARRAY_SIZE;

SortInterface::SortInterface(
		const std::string &src_file,
		const std::string &dest_file)
	:
	  m_src_file(src_file),
	  m_dest_file(dest_file)
{
	std::cout << "Alphabet calculation started...\n";
	calc_frequency_table(std::string());
	std::cout << "Alphabet of file: [";
	for (const auto& freq_ref : m_frequency_table)
		std::cout << "(" << freq_ref.first << ", " << freq_ref.second << "), ";
	std::cout << "]";
	std::cout << std::endl;
}

void SortInterface::calc_frequency_table(std::string prefix)
{
	std::ifstream in(m_src_file);
	size_t sz = m_frequency_table.at(prefix);
	std::for_each(
				std::istream_iterator<std::string>(in),
				std::istream_iterator<std::string>(),
				[this, prefix, &sz](std::string s)
	{
		if (s.size() > prefix.size() && boost::range::equal(prefix, s.substr(0, prefix.size())))
		{
			std::string key = prefix + s[prefix.size()];
			auto it = m_frequency_table.find(key);
			if (it == m_frequency_table.end())
				m_frequency_table[key] = 1;
			else
				it->second++;
			sz--;
		}
	});
	m_frequency_table[prefix] = sz;
	for (const auto& freq_ref : m_frequency_table)
	{
		if (freq_ref.second > BUFFER_ARRAY_SIZE)
		{
			calc_frequency_table(freq_ref.first);
		}
	}
}
