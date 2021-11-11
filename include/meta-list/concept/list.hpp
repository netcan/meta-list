//
// Created by netcan on 2021/11/6.
//

#ifndef META_LIST_LIST_HPP
#define META_LIST_LIST_HPP
#include <concepts>
#include <cstddef>
#include <meta-list/meta_list_ns.hpp>
META_LIST_NS_BEGIN
namespace concepts {
template<typename List>
concept list = requires(List l) {
    { l.size() } -> std::same_as<size_t>;
    l.is_type_list;
    requires l.is_type_list;
};
}
META_LIST_NS_END
#endif //META_LIST_LIST_HPP
