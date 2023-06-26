//  
// Created By Hikari Software
// 
// Y-Enterprise
// 
// 

#include <vector>
#include <string>
#include <unordered_map>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <cmath>
#include "ticksize.h"

PriceTickSize price_ticksize{{0.0, 100.0, 200.0}, {1.0, 5.0, 10.0}};
StockPriceTickSize stock_price_ticksize = {
    {"1234.TAI", {{0.0, 100.0, 200.0}, {1.0, 5.0, 10.0}}},
    {"2345.TAI", {{0.0, 100.0, 200.0}, {1.0, 5.0, 10.0}}}
};

using boost::python::def;
namespace np = boost::python::numpy;

boost::python::list check_within_tick(boost::python::list& price) {
    const int32_t len = boost::python::len(price);
    const int32_t ticksize = price_ticksize.first.size();

    std::vector<double> result(len);

    for(int32_t i = 0; i < len; ++i) {
        const double val = boost::python::extract<double>(price[i]);
        int32_t pt = 1;
        while(pt < ticksize) {
            if(val <= price_ticksize.first[pt]) {
                break;
            }
            ++pt;
        }
        const double this_barrier = price_ticksize.first[pt - 1];
        const double this_size = price_ticksize.second[pt - 1];
        const double times = (val - this_barrier) / this_size;
        const double res = times - std::round(times);
        result[i] = (res <= 1e-6) && (res >= -1e-6);
        result[i] = res;
    }
    return vector_to_pylist(result);
}

boost::python::list check_stock_within_tick(boost::python::list& stock, boost::python::list& price) {
    const int32_t len = boost::python::len(price);
    std::vector<int8_t> result(len);

    for(int32_t i = 0; i < len; ++i) {
        const auto stock_name = boost::python::extract<std::string>(stock[i]);
        if (stock_price_ticksize.find(stock_name) == stock_price_ticksize.end()) {
            result[i] = -1;
            continue;
        }

        const auto& price_ticksize = stock_price_ticksize[stock_name];

        const int32_t ticksize = price_ticksize.first.size();

        const double val = boost::python::extract<double>(price[i]);
        int32_t pt = 1;
        while(pt < ticksize) {
            if(val <= price_ticksize.first[pt]) {
                break;
            }
            ++pt;
        }
        const double this_barrier = price_ticksize.first[pt - 1];
        const double this_size = price_ticksize.second[pt - 1];
        const double times = (val - this_barrier) / this_size;
        const double res = times - std::round(times);
        if((res <= 1e-6) && (res >= -1e-6)) {
            result[i] = 1;
        }
        else {
            result[i] = 0;
        }
    }
    return vector_to_pylist(result);
}

BOOST_PYTHON_MODULE(ticksize) {
    def("check_within_tick", check_within_tick);
    def("check_stock_within_tick", check_stock_within_tick);
}
