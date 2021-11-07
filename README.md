# meta-value-list
This library provides a bunch of consteval toolsets to do metaprogramming,
and provides the pipeline syntactic sugar, 
its experience is better than traditional template metaprogramming.

## value calculation
```
constexpr auto res = value_list<1,2,3,4,5,6,7,8,9,10>
        | transform([](auto x) { return x * x; })
        | filter([](auto x) { return x < 30; })
        | fold_left(0, [](auto acc, auto n) { return acc + n; })
        ;
static_assert(res == 55);
```

## type calculation
```cpp
constexpr auto vl = unique(value_list<_t<int>, _t<int>, _t<float>, _t<short>>);
STATIC_REQUIRE(vl == value_list<_t<int>, _t<float>, _t<short>>);
```

## More motivated examples
[examples](examples/README.md)

## Inspiration
- [Boost.hana](https://www.boost.org/doc/libs/1_61_0/libs/hana/doc/html/index.html)