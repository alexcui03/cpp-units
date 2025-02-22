# C++ Units

The units and demensions header-only library for C++.

C++ 20 is required.

Example:
```cpp
#include "../cpp-units/cpp-units.hpp"

using namespace cpp_units::literals;

int main() {
    constexpr auto v1 = 1_m;
    constexpr auto v2 = 20_mm;
    constexpr auto v3 = v1 - v2; // 980 mm
    constexpr auto v4 = v1 / v2; // 0
    constexpr auto v5 = v1 * v2; // 20 m*mm

    return 0;
}
```

## Tests

```bash
cd /path/to/repo
mkdir build
cd build
cmake ..
cmake --build .
ctest .
```
