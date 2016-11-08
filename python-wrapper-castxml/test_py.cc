// This file has been generated by Py++.

#include "boost/python.hpp"

#include "test_py.h"

namespace bp = boost::python;

BOOST_PYTHON_MODULE(libtest){
    bp::class_< TestPy >( "TestPy" )    
        .def( 
            "haha"
            , (void ( ::TestPy::* )(  ))( &::TestPy::haha ) )    
        .def_readwrite( "_dict", &TestPy::_dict )    
        .def_readwrite( "abc", &TestPy::abc );
}