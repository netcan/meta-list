//
// Created by netcan on 2021/11/6.
//

#ifndef VALUE_LIST_FILTER_H
#define VALUE_LIST_FILTER_H

#include <value-list/concept/list.h>
#include <value-list/algo/pipe_adapter.h>

VALUE_LIST_NS_BEGIN
struct FilterFn {
    template<concepts::list VL, typename F>
    consteval auto operator()(VL vl, F f) const {
        if constexpr (vl.size() == 0) {
            return value_list<>;
        } else {
            constexpr auto x = vl.head();
            constexpr auto xs = vl.tail();
            if constexpr (f(x)) {
                return (*this)(xs, f).template prepend<x>();
            } else {
                return (*this)(xs, f);
            }
        }
    }
};

inline constexpr auto filter = PipeAdapter < FilterFn > {};
VALUE_LIST_NS_END
#endif //VALUE_LIST_FILTER_H
