#ifndef SORTINTERFACE_HPP
#define SORTINTERFACE_HPP

#include <qt5/QtCore/QRunnable>
#include <set>
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
	 * @brief calc_alphabet вычисление алфавита
	 */
	void calc_alphabet();
	/**
	 * @brief m_alpabet алфавит файла
	 */
	std::set<char> m_alpabet;
};

#endif // SORTINTERFACE_HPP
