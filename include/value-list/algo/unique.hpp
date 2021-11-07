//
// Created by netcan on 2021/11/7.
//

#ifndef VALUE_LIST_UNIQUE_HPP
#define VALUE_LIST_UNIQUE_HPP
#include <value-list/concept/list.hpp>
#include <value-list/algo/pipe_adapter.hpp>
#include <value-list/algo/contain.hpp>
VALUE_LIST_NS_BEGIN

struct UniqueFn {
    consteval auto operator()(concepts::list auto vl) const -> concepts::list auto {
        return invoke(vl);
    }
private:
    consteval static auto invoke(concepts::list auto vl) -> concepts::list auto {
        if constexpr (vl.empty()) { return value_list<>; }
        else {
            constexpr auto x = vl.head();
            constexpr auto xs = vl.tail();
            constexpr auto res = invoke(xs);
            if constexpr (contain(res, x)) { return res; }
            else { return res | prepend(x); }
        }
    }
};

inline constexpr auto unique = PipeAdapter<UniqueFn>{};
VALUE_LIST_NS_END
#endif //VALUE_LIST_UNIQUE_HPP
