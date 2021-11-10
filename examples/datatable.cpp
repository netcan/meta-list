//
// Created by netcan on 2021/11/7.
//
#include <value-list/type.hpp>
#include <value-list/algorithm.hpp>
#include <cstdint>
#include <concepts>
#include <bitset>
#include <algorithm>
#include <cassert>

using namespace VALUE_LIST_NS;

///////////////////////////////////////////////////////////////////////////////
// for user to describe key/valuetype Entry
// <key, valuetype>
template<auto Key, typename ValueType, size_t Dim = 1>
struct Entry {
    constexpr static auto key = Key;
    constexpr static size_t dim = Dim;
    constexpr static bool isArray = Dim > 1;
    using type = ValueType;
};

template<auto Key, typename ValueType, size_t Dim>
struct Entry<Key, ValueType[Dim]>: Entry<Key, ValueType, Dim> { };

template<typename E>
concept KVEntry = requires {
    typename E::type;
    requires std::is_standard_layout_v<typename E::type>;
    requires std::is_trivial_v<typename E::type>;
    { E::key } -> std::convertible_to<size_t>;
    { E::dim } -> std::convertible_to<size_t>;
};


consteval bool operator==(KVEntry auto el, KVEntry auto er) {
    using ELType = decltype(el)::type;
    using ERType = decltype(er)::type;
    return el.dim == er.dim
           && sizeof(ELType) == sizeof(ERType)
           && alignof(ELType) == alignof(ERType);
}

static_assert(KVEntry<Entry<0, char[10]>>);

template<auto Key, typename ValueType>
inline constexpr auto entry = Entry<Key, ValueType>{};

///////////////////////////////////////////////////////////////////////////////
template <concepts::list auto entries>
class Datatable {
    template</* KVEntry */ typename EH, /* KVEntry */ typename ...ET>
    class GenericRegion {
        constexpr static size_t numberOfEntries = sizeof...(ET) + 1;
        constexpr static size_t maxSize = std::max(alignof(typename EH::type),
                                                   sizeof(typename EH::type)) * EH::dim;
        char data[numberOfEntries][maxSize];
    public:
        bool getData(size_t nthData, void* out, size_t len) {
            if (nthData >= numberOfEntries) [[unlikely]] { return false; }
            std::copy_n(data[nthData], std::min(len, maxSize), reinterpret_cast<char*>(out));
            return true;
        }
        bool setData(size_t nthData, const void* value, size_t len) {
            if (nthData >= numberOfEntries) [[unlikely]] { return false; }
            std::copy_n(reinterpret_cast<const char*>(value), std::min(len, maxSize), data[nthData]);
            return true;
        }
    };

    template<typename... R>
    class Regions {
        std::tuple<R...> regions;
        template<size_t I, typename OP>
        bool forData(OP&& op, size_t index) {
            size_t regionIdx = index >> 16;
            size_t nthData = index & 0xFFFF;
            if (I == regionIdx) { return op(std::get<I>(regions), nthData); }
            return false;
        }

        template<typename OP, size_t... Is>
        bool forData(std::index_sequence<Is...>, OP&& op, size_t index) {
            return (forData<Is>(std::forward<OP>(op), index) || ...);
        }

    public:
        bool getData(size_t index, void* out, size_t len) {
            auto op = [&](auto&& region, size_t nthData)
            { return region.getData(nthData, out, len); };
            return forData(std::make_index_sequence<sizeof...(R)>{}, op, index);
        }

        bool setData(size_t index, const void* value, size_t len) {
            auto op = [&](auto&& region, size_t nthData)
            { return region.setData(nthData, value, len); };
            return forData(std::make_index_sequence<sizeof...(R)>{}, op, index);
        }
    };

