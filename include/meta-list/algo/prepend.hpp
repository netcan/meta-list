//
// Created by netcan on 2021/11/6.
//

#ifndef META_LIST_PREPEND_HPP
#define META_LIST_PREPEND_HPP
#include <meta-list/concept/list.hpp>
#include <meta-list/concept/value_or_type.hpp>
#include <meta-list/algo/pipe_adapter.hpp>
META_LIST_NS_BEGIN

inline constexpr auto prepend = PipeAdapter(
    []<concepts::val_or_typ E, concepts::val_or_typ... Es,
       typename ...Ts>(TypeList<Ts...>, E, Es...)
    -> TypeList<E, Es..., Ts...> { return {}; }
);

META_LIST_NS_END
#endif //META_LIST_PREPEND_HPP
