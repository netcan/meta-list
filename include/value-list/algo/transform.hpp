//
// Created by netcan on 2021/11/5.
//

#ifndef VALUE_LIST_TRANSFORM_HPP
#define VALUE_LIST_TRANSFORM_HPP
#include <value-list/algo/pipe_adapter.hpp>
#include <value-list/types/type_list.hpp>
#include <value-list/value_list_ns.hpp>

VALUE_LIST_NS_BEGIN
// TODO: constraint f
inline constexpr auto transform = PipeAdapter(
    []<typename F, typename... Ts>(TypeList<Ts...>, F)
    -> TypeList<std::invoke_result_t<F, Ts>...> { return {}; }
);
VALUE_LIST_NS_END

#endif //VALUE_LIST_TRANSFORM_HPP
