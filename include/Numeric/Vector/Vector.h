/**
 *  ==============================================================================
 *
 *          \file   Numeric/Vector/Vector.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-03-26 10:46:03.965585
 *
 *  \Description:  特征的核心表示
 *								 支持读写，dense and sparse
 可以增加支持binary 比如value为空表示binary @TODO
 *   @TODO 是否需要 int length , index 改为int64
 *  ==============================================================================
 */

#ifndef NUMERIC__VECTOR__VECTOR_H_
#define NUMERIC__VECTOR__VECTOR_H_
#include "common_util.h"
#include "serialize_util.h"
namespace gezi {

	//@FIXME depriciated 使用TVector<Float>替代
	class Vector
	{
	public:
		Vector() = default; //sparse生成时必须带有length
		virtual ~Vector() {}
		Vector(Vector&&) = default;
		Vector& operator = (Vector&&) = default;
		Vector(const Vector&) = default;
		Vector& operator = (const Vector&) = default;

		//需要外部注意的 初始设置length 那么如果是Add(value) dense方式 要保证values最后长度
		//和初始设置的一样 不要Add不够 因为实际Length()函数表示向量长度 这个其实主要针对sparse
		Vector(int length_)
			: length(length_)
		{
		}

		Vector(Float value_, int length_)
			: length(length_), _zeroValue(value_)
		{
		}

		Vector(int length_, Float value_)
		{
			values.resize(length_, value_);
			length = length_;
			indices.clear();
		}

		void Resize(int length_, Float value_ = 0)
		{
			values.resize(length_, value_);
			length = length_;
			indices.clear();
		}

		void resize(int length_, Float value_ = 0)
		{
			Resize(length_, value_);
		}

		Vector(int length_, ivec& indices_, Fvec& values_)
			:length(length_)
		{
			indices.swap(indices_);
			values.swap(values_);
		}

		Vector(ivec& indices_, Fvec& values_, int length_ = 1024000)
			:length(length_)
		{
			indices.swap(indices_);
			values.swap(values_);
		}

		//注意desne情况 可以直接用这个种方法产生 推荐 或者调用Add 接口，
		//Add接口 内部不对length处理 
		Vector(Fvec& values_)
		{
			ToDense(values_);
		}

		//方便debug Vector vec("1\t3\t4\t5"); Vector vec("1:2.3\t3:4.5"); or vec("1 3") space is also ok
		Vector(string input, int startIndex = 0, int length_ = 1024000, string sep = ",\t ")
		{
			boost::trim(input); //需要注意 因为DOUBLE采用atof快速但是不安全 可能输入是一个空格 导致有问题
			//注意split("",sep)得到不是空结果 而是有1个空元素的vector c# python	也是		
			svec inputs = from(split(input, sep)) >> where([](string a) { return !a.empty(); }) >> to_vector();
			length = length_;
			if (inputs.size() > 0)
			{ //注意可能稀疏没有带有length
				if (contains(inputs[0], ':'))
				{
					int maxIndex = -1;
					for (string part : inputs)
					{
						string index_, val_;
						split(part, ':', index_, val_);
						int index = INT(index_) + startIndex;
						maxIndex = index;
						double val = DOUBLE(val_);
						Add(index, val);
					}
					length = std::max(maxIndex * 2, length);
				}
				else
				{
					length = inputs.size();
					for (string val_ : inputs)
					{
						Add(DOUBLE(val_));
					}
				}
			}
		}

		void Init(int length_, ivec& indices_, Fvec& values_)
		{
			length = length_;
			indices.swap(indices_);
			values.swap(values_);
		}

		//这种的问题是 外面不能够传递 Vector()临时变量进来，传临时必须只读 const Vector& 
		//所以需要&& 这样可以传临时Vector()进来 并且转为内部使用的
		void Swap(Vector& other)
		{
			length = other.length;
			indices.swap(other.indices);
			values.swap(other.values);
		}

		void Init(Fvec& values_)
		{
			ToDense(values_);
		}

