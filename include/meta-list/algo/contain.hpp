//
// Created by netcan on 2021/11/7.
//

#ifndef META_LIST_CONTAIN_HPP
#define META_LIST_CONTAIN_HPP
#include <meta-list/concept/list.hpp>
META_LIST_NS_BEGIN
namespace detail {
template<typename E, typename ...Ts>
using ContainImpl = ValueConst<(std::is_same_v<Ts, E> || ...)>;
}

template<typename ...Ts, typename E>
consteval auto contain(TypeList<Ts...>, E e)
-> detail::ContainImpl<E, Ts...> { return {}; }

META_LIST_NS_END
#endif //META_LIST_CONTAIN_HPP
