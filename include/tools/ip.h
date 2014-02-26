/**
 *  ==============================================================================
 *
 *          \file   tools/ip.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-02-22 20:24:34.765822
 *
 *  \Description:  ע������ip���ݵĴ洢��ʽuint 4��int�Ĵ洢����ͨ�����洢�����෴
 *                 ��˲���ֱ�ӵ���IpFinder.GetAddressByIp(uint ...) ����������
 *                 ���Ե��� IpFinder.GetAddressByIp��to_ipstr(uint) ...)
 *  ==============================================================================
 */

#ifndef TOOLS_IP_H_
#define TOOLS_IP_H_

#include "common_def.h"
#include <string>
#include "tools/IpFinder.h"
namespace gezi
{
	//���涼�������ɸ�ʽip���ݴ���
	//����ip���� ת���ɿɶ���string��ʽ ���� 1577234 -> 192.168.32.78
	inline string to_ipstr(uint64 ipl)
	{
		int ip1 = ipl / (256 * 256 * 256);
		int ip2 = (ipl % (256 * 256 * 256)) / (256 * 256);
		int ip3 = (ipl % (256 * 256)) / 256;
		int ip4 = ipl % 256;
		return (format("%d.%d.%d.%d") % ip4 % ip3 % ip2 % ip1).str();
	}

	//�������ip���� ��ȡ���ɶ���ip��ʽ��4��int array[3] 192 array[2] 168 array[1] 32 array[0] 78
	inline std::array<int, 4> to_iparray(uint64 ipl)
	{
		std::array<int, 4> vec;
		vec[0] = ipl / (256 * 256 * 256);
		vec[1] = (ipl % (256 * 256 * 256)) / (256 * 256);
		vec[2] = (ipl % (256 * 256)) / 256;
		vec[3] = ipl % 256;
#if __GNUC__ > 3
		return std::move(vec);
#else
		return vec;
#endif  
	}

	inline string get_address(IpFinder& ipFinder, uint64 ipl)
	{
		string country, location;
		ipFinder.GetAddressByIp(to_ipstr(ipl), country, location);
		string result = country.size() < 4 ? country : country.substr(0, 4);
		return result;
	}
}

#endif  //----end of TOOLS_IP_H_