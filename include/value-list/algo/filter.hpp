//
// Created by netcan on 2021/11/6.
//

#ifndef VALUE_LIST_FILTER_HPP
#define VALUE_LIST_FILTER_HPP
#include <value-list/concept/list.hpp>
#include <value-list/algo/pipe_adapter.hpp>
#include <value-list/algo/prepend.hpp>
#include <value-list/algo/is_pred_satisfied.hpp>
VALUE_LIST_NS_BEGIN
namespace detail {
template<typename P, typename Result, typename... Ts>
struct FilterImpl: std::type_identity<Result> { };

template<typename P, typename ...Rs, typename H, typename... Ts>
struct FilterImpl<P, TypeList<Rs...>, H, Ts...>:
        std::conditional_t<is_pred_satisfied<P, H>
        , FilterImpl<P, TypeList<Rs..., H>, Ts...>
        , FilterImpl<P, TypeList<Rs...>, Ts...>> { };

template<typename P, typename ...Ts>
using Filter_t = typename FilterImpl<P, TypeList<>, Ts...>::type;
}

inline constexpr auto filter = PipeAdapter(
    []<typename P, typename... Ts>(TypeList<Ts...>, P)
    -> detail::Filter_t<P, Ts...> { return {}; }
);
VALUE_LIST_NS_END
#endif //VALUE_LIST_FILTER_HPP
