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
        []<auto ...values, concepts::val_or_typ E
        , concepts::val_or_typ... Es>(ValueList<values...> vl, E, Es...)
        -> concepts::list auto {
            return ValueList<E{}, Es{}..., values...>{};
        });

VALUE_LIST_NS_END
#endif //VALUE_LIST_PREPEND_HPP
