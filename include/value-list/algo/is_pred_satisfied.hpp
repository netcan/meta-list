//
// Created by netcan on 2021/11/10.
//

#ifndef VALUE_LIST_IS_PRED_SATISFIED_HPP
#define VALUE_LIST_IS_PRED_SATISFIED_HPP
#include <value-list/types/value_c.hpp>
#include <type_traits>
VALUE_LIST_NS_BEGIN
template<typename P, typename E>
inline constexpr bool is_pred_satisfied // TODO: constraint P result is ValueConst
    = std::is_same_v<std::invoke_result_t<P, E>, ValueConst<true>>;
VALUE_LIST_NS_END
#endif //VALUE_LIST_IS_PRED_SATISFIED_HPP
