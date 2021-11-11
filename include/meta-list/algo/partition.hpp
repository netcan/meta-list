//
// Created by netcan on 2021/11/6.
//

#ifndef META_LIST_PARTITION_HPP
#define META_LIST_PARTITION_HPP
#include <meta-list/concept/list.hpp>
#include <meta-list/concept/value_or_type.hpp>
#include <meta-list/types/pair_c.hpp>
#include <meta-list/algo/pipe_adapter.hpp>
#include <meta-list/algo/append.hpp>
#include <meta-list/algo/is_pred_satisfied.hpp>
META_LIST_NS_BEGIN
namespace detail {
template<typename P, typename Res, typename ...Ts>
struct PartitionImpl: std::type_identity<Res> { };

template<typename... S, typename ...R, typename P, typename T, typename ...Ts>
struct PartitionImpl<P, Pair<TypeList<S...>, TypeList<R...>>, T, Ts...>
        : std::conditional_t<is_pred_satisfied<P, T>
                , PartitionImpl<P, Pair<TypeList<S..., T>, TypeList<R...>>, Ts...>
                , PartitionImpl<P, Pair<TypeList<S...>, TypeList<R..., T>>, Ts...>> {};

template<typename P, typename ...Ts>
using Partition_t = typename PartitionImpl<P, Pair<TypeList<>, TypeList<>>, Ts...>::type;
}

inline constexpr auto partition = PipeAdapter(
    []<typename P, typename... Ts>(TypeList<Ts...>, P)
    -> detail::Partition_t<P, Ts...> { return {}; }
);
META_LIST_NS_END
#endif //META_LIST_PARTITION_HPP
