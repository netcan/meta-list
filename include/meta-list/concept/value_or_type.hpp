//
// Created by netcan on 2021/11/6.
//

#ifndef META_LIST_VALUE_OR_TYPE_HPP
#define META_LIST_VALUE_OR_TYPE_HPP
#include <meta-list/meta_list_ns.hpp>
#include <meta-list/concept/list.hpp>
META_LIST_NS_BEGIN
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
concept pair_const = requires {
    T::is_pair_const;
    requires T::is_pair_const;
};

template<typename T>
concept val_or_typ = (value_const<T> || type_const<T> || list<T> || pair_const<T>);
}
META_LIST_NS_END
#endif //META_LIST_VALUE_OR_TYPE_HPP
