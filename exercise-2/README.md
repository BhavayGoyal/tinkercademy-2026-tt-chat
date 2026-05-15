# Exercise 2

**Update this README with your answers to the questions below.**

## Sources of Information for Questions from Before

### Socket 
- https://man7.org/linux/man-pages/man2/socket.2.html - System call reference
  for creating communication endpoints
- Or type `man socket` in terminal
- https://man7.org/linux/man-pages/man7/socket.7.html - Socket interface 
  overview and protocol families
- Or type `man 7 socket` in terminal
- When would you want to use a `SOCK_RAW` stream?
  - You would use SOCK_RAW when you need to bypass the operating system's transport layer (TCP/UDP) and interact directly with lower-level protocols (like IP).

### TCP and IP Protocols
- [IPv4](https://www.rfc-editor.org/info/rfc791) - Internet Protocol 
  specification defining packet structure and routing
- [IPv6](https://www.rfc-editor.org/info/rfc8200) - Next-generation Internet 
  Protocol with expanded address space
- [TCP](https://datatracker.ietf.org/doc/html/rfc9293) - Transmission Control 
  Protocol providing reliable, ordered data delivery
    
### C++
- [C++23 ISO standard draft](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4950.pdf) - 
  Working draft of the C++ language specification
- Is the above the official C++23 spec? 
  - No, it is a working draft
- Where is the official C++23 spec?
  - The official standard is published by the International Organization for Standardization (ISO) and must be purchased from their official web store.
- Why was this link chosen instead?
  - The official ISO spec sits behind a paywall and is very expensive.
- Is this a helpful reference for learning C++?
  - No. The standard is written as a dense specification meant for compiler writers and language lawyers, not software developers.
- Can the various implementations of C++ compilers be different from the C++ standard?
  - Yes. Compilers might have incomplete support for the newest standards, contain bugs, or provide proprietary extensions that aren't in the official spec.
- What are the most widely used and most significant C++ compilers?
  - GCC, Clang, MSVC
- Where is the equivalent spec for C++26?
  - ISO C++ committee's (WG21) website at open-std.org

- Where do you find the spec for the HTTP protocol?
  - In RFCs (Request for Comments) managed by IETF
- What about HTTPS? Is there a spec for that protocol?
  - HTTPS doesn't have a standalone protocol spec. It is simply HTTP running over a secure TLS (Transport Layer Security) connection.

## Introduction to C++ and Sockets Programming (TODO)

- Read the code in `src/`
- Are there any bugs in this code? 
- What can you do to identify if there are bugs in the code?

## Refactoring: Extract Function

- What is different in this code compared to exercise-1?
  - The code has been modularized. Instead of having one massive procedural block inside main(), the logic is broken out into smaller, single-responsibility functions (Extract Function refactoring).
- Is this code better or worse than exercise-1?
  - Much better, more readable, resuable and easier to test or modify.
- What are the tradeoffs compared to exercise-1?
  - Higher line count and the microscopic overhead of function calls. However, modern compilers will likely inline these functions anyway, negating the overhead.
- Are you able to spot any mistakes or inconsistencies in the changes?
  - (TODO)
  
## Thinking About Performance

- Does writing code this way have any impact on performance?
  - In practice, no. While function calls do push and pop stack frames, modern optimizing compilers will inline these small helper functions, making the machine code identical to the un-refactored version.
- What do we mean when we say performance?
  - Performance typically refers to latency, how many requests can be handled per second, CPU utilization, and memory used.
- How do we measure performance in a program?
  - Through profiling tools life perf or using benchmarking frameworks (like Google Benchmark), or testing the network program under load using tools like Apache Bench (ab).

## Play with Git (TODO)

- There isn't necessarily a single correct answer for how to abstract the 
  code from exercise-1 into functions
- Try different ways to refactor the code from exercise-1 to make it more
  readable.
- Make sure to commit each change as small and self-contained commit
- This will make it easier to revert your code if you need to
- What is `git tag`? How is `git tag` different from `git branch`?
- How can you use `git tag` and `git branch` to make programming easier and
  more fun?

## Learn Basics of Debugging in Your IDE

- How do you enable debug mode in your IDE?
  - Press F5 or click the "Run and Debug", then select my C++ environment (like GDB or LLDB) to start the session.
- In debug mode, how do you add a watch?
  - Click + and type variable name (or &var)
- In debug mode, how do you add a breakpoint?
  - Press F9 or click on to left of line number
- In debug mode, how do you step through code?
  - "Step Over" (F10), "Step Into" (F11), or "Step Out" (Shift+F11) or use the floating widget for the same

### Memory Management and Debug Mode in Your IDE

- How do you see the memory layout of a `std::string` from your IDE debug mode?
  - Expand the variable in the Variables panel to see its heap pointer, size, and capacity, or right-click it and select "View Memory" to see the raw hex bytes.
- How do you see the memory layout of a struct from your IDE debug mode?
  - Expand the struct in the Variables panel to view its individual members sequentially, or right-click the struct and select "View Memory" to inspect its contiguous block of memory and padding in the hex viewer.