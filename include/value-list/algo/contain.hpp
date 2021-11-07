//
// Created by netcan on 2021/11/7.
//

#ifndef VALUE_LIST_CONTAIN_HPP
#define VALUE_LIST_CONTAIN_HPP
#include <value-list/concept/list.hpp>
VALUE_LIST_NS_BEGIN
template<auto ...values, typename E>
consteval bool contain(ValueList<values...>, E e) {
    return ((values == e) || ...);
}

VALUE_LIST_NS_END
#endif //VALUE_LIST_CONTAIN_HPP
