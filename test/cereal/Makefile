#COMAKE2 edit-mode: -*- Makefile -*-
####################64Bit Mode####################
ifeq ($(shell uname -m),x86_64)
CC=g++
CXX=g++
CXXFLAGS=-g \
  -O0 \
  -pipe \
  -W \
  -Wall \
  -fPIC \
  -DHAVE_NETINET_IN_H \
  -Wno-unused-parameter \
  -std=c++0x \
  -fpermissive \
  -Wno-write-strings \
  -Wno-literal-suffix \
  -Wno-unused-local-typedefs \
  -fopenmp
CFLAGS=-g \
  -O0 \
  -pipe \
  -W \
  -Wall \
  -fPIC \
  -DHAVE_NETINET_IN_H \
  -Wno-unused-parameter \
  -std=c++0x \
  -fpermissive \
  -Wno-write-strings \
  -Wno-literal-suffix \
  -Wno-unused-local-typedefs \
  -fopenmp
CPPFLAGS=-D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\"
INCPATH=-I. \
  -I../../include \
  -I../../utils \
  -I../../output \
  -I../../output/include \
  -I../../include/feature \
  -I../../include/model \
  -I../../include/numeric
DEP_INCPATH=-I../../../../../../../app/search/sep/anti-spam/gezi/third \
  -I../../../../../../../app/search/sep/anti-spam/gezi/third/include \
  -I../../../../../../../app/search/sep/anti-spam/gezi/third/output \
  -I../../../../../../../app/search/sep/anti-spam/gezi/third/output/include \
  -I../../../../../../../com/btest/gtest \
  -I../../../../../../../com/btest/gtest/include \
  -I../../../../../../../com/btest/gtest/output \
  -I../../../../../../../com/btest/gtest/output/include \
  -I../../../../../../../lib2-64/bsl \
  -I../../../../../../../lib2-64/bsl/include \
  -I../../../../../../../lib2-64/bsl/output \
  -I../../../../../../../lib2-64/bsl/output/include \
  -I../../../../../../../lib2-64/ccode \
  -I../../../../../../../lib2-64/ccode/include \
  -I../../../../../../../lib2-64/ccode/output \
  -I../../../../../../../lib2-64/ccode/output/include \
  -I../../../../../../../lib2-64/dict \
  -I../../../../../../../lib2-64/dict/include \
  -I../../../../../../../lib2-64/dict/output \
  -I../../../../../../../lib2-64/dict/output/include \
  -I../../../../../../../lib2-64/libcrf \
  -I../../../../../../../lib2-64/libcrf/include \
  -I../../../../../../../lib2-64/libcrf/output \
  -I../../../../../../../lib2-64/libcrf/output/include \
  -I../../../../../../../lib2-64/nlp/compact-trie \
  -I../../../../../../../lib2-64/nlp/compact-trie/include \
  -I../../../../../../../lib2-64/nlp/compact-trie/output \
  -I../../../../../../../lib2-64/nlp/compact-trie/output/include \
  -I../../../../../../../lib2-64/others-ex \
  -I../../../../../../../lib2-64/others-ex/include \
  -I../../../../../../../lib2-64/others-ex/output \
  -I../../../../../../../lib2-64/others-ex/output/include \
  -I../../../../../../../lib2-64/postag \
  -I../../../../../../../lib2-64/postag/include \
  -I../../../../../../../lib2-64/postag/output \
  -I../../../../../../../lib2-64/postag/output/include \
  -I../../../../../../../lib2-64/text-util \
  -I../../../../../../../lib2-64/text-util/include \
  -I../../../../../../../lib2-64/text-util/output \
  -I../../../../../../../lib2-64/text-util/output/include \
  -I../../../../../../../lib2-64/ullib \
  -I../../../../../../../lib2-64/ullib/include \
  -I../../../../../../../lib2-64/ullib/output \
  -I../../../../../../../lib2-64/ullib/output/include \
  -I../../../../../../../lib2-64/wordseg \
  -I../../../../../../../lib2-64/wordseg/include \
  -I../../../../../../../lib2-64/wordseg/output \
  -I../../../../../../../lib2-64/wordseg/output/include \
  -I../../../../../../../ps/se/dict-set \
  -I../../../../../../../ps/se/dict-set/include \
  -I../../../../../../../ps/se/dict-set/output \
  -I../../../../../../../ps/se/dict-set/output/include \
  -I../../../../../../../ps/se/include \
  -I../../../../../../../ps/se/include/include \
  -I../../../../../../../ps/se/include/output \
  -I../../../../../../../ps/se/include/output/include \
  -I../../../../../../../public/comlog-plugin \
  -I../../../../../../../public/comlog-plugin/include \
  -I../../../../../../../public/comlog-plugin/output \
  -I../../../../../../../public/comlog-plugin/output/include \
  -I../../../../../../../public/configure \
  -I../../../../../../../public/configure/include \
  -I../../../../../../../public/configure/output \
  -I../../../../../../../public/configure/output/include \
  -I../../../../../../../public/connectpool \
  -I../../../../../../../public/connectpool/include \
  -I../../../../../../../public/connectpool/output \
  -I../../../../../../../public/connectpool/output/include \
  -I../../../../../../../public/odict \
  -I../../../../../../../public/odict/include \
  -I../../../../../../../public/odict/output \
  -I../../../../../../../public/odict/output/include \
  -I../../../../../../../public/spreg \
  -I../../../../../../../public/spreg/include \
  -I../../../../../../../public/spreg/output \
  -I../../../../../../../public/spreg/output/include \
  -I../../../../../../../public/uconv \
  -I../../../../../../../public/uconv/include \
  -I../../../../../../../public/uconv/output \
  -I../../../../../../../public/uconv/output/include \
  -I../../../../../../../public/urlparser \
  -I../../../../../../../public/urlparser/include \
  -I../../../../../../../public/urlparser/output \
  -I../../../../../../../public/urlparser/output/include \
  -I../../../../../../../quality/autotest/reportlib/cpp \
  -I../../../../../../../quality/autotest/reportlib/cpp/include \
  -I../../../../../../../quality/autotest/reportlib/cpp/output \
  -I../../../../../../../quality/autotest/reportlib/cpp/output/include \
  -I../../../../../../../st/nlp/lm-score \
  -I../../../../../../../st/nlp/lm-score/include \
  -I../../../../../../../st/nlp/lm-score/output \
  -I../../../../../../../st/nlp/lm-score/output/include \
  -I../../../../../../../third-64/boost \
  -I../../../../../../../third-64/boost/include \
  -I../../../../../../../third-64/boost/output \
  -I../../../../../../../third-64/boost/output/include \
  -I../../../../../../../third-64/gflags \
  -I../../../../../../../third-64/gflags/include \
  -I../../../../../../../third-64/gflags/output \
  -I../../../../../../../third-64/gflags/output/include \
  -I../../../../../../../third-64/glog \
  -I../../../../../../../third-64/glog/include \
  -I../../../../../../../third-64/glog/output \
  -I../../../../../../../third-64/glog/output/include \
  -I../../../../../../../third-64/pcre \
  -I../../../../../../../third-64/pcre/include \
  -I../../../../../../../third-64/pcre/output \
  -I../../../../../../../third-64/pcre/output/include \
  -I../../../../../../../third-64/tcmalloc \
  -I../../../../../../../third-64/tcmalloc/include \
  -I../../../../../../../third-64/tcmalloc/output \
  -I../../../../../../../third-64/tcmalloc/output/include

