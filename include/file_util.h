/**
 *  ==============================================================================
 *
 *          \file   file_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-02-17 16:41:16.127829
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef FILE_UTIL_H_
#define FILE_UTIL_H_
#include "common_def.h"
#include "hashmap_util.h"
#include <glog/logging.h>
#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;
namespace bf = boost::filesystem;
//---------------------------for file save load
namespace gezi
{
	inline void try_create_dir(const string& dir)
	{
		if (!bfs::exists(dir))
		{
			LOG_WARNING("%s not exist, will create first", dir.c_str());
			bfs::create_directories(dir);
		}
	}

	inline std::string read_file(const std::string& infile)
	{
		std::ifstream ifs(infile.c_str());
		return boost::trim_copy(std::string((std::istreambuf_iterator<char>(ifs)),
			std::istreambuf_iterator<char>()));
	}

	inline void write_file(const string& content, const string& outfile)
	{
		std::ofstream ofs(outfile.c_str());
		ofs << content;
	}

	template<typename Container>
	bool file_to_set(const std::string& infile, Container& container)
	{
		typedef typename Container::value_type T;
		std::ifstream ifs(infile.c_str());
		if (!ifs.is_open())
		{
			return false;
		}
		std::istream_iterator<T> data_begin(ifs);
		std::istream_iterator<T> data_end;
		std::copy(data_begin, data_end, std::inserter(container, container.begin()));
		return true;
	}

	//�����ڵ����ı�

	template<typename Container>
	bool file_to_vec(const std::string& infile, Container& container)
	{
		typedef typename Container::value_type T;
		std::ifstream ifs(infile.c_str());
		if (!ifs.is_open())
		{
			return false;
		}
		std::istream_iterator<T> data_begin(ifs);
		std::istream_iterator<T> data_end;
		std::copy(data_begin, data_end, std::back_inserter(container));

		foreach(T& value, container)
		{
			boost::trim(value);
		}
		return true;
	}

	inline vector<string> read_lines(const std::string& infile)
	{
		vector<string> vec;
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vec.push_back(line);
		}
#if __GNUC__ > 3
		return std::move(vec);
#else
		return vec;
#endif
	}

	inline void read_lines(string infile, vector<string>& vec)
	{
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vec.push_back(line);
		}
	}

	template<typename T>
	inline void write_lines(vector<T>& lines, string file)
	{
		std::ofstream ofs(file.c_str());

		foreach(T line, lines)
		{
			ofs << line << endl;
		}
	}


	//���� file_

	template<typename Set>
	inline void read_set(string infile, Set& container)
	{
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			container.insert(line);
		}
	}

	inline set<string> to_set(string infile)
	{
		set<string> container;
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			container.insert(line);
		}
#if __GNUC__ > 3
		return std::move(container);
#else
		return container;
#endif
	}

	inline unordered_set<string> to_uset(string infile)
	{
		unordered_set<string> container;
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			container.insert(line);
		}
#if __GNUC__ > 3
		return std::move(container);
#else
		return container;
#endif
	}

	//���� read_to

	inline void read_to_set(const std::string& infile, std::set<std::string>& container,
		int index = 0, const string& sep = "\t ")
	{
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vector<string> vec;
			boost::split(vec, line, is_any_of(sep));
			container.insert(vec[index]);
		}
	}

	inline void read_to_set(const std::string& infile, unordered_set<std::string>& container,
		int index = 0, const string& sep = "\t ")
	{
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vector<string> vec;
			boost::split(vec, line, is_any_of(sep));
			container.insert(vec[index]);
		}
	}

	template<typename Container>
	void read_to_set(const std::string& infile, Container& container, int index = 0, const string& sep = "\t ")
	{
		typedef typename Container::value_type T;
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vector<string> vec;
			boost::split(vec, line, is_any_of(sep));
			container.insert(boost::lexical_cast<T>(vec[index]));
		}
	}

	inline void read_to_vec(const std::string& infile, std::vector<std::string>& container,
		int index = 0, const string& sep = "\t ")
	{
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vector<string> vec;
			boost::split(vec, line, is_any_of(sep));
			container.push_back(vec[index]);
		}
	}

	template<typename Container>
	void read_to_vec(const std::string& infile, Container& container, int index = 0, const string& sep = "\t ")
	{
		typedef typename Container::value_type T;
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vector<string> vec;
			boost::split(vec, line, is_any_of(sep));
			container.push_back(boost::lexical_cast<T>(vec[index]));
		}
	}
	//TODO better method...

	inline void read_map(const std::string& infile, std::map<std::string, std::string>& container,
		const string& sep = "\t", int key_idx = 0, int value_idx = 1)
	{
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vector<string> vec;
			boost::split(vec, line, is_any_of(sep));
			container[boost::trim_copy(vec[key_idx])] = boost::trim_copy(vec[value_idx]);
		}
	}

	inline void read_map(const std::string& infile, unordered_map<std::string, std::string>& container,
		const string& sep = "\t", int key_idx = 0, int value_idx = 1)
	{
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vector<string> vec;
			boost::split(vec, line, is_any_of(sep));
			container[boost::trim_copy(vec[key_idx])] = boost::trim_copy(vec[value_idx]);
		}
	}

	template<typename Container>
	void read_map(const std::string& infile, Container& container, const string& sep = "\t",
		int key_idx = 0, int value_idx = 1)
	{
		//  typedef typename Container::key_type T;
		typedef typename Container::mapped_type U;
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vector<string> vec;
			boost::split(vec, line, is_any_of(sep));
			//    container[boost::lexical_cast<T>(vec[key_idx])] = boost::lexical_cast<U>(vec[value_idx]);
			container[boost::trim_copy(vec[key_idx])] = boost::lexical_cast<U>(boost::trim_copy(vec[value_idx]));
		}
	}

	inline unordered_map<string, int> to_identifer_map(string infile, int start = 0)
	{
		unordered_map<string, int> m;
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			m[line] = start++;
		}
#if __GNUC__ > 3
		return std::move(m);
#else
		return m;
#endif
	}

	template<typename Map>
	void write_map(const Map& m, const std::string& ofile, const std::string& sep = "\t")
	{
		ofstream ofs(ofile.c_str());
		typedef typename Map::value_type Pair;

		foreach(Pair& item, m)
		{
			ofs << m.first << sep << m.second << endl;
		}
	}

	/**
	* ע�� write_ve �� read_vec���ʹ��, ֻ������_Node �Ǽ����͵��������int,float struct{int,float}
	*/
	template<typename _Node>
	void write_vec(const std::vector<_Node>& vec, const std::string& file)
	{//���������
		std::ofstream ofs(file.c_str(), std::ios::binary);
		ofs.write(reinterpret_cast<const char*> (&vec[0]), sizeof (_Node)* vec.size());
	}

	template<typename _Node>
	bool read_vec(const std::string& file, std::vector<_Node>& vec)
	{
		std::ifstream ifs(file.c_str(), std::ios::binary);
		if (!ifs.is_open())
			return false;
		vec.clear();
		ifs.seekg(0, std::ios::end);
		int length = ifs.tellg(); //FIXME big file?
		ifs.seekg(0, std::ios::beg);
		vec.resize(length / sizeof (_Node));
		ifs.read(reinterpret_cast<char*> (&vec[0]), length);
		return true;
	}

	template<typename T>
	void write_elem(const T& elem, const std::string& file)
	{
		std::ofstream ofs(file.c_str());
		ofs << elem;
	}

	template<typename T>
	bool read_elem(const std::string& file, T& elem)
	{
		std::ifstream ifs(file.c_str());
		if (!ifs.is_open())
			return false;
		ifs >> elem;
		return true;
	}

	template<typename _Node>
	void write_vec2d(const std::vector<std::vector<_Node> >& vec, std::ofstream& ofs)
	{
		size_t row_len = vec.size();
		if (!row_len)
			return;
		for (size_t i = 0; i < row_len; i++)
		{
			int len = (int)vec[i].size();
			ofs.write(reinterpret_cast<const char*> (&len), sizeof (len));
			if (!len)
				continue;
			ofs.write(reinterpret_cast<const char*> (&vec[i][0]), sizeof (_Node)* vec[i].size());
		}
	}

	template<typename _Node>
	void write_vec2d(const std::vector<std::vector<_Node> >& vec, const std::string& file)
	{
		std::ofstream ofs(file.c_str(), std::ios::binary);
		size_t row_len = vec.size();
		ofs.write(reinterpret_cast<const char*> (&row_len), sizeof (row_len));
		write_vec2d(vec, ofs);
	}

	template<typename _Node>
	bool read_vec2d(const std::string& file, std::vector<std::vector<_Node> >& vec)
	{
		std::ifstream ifs(file.c_str(), std::ios::binary);
		if (!ifs.is_open())
			return false;
		vec.clear();
		//size_t total_len;
		int total_len; //TODO check ��شʵ�ʱ��write ����int
		ifs.read(reinterpret_cast<char*> (&total_len), sizeof (total_len));
		if (!total_len)
			return false;
		vec.resize(total_len);
		for (int i = 0; i < total_len; i++)
		{
			int len;
			ifs.read(reinterpret_cast<char*> (&len), sizeof (len));
			if (!len)
				continue;
			vec[i].resize(len);
			ifs.read(reinterpret_cast<char*> (&vec[i][0]), sizeof (_Node)* len);
		}
		return true;
	}

	class Vec2dWriter
	{
	public:

		Vec2dWriter(const std::string& file)
			: _ofs(file.c_str(), std::ios::binary)
		{
		}

		template<typename _Node>
		void write(const std::vector<_Node>& vec)
		{
			int len = (int)vec.size();
			_ofs.write(reinterpret_cast<const char*> (&len), sizeof (len));
			if (!len)
				return;
			_ofs.write(reinterpret_cast<const char*> (&vec[0]), sizeof (_Node)* len);
		}

		template<typename _Iter>
		void write(_Iter begin, _Iter end)
		{
			typedef typename _Iter::value_type value_type;
			int len = std::distance(begin, end);
			_ofs.write(reinterpret_cast<const char*> (&len), sizeof (len));
			if (!len)
				return;
			while (begin != end)
			{
				_ofs.write(reinterpret_cast<const char*> (&(*begin)), sizeof (value_type));
			}
		}

		void close()
		{
			_ofs.close();
		}
	private:
		std::ofstream _ofs;
	};

	class VecWriter
	{
	public:

		VecWriter(const std::string& file)
			: _ofs(file.c_str(), std::ios::binary)
		{
		}

		template<typename _Node>
		void write(const std::vector<_Node>& vec)
		{
			int len = (int)vec.size();
			_ofs.write(reinterpret_cast<const char*> (&vec[0]), sizeof (_Node)* len);
		}

		template<typename _Iter>
		void write(_Iter begin, _Iter end)
		{
			typedef typename _Iter::value_type value_type;
			while (begin != end)
			{
				_ofs.write(reinterpret_cast<const char*> (&(*begin)), sizeof (value_type));
			}
		}

		void close()
		{
			_ofs.close();
		}
	private:
		std::ofstream _ofs;
	};
}
//----end of namespace gezi

#endif  //----end of FILE_UTIL_H_