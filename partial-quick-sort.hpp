#ifndef PARTIALQUICKSORT_HPP
#define PARTIALQUICKSORT_HPP

#include "sort-interface.hpp"

class PartialQuickSort : public SortInterface
{
public:
        PartialQuickSort(
			const std::string& src_file,
			const std::string& dst_file);

		void run() override;

private:
};

#endif // PARTIALQUICKSORT_H
