#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include "sort-interface.hpp"

class MergeSort : public SortInterface
{
public:
	MergeSort(
			const std::string& src_file,
			const std::string& dest_file);

	void run() override;
};

#endif // MERGESORT_HPP
