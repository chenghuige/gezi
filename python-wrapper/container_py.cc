#define private public
#define protected public
#include "python_util.h"
// This file has been generated by Py++.

#include "boost/python.hpp"

#include "common_util.h"

#include "container/LruSetPy.h"

namespace bp = boost::python;

BOOST_PYTHON_MODULE(libcontainer){
DEF_VEC(ivec);
DEF_VEC(dvec);
DEF_VEC(uvec);
DEF_VEC(svec);
DEF_VEC(ulvec);
DEF_MAP(id_map);
DEF_MAP(sd_map);
DEF_MAP(si_map);
DEF_MAP(ss_map);
DEF_PAIR(ii_pair);
DEF_PAIR(si_pair);
DEF_PAIR(wsi_pair);
DEF_VEC(si_pair_vec);
DEF_VEC(wsi_pair_vec);
DEF_SET(iset);
DEF_SET(lset);
DEF_SET(ulset);

//    bp::class_< gezi::PyHack_LruHashSet_int >( "PyHack_LruHashSet_int" );

//    bp::class_< gezi::PyHack_LruHashSet_uint64 >( "PyHack_LruHashSet_uint64" );
}
