#pragma once
#include <vector>

enum class OrderUptickResult : int8_t {
    WithinLimitWithinTick = 0,
    ExceedLimitWithinTick = 1,
    WithinLimitExceedTick = 2,
    ExceedLimitExceedTick = 3,
    
    WithinLimitUnknownTick = 4,
    ExceedLimitUnknownTick = 5
};

// std::vector to boost::python::list
template<class T>
inline boost::python::list vector_to_pylist(const std::vector<T>& vec) {
    boost::python::list l;
    for(const auto ele : vec) {
        l.append(ele);
    }
    return l;
}

using PriceTickSize = std::pair<std::vector<double>, std::vector<double>>;
using StockPriceTickSize = std::unordered_map<std::string, PriceTickSize>;

// class TickSize {
// public:
    // explicit TickSize(const )

// private:
    // struct TickSize_Config
// };