		void ToDense(Fvec& values_)
		{
			values.swap(values_);
			length = values.size();
			indices.clear();
		}

		void ToDense()
		{
			Fvec vec(length, _zeroValue);
			for (size_t i = 0; i < indices.size(); i++)
			{
				vec[indices[i]] = values[i];
			}
			numNonZeros = indices.size();
			indices.clear();
			values.swap(vec);
		}

		void ToSparse()
		{
			if (!length)
				length = values.size();  //为了安全 转sparse时候设置下length 
			Fvec vec;
			for (size_t i = 0; i < values.size(); i++)
			{
				if (values[i] != _zeroValue) //@TODO for double may not work if not 0
				{
					indices.push_back(i);
					vec.push_back(values[i]);
				}
			}
			values.swap(vec);
		}

		void MakeDense()
		{
			if (IsSparse())
			{
				ToDense();
			}
		}

		void MakeSparse()
		{
			if (IsDense())
			{
				ToSparse();
			}
		}

		void Add(Float value)
		{
			values.push_back(value);
		}

		void Add(int index, Float value)
		{
			if (value != _zeroValue)
			{
				indices.push_back(index);
				values.push_back(value);
			}
		}

		void PrepareDense()
		{
			values.reserve(length);
		}

		void Sparsify(Float maxSparsity)
		{
			if (!IsDense() || keepDense)
				return;

			int nonZeroNum = GetNumNonZeros();
			//@TODO 检查特征全是0的情况
			if (nonZeroNum < (uint64)(length * maxSparsity))
			{
				ToSparse();
			}
		}


		void Sparsify()
		{
			Sparsify(sparsityRatio);
		}

		void Densify(Float maxSparsity)
		{
			if (length > 0 && (keepDense || Count() >= (uint64)(length * maxSparsity)))
			{
				ToDense();
			}
		}

		void Densify()
		{
			Densify(sparsityRatio);
		}

		Float operator[](int i) const
		{
			if (i < 0 || i >= length)
				return _zeroValue;
			//THROW((format("Index %d out of range in Vector of length %d") % i % length).str());

			if (IsDense())
			{
				return values[i];
			}
			else
			{
				auto iter = std::lower_bound(indices.begin(), indices.end(), i);
				if (iter == indices.end() || *iter != i)
				{
					return _zeroValue;
				}
				return values[iter - indices.begin()];
			}
		}

		Float& operator[](int i)
		{
			/*if (i < 0 || i >= length)
				return _value;*/
			//THROW((format("Index %d out of range in Vector of length %d") % i % length).str());
			if (IsDense())
			{//外部确保不越界！
				return values[i];
			}
			else
			{
				auto iter = std::lower_bound(indices.begin(), indices.end(), i);
				//hack
				if (iter == indices.end() || *iter != i)
				{
					return _zeroValue;
					//THROW((format("In sparse vector could not find the index %d") % i).str());
				}
				return values[iter - indices.begin()];
			}
		}

		Vector& operator()(int index, Float value)
		{
			Add(index, value);
		}