    template</* concepts::pair_const */ typename ...KeyWithId>
    struct Indexer {
        static constexpr size_t IndexSize = sizeof...(KeyWithId);
        size_t keyToId[IndexSize];
        std::bitset<IndexSize> mask;
        constexpr Indexer() {
            static_assert(((KeyWithId::first < IndexSize) && ...), "key is out of size");
            (void(keyToId[KeyWithId::first] = KeyWithId::second), ...);
        }
    };
    template<auto...> struct dump;

///////////////////////////////////////////////////////////////////////////////
// meta value list consteval meta programming
    consteval static auto group_entries(concepts::list auto es) {
        if constexpr (es.empty()) {
            return value_list<>;
        } else {
            constexpr auto e = es.head();
            constexpr auto group_result = es | partition([](auto entry) { return _v<(typename decltype(entry)::type() == typename decltype(e)::type())>; });
            return group_entries(group_result.second)
                   | prepend(group_result.first);
        }
    }
    constexpr static auto entry_groups = group_entries(entries);

    constexpr static auto regions_type = entry_groups
                                    | transform([](/* concepts::list */ auto group)
                                                  { return group | convert_to<GenericRegion>(); })
                                    | convert_to<Regions>()
                                    ;
//
    constexpr static auto indexer_type = (entry_groups
            | fold_left(pair<ValueConst<0>, TypeList<>>, [](/* concepts::pair_const */ auto group_list, /* concepts::list */ auto group_entries) {
                constexpr auto res = group_entries
                       | fold_left(pair<ValueConst<0>, TypeList<>>, [group_list]<typename E>(concepts::pair_const auto inner_group, TypeConst<E>) {
                           constexpr auto group_id = group_list.first;
                           constexpr auto inner_id = inner_group.first;
                           return pair<ValueConst<inner_id + 1>,
                                       decltype(inner_group.second | append(pair<ValueConst<E::key>, ValueConst<(group_id << 16 | inner_id)>>))>;
                        });
                return pair<ValueConst<group_list.first + 1>, decltype(concat(group_list.second, res.second))>;
            })).second
            | convert_to<Indexer>()
            ;

    get_typ<regions_type> regions;
    get_typ<indexer_type> indexer;
///////////////////////////////////////////////////////////////////////////////

public:
    bool getData(size_t key, void* out, size_t len = -1) {
        if (key >= entries.size() || ! indexer.mask[key]) { return false; }
        return regions.getData(indexer.keyToId[key], out, len);
    }
    bool setData(size_t key, const void* value, size_t len = -1) {
        if (key >= entries.size()) { return false; }
        return indexer.mask[key] =
                       regions.setData(indexer.keyToId[key], value, len);
    }
    void dumpGroupInfo() {
        printf("sizeof Datatable = %zu\n", sizeof(Datatable));
        printf("sizeof Region = %zu\n", sizeof(regions));
        printf("sizeof Indexer = %zu\n", sizeof(indexer));
        for (size_t k = 0; k < entries.size(); ++k) {
            printf("key = %d id = 0x%05x group = %d subgroup = %d\n", k,
                   indexer.keyToId[k],
                   indexer.keyToId[k] >> 16,
                   indexer.keyToId[k] & 0xFFFF);
        }
    }
};

///////////////////////////////////////////////////////////////////////////////

int main() {
    constexpr auto all_entries = type_list<
        Entry<0, int>,
        Entry<1, char>,
        Entry<2, char>,
        Entry<3, short>,
        Entry<4, char[10]>,
        Entry<5, char[10]>,
        Entry<6, int>
    >;

    Datatable<all_entries> datatbl;
    datatbl.dumpGroupInfo();

    {
        int expectedValue = 23;
        assert(! datatbl.getData(0, &expectedValue));
        assert(datatbl.setData(0, &expectedValue));
        int value = -1;
        assert(datatbl.getData(0, &value));
        assert(value == expectedValue);
    }

    {
        int expectedValue = 23;
        assert(! datatbl.getData(6, &expectedValue));
        assert(datatbl.setData(6, &expectedValue));
        int value = -1;
        assert(datatbl.getData(6, &value));
        assert(value == expectedValue);
    }

    {
        int invalid;
        assert(! datatbl.getData(7, &invalid));
        assert(! datatbl.setData(7, &invalid));
    }

    {
        std::string_view expectedValue = "hello";
        char value[10] {};
        assert(! datatbl.getData(4, value));
        assert(datatbl.setData(4, expectedValue.data(), expectedValue.length()));
        assert(datatbl.getData(4, value));

        assert(expectedValue == value);
    }
    return 0;
}