//
// Created by netcan on 2021/11/6.
//

#ifndef VALUE_LIST_CONCAT_HPP
#define VALUE_LIST_CONCAT_HPP
#include <value-list/concept/list.hpp>
#include <value-list/types/type_list.hpp>
VALUE_LIST_NS_BEGIN
template<typename... L, typename ...R>
consteval auto concat(TypeList<L...>, TypeList<R...>)
-> TypeList<L..., R...> { return {}; }

template<concepts::list VL1, concepts::list VL2, concepts::list... VLRests>
requires requires { sizeof...(VLRests) > 0; }
consteval concepts::list auto concat(VL1 vl1, VL2 vl2, VLRests... vlrests) {
    return concat(concat(vl1, vl2), vlrests...);
}

VALUE_LIST_NS_END
#endif //VALUE_LIST_CONCAT_HPP
