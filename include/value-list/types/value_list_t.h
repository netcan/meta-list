//
// Created by netcan on 2021/11/5.
//

#ifndef VALUE_LIST_VALUE_LIST_H
#define VALUE_LIST_VALUE_LIST_H
#include <value-list/types/dispatch_value.h>
#include <value-list/value_list_ns.h>
VALUE_LIST_NS_BEGIN

template<auto... vs>
requires ((vs.is_value_const || vs.is_type_const) && ...)
struct ValueList {
    constexpr static bool is_value_list = true;
    consteval size_t size() const { return sizeof...(vs); }
    consteval auto head() const requires requires { this->size() > 0; } {
        return std::get<0>(std::tie(vs...));
    }
    consteval auto tail() const requires requires { this->size() > 0; } {
        return []<typename T, typename... Rest>(T, Rest...) {
            return ValueList<Rest{}...>{};
        }(vs...);
    }
///////////////////////////////////////////////////////////////////////////////
    template<auto... v>
    consteval auto append() const {
        return ValueList<vs..., dispatch_value<v>...>{};
    }
    template<typename... T>
    consteval auto append() const { return append<t<T>...>(); }
///////////////////////////////////////////////////////////////////////////////
    template<auto... v>
    consteval auto prepend() const {
        return ValueList<dispatch_value<v>..., vs...>{};
    }
    template<typename... T>
    consteval auto prepend() const { return prepend<t<T>...>(); }
};

template<auto... values>
inline constexpr ValueList<dispatch_value<values>...> value_list{};

template<auto... lhs, auto... rhs>
consteval bool operator==(ValueList<lhs...>, ValueList<rhs...>) {
    return ((lhs == rhs) && ...);
}
VALUE_LIST_NS_END
#endif //VALUE_LIST_VALUE_LIST_H
