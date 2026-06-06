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

## Introduction to Compiler Explorer (TODO)

- Try out the old `create_socket()` and the new `check_error()` and 
  `create_socket()` in [Compiler Explorer](https://godbolt.org) - Interactive 
  tool for exploring how C++ code compiles to assembly
- What is happening here?
- Can you think of any different approaches to this problem?
- How can you modify your Makefile to generate assembly code instead of
  compiled code?
- **Note**: You can save the generated assembly from Compiler Explorer
- **Bonus**: Can you view assembly code using your IDE?
- **Bonus**: How do you see the assembly when you step through each line in
  debugging mode from your IDE?
- [x86 assembly reference](http://ref.x86asm.net/) - Comprehensive reference 
  for x86 assembly language instructions and syntax

## More About Memory Management (TODO)

- Make sure you have `-fsanitize=address` in both your `CXX_FLAGS` and 
  `LD_FLAGS` in your Makefile - **DONE**
- What do `-fsanitize=address`, `CXX_FLAGS` and `LD_FLAGS` mean?
  - `-fsanitize=address`: This enables address sanitizer which is a memory error detector.
  - `CXXFLAGS`: Compiler flags used by `g++` during the compilation of source files into object files.
  - `LDFLAGS`: Linker flags used when stitching object files together into the final executable.
- With the new tool of the Compiler Explorer, and keeping in mind what you 
  have learned about how to use debug mode
- What happens when you look at a `std::string` using the above methods?
- Where is the text in your `std::string`?
- What is `std::optional`?
- How do you find out the memory layout of a `std::optional`?
- Read https://en.cppreference.com/w/cpp/memory#Smart_pointers - Guide to 
  modern C++ memory management using smart pointers
- Which pointer types are the most important to know about?
- Which smart pointer should you use by default if you can?
- Does changing your optimization level in `CXXFLAGS` from `-O0` to `-O3` have
  any impact on the answers to any of the above questions?

## More Thinking About Performance

- After your experiments with Compiler Explorer, do you have any updates for your answers in exercise-2? (TODO)

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