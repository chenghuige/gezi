/**
 *  ==============================================================================
 *
 *          \file   collocation.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-01-18 22:15:02.575571
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef COLLOCATION_H_
#define COLLOCATION_H_
#include "common_util.h"

namespace gezi
{
//chi square �������� ���㵥��feature�͵�����Ŀ���ֵ,����������������ȡ�����������Ļ��߼�Ȩƽ��
//information gain(��Ϣ����) Ҳ�ɳ�ΪMI(mutual info����Ϣ) ����Ϣ���Դ� ��Ϣ����ͷֲ������������Ƕ����� ������
//MI �����������µ�ͬIG������������A,B,C)�Ƕ�ÿ�������� A����A����A�����������IG �ο����������Ǳ��� ����ѡ��
//PMI �㻥��Ϣ�����������������ԶԶ������Ȩƽ������ȡPMI���ֵ D:\baiduyun\ml\machine-learning.pptxt 27
//ECE ���������� �����غ�����ظ���һ�� KL ����غ����������ֲ�����Ļ���ҪҪ���õ�bit�����������ؼ��ǲ���q�ֲ�ʱ��һ��Ҫ�õ�bit��
//http://en.wikipedia.org/wiki/Cross_entropy the cross entropy between two probability distributions measures 
//the average number of bits needed to identify an event from a set of possibilities, 
//if a coding scheme is used based on a given probability distribution q, rather than the "true" distribution p.
//\mathrm{H}(p, q) = \mathrm{E}_p[-\log q] = \mathrm{H}(p) + D_{\mathrm{KL}}(p \| q),\!
//��������������Ϣ���������,��֮ͬ������,����������ֻ�����������ı��з��������,����Ϣ����ͬʱ�������������ı��з����벻�����������
//H(p,q) = -sum(p(x)log(q(x))
//����˵������������ ���˾�����ʵ����������صĸ���ERE(KL) http://wenku.baidu.com/view/742037946bec0975f465e261.html
//��mi������ mi ����p(x)p(y)��p(x,y)�ķֲ�������(kl)����������ͼֱ�Ӷ���p(c),p(c|v)�ķֲ�������(kl)
//�������Դ��� 20.4 WSD word sense disambiguation �ʵĶ���ʶ�� selectional preference
//D:\baiduyun\ml\����ѡ��SelectionalPreference.pdf
//Information theory provides an appropriate way 
//to quantify the difference between the prior and pos- 
//terior distributions, in the form of relative entropy (Kullback and Leibler, 1951). 
//The model defines the selectional preference strength of a predicate as: ? 
//SR(p) = D(er(clp)[I Pr(c)) = E pr(clp)log Pr(clp) Pr(c) " 
//ע�����ı����������ᵽ�Ľ���������ѡ����󻹳���pr(v) measures_of_rule_quality_for_feature_selection_in_text_categorization.pdf
namespace collocation
{

enum Method
{
  FREQ, //DF
  IDF,
  CHI, //chi square
  IG, //information gain(��Ϣ����) 
  MI, //mutual info
  MI2, //the same as mutual info
  PMI, //point mutual info 
  ECE, //expected cross entropy 
  EMI, //expected mutual info
  T_TEST,
  LIR, //likely hood tio
};

}
//typedef double Float;

struct ChiSquareFunc
{
  /**
   *
   * @param a  coccur num of (term1,ter2)
   * @param n1   occur num of term1
   * @param n2   occur num of occur term2
   * @param n    total words
   * @return     messure
   *
   */
  //float Chi2(int a, int b, int c, int d) 
  //{ 
  //   return 
  //   (a+b+c+d) * ((a*d-b*c)^2) / 
  //      ((a+b)*(a+c)*(c+d)*(b+d)); 
  //}
  //
  //float Chi2_v2(int a, int b, int c, int d)
  //{
  //   double total = a + b + c + d;
  //   double n = Math.Log(total);
  //   double num = 2.0 * Math.Log(Math.Abs((a * d) - (b * c)));
  //   double den = Math.Log(a + b) + Math.Log(a + c) + Math.Log(c + d) + Math.Log(b + d);
  //   return (float) Math.Exp(n+num-den);
  //}

  //  Float operator()(int a00, int nterm1, int nterm2, unsigned long long n)
  //  {
  //    if (!a00)
  //      return 0;
  //    int a10 = nterm1 - a00;
  //    int a01 = nterm2 - a00;
  //    long long a11 = n - a00 - a10 - a01; 
  //    Float t = Float(a00 * a11 - a01 * a10);
  //    return (t / (a00 + a10)) * (t / (a01 + a11))
  //            * (n / Float(a10 + a11)) / (a00 + a01);
  //  }

  Float operator()(int a, int n1, int n2, uint64 total)
  {
    Float n = log(total);
    Float b = n1 - a;
    Float c = n2 - a;
    Float d = total - (a + b + c);
    Float num = 2.0 * log(fabs((a * d) - (b * c)));
    Float den = log(a + b) + log(a + c) + log(c + d) + log(b + d);
    return (Float) exp(n + num - den);
  }
};

//how about when a is 0

inline Float chi_square(int a, int n1, int n2, uint64 total)
{
  Float n = log(total);
  Float b = n1 - a;
  Float c = n2 - a;
  Float d = total - (a + b + c);
  Float num = 2.0 * log(fabs((a * d) - (b * c)));
  Float den = log(a + b) + log(a + c) + log(c + d) + log(b + d);
  return (Float) exp(n + num - den);
}

struct EchoFunc
{

  Float operator()(int a, int n1, int n2, uint64 n)
  {
    return a;
  }
};

