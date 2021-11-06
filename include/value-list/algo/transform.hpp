//
// Created by netcan on 2021/11/5.
//

#ifndef VALUE_LIST_TRANSFORM_HPP
#define VALUE_LIST_TRANSFORM_HPP
#include <value-list/algo/pipe_adapter.hpp>
#include <value-list/types/value_list_t.hpp>
#include <value-list/value_list_ns.hpp>

VALUE_LIST_NS_BEGIN
// TODO: constraint f
inline constexpr auto transform = PipeAdapter(
        []<auto... values, typename F>(ValueList<values...>, F f)
        -> concepts::list auto {
            return value_list<f(values)...>;
        });
VALUE_LIST_NS_END

#endif //VALUE_LIST_TRANSFORM_HPP
