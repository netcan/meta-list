//
// Created by netcan on 2021/11/6.
//

#ifndef VALUE_LIST_PREPEND_H
#define VALUE_LIST_PREPEND_H
#include <value-list/concept/list.h>
#include <value-list/concept/value_or_type.h>
#include <value-list/algo/pipe_adapter.h>
VALUE_LIST_NS_BEGIN

inline constexpr auto prepend = PipeAdapter(
        []<auto ...values, concepts::val_or_typ... Es>(ValueList<values...> vl, Es...)
        -> concepts::list auto {
            return ValueList<Es{}..., values...>{};
        });

VALUE_LIST_NS_END
#endif //VALUE_LIST_PREPEND_H
