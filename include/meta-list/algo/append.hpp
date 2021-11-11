//
// Created by netcan on 2021/11/6.
//

#ifndef META_LIST_APPEND_HPP
#define META_LIST_APPEND_HPP
#include <meta-list/concept/list.hpp>
#include <meta-list/algo/pipe_adapter.hpp>
META_LIST_NS_BEGIN

inline constexpr auto append = PipeAdapter(
    []<concepts::val_or_typ E
    , concepts::val_or_typ... Es
    , typename ...Ts>(TypeList<Ts...> vl, E, Es...)
    -> TypeList<Ts..., E, Es...> { return {}; }
);

META_LIST_NS_END
#endif //META_LIST_APPEND_HPP
