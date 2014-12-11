/**
 *  ==============================================================================
 *
 *          \file   urate_train.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-09 22:26:08.809415
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public

#include "common_util.h"
#include "feature/Features.h"
#include "tieba/urate/get_urate_info.h"
#include "tieba/urate/urate_features.h"
using namespace std;
using namespace gezi;
using namespace gezi::tieba;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(history, "./history", "");
DEFINE_string(i, "./test.data/pid.txt", "input file");
DEFINE_string(o, "feature.txt", "output file");
DEFINE_int32(nt, 12, "thread num");

DEFINE_int32(index, 0, "pid index");
DEFINE_int32(index2, 1, "thread index");

void run()
{
	try_create_dir(FLAGS_history);
	omp_set_num_threads(FLAGS_nt);
	
	AutoTimer timer("run", 0);
	vector<uint64> pids;
	vector<int> labels;
	read_to_vec(FLAGS_i, pids, labels, FLAGS_index, FLAGS_index2);
	Pval2(pids.size(), pids[0]);
	write_features(pids, labels, 
		[&](uint64 tid) { return gen_urate_features(tid, FLAGS_history); }, FLAGS_o);
}

int main(int argc, char *argv[])
{
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	int s = google::ParseCommandLineFlags(&argc, &argv, false);
	if (FLAGS_log_dir.empty())
		FLAGS_logtostderr = true;
	LogHelper::set_level(FLAGS_level);
	FLAGS_minloglevel = FLAGS_level;
	if (FLAGS_v == 0)
		FLAGS_v = FLAGS_vl;
	SharedConf::init("urate_strategy.conf");
	run();

	return 0;
}
