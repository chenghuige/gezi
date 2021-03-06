/**
 *  ==============================================================================
 *
 *          \file   SharedIdentifers.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-17 23:16:18.168343
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef SHARED_IDENTIFERS_H_
#define SHARED_IDENTIFERS_H_
#include "Identifer.h"
namespace gezi {
	class Identifer;
	//并非线程安全！ @WARNING
	class SharedIdentifers
	{
	public:
		static Identifer& Instance()
		{
			static Identifer _identifer;
			return _identifer;
		}
		static Identifer& Instance(string path)
		{
			static map<string, Identifer> _identifers;
			auto iter = _identifers.find(path);
			if (iter != _identifers.end())
			{
				return iter->second;
			}
			else
			{
				auto& identifer = _identifers[path];
				identifer.Load(path);
				return identifer;
			}
		}
		static Identifer& instance(string path)
		{
			static map<string, Identifer> _identifers;
			auto iter = _identifers.find(path);
			if (iter != _identifers.end())
			{
				return iter->second;
			}
			else
			{
				auto& identifer = _identifers[path];
				identifer.load(path);
				return identifer;
			}
		}
	protected:
	private:

	};
	template<typename T>
	class ValueIdentifer;
	template<typename T>
	class SharedValueIdentifers
	{
	public:
		static shared_ptr<ValueIdentifer<T> >& Instance(string path)
		{
			static map<string, shared_ptr<ValueIdentifer<T> > > _identifers;
			auto iter = _identifers.find(path);
			if (iter != _identifers.end())
			{
				return iter->second;
			}
			else
			{
				_identifers[path] = make_shared<ValueIdentifer<T> >();
				auto& identifer = _identifers[path];
				identifer->Load(path);
				return identifer;
			}
		}
	};

	typedef SharedValueIdentifers<int> SharedIntIdentifers;
	typedef SharedValueIdentifers<double> SharedDoubleIdentifers;

}  //----end of namespace gezi

#endif  //----end of SHARED_IDENTIFERS_H_
