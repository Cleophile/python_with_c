//  
// Created By Hikari Software
// 
// Y-Enterprise
// 
// 

#include <string>
#include <vector>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

using boost::python::def;

std::string greet() {
    std::string s = "Hello Python from C++";
    return s;
}

int32_t sum_list(boost::python::list& num) {
    boost::python::ssize_t len_num = boost::python::len(num);
    int32_t result = 0;
    for(int32_t i = 0; i < len_num; ++i) {
        result += boost::python::extract<int32_t>(num[i]);
    }
    // std::string s = "result: " + std::to_string(result);
    return result;
}

int32_t sum_square_list(boost::python::list& num) {
    boost::python::ssize_t len_num = boost::python::len(num);
    int32_t result = 0;
    for(int32_t i = 0; i < len_num; ++i) {
        const auto x = boost::python::extract<int32_t>(num[i]);
        result += x * x;
    }
    // std::string s = "result: " + std::to_string(result);
    return result;
}

std::string greet_numpy(boost::python::numpy::ndarray& num) {
    std::string s = "Hello Python NUMPY from C++";
    return s;
}

BOOST_PYTHON_MODULE(hello) {
    boost::python::numpy::initialize();
    def("greet", greet);
    def("sum_list", sum_list);
    def("sum_square_list", sum_square_list);
    def("greet_numpy", greet_numpy);
}
