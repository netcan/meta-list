//
// Created by netcan on 2021/11/5.
//

#ifndef VALUE_LIST_TYPE_C_H
#define VALUE_LIST_TYPE_C_H
#include <type_traits>
#include <value-list/value_list_ns.h>
VALUE_LIST_NS_BEGIN
template<typename T>
struct TypeConst {
    using type = T;
};

template<typename T>
inline constexpr TypeConst<T> tc;

template<typename L, typename R>
consteval bool operator==(TypeConst<L>, TypeConst<R>) {
    return std::is_same_v<L, R>;
}

VALUE_LIST_NS_END
#endif //VALUE_LIST_TYPE_C_H
