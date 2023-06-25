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
namespace np = boost::python::numpy;

// std::vector to boost::python::list
template<class T>
boost::python::list vector_to_pylist(const std::vector<T>& vec) {
    boost::python::list l;
    for(const auto ele : vec) {
        l.append(ele);
    }
    return l;
}

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

std::string greet_numpy(np::ndarray& num) {
    std::string s = "Hello Python NUMPY from C++";
    return s;
}

boost::python::list dump_list() {
    const std::vector<int32_t> result = {{1, 2, 3}};
    const boost::python::list py_result = vector_to_pylist(result);
    return py_result;
}

np::ndarray dump_array() {
    std::vector<double> vec = {{1.0, 2.0, 3.3}};
    const Py_intptr_t shape = vec.size();
    np::ndarray result = np::zeros(1, &shape, np::dtype::get_builtin<double>());
    std::copy(vec.begin(), vec.end(), reinterpret_cast<double*>(result.get_data()));
    return result;
}


BOOST_PYTHON_MODULE(hello) {
    np::initialize();
    def("greet", greet);
    def("sum_list", sum_list);
    def("sum_square_list", sum_square_list);
    def("greet_numpy", greet_numpy);
    def("dump_list", dump_list);
    def("dump_array", dump_array);
}
