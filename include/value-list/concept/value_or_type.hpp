//
// Created by netcan on 2021/11/6.
//

#ifndef VALUE_LIST_VALUE_OR_TYPE_HPP
#define VALUE_LIST_VALUE_OR_TYPE_HPP
#include <value-list/value_list_ns.hpp>
#include <value-list/concept/list.hpp>
VALUE_LIST_NS_BEGIN
namespace concepts {
template<typename T>
concept value_const = requires {
    T::is_value_const;
    requires T::is_value_const;
};

template<typename T>
concept type_const = requires {
    T::is_type_const;
    requires T::is_type_const;
};

template<typename T>
concept val_or_typ = value_const<T> || type_const<T> || list<T>;
}
VALUE_LIST_NS_END
#endif //VALUE_LIST_VALUE_OR_TYPE_HPP
