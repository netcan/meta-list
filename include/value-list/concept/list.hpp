//
// Created by netcan on 2021/11/6.
//

#ifndef VALUE_LIST_LIST_HPP
#define VALUE_LIST_LIST_HPP
#include <concepts>
#include <cstddef>
#include <value-list/value_list_ns.hpp>
VALUE_LIST_NS_BEGIN
namespace concepts {
template<typename List>
concept list = requires(List l) {
    { l.size() } -> std::same_as<size_t>;
    requires l.is_value_list;
};
}
VALUE_LIST_NS_END
#endif //VALUE_LIST_LIST_HPP
