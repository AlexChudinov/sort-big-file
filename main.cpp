#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <chrono>

void save_test_file(const std::string& filename, uint32_t num)
{
	std::ofstream out(filename);
	std::ostream_iterator<uint32_t> it(out, "\n");
	std::mt19937_64 gen;
	std::uniform_int_distribution<uint32_t> dist;

	for (uint32_t i = 0; i < num; ++i, ++it)
		*it = dist(gen);
}

void sort(
		const std::string& file_src,
		const std::string& file_dest)
{
	std::ofstream out(file_dest);
	std::vector<uint32_t> vals;
	uint32_t min_val = 0;
	uint32_t d_val = 10000000;
	while(min_val != std::numeric_limits<uint32_t>::max())
	{
		std::ifstream in(file_src);
		uint32_t max_val = std::numeric_limits<uint32_t>::max() - d_val >= min_val ? min_val + d_val
				: std::numeric_limits<uint32_t>::max();
		std::copy_if(std::istream_iterator<uint32_t>(in), std::istream_iterator<uint32_t>(), std::back_inserter(vals),
					 [min_val, max_val](std::istream_iterator<uint32_t>::reference val)
		{
			return val >= min_val && val < max_val;
		});
		std::sort(vals.begin(), vals.end());
		std::copy(vals.begin(), vals.end(), std::ostream_iterator<uint32_t>(out, "\n"));
		vals.clear();
		min_val = max_val;
	}
	std::ifstream in(file_src);
	std::copy_if(std::istream_iterator<uint32_t>(in), std::istream_iterator<uint32_t>(), std::ostream_iterator<uint32_t>(out),
				 [](std::istream_iterator<uint32_t>::reference val)
	{
		return val == std::numeric_limits<uint32_t>::max();
	});
}

void merge_sort(
				const std::string& file_src,
				const std::string& file_dest)
{
	std::ifstream in(file_src), temp;
	std::istream_iterator<uint32_t> it(in);
	size_t sz = 10000000;
	std::vector<uint32_t> vals;
	bool switch_to_temp = false;
	std::ofstream out;
	while(it != std::istream_iterator<uint32_t>())
	{
		std::ofstream out(file_dest);
		std::ostream_iterator<uint32_t> it_out(out);
		for (size_t i = 0; it != std::istream_iterator<uint32_t>() && i < sz; ++i, ++it)
		{
			vals.push_back(*it);
		}
		std::sort(vals.begin(), vals.end());
		if (switch_to_temp)
		{
			out.open("temp");
			temp.open(file_dest);
		}
		else
		{
			out.open(file_dest);
			temp.open("temp");
		}
		std::merge(
					vals.begin(),
					vals.end(),
					std::istream_iterator<uint32_t>(temp),
					std::istream_iterator<uint32_t>(),
					std::ostream_iterator<uint32_t>(out));
		out.close();
		temp.close();
	}
}

int main()
{
	save_test_file("test_file.bin", std::numeric_limits<uint32_t>::max());

	auto start = std::chrono::system_clock::now();
	sort("test_file.bin", "sorted.txt");

	std::cout << "Time to sort without merge: " << std::chrono::duration<double>(std::chrono::system_clock::now() - start).count() << std::endl;

	std::ifstream in("sorted.txt");

	assert(std::is_sorted(std::istream_iterator<uint32_t>(in), std::istream_iterator<uint32_t>()));

	return 0;
}