		/// Applies the given ValueVisitor to every element of the vector, in order of index.  (Zeros of sparse vectors will not be included.)
		template<typename ValueVistor>
		void ForEach(ValueVistor visitor) const
		{
			if (IsDense())
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					visitor(i, values[i]);
				}
			}
			else
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					visitor(indices[i], values[i]);
				}
			}
		}

		template<typename ValueVistor>
		void ForEachAll(ValueVistor visitor) const
		{
			if (IsDense())
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					visitor(i, values[i]);
				}
			}
			else
			{
				size_t j = 0;
				for (size_t i = 0; i < values.size(); i++)
				{
					while (j < indices[i])
					{
						visitor(j++, _zeroValue);
					}
					visitor(j++, values[i]);
				}
				while (j < length)
				{
					visitor(j++, _zeroValue);
				}
			}
		}

		template<typename ValueVistor>
		bool ForEachAllIf(ValueVistor visitor) const
		{
			if (IsDense())
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					if (!visitor(i, values[i]))
						return false;
				}
			}
			else
			{
				size_t j = 0;
				for (size_t i = 0; i < values.size(); i++)
				{
					while (j < indices[i])
					{
						if (!visitor(j++, _zeroValue))
							return false;
					}
					if (!visitor(j++, values[i]))
						return false;
				}
				while (j < length)
				{
					if (!visitor(j++, _zeroValue))
						return false;
				}
			}
			return true;
		}

		//@TODO  这个逻辑有些问题 应该是遍历所有Length 而不是截止到values.size()
		template<typename ValueVistor>
		void ForEachAllSparse(ValueVistor visitor) const
		{
			size_t j = 0;
			for (size_t i = 0; i < values.size(); i++)
			{
				while (j < indices[i])
				{
					visitor(j++, _zeroValue);
				}
				visitor(j++, values[i]);
			}
			while (j < length)
			{
				visitor(j++, _zeroValue);
			}
		}

		template<typename ValueVistor>
		bool ForEachAllSparseIf(ValueVistor visitor) const
		{
			size_t j = 0;
			for (size_t i = 0; i < values.size(); i++)
			{
				while (j < indices[i])
				{
					if (!visitor(j++, _zeroValue))
						return false;
				}
				if (!visitor(j++, values[i]))
					return false;
			}
			while (j < length)
			{
				if (!visitor(j++, _zeroValue))
					return false;
			}
			return true;
		}


		template<typename ValueVistor>
		void ForEach(ValueVistor visitor)
		{
			if (IsDense())
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					visitor(i, ref(values[i]));
				}
			}
			else
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					visitor(indices[i], ref(values[i]));
				}
			}
		}

		template<typename ValueVistor>
		void ForEachDense(ValueVistor visitor) const
		{
			for (size_t i = 0; i < values.size(); i++)
			{
				visitor(i, values[i]);
			}
		}

		template<typename ValueVistor>
		bool ForEachDenseIf(ValueVistor visitor) const
		{
			for (size_t i = 0; i < values.size(); i++)
			{
				if (!visitor(i, values[i]))
					return false;
			}
			return true;
		}

		template<typename ValueVistor>
		void ForEachDense(ValueVistor visitor)
		{
			for (size_t i = 0; i < values.size(); i++)
			{
				visitor(i, ref(values[i]));
			}
		}

		template<typename ValueVistor>
		void ForEachSparse(ValueVistor visitor) const
		{
			for (size_t i = 0; i < values.size(); i++)
			{
				visitor(indices[i], values[i]);
			}
		}

		template<typename ValueVistor>
		bool ForEachSparseIf(ValueVistor visitor) const
		{
			for (size_t i = 0; i < values.size(); i++)
			{
				if (!visitor(indices[i], values[i]))
					return false;
			}
			return true;
		}

		template<typename ValueVistor>
		void ForEachSparse(ValueVistor visitor)
		{
			for (size_t i = 0; i < values.size(); i++)
			{
				visitor(indices[i], ref(values[i]));
			}
		}

		//注意自己保证稀疏格式value不是0 一般用于print 只读 还ok
		template<typename ValueVistor>
		void ForEachNonZero(ValueVistor visitor) const
		{
			if (IsDense())
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					if (values[i] != _zeroValue)
					{
						visitor(i, values[i]);
					}
				}
			}
			else
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					visitor(indices[i], values[i]);
				}
			}
		}

		template<typename ValueVistor>
		void ForEachNonZero(ValueVistor visitor)
		{
			if (IsDense())
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					if (values[i] != _zeroValue)
					{
						visitor(i, ref(values[i]));
					}
				}
			}
			else
			{
				for (size_t i = 0; i < values.size(); i++)
				{
					visitor(indices[i], ref(values[i]));
				}
			}
		}
	public:
		//注意和TLC的区别 默认一个空的Vector是Sparse的 也就是表示所有向量值都是0的情况
		//注意需要保证如果是sparse indices和values始终长度相同 Count() == 0 一定是Sparse
		bool IsDense() const
		{
			return indices.size() != values.size();
		}

		bool IsSparse() const
		{
			return indices.size() == values.size();
		}

		//@TODO  尽量少用length Length
		/// Gets a int value representing the dimensionality of the vector.
		int Length() const
		{
			if (length)
				return length;
			if (indices.empty()) //dense
			{
				return values.size();
			}
			//sparse no length return 0 empty
			return length;
		}

		//小写开头的是为了兼容stl
		int size() const
		{
			return Length();
		}

		void SetLength(int length_)
		{
			length = length_;
		}

		bool Empty() const
		{
			return length == 0;
		}

		bool empty() const
		{
			return length == 0;
		}

		/// Gets the number of explicitly represented values in the vector.
		int Count() const
		{
			return values.size();
		}

		//注意只适用于初始化好后 如果后续修改Vector内容 可能造成NumNonZerors结果不对
		int NumNonZeros()
		{
			if (IsSparse())
			{
				return indices.size();
			}
			else if (numNonZeros >= 0)
			{
				return numNonZeros;
			}
			else
			{
				return GetNumNonZeros();
			}
		}

		const ivec& Indices() const
		{
			return indices;
		}

		const Fvec& Values() const
		{
			return values;
		}

		ivec& Indices()
		{
			return indices;
		}

		Fvec& Values()
		{
			return values;
		}

		int Index(int index) const
		{
			return indices[index];
		}

		int Index(int index)
		{
			return indices[index];
		}

		Float Value(int index) const
		{
			return values[index];
		}

		//@FIXME why fail boost.python
