#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>

struct MyStruct {
  int a;
  double b;
  char c;
  std::vector<int> d;
  std::string e;
};

int main() {
    MyStruct my_struct {
        .a = 42,
        .b = 3.14,
        .c = 'x',
        .d = {1, 2, 3, 4, 5},
        .e = "Hello, World!"
    };

    std::cout << "Size of MyStruct: " << sizeof(MyStruct) << " bytes\n";
    int8_t* ptr = reinterpret_cast<int8_t*>(&my_struct);
    std::cout << "Memory layout of MyStruct:\n";
    for (size_t i = 0; i < sizeof(MyStruct); ++i) {
        std::cout << "Byte " << i << ": " << static_cast<char>(ptr[i]) << "\n";
    }
}