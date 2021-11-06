//
// Created by netcan on 2021/11/5.
//

#ifndef VALUE_LIST_TRANSFORM_H
#define VALUE_LIST_TRANSFORM_H
#include <value-list/algo/pipe_adapter.h>
#include <value-list/types/value_list_t.h>
#include <value-list/value_list_ns.h>

VALUE_LIST_NS_BEGIN
// TODO: constraint f
inline constexpr auto transform = PipeAdapter(
        []<auto... values, typename F>(ValueList<values...>, F f) {
            return value_list<f(values)...>;
        });
VALUE_LIST_NS_END

#endif //VALUE_LIST_TRANSFORM_H
