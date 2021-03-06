/**
 *  ==============================================================================
 *
 *          \file   test_get_posts_info.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-04 08:05:51.995543
 *
 *  \Description: 根据pid获取帖子信息
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "tieba/get_parsed_info.h"
using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

void run()
{

}
TEST(get_post_info, func)
{
	{
		tieba::PostInfo info = tieba::get_post_info(54648048128);
		Pval5(info.postId, info.forumName, info.userName, info.title, info.content);
		Pval5(info.forumId, info.threadId, info.userId, info.ip, info.createTime);
	}
	{
	tieba::PostInfo info = tieba::get_post_info(57037402014);
	Pval5(info.postId, info.forumName, info.userName, info.title, info.content);
	Pval5(info.forumId, info.threadId, info.userId, info.ip, info.createTime);
	}

	{
		tieba::PostInfo info = tieba::get_post_info(57218425529);
		Pval5(info.postId, info.forumName, info.userName, info.title, info.content);
		Pval5(info.forumId, info.threadId, info.userId, info.ip, info.createTime);
		Pval2(info.quoteInfo.postId, info.quoteInfo.content);
	}
	{
		tieba::PostInfo info = tieba::get_post_info(57218499162);
		Pval5(info.postId, info.forumName, info.userName, info.title, info.content);
		Pval5(info.forumId, info.threadId, info.userId, info.ip, info.createTime);
		Pval2(info.quoteInfo.postId, info.quoteInfo.content);
	}
}

TEST(get_posts_info, func)
{
	auto infos = tieba::get_posts_info(vector<uint64>({ 54648048128, 54648202523 }));
	for (auto& info : infos)
	{
		Pval5(info.forumId, info.threadId, info.userId, info.ip, info.createTime);
	}
	
	PrintVec2(infos, title, content);
}

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
