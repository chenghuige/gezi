/**
 *  ==============================================================================
 *
 *          \file   Identifer.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-01-19 09:53:10.353333
 *
 *  \Description:    Key Id 双向索引
 *  ==============================================================================
 */

#ifndef IDENTIFER_H_
#define IDENTIFER_H_

#include <glog/logging.h>
#include "common_def.h"    //很奇怪 单独使用Identifer.h 必须放在common_util.h后面才可以
#include "serialize_util.h"
//#include "common_util.h"
namespace gezi {

	class Identifer
	{
	public:
		typedef int IdType; //@TODO may be changed to int64 or use uint32 ?
		typedef vector<string>::iterator iterator;
		typedef vector<string>::const_iterator const_iterator;
		typedef unordered_map<string, IdType> HashMap;
		typedef HashMap::const_iterator const_mapiter;

		Identifer()
		{
		}

		Identifer(string file)
		{
			Load(file);
		}

	public:

		//@TODO PYTHON
#ifndef PYTHON_WRAPPER
		enum IdTypes{ NullId = -1, };  //这样写 使用NullId更加简洁 但是python封装不会对外暴露
#else
		static const int NullId = -1;
#endif

		static const IdType null_id()
		{
			static const IdType _null_id = -1;
			return _null_id;
		}

		vector<string>& words()
		{
			return _index;
		}

		//@TODO PYTHON
#ifndef GCCXML	
		iterator begin()
		{
			return _index.begin();
		}

		iterator end()
		{
			return _index.end();
		}

		const_iterator begin()const
		{
			return _index.begin();
		}

		const_iterator end()const
		{
			return _index.end();
		}
#endif

		size_t size()const
		{
			return _index.size();
		}

		bool empty()const
		{
			return _index.empty();
		}

		void clear()
		{
			_hashdict.clear();
			_index.clear();
		}

		inline string key(IdType id) const
		{
			return _index[id];
		}

		inline string key(IdType id, string defualtKey) const
		{
			return id >= 0 && id < _index.size() ? _index[id] : defualtKey;
		}

		vector<string>& keys()
		{
			return _index;
		}

		//get a item's id (index in dict),if the item does not exist return null_id()
		inline IdType id(string f) const
		{
			HashMap::const_iterator it = _hashdict.find(f);
			if (it == _hashdict.end())
				return null_id();
			return it->second;
		}

		inline IdType id(string f, IdType defaultVal) const
		{
			HashMap::const_iterator it = _hashdict.find(f);
			if (it == _hashdict.end())
				return defaultVal;
			return it->second;
		}

		inline bool has(string f) const
		{
			return _hashdict.find(f) != _hashdict.end();
		}

		inline IdType add(string f)
		{
			HashMap::iterator it = _hashdict.find(f);
			if (it != _hashdict.end())
				return it->second;

			IdType id = _index.size();
			_hashdict[f] = id;
			_index.push_back(f);
			return id;
		}

		inline IdType add(string f, bool& isnew)
		{
			HashMap::iterator it = _hashdict.find(f);
			if (it != _hashdict.end())
			{
				isnew = false;
				return it->second;
			}
			isnew = true;
			IdType id = _index.size();
			_hashdict[f] = id;
			_index.push_back(f);
			return id;
		}

		string last()
		{
			return _index.back();
		}

		inline IdType add_unique(string f)
		{
			int id = _index.size();
			_hashdict[f] = id;
			_index.push_back(f);
			return id;
		}

		bool load(string file, string sep = "\t")
		{
			ifstream ifs(file.c_str());
			CHECK_EQ(ifs.is_open(), true) << file;
			VLOG(3) << "Begin loading " << file;
			string line, key;
			IdType id = 0;
			while (std::getline(ifs, line))
			{
				vector<string> vec = split(line, sep);
				_hashdict[vec[0]] = id++;
			}
			_index.resize(id);
			HashMap::const_iterator iter = _hashdict.begin();
			for (; iter != _hashdict.end(); ++iter)
			{
				_index[iter->second] = iter->first;
			}
			VLOG(3) << "End loading " << file << " size: " << size();
			return true;
		}

