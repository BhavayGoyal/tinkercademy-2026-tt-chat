# Exercise 4

**Update this README with your answers to the questions below.**

## Learning Multi-File C++ Projects

- Move code that can be shared between `tcp_echo_server.cpp` and 
  `tcp_echo_client.cpp` to separate `.h` and `.cpp` files - **DONE**
- How would you compile from the command line?
  - g++ -o tcp_echo_server tcp_echo_server.cpp utils.cpp
  - g++ -o tcp_echo_client tcp_echo_client.cpp utils.cpp
- How would you compile using make?
  - Just write the makefile, and run make
- How would you compile using VS Code?
  - We can create a tasks.json file in vs code where we can setup tasks for compiling the server and the client files. We can run them by using either keyboard shortcuts or using command palette.

### Compiling vs Linking

- What is the difference between compiling and linking in C++?
  - Compiling means converting a .cpp file into assembly instructions and then into machine-readable object files (.o). Linking, on the other hand, is combining these object files (and any external libraries) into a final, runnable executable or library.
- What is the difference between creating an executable and creating a 
  library?
  - An executable is like a stand-alone program which can run directly
  - A library is a collection of some already compiled code that can be reused by other programs. (They can be static (linked at compile time) or dynamic (linked at runtime))
  - An executable usually contains a main file, while library usually does not
- How do you compile a library, and then use that library to compile an
  executable?
  - For a static library:
    - Compile the source into an object file: g++ -c utils.cc -o utils.o
    - Package the object file into a static library archive: ar rcs libutils.a utils.o
    - Compile your executable and link the library: g++ main.cc -L. -lutils -o my_program (Note: -L. tells the compiler to look in the current directory for libraries, and -lutils tells it to link the libutils.a file).
  - For a dynamic library:
    - Compile object: g++ -c -fPIC utils.cc -o utils.o
    - Build shared library: g++ -shared -o libutils.so utils.o
    - Link to program: g++ main.cc -L. -lutils -o app
    - Run program: LD_LIBRARY_PATH=. ./app

### Reminder 
[Quickstart tutorial to make](https://makefiletutorial.com/) - Learn make 
fundamentals with practical examples and common patterns.

## Experiments in Performance

- Is it better to have many small files spread across many directories, or
  a few large files across fewer directories?
  - There is no direct answer to this, it really depends upon the size and complexity of your project. Having small files can improve the maintainability of your project.
  - Another advantage of having many small files is that your compile time can be decreased if you're using make and only a few files have changed. (Only the changed files need to be compiled again).
- Is there a difference in compilation time between the two?
  - If it's a fresh make or fresh compilation of the project, there won't be a huge difference in compilation time. But as stated above, if you're using make and only a few files have changed, having many small files would be faster as only changed files need to be recompiled and not all the files.
- How can you assess performance other than compilation speed?
  - Other than compilation speed, we can assess the runtime speed and the memory usage or executable size. Usually, having a static library increases the size of the executable significantly. Using dynamic libraries can reduce the size of the executable but it can slightly introduce some overhead time due to dynamic linking.