#ifndef GCCXML
		Float& Value(int index)
		{
			return values[index];
		}
		//#else 
		//		double& Value(int index) //这个没问题但是python里面 不能用 例如 fe.Value(3) = 4
		//		{
		//			return values[index];
		//		}
#endif

		void Clear()
		{
			length = 0;
			indices.clear();
			values.clear();
		}

		void CheckInvariants()
		{
			if (IsDense())
			{
				CHECK_EQ(values.size(), length);
			}
			else
			{
				CHECK_EQ(values.size(), indices.size());
				//@TODO 检查所有indice是在合理范围？ 排序？
			}
		}

		Vector& operator *= (Float d)
		{
			ScaleBy(d);
			return *this;
		}

		/// Multiples the Vector by a real value
		void ScaleBy(Float d)
		{
			if (d == 1.0)
				return;

			if (d == 0)
			{
				if (!keepDense)
				{
					values.clear();
					indices.clear();
				}
				else
				{
					for (size_t i = 0; i < values.size(); i++)
						values[i] = 0;
				}
			}
			else
			{
				for (size_t i = 0; i < values.size(); i++)
					values[i] *= d;
			}
		}

		/// Adds the supplied vector to myself.  (this += a)
		void Add(Vector a)
		{
			/*	if (a.length != length)
				{
				THROW("Vectors must have the same dimensionality.");
				}*/

			if (a.Count() == 0)
				return;

			if (generalized_same(a.indices, indices))
			{
				for (size_t i = 0; i < values.size(); i++)
					values[i] += a.values[i];
			}
			else if (IsDense())
			{ // a sparse, this not sparse
				for (int i = 0; i < a.indices.size(); i++)
				{
					values[a.indices[i]] += a.values[i];
				}
			}
			else
			{
				ApplyWith(a, [](int ind, Float v1, Float& v2) { v2 += v1; });
			}
		}

		/// Applies the ParallelManipulator to each corresponding pair of elements where the argument is non-zero, in order of index.
		//@TODO 拷贝之痛 暂时使用swap 不保证运算后a不会被改变,如果需要提前拷贝复制a
		//@TODO 理解两个稀疏向量相加/相乘...
		template<typename ParallelManipulator>
		void ApplyWith(Vector a, ParallelManipulator manip)
		{
			/*		if (a.length != length)
					{
					THROW("Vectors must have the same dimensionality.");
					}*/

			if (a.Count() == 0)
				return;

			if (a.IsDense())
			{
				if (IsDense())
				{
					for (size_t i = 0; i < values.size(); i++)
					{
						manip(i, a.values[i], ref(values[i]));
					}
				}
				else
				{  // this sparse, a not sparse
					Fvec newValues(length);
					int myI = 0;
					for (size_t i = 0; i < newValues.size(); i++)
					{
						if (myI < Count() && indices[myI] == i)
						{
							newValues[i] = values[myI++];
						} // else, newValues[i] is already zero
						manip(i, a.values[i], ref(newValues[i]));
					}

					indices.clear();
					values.swap(newValues);
				}
				Sparsify();
			}
			else if (IsDense())
			{ // a sparse, this not sparse
				for (size_t i = 0; i < a.indices.size(); i++)
				{
					int index = a.indices[i];
					manip(index, a.values[i], ref(values[index]));
				}
			}
			else if (&a.indices == &indices)
			{ // both sparse, same indices
				for (size_t i = 0; i < values.size(); i++)
				{
					manip(indices[i], a.values[i], ref(values[i]));
				}
			}
			else if (Count() == 0)
			{
				values.resize(a.Count(), 0);
				indices.swap(a.indices);
				for (size_t i = 0; i < values.size(); i++)
				{
					manip(indices[i], a.values[i], ref(values[i]));
				}
			}
			else
			{ // both sparse
				size_t myI = 0;

				size_t newLength = indices.size();
				// try to find each a index in my indices, counting how many more we'll add
				for (size_t aI = 0; aI < a.indices.size(); aI++)
				{
					int aIndex = a.indices[aI];
					while (myI < indices.size() && indices[myI] < aIndex)
					{
						myI++;
					}
					if (myI == indices.size())
					{
						newLength += a.indices.size() - aI;
						break;
					}
					else if (indices[myI] == aIndex)
					{
						myI++;
					}
					else
					{
						newLength++;
					}
				}

				myI = 0;

				if (newLength == indices.size())
				{
					if (newLength == a.indices.size())
					{
						for (size_t i = 0; i < values.size(); i++)
						{
							manip(indices[i], a.values[i], ref(values[i]));
						}
						//a.indices = indices;
					}
					else
					{
						for (size_t aI = 0; aI < a.indices.size(); aI++)
						{
							int aIndex = a.indices[aI];
							while (indices[myI] < aIndex)
								myI++;
							manip(aIndex, a.Value(aI), ref(values[myI++]));
						}
					}
				}
				else if (newLength == a.indices.size())
				{
					Fvec newVals(newLength, 0);

					for (int aI = 0; aI < a.indices.size(); aI++)
					{
						int aIndex = a.indices[aI];
						if (myI < indices.size() && indices[myI] == aIndex)
						{
							newVals[aI] = values[myI++];
						}

						manip(aIndex, a.Value(aI), ref(newVals[aI]));
					}

					indices.swap(a.indices);
					values.swap(newVals);
				}
				else
				{
					ivec newIndices(newLength, 0);
					Fvec newVals(newLength, 0);

					int newI = 0;
					for (size_t aI = 0; aI < a.indices.size(); aI++)
					{
						int aIndex = a.indices[aI];
						while (myI < indices.size() && indices[myI] < aIndex)
						{
							newVals[newI] = values[myI];
							newIndices[newI] = indices[myI];
							myI++;
							newI++;
						}
						if (myI == indices.size())
						{
							while (aI < a.indices.size())
							{
								newIndices[newI] = a.indices[aI];
								manip(aIndex, a.Value(aI), ref(newVals[newI]));
								aI++;
								newI++;
							}
							break;
						}

						Float myVal = 0;
						if (indices[myI] == aIndex)
						{
							myVal = values[myI++];
						}

						manip(aIndex, a.Value(aI), ref(myVal));
						newVals[newI] = myVal;
						newIndices[newI] = aIndex;
						newI++;
					}

					while (myI < indices.size())
					{
						newVals[newI] = values[myI];
						newIndices[newI] = indices[myI];
						myI++;
						newI++;
					}

					indices.swap(newIndices);
					values.swap(newVals);

					Densify();
				}
			}
		}

		//l2norm
		Float Norm()
		{
			return sqrt(std::accumulate(values.begin(), values.end(), 0.0, sd_op()));
		}

		string Str(string sep = ",")
		{
			stringstream ss;
			ForEachNonZero([&](int index, Float value) {
				ss << index << ":" << value << sep;
			});
			return ss.str();
		}

		string DenseStr(string sep = ",")
		{
			stringstream ss;
			ForEachAll([&](int index, Float value) {
				ss << index << ":" << value << sep;
			});
			return ss.str();
		}

		string str(string sep = ",")
		{
			stringstream ss;
			ForEachNonZero([&](int index, Float value) {
				ss << index << ":" << value << sep;
			});
			return ss.str();
		}

		friend Float dot(const Vector& l, const Vector& r);

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive &ar, const unsigned int version)
		{
			ar & indices;
			ar & values;
			ar & length;
			ar & sparsityRatio;
			ar & keepDense;
			ar & keepSparse;
			ar & normalized;
			ar & numNonZeros;
			ar & _zeroValue;
		}
	private:
		//获取dense格式表示结构中的非0数目
		int GetNumNonZeros()
		{
			int nonZeroNum = 0;
			for (auto item : values)
			{
				if (item != 0)
				{
					nonZeroNum++;
				}
			}
			numNonZeros = nonZeroNum; //save non zero num
			return numNonZeros;
		}
	public:
		//@TODO 有没有必要写成shared_ptr<ivec> indices; //更加灵活 允许两个Vector相同indice 不同value 避免拷贝
		ivec indices; //不使用Node(index,value)更加灵活 同时可以允许一项为空
		Fvec values; //@TODO may be FvecPtr 或者加一个指针 修改代码 如果指针不是空 使用指针指向的
		//non_zero count < ratio to sparse, non_zero count >= ratio to dense
		Float sparsityRatio = 0.25;
		bool keepDense = false;
		bool keepSparse = false;
		bool normalized = false;
		int numNonZeros = -1; //-1 means unknow
	private:
		int length = 0;
		Float _zeroValue = 0.0;
	};

	typedef shared_ptr<Vector> VectorPtr;

	//@TODO generic for Vector or IntArray
	inline Float dot(const Vector& a, const Vector& b)
	{
		if (!a.Count() || !b.Count())
		{
			return 0;
		}

		if (generalized_same(a.indices, b.indices))
		{
			/*if (a.Length() != b.Length())
			{
			THROW("Vectors must have the same dimensionality.");
			}*/
			Float res = 0;
			for (size_t i = 0; i < a.values.size(); i++)
			{
				res += a.values[i] * b.values[i];
			}
			return res;
		}

		Float result = 0;

		//注意TLC对 内容为空的indices,values做了特殊处理 
		if (b.IsDense())
		{
			for (size_t i = 0; i < a.indices.size(); i++)
				result += a.values[i] * b.values[a.indices[i]];
		}
		else if (a.IsDense())
		{
			for (size_t i = 0; i < b.indices.size(); i++)
				result += a.values[b.indices[i]] * b.values[i];
		}
		else
		{ // both sparse
			size_t aI = 0, bI = 0;
			while (aI < a.indices.size() && bI < b.indices.size())
			{
				switch (compare(a.indices[aI], b.indices[bI]))
				{
				case 0:
					result += a.Value(aI++) * b.Value(bI++);
					PVAL(result);
					break;
				case -1:
					aI++;
					break;
				case 1:
					bI++;
					break;
				default:
					break;
				}
			}
		}
		return result;
	}
}  //----end of namespace gezi

#endif  //----end of NUMERIC__VECTOR__VECTOR_H_
