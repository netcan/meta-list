//
// Created by netcan on 2021/11/6.
//

#ifndef VALUE_LIST_PARTITION_HPP
#define VALUE_LIST_PARTITION_HPP
#include <value-list/concept/list.hpp>
#include <value-list/types/pair_c.hpp>
#include <value-list/algo/pipe_adapter.hpp>
#include <value-list/algo/append.hpp>
VALUE_LIST_NS_BEGIN

struct PartitionFn {
    template<concepts::list VL, typename P>
    consteval auto operator()(VL vl, P p) const {
        return invoke(vl, p, value_list<>, value_list<>);
    }
private:
    template<concepts::list VL, typename P
            , concepts::list Satisified
            , concepts::list Rest>
    consteval concepts::pair_const auto invoke(VL vl, P p, Satisified satisified, Rest rest) const {
        if constexpr (vl.empty()) {
            return pair<Satisified{}, Rest{}>;
        } else {
            constexpr auto x = vl.head();
            constexpr auto xs = vl.tail();
            if constexpr (p(x)) {
                return invoke(xs, p, satisified | append(x), rest);
            } else {
                return invoke(xs, p, satisified, rest | append(x));
            }
        }
    }
};

inline constexpr auto partition = PipeAdapter<PartitionFn> {};
VALUE_LIST_NS_END
#endif //VALUE_LIST_PARTITION_HPP
