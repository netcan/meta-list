//
// Created by netcan on 2021/11/6.
//

#ifndef VALUE_LIST_LIST_H
#define VALUE_LIST_LIST_H
#include <value-list/value_list_ns.h>
VALUE_LIST_NS_BEGIN
namespace concepts {
template<typename List>
concept list = requires(List l) {
    { l.size() } -> std::same_as<size_t>;
    requires l.is_value_list;
};
}
VALUE_LIST_NS_END
#endif //VALUE_LIST_LIST_H
