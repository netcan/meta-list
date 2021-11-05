//
// Created by netcan on 2021/11/5.
//

#ifndef VALUE_LIST_VALUE_LIST_H
#define VALUE_LIST_VALUE_LIST_H
#include <value-list/value_list_ns.h>
VALUE_LIST_NS_BEGIN

template<auto...>
struct ValueList {};

template<auto... values>
inline constexpr ValueList<values...> value_list {};

template<auto... lhs, auto... rhs>
consteval bool operator==(ValueList<lhs...>, ValueList<rhs...>) {
    return ( (lhs == rhs) && ...);
}

VALUE_LIST_NS_END
#endif //VALUE_LIST_VALUE_LIST_H
