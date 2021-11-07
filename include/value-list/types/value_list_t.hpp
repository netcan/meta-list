//
// Created by netcan on 2021/11/5.
//

#ifndef VALUE_LIST_VALUE_LIST_H
#define VALUE_LIST_VALUE_LIST_H
#include <value-list/types/dispatch_value.hpp>
#include <value-list/value_list_ns.hpp>
VALUE_LIST_NS_BEGIN

template<concepts::val_or_typ auto... vs>
struct ValueList {
    constexpr static bool is_value_list = true;
    consteval size_t size() const { return sizeof...(vs); }
    consteval bool empty() const { return size() == 0; }
    consteval auto head() const requires requires { this->empty(); } {
        return std::get<0>(std::tie(vs...));
    }
    consteval auto tail() const requires requires { this->empty(); } {
        return []<typename T, typename... Rest>(T, Rest...) {
            return ValueList<Rest{}...>{};
        }(vs...);
    }
};

template<auto... values>
inline constexpr ValueList<dispatch_value<values>...> value_list{};

template<auto... lhs, auto... rhs>
consteval bool operator==(ValueList<lhs...>, ValueList<rhs...>) {
    if constexpr (sizeof...(lhs) != sizeof...(rhs)) { return false; }
    else { return ((lhs == rhs) && ...); }
}
VALUE_LIST_NS_END
#endif //VALUE_LIST_VALUE_LIST_H
