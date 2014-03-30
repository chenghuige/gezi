/**
 *  ==============================================================================
 *
 *          \file   random_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-03-30 13:12:25.981986
 *
 *  \Description: gcc4 only
 *  ==============================================================================
 */

#ifndef RANDOM_UTIL_H_
#define RANDOM_UTIL_H_

#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

namespace gezi {
 
	inline unsigned random_seed()
	{
		return std::chrono::system_clock::now().time_since_epoch().count();
	}

	typedef std::default_random_engine RandomEngine;
	typedef RandomEngine Random;
	//ע���Ǳ�����
	typedef std::uniform_int_distribution<uint32_t> RandomRange; 

	/*std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(v.begin(), v.end(), g);*/

	inline RandomEngine get_random(unsigned randSeed = 0)
	{
		if (randSeed)
		{
			return RandomEngine(randSeed);
		}
		else
		{
			std::random_device rd;
			return RandomEngine(rd());
			//or
			//return RandomEngine(random_seed());
		}
	}

	template<typename Vec>
	void shuffle(Vec& vec, unsigned randSeed = 0)
	{
		shuffle(vec.begin(), vec.end(), get_random(randSeed));
	}

	template<typename RandomAccessIterator, typename RandomNumberEngine>
	inline void sample(RandomAccessIterator first, RandomAccessIterator last, int sample_num, RandomNumberEngine&& rng)
	{
		if (first == last)
			return;

		int total = last - first;
		int len = std::min(total, sample_num);

		for (size_t i = 0; i < len; i++)
		{
			std::uniform_int_distribution<size_t> d(i, total - 1);
			swap(first[i], first[i + d(rng)]);
		}
	}

	template<typename Vec>
	void sample(Vec& vec, int maxNum, unsigned randSeed = 0)
	{
		sample(vec.begin(), vec.end(), maxNum, get_random(randSeed));
	}
}  //----end of namespace gezi

#endif  //----end of RANDOM_UTIL_H_
