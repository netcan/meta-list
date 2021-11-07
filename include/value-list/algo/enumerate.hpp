//
// Created by netcan on 2021/11/7.
//

#ifndef VALUE_LIST_ENUMERATE_HPP
#define VALUE_LIST_ENUMERATE_HPP
#include <value-list/concept/list.hpp>
#include <value-list/algo/prepend.hpp>
#include <value-list/algo/pipe_adapter.hpp>
#include <value-list/types/pair_c.hpp>
VALUE_LIST_NS_BEGIN

struct EnumerateFn {
    consteval auto operator()(concepts::list auto vl) const -> concepts::list auto
    { return invoke(vl, _v<0>); }
private:
    consteval concepts::list auto invoke(concepts::list auto vl, concepts::value_const auto index) const {
        if constexpr (vl.empty()) {
            return value_list<>;
        } else {
            return invoke(vl.tail(), _v<index.value + 1>) | prepend(pair<index.value, vl.head()>);
        }
    }
};

inline constexpr auto enumerate = PipeAdapter<EnumerateFn>{};
VALUE_LIST_NS_END

#endif //VALUE_LIST_ENUMERATE_HPP
