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
  - Yes.
    - sockaddr_in address; is not being initialized to zero which can leave garbage values in memory.
    - send() return values is unchecked and we should deal with it. TCP can also do partial sends so we should loop untill all bytes are sent or use send_all()
    - read() is called once only which assumes that it'll read full message which is incorrect as TCP can send partially. To fix this we should either loop until full message is recieved or use read_all()
    - ...
- What can you do to identify if there are bugs in the code?
  - use debugging tools like gdb, run with -fsanitize=address, undefined. Read compiler warning carefully and use -Wall, -Wextra to get proper compiler warnings. When unsure about the function arguments etc, make sure to refer to man guides or some resource to verify otherwise you can very easily make bugs. Also check if all the return values of calls like socket(), send(), recv() etc. are handled/dealt.

## Refactoring: Extract Function

- What is different in this code compared to exercise-1?
  - The code has been modularized. Instead of having one massive procedural block inside main(), the logic is broken out into smaller, single-responsibility functions (Extract Function refactoring).
- Is this code better or worse than exercise-1?
  - Much better, more readable, resuable and easier to test or modify.
- What are the tradeoffs compared to exercise-1?
  - Higher line count and the microscopic overhead of function calls. However, modern compilers will likely inline these functions anyway, negating the overhead.
- Are you able to spot any mistakes or inconsistencies in the changes?
  - ...
  
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
  - git tag marks a specific commit with a special permanent label (eg. v1.0). It is usually used to mark important commits where everything was working or to mark specific versions. It does not move.
  - git branch creates a new pointer which can be moved forward by commits independently of the main branch pointer. this new branch can be later merged with the main branch. This is used to impliment different features independently which can be later merged into one project.
- How can you use `git tag` and `git branch` to make programming easier and more fun?
  - tags are useful for stable milestones so we can always go back and compare our current version with the previous version. branches are useful when we want to work on different features parallely which are different from the main branch.

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