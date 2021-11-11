//
// Created by netcan on 2021/11/6.
//

#ifndef META_LIST_FILTER_HPP
#define META_LIST_FILTER_HPP
#include <meta-list/concept/list.hpp>
#include <meta-list/algo/pipe_adapter.hpp>
#include <meta-list/algo/prepend.hpp>
#include <meta-list/algo/is_pred_satisfied.hpp>
META_LIST_NS_BEGIN
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
META_LIST_NS_END
#endif //META_LIST_FILTER_HPP
