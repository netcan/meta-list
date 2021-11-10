//
// Created by netcan on 2021/11/6.
//

#ifndef VALUE_LIST_PARTITION_HPP
#define VALUE_LIST_PARTITION_HPP
#include <value-list/concept/list.hpp>
#include <value-list/concept/value_or_type.hpp>
#include <value-list/types/pair_c.hpp>
#include <value-list/algo/pipe_adapter.hpp>
#include <value-list/algo/append.hpp>
#include <value-list/algo/is_pred_satisfied.hpp>
VALUE_LIST_NS_BEGIN
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
VALUE_LIST_NS_END
#endif //VALUE_LIST_PARTITION_HPP
