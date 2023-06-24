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

using boost::python::def;

BOOST_PYTHON_MODULE(hello) {
    def("greet", greet);
}
