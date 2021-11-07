//
// Created by netcan on 2021/11/6.
//

#ifndef VALUE_LIST_CONCAT_HPP
#define VALUE_LIST_CONCAT_HPP
#include <value-list/concept/list.hpp>
#include <value-list/types/value_list_t.hpp>
VALUE_LIST_NS_BEGIN
template<auto... l, auto ...r>
consteval concepts::list auto concat(ValueList<l...>, ValueList<r...>) {
    return ValueList<l..., r...>{};
}

template<concepts::list VL1, concepts::list VL2, concepts::list... VLRests>
requires requires { sizeof...(VLRests) > 0; }
consteval concepts::list auto concat(VL1 vl1, VL2 vl2, VLRests... vlrests) {
    return concat(concat(vl1, vl2), vlrests...);
}

VALUE_LIST_NS_END
#endif //VALUE_LIST_CONCAT_HPP
