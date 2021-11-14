//
// Created by netcan on 2021/11/06.
//

#ifndef META_LIST_PIPE_ADAPTER_HPP
#define META_LIST_PIPE_ADAPTER_HPP
#include <concepts>
#include <type_traits>
#include <meta-list/types/type_list.hpp>
#include <meta-list/concept/list.hpp>
#include <meta-list/meta_list_ns.hpp>
META_LIST_NS_BEGIN

template<typename Fn>
struct PipeAdapter: private Fn {
    consteval PipeAdapter(Fn) {}

    template<typename... Args>
    requires(std::invocable<Fn, TypeList<>, Args...>)
    consteval auto operator()(Args... args) const {
        return [=, this](concepts::list auto vl) consteval {
            return static_cast<const Fn &>(*this)(vl, args...);
        };
    }

    using Fn::operator();
};

template<concepts::list VL, typename Adapter> // TODO: constraint Adapter
consteval auto operator|(VL vl, Adapter adapter) {
    return adapter(vl);
}

META_LIST_NS_END
#endif //META_LIST_PIPE_ADAPTER_HPP
