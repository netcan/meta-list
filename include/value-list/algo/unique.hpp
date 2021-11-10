//
// Created by netcan on 2021/11/7.
//

#ifndef VALUE_LIST_UNIQUE_HPP
#define VALUE_LIST_UNIQUE_HPP
#include <value-list/concept/list.hpp>
#include <value-list/algo/pipe_adapter.hpp>
#include <value-list/algo/contain.hpp>
VALUE_LIST_NS_BEGIN
namespace detail {
template<typename Result, typename ...Ts>
struct UniqueImpl: std::type_identity<Result> { };

template<typename ...Rs, typename T, typename ...Ts>
struct UniqueImpl<TypeList<Rs...>, T, Ts...>:
        std::conditional_t<detail::ContainImpl<T, Rs...>::value
                , UniqueImpl<TypeList<Rs...>, Ts...>
                , UniqueImpl<TypeList<Rs..., T>, Ts...> > {};

template<typename ...Ts>
using Unique_t = typename UniqueImpl<TypeList<>, Ts...>::type;
}

inline constexpr auto unique = PipeAdapter(
    []<typename... Ts>(TypeList<Ts...>)
    -> detail::Unique_t<Ts...> { return {}; }
);
VALUE_LIST_NS_END
#endif //VALUE_LIST_UNIQUE_HPP