#============ CCP vars ============
CCHECK=@ccheck.py
CCHECK_FLAGS=
PCLINT=@pclint
PCLINT_FLAGS=
CCP=@ccp.py
CCP_FLAGS=


#COMAKE UUID
COMAKE_MD5=5496344c9f30cafd0184907a42382fe7  COMAKE


.PHONY:all
all:comake2_makefile_check test_cereal test_eigen 
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mall[0m']"
	@echo "make all done"

.PHONY:comake2_makefile_check
comake2_makefile_check:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mcomake2_makefile_check[0m']"
	#in case of error, update 'Makefile' by 'comake2'
	@echo "$(COMAKE_MD5)">comake2.md5
	@md5sum -c --status comake2.md5
	@rm -f comake2.md5

.PHONY:ccpclean
ccpclean:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mccpclean[0m']"
	@echo "make ccpclean done"

.PHONY:clean
clean:ccpclean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mclean[0m']"
	rm -rf test_cereal
	rm -rf ./output/bin/test_cereal
	rm -rf test_eigen
	rm -rf ./output/bin/test_eigen
	rm -rf test_cereal_test_cereal.o
	rm -rf test_eigen_test_eigen.o

.PHONY:dist
dist:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdist[0m']"
	tar czvf output.tar.gz output
	@echo "make dist done"

.PHONY:distclean
distclean:clean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdistclean[0m']"
	rm -f output.tar.gz
	@echo "make distclean done"

.PHONY:love
love:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlove[0m']"
	@echo "make love done"

test_cereal:test_cereal_test_cereal.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_cereal[0m']"
	$(CXX) test_cereal_test_cereal.o -Xlinker "-("  ../../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../../lib2-64/nlp/compact-trie/lib/libctrie.a \
  ../../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../../lib2-64/text-util/lib/libtextutil.a \
  ../../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../../ps/se/dict-set/libdictset.a \
  ../../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../../public/configure/libconfig.a \
  ../../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../../public/odict/libodict.a \
  ../../../../../../../public/spreg/libspreg.a \
  ../../../../../../../public/uconv/libuconv.a \
  ../../../../../../../public/urlparser/libnewurl.a \
  ../../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../../st/nlp/lm-score/output/lib/libScoreCal.a \
  ../../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../../third-64/boost/lib/libboost_container.a \
  ../../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../../third-64/boost/lib/libboost_coroutine.a \
  ../../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../../third-64/boost/lib/libboost_mpi.a \
  ../../../../../../../third-64/boost/lib/libboost_mpi_python.a \
  ../../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -lrt \
  -ldl \
  -lldap \
  -lcurl \
  -rdynamic -Xlinker "-)" -o test_cereal
	mkdir -p ./output/bin
	cp -f --link test_cereal ./output/bin

test_eigen:test_eigen_test_eigen.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_eigen[0m']"
	$(CXX) test_eigen_test_eigen.o -Xlinker "-("  ../../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../../lib2-64/nlp/compact-trie/lib/libctrie.a \
  ../../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../../lib2-64/text-util/lib/libtextutil.a \
  ../../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../../ps/se/dict-set/libdictset.a \
  ../../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../../public/configure/libconfig.a \
  ../../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../../public/odict/libodict.a \
  ../../../../../../../public/spreg/libspreg.a \
  ../../../../../../../public/uconv/libuconv.a \
  ../../../../../../../public/urlparser/libnewurl.a \
  ../../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../../st/nlp/lm-score/output/lib/libScoreCal.a \
  ../../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../../third-64/boost/lib/libboost_container.a \
  ../../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../../third-64/boost/lib/libboost_coroutine.a \
  ../../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../../third-64/boost/lib/libboost_mpi.a \
  ../../../../../../../third-64/boost/lib/libboost_mpi_python.a \
  ../../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -lrt \
  -ldl \
  -lldap \
  -lcurl \
  -rdynamic -Xlinker "-)" -o test_eigen
	mkdir -p ./output/bin
	cp -f --link test_eigen ./output/bin

test_cereal_test_cereal.o:test_cereal.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_cereal_test_cereal.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_cereal_test_cereal.o test_cereal.cc

test_eigen_test_eigen.o:test_eigen.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_eigen_test_eigen.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_eigen_test_eigen.o test_eigen.cc

endif #ifeq ($(shell uname -m),x86_64)


