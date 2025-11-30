## Just a brief compilation reminder

To compile projects, you may want to use Makefiles/CMakeLists or xmake.
For AoC and quick one-off scripts just compile directly with g++. Example:

```bash
    g++-14 hello.cpp -Wall -pedantic -std=c++23 -o bin/hello
    ./bin/hello
``` 

- The above specifies the g++ version 14 compiler, enabling C++ version 23 features.
- The -std argument specifies the C++ standard to use.
- The -Wall and -pedantic flags enable all compiler warnings and enforce strict compliance with the C++ standard, respectively.

Make sure to create the `bin` directory beforehand to avoid errors when specifying the output path, e.g.

```bash
    mkdir -p bin
    g++-14 hello.cpp -Wall -pedantic -std=c++23 -o bin/hello && ./bin/hello
```
