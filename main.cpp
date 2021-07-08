#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <iterator>
#include <algorithm>
#include <chrono>
#include <memory>
#include "partial-quick-sort.hpp"
#include "merge-sort.hpp"

#define SORT_ASSERT(CODE) sort_assert(CODE, #CODE)

void sort_assert(bool ok, const char* code)
{
	if (!ok)
	{
		std::cout << "Assertion failed for " << code << std::endl;
		std::exit(3);
	}
}

void save_test_file(const std::string& filename, uint32_t num)
{
	std::ofstream out(filename);
	std::ostream_iterator<uint32_t> it(out, "\n");
	std::mt19937_64 gen;
	std::uniform_int_distribution<uint32_t> dist;

	for (uint32_t i = 0; i < num; ++i, ++it)
		*it = dist(gen);
}

int main()
{
	//save_test_file("test_file.bin", std::numeric_limits<uint32_t>::max());

	const std::string src_file = "test_file.bin";
	const std::string dst_file_quick = "quick_sorted.txt";
	const std::string dst_file_merge = "merge_sorted.text";

	std::unique_ptr<SortInterface> sort_alg;

	auto start = std::chrono::system_clock::now();
	sort_alg = std::make_unique<PartialQuickSort>(src_file, dst_file_quick);
	sort_alg->run();

	std::cout << "Time to sort without merge: "
			  << std::chrono::duration<double>(std::chrono::system_clock::now() - start).count() << std::endl;

	std::ifstream in_quick(dst_file_quick);

	SORT_ASSERT(std::is_sorted(
				std::istream_iterator<std::string>(in_quick),
				std::istream_iterator<std::string>()));

	start = std::chrono::system_clock::now();
	sort_alg = std::make_unique<MergeSort>(src_file, dst_file_quick);
	sort_alg->run();

	std::cout << "Time to sort without merge: "
			  << std::chrono::duration<double>(std::chrono::system_clock::now() - start).count() << std::endl;

	in_quick.seekg(0);
	std::ifstream in_merge(dst_file_merge);

	SORT_ASSERT(std::equal(
					std::istream_iterator<std::string>(in_quick),
					std::istream_iterator<std::string>(),
					std::istream_iterator<std::string>(in_merge),
					std::istream_iterator<std::string>()));

	return 0;
}
