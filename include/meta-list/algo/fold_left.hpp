//
// Created by netcan on 2021/11/6.
//

#ifndef META_LIST_FOLD_LEFT_HPP
#define META_LIST_FOLD_LEFT_HPP
#include <meta-list/concept/list.hpp>
#include <meta-list/algo/pipe_adapter.hpp>
META_LIST_NS_BEGIN
namespace detail {
template<typename Op, typename Acc, typename ...Ts>
struct FoldImpl: std::type_identity<Acc> {};

template<typename Op, typename Acc, typename T, typename ...Ts>
struct FoldImpl<Op, Acc, T, Ts...>:
        FoldImpl<Op, std::invoke_result_t<Op, Acc, T>, Ts...> { };

template<typename Op, typename Acc, typename ...Ts>
using Fold_t = typename FoldImpl<Op, Acc, Ts...>::type;
}

inline constexpr auto fold_left = PipeAdapter(
        []<typename Op, typename Acc, typename... Ts>(TypeList<Ts...>, Acc, Op)
        -> detail::Fold_t<Op, Acc, Ts...> { return {}; }
 );

META_LIST_NS_END
#endif //META_LIST_FOLD_LEFT_HPP
