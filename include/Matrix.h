/**
 *  ==============================================================================
 *
 *          \file   Matrix.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-01-19 08:00:46.364395
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef MATRIX_H_
#define MATRIX_H_
#include "common_def.h"
#include "serialize_util.h"
namespace gezi {
	namespace ufo {

		template<typename T>
		class Matrix
		{
		public:

			Matrix()
			{

			}

			Matrix(int rows, int cols)
				:_nrow(rows), _ncol(cols)
			{
				resize(rows, cols);
			}

			Matrix(int rows, int cols, T defaultValue)
				:_nrow(rows), _ncol(cols)
			{
				resize(rows, cols, defaultValue);
			}

			inline void resize(int rows, int cols)
			{
				_nrow = rows;
				_ncol = cols;
				_mat.resize(rows);
				for (int i = 0; i < rows; i++)
				{
					_mat[i].resize(cols);
				}
			}

			inline void resize(int rows, int cols, T defaultValue)
			{
				_nrow = rows;
				_ncol = cols;
				_mat.resize(rows);
				for (int i = 0; i < rows; i++)
				{
					_mat[i].resize(cols, defaultValue);
				}
			}

			void zeroset()
			{
				for (int i = 0; i < _nrow; i++)
				{
					std::fill(_mat[i].begin(), _mat[i].end(), 0);
				}
			}

			void set_zero()
			{
				for (int i = 0; i < _nrow; i++)
				{
					std::fill(_mat[i].begin(), _mat[i].end(), 0);
				}
			}

			inline const T& operator()(int rowIdx, int colIdx) const
			{
				return _mat[rowIdx][colIdx];
			}

			inline  T& operator()(int rowIdx, int colIdx)
			{
				return _mat[rowIdx][colIdx];
			}

			vector<vector<T> >& mat()
			{
				return _mat;
			}

			vector<T>& operator[](int index)
			{
				return _mat[index];
			}

			inline int rows()
			{
				return _nrow;
			}

			inline int cols()
			{
				return _ncol;
			}

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & _mat;
				ar & _nrow;
				ar & _ncol;
			}

		private:
			vector<vector<T> > _mat;
			int _nrow = 0;
			int _ncol = 0;
		};

	}

	template<typename T>
	inline void init(vector<vector<T> >& mat, int rows, int cols, T value)
	{
		mat.resize(rows);
		for (int i = 0; i < rows; i++)
		{
			mat[i].resize(cols, value);
		}
	}

	template<typename T>
	inline void init(vector<vector<T> >& mat, int rows, int cols)
	{
		mat.resize(rows);
		for (int i = 0; i < rows; i++)
		{
			mat[i].resize(cols);
		}
	}

	typedef vector<vector<int> > imat;
	typedef vector<vector<float> > fmat;
	typedef vector<vector<Float> > Fmat;
	typedef vector<vector<double> > dmat;
} //----end of namespace gezi

#endif  //----end of MATRIX_H_
