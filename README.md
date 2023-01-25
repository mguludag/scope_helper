# scope_helper
A RAII style helper for invoking functions begin and end of scope

## Usage

```C++
#include <iostream>
#include "scope_helper.hpp"

int main()
{
    auto sh{make_scope_helper([]{ std::cout << "begin main()\n"; }, []{ std::cout << "end main()\n"; })};
    //...
    //...
    //...
}
```
