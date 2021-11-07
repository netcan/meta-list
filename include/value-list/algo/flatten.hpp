//
// Created by netcan on 2021/11/7.
//

#ifndef VALUE_LIST_FLATTEN_HPP
#define VALUE_LIST_FLATTEN_HPP
#include <value-list/concept/list.hpp>
#include <value-list/algo/fold_left.hpp>
#include <value-list/algo/concat.hpp>
#include <value-list/algo/append.hpp>

VALUE_LIST_NS_BEGIN
struct FlattenFn {
    consteval auto operator()(concepts::list auto vl) const -> concepts::list auto {
        return invoke(vl);
    }
private:
    consteval static auto invoke(concepts::list auto vl) -> concepts::list auto {
        return vl
               | fold_left(value_list<>, []<typename E>(concepts::list auto acc, E elem) {
                    if constexpr (concepts::list<E>) { return concat(acc, invoke(elem)); }
                    else { return acc | append(elem); }
               });
    }
};

inline constexpr auto flatten = PipeAdapter<FlattenFn>{};
VALUE_LIST_NS_END
#endif //VALUE_LIST_FLATTEN_HPP
