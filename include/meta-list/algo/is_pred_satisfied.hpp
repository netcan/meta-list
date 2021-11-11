//
// Created by netcan on 2021/11/10.
//

#ifndef META_LIST_IS_PRED_SATISFIED_HPP
#define META_LIST_IS_PRED_SATISFIED_HPP
#include <meta-list/types/value_c.hpp>
#include <meta-list/concept/value_or_type.hpp>
#include <type_traits>
META_LIST_NS_BEGIN
template<typename P, typename E>
requires (concepts::value_const<std::invoke_result_t<P, E>>)
inline constexpr bool is_pred_satisfied
    = std::is_same_v<std::invoke_result_t<P, E>, ValueConst<true>>;
META_LIST_NS_END
#endif //META_LIST_IS_PRED_SATISFIED_HPP
