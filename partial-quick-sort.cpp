#include "partial-quick-sort.hpp"

constexpr size_t MEMORY_BUFFER_SIZE = 10000000;

PartialQuickSort::PartialQuickSort(
		const std::string &src_file,
		const std::string &dst_file)
	:
	  SortInterface(src_file, dst_file)
{

}

void PartialQuickSort::run()
{
}
