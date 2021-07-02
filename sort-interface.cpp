#include "sort-interface.hpp"
#include <fstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <unordered_set>
#include <boost/filesystem.hpp>
#include <cassert>
#include <QtConcurrent>

SortInterface::SortInterface(
		const std::string &src_file,
		const std::string &dest_file)
	:
	  m_src_file(src_file),
	  m_dest_file(dest_file)
{
	assert(boost::filesystem::exists(src_file));
	std::array<std::function<void()>, 2> functions
	{
		[this](){ std::cout << "Max string length in a file: " << max_length() << "\n"; },
		[this](){ std::cout << "Alphabet size of a file: " << alphabet_size() << "\n"; }
	};
	auto future = QtConcurrent::map(functions, [](std::function<void()>& fun)
	{
		fun();
	});
	future.waitForFinished();
}

size_t SortInterface::max_length() const
{
	std::ifstream in(m_src_file);
	size_t result = 0;
	std::for_each(
				std::istream_iterator<std::string>(in),
				std::istream_iterator<std::string>(),
				[&result](std::string str)
	{
		result = std::max(result, str.size());
	});
	return result;
}

size_t SortInterface::alphabet_size() const
{
	std::ifstream in(m_src_file);
	std::unordered_set<char> alphabet;
	std::for_each(
				std::istream_iterator<std::string>(in),
				std::istream_iterator<std::string>(),
				[&alphabet](std::string str)
	{
		alphabet.insert(str.begin(), str.end());
	});
	return alphabet.size();
}
