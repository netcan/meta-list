//
// Created by netcan on 2021/11/6.
//

#ifndef VALUE_LIST_FOLD_LEFT_HPP
#define VALUE_LIST_FOLD_LEFT_HPP
#include <value-list/concept/list.hpp>
#include <value-list/algo/pipe_adapter.hpp>
VALUE_LIST_NS_BEGIN
struct FoldLeftFn {
    template<concepts::list VL, typename Acc, typename Op>
    consteval auto operator()(VL vl, Acc acc, Op op) const {
        if constexpr (vl.empty()) { return acc; }
        else { return (*this)(vl.tail(), op(acc, vl.head()), op); }
    }
};

inline constexpr auto fold_left = PipeAdapter<FoldLeftFn> {};

VALUE_LIST_NS_END
#endif //VALUE_LIST_FOLD_LEFT_HPP
