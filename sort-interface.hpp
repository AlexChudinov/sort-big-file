#ifndef SORTINTERFACE_HPP
#define SORTINTERFACE_HPP

#include <qt5/QtCore/QRunnable>
#include <map>
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
	 * @brief BUFFER_ARRAY_SIZE максимальный размер массива для сортировки
	 */
	static constexpr size_t BUFFER_ARRAY_SIZE = 100000000;
	/**
	 * @brief calc_frequency_table вычисляет тыблицу частот
	 * @param prefix строка, которая добавляется к каждому ключу таблицы спереди
	 */
	void calc_frequency_table(std::string prefix);
	/**
	 * @brief m_frequency_table таблица частот файла
	 */	
	std::map<std::string, size_t> m_frequency_table;
};

#endif // SORTINTERFACE_HPP
