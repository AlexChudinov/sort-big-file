#ifndef SORTINTERFACE_HPP
#define SORTINTERFACE_HPP

#include <qt5/QtCore/QRunnable>
#include <string>

class SortInterface : public QRunnable
{
protected:
	/**
	 * @brief m_src_file файл с неотсортированным массивом
	 */
	std::string m_src_file;
	/**
	 * @brief m_dest_file файл, куда сохраняем отсортированный массив
	 */
	std::string m_dest_file;
public:
	SortInterface(
			const std::string& src_file,
			const std::string& dest_file);

protected:
	/**
	 * @brief max_length вычисляет максимальную длинну строки во входном файле
	 */
	size_t max_length() const;
	/**
	 * @brief alphabet_size вычисляет длинну алфавита во входном файле
	 * @return
	 */
	size_t alphabet_size() const;
};

#endif // SORTINTERFACE_HPP
