//
// Created by netcan on 2021/11/6.
//

#ifndef VALUE_LIST_FILTER_HPP
#define VALUE_LIST_FILTER_HPP
#include <value-list/concept/list.hpp>
#include <value-list/algo/pipe_adapter.hpp>
#include <value-list/algo/prepend.hpp>
VALUE_LIST_NS_BEGIN
struct FilterFn {
    template<concepts::list VL, typename P>
    consteval concepts::list auto operator()(VL vl, P p) const {
        if constexpr (vl.empty()) { return value_list<>; }
        else {
            constexpr auto x = vl.head();
            constexpr auto xs = vl.tail();
            if constexpr (p(x)) {
                return (*this)(xs, p) | prepend(x);
            } else {
                return (*this)(xs, p);
            }
        }
    }
};

inline constexpr auto filter = PipeAdapter<FilterFn>{};
VALUE_LIST_NS_END
#endif //VALUE_LIST_FILTER_HPP