struct PointMutualInfoFunc
{

  /**
   *  �㻥��Ϣ
   *  log ( P(AB) / P(A)P(B) ) <=> log(O11/ E11)
   *     (AB / N) / (A / N) (B / N) = (AB * N) / (A * B )
   * 
   */
  Float operator()(int a, int n1, int n2, uint64 n)
  {
    if (!a)
      return std::numeric_limits<int>::min();
    return log(Float(n / n1) * (Float(a) / n2));
  }
};

inline Float point_mutual_info(int a, int n1, int n2, uint64 n)
{
  if (!a)
    return std::numeric_limits<int>::min();
  return log(Float(n / n1) * (Float(a) / n2));
}

//������Ϣ���� ����ǰ��ն��class �ۼӵ���Ҫ һ��ֻ����һ��class �Ĺ���  �������ֻ��AVGģʽ�������յ�IG���
//n1 ����class���ִ���, n2 ���� feature���ִ���

inline Float information_gain(int a, int n1, int n2, uint64 n)
{
//  Float cratio = n1 / (double) n;
//  return -log()
  return 0;
}

//���㻥��Ϣ��2class ��Ϣ����) ����ǰ�������class һ�μ����ۺ�2���Ļ���Ϣ

inline Float mutual_info(int a, int n1, int n2, uint64 n)
{
  return 0;
}

//���㻥��Ϣ ��ʽ2 Ӧ�ú�����Ľ����ͬ just for test ֻ������ͺ� 

inline Float mutual_info2(int a, int n1, int n2, uint64 n)
{
  return 0;
}

inline Float cross_entropy(int a, int n1, int n2, uint64 n)
{
  return 0;
}

struct DiscountedMutualInfoFunc
{

  /**
   *  �㻥��Ϣ
   *  log ( P(AB) / P(A)P(B) ) <=> log(O11/ E11)
   *     (AB / N) / (A / N) (B / N) = (AB * N) / (A * B )
   *
   */
  Float operator()(int a00, int nterm1, int nterm2, unsigned long long n)
  {
    if (!a00)
      return 0;
    int m = std::min(nterm1, nterm2);
    return ( (a00 / Float(a00 + 1)) * (m / Float(m + 1)))
            * log(Float(n / nterm1) * (Float(a00) / nterm2)) / log(2);
  }
};

struct EMutualInfoFunc
{

  /**
   * ����Ϣ������ֵ
   * E(plog ( P(AB) / P(A)P(B) )
   * ����Ϣ�Ļ����� * ʵ�ʶ�Ԫ���ָ��ʣ���������Ϣ���ڵ�Ƶ�ʵ�ƫ��
   */
  Float operator()(int a00, int nterm1, int nterm2, unsigned long long n)
  {
    if (!a00)
      return 0;
    return (Float(a00) / n) * (log(Float(n / nterm1) * (Float(a00) / nterm2)) / log(2));
  }

};

struct TTestFunc
{

  /**
   * t_test
   *  ( mean(actual) - mean(bad suppose) ) / (sd(actual) )
   *  ��ֵԽ�����bad suppose����ؼٶ�Խ�����գ�Ҳ���Ǵ���̶�Խ��
   *  FIXME ������nan
   */
  Float operator()(int a00, int nterm1, int nterm2, unsigned long long n)
  {
    if (!a00)
      return 0;
    //        return Float( a00  - nterm1 * nterm2 / n) / sqrt(a00 * n);
    return Float(a00 - (nterm1 * nterm2) / n) / sqrt(a00) * sqrt(n);
  }
};

struct EChiSquareFunc
{

  /**
   *
   * @param a00  coccur num of (term1,ter2)
   * @param nl   occur num of term1
   * @param nr   occur num of occur term2
   * @param n    total words
   * @return     messure
   *
   *  x^2 = N(a00a11 - a01a10)^2/(a00 + a01)(a00 + a10)(a01 + a11)(a10 + a11)
   *  Ϊ�˷�ֹ���ӹ��������˳��� ��Ϊ��ʱ
   */
  Float operator()(int a00, int nterm1, int nterm2, unsigned long long n)
  {
    if (!a00)
      return 0;
    int a10 = nterm1 - a00;
    int a01 = nterm2 - a00;
    long long a11 = n - a00 - a10 - a01;
    Float t = Float(a00 * a11 - a01 * a10);
    return Float(a00) * (t / (a00 + a10)) * (t / (a01 + a11))
            * (n / Float(a10 + a11)) / (a00 + a01);
  }
};

struct LogEChiSquareFunc
{

  /**
   *
   * @param a00  coccur num of (term1,ter2)
   * @param nl   occur num of term1
   * @param nr   occur num of occur term2
   * @param n    total words
   * @return     messure
   *
   *  x^2 = N(a00a11 - a01a10)^2/(a00 + a01)(a00 + a10)(a01 + a11)(a10 + a11)
   *  Ϊ�˷�ֹ���ӹ��������˳��� ��Ϊ��ʱ
   *  ע��ȷ��a00 > 0
   */
  Float operator()(int a00, int nterm1, int nterm2, unsigned long long n)
  {
    if (!a00)
      return 0;
    int a10 = nterm1 - a00;
    int a01 = nterm2 - a00;
    long long a11 = n - a00 - a10 - a01;
    Float t = Float(a00 * a11 - a01 * a10);
    return log(a00) * Float(t / (a00 + a10)) * (t / (a01 + a11))
            * (n / Float(a10 + a11)) / (a00 + a01);
  }
};
}
#endif  //----end of COLLOCATION_H_