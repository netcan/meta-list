//
// Created by netcan on 2021/11/5.
//

#ifndef META_LIST_TRANSFORM_HPP
#define META_LIST_TRANSFORM_HPP
#include <meta-list/algo/pipe_adapter.hpp>
#include <meta-list/types/type_list.hpp>
#include <meta-list/meta_list_ns.hpp>

META_LIST_NS_BEGIN
// TODO: constraint f
inline constexpr auto transform = PipeAdapter(
    []<typename F, typename... Ts>(TypeList<Ts...>, F)
    -> TypeList<std::invoke_result_t<F, Ts>...> { return {}; }
);
META_LIST_NS_END

#endif //META_LIST_TRANSFORM_HPP
