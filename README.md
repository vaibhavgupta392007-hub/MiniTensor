# MiniTensor

A simple C++ tensor library built from scratch.

MiniTensor is a project that implements basic tensor operations using C++. It supports multidimensional tensors and common mathematical operations.

## Features

- Create tensors with different shapes.
- Access and modify tensor elements.
- Add and subtract tensors.
- Perform element-wise multiplication.
- Perform matrix multiplication.
- Reshape tensors.
- Handle invalid operations using exceptions.
- Build and install the library using CMake.

## Project Structure

```text
MiniTensor/
├── cmake/
├── examples/
├── include/
├── src/
├── tests/
└── CMakeLists.txt
```

## Requirements

- C++17
- CMake 3.16 or later
- GCC, Clang, or MSVC

## Build and Run

Clone the repository:

```bash
git clone https://github.com/vaibhavgupta392007-hub/MiniTensor.git
cd MiniTensor
```

Build the project:

```bash
cmake -S . -B build
cmake --build build
```

Run the demo:

```bash
./build/tensor_demo
```

Run tests:

```bash
ctest --test-dir build --output-on-failure
```

## Example

```cpp
#include <iostream>
#include <tensor.hpp>

int main() {
    Tensor a({1, 2, 3, 4, 5, 6}, {2, 3});
    Tensor b({7, 8, 9, 10, 11, 12}, {3, 2});

    Tensor result = a.matmul(b);

    result.display();

    return 0;
}
```

Output:

```text
Shape: 2x2
Data: 58 64 139 154
```

## Author

**Vaibhav Gupta**

[GitHub Profile](https://github.com/vaibhavgupta392007-hub)
