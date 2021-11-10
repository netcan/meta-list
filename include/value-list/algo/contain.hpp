//
// Created by netcan on 2021/11/7.
//

#ifndef VALUE_LIST_CONTAIN_HPP
#define VALUE_LIST_CONTAIN_HPP
#include <value-list/concept/list.hpp>
VALUE_LIST_NS_BEGIN
namespace detail {
template<typename E, typename ...Ts>
using ContainImpl = ValueConst<(std::is_same_v<Ts, E> || ...)>;
}

template<typename ...Ts, typename E>
consteval auto contain(TypeList<Ts...>, E e)
-> detail::ContainImpl<E, Ts...> { return {}; }

VALUE_LIST_NS_END
#endif //VALUE_LIST_CONTAIN_HPP
