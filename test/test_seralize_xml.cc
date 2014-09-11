/**
 *  ==============================================================================
 *
 *          \file   test_seralize_xml.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-05 08:09:03.053970
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define  XML_SERALIZE

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "serialize_util.h"

using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

struct Node
{
	string name = "abc";
	int age = 32;

	friend class boost::serialization::access;
#ifdef XML_SERALIZE
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(name);
		ar & BOOST_SERIALIZATION_NVP(age);
	}
#else 
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & name;
		ar & age;
	}
#endif
	
};
TEST(serialize_vector, func)
{
	vector<uint64> pids = { 56934773506, 56929671202, 56921814305, 56921851753, 56921859840 };
	serialize::save(pids, "./test.data/pids.bin");
	{
		vector<uint64> pids;
		serialize::load("./test.data/pids.bin", pids);
		Pvec(pids);
	}
}

TEST(serialize_text_vector, func)
{
	vector<uint64> pids = { 56934773506, 56929671202, 56921814305, 56921851753, 56921859840 };
	serialize::save_text(pids, "./test.data/pids.txt");
	{
		vector<uint64> pids;
		serialize::load_text("./test.data/pids.txt", pids);
		Pvec(pids);
	}
}

TEST(seralize_xml_vector, func)
{
	vector<uint64> pids = { 56934773506, 56929671202, 56921814305, 56921851753, 56921859840 };
	serialize::save_xml(pids, "./test.data/pids.xml");
	{
		vector<uint64> pids;
		serialize::load_xml("./test.data/pids.xml", pids);
		Pvec(pids);
	}
}

TEST(seralize_text_map, func)
{
	map<string, uint64> m = { { "abc" , 3 }, { "def" , 4 } };
	serialize::save_text(m, "./test.data/map.txt");
	{
		map<string, uint64> m;
		serialize::load_text("./test.data/map.txt", m);
		for (auto& item : m)
		{
			Pval2(item.first, item.second);
		}
	}
}

TEST(seralize_xml_map, func)
{
	map<string, uint64> m = { { "abc" , 3 }, { "def" , 4 } };
	serialize::save_xml(m, "./test.data/map.xml");
	{
		map<string, uint64> m;
		serialize::load_xml("./test.data/map.xml", m);
		for (auto& item : m)
		{
			Pval2(item.first, item.second);
		}
	}
}

#ifndef XML_SERALIZE
TEST(seralize_text_vector_struct, func)
{
	Node node;
	vector<Node> vec;
	vec.push_back(node);
	node.name = "meixi";
	node.age = 27;
	vec.push_back(node);
	serialize::save_text(vec, "./test.data/nodeVec.txt");
	{
		vector<Node> vec;
		serialize::load_text("./test.data/nodeVec.txt", vec);
		Pval(vec.size());
		PrintVec2(vec, name, age);
	}
}

TEST(seralize_text_map_struct, func)
{

}
#else
TEST(seralize_xml_vector_struct, func)
{
	Node node;
	vector<Node> vec;
	vec.push_back(node);
	node.name = "meixi";
	node.age = 27;
	vec.push_back(node);
	serialize::save_xml(vec, "./test.data/nodeVec.xml");
	{
		vector<Node> vec;
		serialize::load_xml("./test.data/nodeVec.xml", vec);
		PrintVec2(vec, name, age);
	}
}
TEST(seralize_xml_map_struct, func)
{
	Node node;
	map<uint64, Node> m;
	m[1982] = node;
	node.name = "meixi";
	node.age = 27;
	m[1987] = node;
	serialize::save_xml(m, "./test.data/nodeMap.xml");
	{
		map<uint64, Node> m;
		serialize::load_xml("./test.data/nodeMap.xml", m);
		for (auto& item : m)
		{
			Pval3(item.first, item.second.name, item.second.age);
		}
	}
}
#endif


int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	int s = google::ParseCommandLineFlags(&argc, &argv, false);
	if (FLAGS_log_dir.empty())
		FLAGS_logtostderr = true;
	if (FLAGS_v == 0)
		FLAGS_v = FLAGS_vl;

	return RUN_ALL_TESTS();
}