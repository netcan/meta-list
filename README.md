# meta-value-list
This library provides a bunch of consteval toolsets to do metaprogramming,
and provides the pipeline syntactic sugar for function combination, 
its experience is better than traditional template metaprogramming.

All PRs are welcome.
## value calculation
```cpp
constexpr auto res = value_list<1,2,3,4,5,6,7,8,9,10>
                   | transform([](auto x) { return _v<x * x>; })
                   | filter([](auto x) { return _v<x < 30>; })
                   | fold_left(_v<0>, [](auto acc, auto n) { return _v<acc + n>; })
                   ;
static_assert(res == 55);
```

## type calculation
```cpp
constexpr auto result = type_list<int, char, long, char, short, float, double>
                      | filter([]<typename T>(TypeConst<T>) { return _v<sizeof(T) < 4>; })
                      | transform([]<typename T>(TypeConst<T>) { return _t<std::add_pointer_t<T>>; })
                      | unique()
                      | convert_to<std::variant>()
                      ;
static_assert(result == _t<std::variant<char*, short*>>);
```

## Tested Compiler
- gcc-11.2 **Worked**
- msvc-19.30.30705 VS17.0 **Worked**
- clang-14 **Crashed**

## More motivated examples
[examples](examples/README.md)

## Inspiration
- [Boost.hana](https://www.boost.org/doc/libs/1_61_0/libs/hana/doc/html/index.html)
- [range-v3](https://github.com/ericniebler/range-v3)
- [holo](https://github.com/godsme/holo)
