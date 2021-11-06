//
// Created by netcan on 2021/11/06.
//

#ifndef VALUE_LIST_PIPE_ADAPTER_H
#define VALUE_LIST_PIPE_ADAPTER_H
#include <concepts>
#include <type_traits>
#include <value-list/types/value_list_t.h>
#include <value-list/value_list_ns.h>
VALUE_LIST_NS_BEGIN

template<typename Fn>
struct PipeAdapter: private Fn {
    consteval PipeAdapter(Fn) {}
    template<typename... Args>
    requires(std::invocable<Fn, ValueList<>, Args...>)
    consteval auto operator()(Args... args) const {
        return [=, this]<auto... values>(ValueList<values...> vl) consteval {
            return static_cast<const Fn&>(*this)(vl, args...);
        };
    }

    template<auto... values, typename... Args>
    requires(std::invocable<Fn, ValueList<>, Args...>)
    consteval auto operator()(ValueList<values...> vl, Args... args) const {
        return static_cast<const Fn&>(*this)(vl, args...);
    }
};

VALUE_LIST_NS_END
#endif //VALUE_LIST_PIPE_ADAPTER_H
