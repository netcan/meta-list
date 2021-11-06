//
// Created by netcan on 2021/11/5.
//

#ifndef VALUE_LIST_DISPATCH_VALUE_H
#define VALUE_LIST_DISPATCH_VALUE_H
#include <value-list/types/type_c.h>
#include <value-list/types/value_c.h>
#include <value-list/value_list_ns.h>
VALUE_LIST_NS_BEGIN

template<auto value>
inline constexpr auto dispatch_value = v<value>;

template<auto value>
requires(value.is_value_const)
inline constexpr auto dispatch_value<value> = dispatch_value<value.value>;

template<auto value>
requires(value.is_type_const)
inline constexpr auto dispatch_value<value> = value;

VALUE_LIST_NS_END
#endif //VALUE_LIST_DISPATCH_VALUE_H
