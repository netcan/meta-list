//
// Created by netcan on 2021/11/5.
//

#ifndef VALUE_LIST_VALUE_C_H
#define VALUE_LIST_VALUE_C_H
#include <value-list/value_list_ns.h>
VALUE_LIST_NS_BEGIN

template<auto v>
struct ValueConst {
    constexpr static auto value = v;
    constexpr static bool is_value_const = true;
    consteval operator decltype(v)() {
        return v;
    }
};

template<auto value>
inline constexpr ValueConst<value> v;

template<auto l, auto r>
consteval bool operator==(ValueConst<l>, ValueConst<r>) {
    return l == r;
}

VALUE_LIST_NS_END
#endif //VALUE_LIST_VALUE_C_H
