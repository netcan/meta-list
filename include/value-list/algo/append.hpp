//
// Created by netcan on 2021/11/6.
//

#ifndef VALUE_LIST_APPEND_HPP
#define VALUE_LIST_APPEND_HPP
#include <value-list/concept/list.hpp>
#include <value-list/algo/pipe_adapter.hpp>
VALUE_LIST_NS_BEGIN

inline constexpr auto append = PipeAdapter(
        []<auto ...values, concepts::val_or_typ E
        , concepts::val_or_typ... Es>(ValueList<values...> vl, E, Es...)
        -> concepts::list auto {
            return ValueList<values..., E{}, Es{}...>{};
        });

VALUE_LIST_NS_END
#endif //VALUE_LIST_APPEND_HPP
