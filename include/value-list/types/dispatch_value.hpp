//
// Created by netcan on 2021/11/5.
//

#ifndef VALUE_LIST_DISPATCH_VALUE_HPP
#define VALUE_LIST_DISPATCH_VALUE_HPP
#include <value-list/types/value_c.hpp>
#include <value-list/concept/value_or_type.hpp>
#include <value-list/concept/list.hpp>
#include <value-list/value_list_ns.hpp>
VALUE_LIST_NS_BEGIN

template<auto value>
struct DispatchValue { using type = ValueConst<value>; };

template<concepts::value_const auto value>
struct DispatchValue<value>: DispatchValue<value.value> { };

template<concepts::list auto ts>
struct DispatchValue<ts> {
    using type = std::decay_t<decltype(ts)>;
};

template<auto value>
using dispatch_value = typename DispatchValue<value>::type;
VALUE_LIST_NS_END
#endif //VALUE_LIST_DISPATCH_VALUE_HPP
