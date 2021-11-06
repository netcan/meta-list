//
// Created by netcan on 2021/11/6.
//

#ifndef VALUE_LIST_APPEND_H
#define VALUE_LIST_APPEND_H
#include <value-list/concept/list.h>
#include <value-list/algo/pipe_adapter.h>
VALUE_LIST_NS_BEGIN

inline constexpr auto append = PipeAdapter(
        []<auto ...values, typename... Es>(ValueList<values...> vl, Es...)
        -> concepts::list auto
        requires ((Es::is_value_const || Es::is_type_const) && ...) {
            return ValueList<values..., Es{}...>{};
        });

VALUE_LIST_NS_END
#endif //VALUE_LIST_APPEND_H
