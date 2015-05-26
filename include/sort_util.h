/**
 *  ==============================================================================
 *
 *          \file   sort_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-01-19 17:54:00.265288
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef SORT_UTIL_H_
#define SORT_UTIL_H_

namespace gezi {

	/**
	 * value second从大到小排序  作为默认顺序
	 * index id first 从小到大排序 作为默认顺序
	 */
	struct CmpNode
	{
		template<typename _Node>
		bool operator() (const _Node& left, const _Node& right)
		{
			return (left.second > right.second);
		}
	};

	struct CmpNodeValue
	{
		template<typename _Node>
		bool operator() (const _Node& left, const _Node& right)
		{
			return (left.value > right.value);
		}
	};

	struct CmpNodeReverse
	{
		template<typename _Node>
		bool operator() (const _Node& left, const _Node& right)
		{
			return (left.second < right.second);
		}
	};

	struct CmpNodeReverseValue
	{

		template<typename _Node>
		bool operator() (const _Node& left, const _Node& right)
		{
			return (left.value < right.value);
		}
	};

	struct CmpNodeFirst
	{
		template<typename _Node>
		bool operator() (const _Node& left, const _Node& right)
		{
			return (left.first < right.first);
		}
	};

	struct CmpNodeReverseFirst
	{
		template<typename _Node>
		bool operator() (const _Node& left, const _Node& right)
		{
			return (left.first > right.first);
		}
	};

	//--------------------------尽量使用这一组  如果是pair类型
	struct CmpPairByFirst
	{
		template<typename _Node>
		bool operator() (const _Node& left, const _Node& right)
		{
			return (left.first < right.first);
		}
	};

	struct CmpPairBySecond
	{
		template<typename _Node>
		bool operator() (const _Node& left, const _Node& right)
		{
			return (left.second < right.second);
		}
	};

	struct CmpPairByFirstReverse
	{
		template<typename _Node>
		bool operator() (const _Node& left, const _Node& right)
		{
			return (left.first > right.first);
		}
	};

	struct CmpPairBySecondReverse
	{

		template<typename _Node>
		bool operator() (const _Node& left, const _Node& right)
		{
			return (left.second > right.second);
		}
	};

	struct EqualPairByFirst
	{
		template<typename _Node>
		bool operator() (const _Node& left, const _Node& right)
		{
			return (left.first == right.first);
		}
	};

	struct EqualPairBySecond
	{
		template<typename _Node>
		bool operator() (const _Node& left, const _Node& right)
		{
			return (left.second == right.second);
		}
	};
	//----------------------------------------------------

	struct EqualNodeFirst
	{
		template<typename _Node>
		bool operator() (const _Node& left, const _Node& right)
		{
			return (left.first == right.first);
		}
	};

	struct EqualNodeByID
	{
		template<typename _Node>
		bool operator() (const _Node& left, const _Node& right)
		{
			return (left.id == right.id);
		}
	};

	struct CmpNodeByID
	{
		template<typename _Node>
		bool operator() (const _Node& left, const _Node& right)
		{
			return (left.id < right.id);
		}
	};

	struct EqualNodeByIndex
	{
		template<typename _Node>
		bool operator() (const _Node& left, const _Node& right)
		{
			return (left.index == right.index);
		}
	};

	struct CmpNodeByIndex
	{
		template<typename _Node>
		bool operator() (const _Node& left, const _Node& right)
		{
			return (left.index < right.index);
		}
	};


	template<typename ValueVec = vector<double>, typename IndexVec = vector<int> >
	struct IndexCmper
	{
		const ValueVec* valueVec;
		typedef typename IndexVec::value_type T;

		IndexCmper() {}

		IndexCmper(const ValueVec& valueVec_)
			:valueVec(&valueVec_)
		{

		}

		bool operator() (T left, T right)
		{
			return ((*valueVec)[left] > (*valueVec)[right]);
		}
	};

	template<typename ValueVec = vector<double>, typename IndexVec = vector<int> >
	struct IndexReverseCmper
	{
		const ValueVec* valueVec;
		typedef typename IndexVec::value_type T;

		IndexReverseCmper(){}

		IndexReverseCmper(const ValueVec& valueVec_)
			:valueVec(&valueVec_)
		{

		}

		bool operator() (T left, T right)
		{
			return ((*valueVec)[left] < (*valueVec)[right]);
		}
	};

	template<typename ValueVec, typename IndexVec, typename Func>
	void sort(const ValueVec& valueVec, IndexVec& indexVec, Func func)
	{
		func.valueVec = &valueVec;
		int len = valueVec.size();
		if (indexVec.empty())
		{
			indexVec.resize(len);
			for (size_t i = 0; i < len; i++)
			{
				indexVec[i] = i;
			}
		}
		std::sort(indexVec.begin(), indexVec.end(), func);
	}

	//默认是从大到小排序
	template<typename ValueVec, typename IndexVec>
	void sort(const ValueVec& valueVec, IndexVec& indexVec)
	{
		IndexCmper<ValueVec, IndexVec> func;
		sort(valueVec, indexVec, func);
	}

	template<typename ValueVec, typename IndexVec, typename Func>
	void sort(const ValueVec& valueVec, IndexVec& indexVec, int maxLen, Func func)
	{
		func.valueVec = &valueVec;
		int len = valueVec.size();
		if (indexVec.empty())
		{
			indexVec.resize(len);
			for (size_t i = 0; i < len; i++)
			{
				indexVec[i] = i;
			}
		}
		if (len <= maxLen)
		{
			std::sort(indexVec.begin(), indexVec.end(), func);
		}
		else
		{
			std::partial_sort(indexVec.begin(), indexVec.begin() + maxLen, indexVec.end(), func);
		}
	}

	template<typename ValueVec, typename IndexVec>
	void sort(ValueVec& valueVec, IndexVec& indexVec, int maxLen)
	{
		IndexCmper<ValueVec, IndexVec> func;
		sort(valueVec, indexVec, maxLen, func);
	}

	template<typename Vec, typename Func>
	void sort(Vec& vec, int maxLen, Func func)
	{
		if ((size_t)maxLen >= vec.size())
		{
			std::sort(vec.begin(), vec.end(), func);
		}
		else
		{
			std::partial_sort(vec.begin(), vec.begin() + maxLen, vec.end(), func);
		}
	}

	template<typename Vec, typename Func>
	void partial_sort(Vec& vec, int maxLen, Func func)
	{
		if ((size_t)maxLen >= vec.size())
		{
			std::sort(vec.begin(), vec.end(), func);
		}
		else
		{
			std::partial_sort(vec.begin(), vec.begin() + maxLen, vec.end(), func);
		}
	}

	template<typename Vec>
	void partial_sort(Vec& vec, int maxLen)
	{
		if ((size_t)maxLen >= vec.size())
		{
			std::sort(vec.begin(), vec.end());
		}
		else
		{
			std::partial_sort(vec.begin(), vec.begin() + maxLen, vec.end());
		}
	}

} //----end of namespace gezi

#endif  //----end of SORT_UTIL_H_
