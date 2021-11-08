//
// Created by netcan on 2021/11/06.
//

#ifndef VALUE_LIST_PIPE_ADAPTER_HPP
#define VALUE_LIST_PIPE_ADAPTER_HPP
#include <concepts>
#include <type_traits>
#include <value-list/types/value_list_t.hpp>
#include <value-list/concept/list.hpp>
#include <value-list/value_list_ns.hpp>
VALUE_LIST_NS_BEGIN

template<typename Fn>
struct PipeAdapter: private Fn {
    consteval PipeAdapter() = default;
    consteval PipeAdapter(Fn) {}

    template<typename... Args>
    requires(std::invocable<Fn, ValueList<>, Args...>)
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

VALUE_LIST_NS_END
#endif //VALUE_LIST_PIPE_ADAPTER_HPP
