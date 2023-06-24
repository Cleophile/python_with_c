//  
// Created By Hikari Software
// 
// Y-Enterprise
// 
// 


char const* greet() {
    return "Hello Python from C++";
}

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

BOOST_PYTHON_MODULE(hello) {
    using namespace boost::python;
    def("greet", greet)
}
