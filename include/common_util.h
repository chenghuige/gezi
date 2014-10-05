/** 
 *  ==============================================================================
 * 
 *          \file   common_util.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2010-11-15 16:33:52.681821
 *  
 *  \Description:  
 *  ==============================================================================
 */

#ifndef COMMON_UTIL_H_
#define COMMON_UTIL_H_

#include <stdlib.h>
#include <string.h>
#include <complex>      // std::complex, std::abs
#include <cmath>

#include <gtest/gtest.h> 
#include <glog/logging.h>
#include <gflags/gflags.h>

#include "common_def.h"

#include "string_util.h" //will remove baidu dependence 
#include "log_util.h"
#include "conf_util.h"

#include "debug_util.h"
#include "serialize_util.h"
#include "Matrix.h"
#include "sort_util.h"

#include "statistic_util.h"

//#ifndef GCCXML
#include "datetime_util.h"
#include "time_util.h"
#include "ProgressBar.h" //use timer
//#endif

#include "file_util.h"

#include "serialize_util.h"

#include "linq.h"
#include "stl_util.h"

#include "Exception.h"

#include "LoadSave.h"


#include "format.h" //最好在convert_type.h前面 有宏的冲突处理 不过在format.h内部已经引用convert_type.h
#ifndef NO_GEZI_CONVERT
#include "convert_type.h"
#endif

#include "sort_map_by_value.h"

#include "openmp_util.h"

#include "ThreadLocalAnyMap.h"
#include "SharedAnyMap.h"
#include "Singleton.h"
#include "Identifer.h" 
#include "SharedIdentifers.h"

#include "SharedObjects.h"

namespace gz = gezi;
#endif  //----end of COMMON_UTIL_H_
