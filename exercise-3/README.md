# Exercise 3

**Update this README with your answers to the questions below.**

## Re-using Code

- Read the code in `src/tcp_echo_client.cc` - **DONE**
- A new function `check_error()` has been created and `create_socket()` from 
  exercise-2 has been refactored to make use of it - **Yes, right**
- What are the benefits of writing code in this way? - **DONE**
  - It makes the code much more readable by removing repetitive `if (condition < 0) { ... }` blocks.
- Are there any costs to writing code like this? - **DONE**
  - Minor perfomance cost due to function calls (tho the compiler would mostly inline these functions so even that might not be true)
- Apply `check_error` to all the code in `src/` - **DONE**

## Introduction to Compiler Explorer

- Try out the old `create_socket()` and the new `check_error()` and 
  `create_socket()` in [Compiler Explorer](https://godbolt.org) - Interactive 
  tool for exploring how C++ code compiles to assembly

**Old `create_socket()` Assembly:**
```assembly
.LC0:
        .string "Socket creation"
"create_socket()":
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16
        mov     edx, 0
        mov     esi, 1
        mov     edi, 2
        call    "socket"
        mov     DWORD PTR [rbp-4], eax
        cmp     DWORD PTR [rbp-4], 0
        jns     .L2
        mov     esi, OFFSET FLAT:.LC0
        mov     edi, OFFSET FLAT:"std::cerr"
        call    "std::basic_ostream<char, std::char_traits<char>>& std::operator<<<std::char_traits<char>>(std::basic_ostream<char, std::char_traits<char>>&, char const*)"
        mov     edi, 1
        call    "exit"
.L2:
        mov     eax, DWORD PTR [rbp-4]
        leave
        ret
```

**New `check_error()` and `create_socket()` Assembly:**
```assembly
.LC0:
        .string "\n"
"check_error(bool, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> const&)":
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16
        mov     BYTE PTR [rbp-1], dil
        mov     QWORD PTR [rbp-16], rsi
        cmp     BYTE PTR [rbp-1], 0
        je      .L15
        mov     rax, QWORD PTR [rbp-16]
        mov     rsi, rax
        mov     edi, OFFSET FLAT:"std::cerr"
        call    "std::basic_ostream<char, std::char_traits<char>>& std::operator<<<char, std::char_traits<char>, std::allocator<char>>(std::basic_ostream<char, std::char_traits<char>>&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> const&)"
        mov     esi, OFFSET FLAT:.LC0
        mov     rdi, rax
        call    "std::basic_ostream<char, std::char_traits<char>>& std::operator<<<std::char_traits<char>>(std::basic_ostream<char, std::char_traits<char>>&, char const*)"
        mov     edi, 1
        call    "exit"
.L15:
        nop
        leave
        ret
.LC1:
        .string "Socket creation"
"create_socket()":
        push    rbp
        mov     rbp, rsp
        push    rbx
        sub     rsp, 72
        mov     edx, 0
        mov     esi, 1
        mov     edi, 2
        call    "socket"
        mov     DWORD PTR [rbp-20], eax
        lea     rax, [rbp-33]
        mov     QWORD PTR [rbp-32], rax
        nop
        nop
        lea     rdx, [rbp-33]
        lea     rax, [rbp-80]
        mov     esi, OFFSET FLAT:.LC1
        mov     rdi, rax
        call    "std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>::basic_string<std::allocator<char>>(char const*, std::allocator<char> const&)"
        mov     eax, DWORD PTR [rbp-20]
        shr     eax, 31
        lea     rdx, [rbp-80]
        movzx   eax, al
        mov     rsi, rdx
        mov     edi, eax
        call    "check_error(bool, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> const&)"
        lea     rax, [rbp-80]
        mov     rdi, rax
        call    "std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>::~basic_string()"
        nop
        mov     eax, DWORD PTR [rbp-20]
        jmp     .L23
```

- What is happening here?
  - In the old version, error handling was entirely inline within `create_socket`. In the new version, this logic has been refactored and delegated to a separate `check_error` function. The assembly reflects this by introducing the mechanical overhead of a function call including argument preparation and stack frame management that wasn't necessary when the logic was monolithic.
- Can you think of any different approaches to this problem?
  - **Exceptions:** Using `throw std::runtime_error(msg)` is one possible way which we could have used instead of this.
- How can you modify your Makefile to generate assembly code instead of
  compiled code?
  - You can add a target that uses the `-S` flag with `g++`. For example: `g++ -S src/tcp_echo_client.cc -o build/tcp_echo_client.s`.
- **Note**: You can save the generated assembly from Compiler Explorer
- **Bonus**: Can you view assembly code using your IDE?
  - Yes, in VS code, while we're in debugging mode we can right click on the source code and select "Open disassembly view" to view the assembly code.
- **Bonus**: How do you see the assembly when you step through each line in debugging mode from your IDE?
  - In VS Code we can use the "Open Disassembly View" option from the editor's context menu while we are at the breakpoint.
- [x86 assembly reference](http://ref.x86asm.net/) - Comprehensive reference 
  for x86 assembly language instructions and syntax

## More About Memory Management

- Make sure you have `-fsanitize=address` in both your `CXX_FLAGS` and 
  `LD_FLAGS` in your Makefile - **DONE**
- What do `-fsanitize=address`, `CXX_FLAGS` and `LD_FLAGS` mean?
  - `-fsanitize=address`: This enables address sanitizer which is a memory error detector.
  - `CXXFLAGS`: Compiler flags used by `g++` during the compilation of source files into object files.
  - `LDFLAGS`: Linker flags used when stitching object files together into the final executable.
- With the new tool of the Compiler Explorer, and keeping in mind what you 
  have learned about how to use debug mode
- What happens when you look at a `std::string` using the above methods?
  - A `std::string` object is instantiated from a string literal. In the assembly, we see a call to `std::__cxx11::basic_string<char>::basic_string(char const*)`. For a string like "Socket creation error\n" (22 characters), the object triggers a heap allocation because it exceeds the capacity of the small-string optimization (SSO) buffer.
- Where is the text in your `std::string`?
  - It depends on the length:
    - **Short strings (typically <= 15 chars):** The text is stored directly inside the `std::string` object on the stack (using SSO).
    - **Long strings (like "Socket creation error\n"):** The text is allocated on the heap, and the `std::string` object on the stack merely holds a pointer to that heap memory.
- What is `std::optional`?
  - `std::optional` is a wrapper that may or may not contain a value of a specific type. It provides a type-safe way to represent "empty" or "null" states without the complexity of raw pointers or the ambiguity of "magic" return values (like -1).
- How do you find out the memory layout of a `std::optional`?
  - We can discover the layout by using `sizeof` or by inspecting the assembly/debugger. Mechanically, `std::optional` contains two main parts: a boolean flag (to track if it holds a value) and a storage area (the "payload") big enough to hold the actual value.

- Read https://en.cppreference.com/w/cpp/memory#Smart_pointers - Guide to 
  modern C++ memory management using smart pointers
- Which pointer types are the most important to know about?
  - `std::unique_ptr` (sole ownership), `std::shared_ptr` (shared ownership), and `std::weak_ptr` (non-owning reference to shared object).
- Which smart pointer should you use by default if you can?
  - **`std::unique_ptr`**. It has zero overhead compared to a raw pointer and clearly defines ownership, making the code safer and easier to reason about.
- Does changing your optimization level in `CXXFLAGS` from `-O0` to `-O3` have
  any impact on the answers to any of the above questions?
  - Yes, significantly. While the **memory layout** (size and structure) of `std::string` and `std::optional` remains the same to maintain ABI compatibility, the **assembly** changes drastically. At `-O3`, the compiler will likely **inline** `check_error` and `create_socket`, potentially optimizing away the heap allocation for the string if it can prove the error path is never taken or if the string isn't truly needed. It also uses advanced CPU instructions (like SIMD/AVX) for data movement.

## More Thinking About Performance

- After your experiments with Compiler Explorer, do you have any updates for your answers in exercise-2?
  - At -O0, small helper functions such as create_socket() and create_address() are compiled as separate function calls, complete with stack frame setup and teardown. At -O3, the compiler typically inlines these functions, eliminating the call overhead. As a result, the decomposition used in exercise-2 primarily improves readability and maintainability, since the compiler can optimize away the abstraction at higher optimization levels.

### Bonus: Do Not Watch Now 

- [More about Compiler Explorer](https://www.youtube.com/watch?v=bSkpMdDe4g4) - 
  Deep dive into compiler optimization and assembly analysis
  - Create a struct which contain many different data types - **DONE**
  - Look at the memory layout in the debugger - **DONE**
  - Create a `char` or `uint8_t` pointer to the beginning of the struct, 
    iterate to the end of the struct, printing out the value of each byte in hexadecimal - **DONE**
  - Try accessing different parts of the struct and see in compiler explorer what the assembly looks like - **DONE**
  - What happens if you iterate the pointer to outside the bounds of your array? 
    - It causes undefined behaviour. (UB)
  - Let's say your struct is called `Foo` - **OK**
  - What is the difference between `std::vector<Foo>` and `std::vector<Foo*>`?
    - std::vector<Foo> is a vector of Foo objects, while std::vector<Foo*> is a vector of pointers to Foo object where each pointer can point to a Foo object.
  - What are the tradeoffs between using `std::vector<Foo>` vs 
    `std::vector<Foo*>`? 
    - vector<Foo>
      - Better cache locality as everything in continuous memory
      - Simple memory management (as vector will handle the creation and destruction of objects)
      - Polymorphism is not possible (as they are objects direclty)
      - Reallocation cost is high, as all the objects might need to be shifted to a new location
    - vector<Foo*>
      - Worse cache locality as real objects can be anywhere in the memory
      - If objects are created using new/malloc, need manual memory deletion
      - Polymorphism is possible as they can point to derived classes
      - Low realocaion cost as only pointers need to be reallocated
  - Give an example where `std::vector<Foo>` is a better choice than 
    `std::vector<Foo*>`
      - vector<Foo> is better than vector<Foo*> when the struct object is small and it does not need dynamic memory allocation or polymorphism. 
      - If Foo is a large struct or need runtime polymorphism it might be a better choice to use vector<Foo*>
  - Give another example where the opposite is true
    - Done above already
  - Can you create `std::vector<Foo&>`? 
    - No, you cannot create std::vector<Foo&> because C++ does not allow containers of references
  - Can you create `std::vector<std::optional<Foo>>`?
    - Yes, it is allowed (so here each element can either be a foo object, or be empty)
  - What happens if your struct contains another struct?
    - The inner struct will simply be a member of outer struct
  - What is the difference between a struct and a class?
    - They are pretty much same, the only main difference is that a struct all the members are public by default while in a class all members are private by default.