		void save(string file)
		{
			ofstream ofs(file.c_str());

			int len = int(_index.size());
			for (int i = 0; i < len; i++)
			{
				ofs << _index[i] << std::endl;
			}
		}

		string operator [] (int id) const {
			return _index[id];
		}

		const IdType operator () (string key) const
		{
			HashMap::const_iterator it = _hashdict.find(key);
			if (it == _hashdict.end())
				return null_id();
			return it->second;
		}

		void Load(string path)
		{
			VLOG(0) << "Identifer Loading " << path;
			serialize_util::load(*this, path);
			VLOG(0) << "Identifer Loading Done size: " << size();
		}

		void Save(string path)
		{
			serialize_util::save(*this, path);
		}

		//写成cereal形式ok 转换成boost也可以通过define NO_CEREAL完成 测试ok 但是GCCXML似乎不能处理 反馈找不到cereal 因此workaround。。
		/*	friend class cereal::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
			ar & CEREAL_NVP(_hashdict);
			ar & CEREAL_NVP(_index);
			}*/
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive &ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_NVP(_hashdict);
			ar & BOOST_SERIALIZATION_NVP(_index);
		}

	protected:
		HashMap _hashdict;
		vector<string> _index; //kid->key
	};

	typedef vector<Identifer> Identifers;

	template<typename T>
	class ValueIdentifer : public Identifer
	{
	public:
		ValueIdentifer()
		{

		}

		ValueIdentifer(string file)
		{
			Load(file);
		}

		bool load(string file, int index = 1, string sep = "\t")
		{
			ifstream ifs(file.c_str());
			CHECK_EQ(ifs.is_open(), true) << file;
			VLOG(3) << "Begin loading " << file;
			string line, key;
			IdType id = 0;
			while (std::getline(ifs, line))
			{
				vector<string> vec = split(line, sep);
				_hashdict[vec[0]] = id++;
				if (index < vec.size())
				{
					try
					{
						_values.push_back(boost::lexical_cast<T>(vec[index]));
					}
					catch (...)
					{
						_values.push_back(1);
					}
				}
				else
				{
					_values.push_back(1);
				}
			}
			_index.resize(id);
			HashMap::const_iterator iter = _hashdict.begin();
			for (; iter != _hashdict.end(); ++iter)
			{
				_index[iter->second] = iter->first;
			}
			VLOG(0) << "End loading " << file << " size: " << size();
			return true;
		}

		void save(string file)
		{
			ofstream ofs(file);
			for (size_t i = 0; i < size(); i++)
			{
				ofs << _index[i] << "\t" << _values[i] << endl;
			}
		}

		void add(string key, T value)
		{
			Identifer::add(key);
			_values.push_back(value);
		}

		void Save(string file)
		{
			serialize_util::save(*this, file);
		}

		void Load(string file)
		{
			VLOG(0) << "Identifer Loading " << file;
			serialize_util::load(*this, file);
			VLOG(0) << "Identifer Loading Done size: " << size();
		}

		T value(int index) const
		{
			return _values[index];
		}

		//注意 可能 -1 越界
		T get_value(string key) const
		{
			return _values[id(key)];
		}

		T value(string key) const
		{
			return _values[id(key)];
		}

		//friend class cereal::access;
		//template<class Archive>
		//void serialize(Archive &ar, const unsigned int version)
		//{
		//	ar & CEREAL_BASE_OBJECT_NVP(Identifer);
		//	ar & CEREAL_NVP(_values); 
		//}
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive &ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Identifer);
			ar & BOOST_SERIALIZATION_NVP(_values);
		}
	private:
		vector<T> _values;
	};

	typedef ValueIdentifer<int> IntIdentifer;
	typedef ValueIdentifer<int64> Int64Identifer;
	typedef ValueIdentifer<size_t> CountIdentifer;
	typedef ValueIdentifer<double> DoubleIdentifer;

	//@TODO PYTHON
#ifdef PYTHON_WRAPPER
	PYHACK(IntIdentifer);
	PYHACK(Int64Identifer);
	PYHACK(CountIdentifer);
	PYHACK(DoubleIdentifer);
#endif //PYTHON_WRAPPER

} //----end of namespace gezi

#endif  //----end of IDENTIFER_H_
