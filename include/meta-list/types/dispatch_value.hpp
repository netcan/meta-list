//
// Created by netcan on 2021/11/5.
//

#ifndef META_LIST_DISPATCH_VALUE_HPP
#define META_LIST_DISPATCH_VALUE_HPP
#include <meta-list/types/value_c.hpp>
#include <meta-list/concept/value_or_type.hpp>
#include <meta-list/concept/list.hpp>
#include <meta-list/meta_list_ns.hpp>
META_LIST_NS_BEGIN

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
META_LIST_NS_END
#endif //META_LIST_DISPATCH_VALUE_HPP
