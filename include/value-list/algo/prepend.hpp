//
// Created by netcan on 2021/11/6.
//

#ifndef VALUE_LIST_PREPEND_HPP
#define VALUE_LIST_PREPEND_HPP
#include <value-list/concept/list.hpp>
#include <value-list/concept/value_or_type.hpp>
#include <value-list/algo/pipe_adapter.hpp>
VALUE_LIST_NS_BEGIN

inline constexpr auto prepend = PipeAdapter(
    []<concepts::val_or_typ E, concepts::val_or_typ... Es,
       typename ...Ts>(TypeList<Ts...>, E, Es...)
    -> TypeList<E, Es..., Ts...> { return {}; }
);

VALUE_LIST_NS_END
#endif //VALUE_LIST_PREPEND_HPP
