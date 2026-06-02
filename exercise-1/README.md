# Exercise 1

## How to Approach This Exercise

Before you scroll down to the questions, try this:

1. **Don't peek at the questions yet.** Pretend you've just been handed a brief
   that says: *"Learn these topics as deeply as you can — g++ CLI, Make, Git,
   sockets, and memory management in C++."* That's the whole assignment.
   How would you go about it? What would you read, what would you try, in what
   order, and how would you know when you've understood something well enough?
   Write that plan down in this README, then actually follow it.

   **My plan (3 phases):**
   - **Phase 1: Bird's-eye view first.** I will build a broad understanding of
     each topic (`g++`, `make`, Git, sockets, memory management): what it is,
     why it exists, and how it is used in industry. My goal here is context
     before depth. I may use AI tools like Claude or Gemini to quickly map the
     landscape.
   - **Phase 2: Primary-source deep dive.** I will study references/textbooks 
     and focus first on what I do not know. I will start with `g++`
     CLI and `make` (man pages + practical docs), then move to sockets in C++
     (e.g., Beej's Guide + man pages). Since I already know some Git and
     memory-management basics, I will cover those later.
   - **Phase 3: Apply on the assignment files.** I will open the provided C++
     source files and work through the README questions by solving them
     directly from my understanding and notes.
   - How would I know if I have understood something well enough - I know I truly understand something when I can explain the concept to others who does not know the concept clearly.

2. **Now go through the questions below and answer them like you're an LLM.**
   No live Googling, no Stack Overflow, no asking ChatGPT mid-question. You may
   refer to notes *you* took during step 1 — that's your context window. Answer
   from what you've internalised.

3. **Reflect on how it went.** Honestly:
   - Did your self-directed learning actually prepare you for the questions, or
     did you over-study things that never came up?
   - Which questions blindsided you? Why — was the topic missing from your
     plan, or did you skim past it?
   - Map your experience onto the *known knowns / known unknowns / unknown
     unknowns* idea. The interesting category is usually the last one: things
     you didn't even realise you should have learned. What were yours, and how
     could a better learning plan have surfaced them earlier?

       - Wasted time in thinking about project, Even used AI to understand concepts and learn concepts, I don't really feel I've read even close to suffice (TODO), known-unknown(other kinds of builds that are useful)

The point of this exercise isn't to get the questions "right" — it's to notice
the gap between how you *think* you learn and how you actually do, so you can
close it.

## Learning How to Learn

- Answer the following questions in this file and commit and push your changes.
- Bonus sections are more difficult and optional.
- How can you find the information required to complete these tasks?
  - The most reilable way is to consult the official documentation, and read tutorials or technical books (For ex. Beej's guide on networking etc.)
- How can you tell if the source of your information is good?
  - It's highly regarded in the community (Having high citations might be helpful)
  - Maintained properly by the creators
  - It's up-to-date and provides a good context
- How would you define "good" in this situation?
  - Given that I do not have a lot of time and need to study multiple topics, a “good” source is one that is:
    - Accurate, clear, updated and trusted by experienced developers
    - Focused on practial understanding instead of unnecessary theory
    - Efficient to learn from

## Learn Basics of g++ CLI

- Compile the TCP client and server using `g++` from command line.
  - Client:
    g++ -std=c++20 src/tcp_echo_client.cc -o build/client
  - Server:
    g++ -std=c++20 src/tcp_echo_server.cc -o build/server
- What are the most important command line arguments to learn for `g++`?
  - -o (output path), -c (only compiles, good to view assembly code in .o files), -g (generates debug information), -O(optimization level), -W(-Wall, -Wextra, -Werror), -std=c++17 (to specify c++ version to use)
- What is the difference between debug vs release versions?
  - A debug version does not apply optimizations and adds debugging symbols, while release version applies a lot of optimizations to make code as fast as possible
- What are the tradeoffs between debug and release versions?
  - Debug -: Slower code and larger binary file but allows us to step through the code line-by-line and inspect variables correctly
  - Release -: Much faster code and smaller binary feel but really difficult to debug the code
- What arguments would you use in a debug build?
  - g++ -g -O0 -Wall -std=c++17
- What about for release?
  - g++ -O3 -DNDEBUG -Wall -Wextra -std=c++17 (DNDEBUG is to remove assert statements, also O2 is used for optimization number)
- What other kinds of build types are useful?
  - -Os is a build type which optimizes it for size. I don't remember any other build types

## Learn Basics of Make

- Create a Makefile that will speed up the process.
- [Quickstart tutorial to make](https://makefiletutorial.com/) - Learn make fundamentals with practical examples and common patterns.
- How else can you learn about make?
  - man make/info make or searching the web for tutorials is a good way to start with, besides that looking at make files of other online open-source projects can really help in learning a lot about make.
- How can you tell if the resource you are using is correct?
  - Start by seeing the reliability of source (good sources usually have references to source materials). Also cross-referring what you're reading with official documentations can be really helpful and avoids misinformation. I also many times try clearing things up using AI tools if I have any doubts and it's mostly correct as it has been trained on a lot of text including official documentations.
- Create a makefile such that when you run `make` with no arguments, it will:
  - Create `build/` directory if it does not exist
  - Create executables **client** and **server** in `build/`, if needed
  - How does make know when it needs to rebuild the executables?
    - Make uses timestamps of files to know if something needs to be rebuilt or not. So if the target executable is dependent on some dependency file, it compares the last modified timestamps of both files and rebuild the target file if dependency file is newer. Otherwise it skips rebuilding which helps make build faster.
  - Change your Makefile such that `make clean` will remove `build/` and all
    its contents
- What are the most important command line arguments to learn for make?
  - make -j: Allow parallel build for faster builds
  - make -n: shows what files make will execute but does not execute them, good for debugging make files
  - make -b: Rebuild everything, regardless of timestamps
  - make -c dir: to run make file in some other directory 
  - make -d: prints verbose debugging info
- What are the most important directives to learn about in Makefile?
  - Automatic: 
    - $@: The name of the target being generated
    - $<: The first prerequisite (usually the source file)
    - $^: All prerequisites (useful for linking multiple object files)
  - Variable assignment: = (lazy assignment), := (immediate assignment), ?= (assign if defined)
  - .PHONY - This declares non-file targets
- What are the most important commands to implement in your Makefile?
  - all - Builds the main project/program
  - clean - Removes generated files like executables and object files
  - test - Runs the project's test suite to verify correctness
  - install - Copies the built program/files to system or user install locations
  - format - Automatically formats source code using a formatter tool
- Which ones are essential, which ones are nice to haves?
  - essential: all, clean
  - nice to have: test, format, install

## Learn Basics of Git

- Read through the code in `src/` - Done
- Answer any `#Questions` as a comment - Done
- Commit and push your changes to git - Done
- Each commit should be responding to a single task or question - Done
- Why is it important to keep your commit to a single task or question?
  - Small commits make it easier to review code, understand the project's history and roll back changes. If a commit contained both new features and bugs than reverting it remove all of it at once removing the hardly implimented features so it's better to keep commits to a single task or question.
- Is it better to have a lot of very small commits, or one big commit when 
  everything is working?
  - Lots of small commits are still better because even if everything seems to work in a big commit you might have missed some small mistakes which becomes hard to be reverted. 
- What are the most important commands to know in git?
  - clone, add, commit, push, pull, status, log, diff, branch, tag

## Introduction to Sockets

- Read the code in `src/tcp-echo-client.cc` and add a way to change the message sent using command line arguments - Done
- **Example**: `./client "hello message from the command prompt"` should send `"hello message from the command prompt"` to the server - Done
- Commit your changes into git - Done
- What do all these headers do?
  - arpa/inet.h: address conversion related functions like inet_pton, inet_ntop
  - iostream: stdio related stuff, like cin, cout etc.
  - netinet/in.h: provides protocol related structs and constants
  - string: offers std::string (which we already discussed in other sections)
  - sys/socket.h: provides the core socket functionality like socket, connect, bind etc.
  - sys/types.h: defines types which are related to systems
  - unistd.h: read, close and other posix os apis
- How do you find out which part of the below code comes from which header?
  - use man pages, like doing man connect will tell that it requires sys/socket.h
- How do you change the code so that you are sending messages to servers other than localhost?
  - just change kServerAddress from "127.0.0.1" to the required target server's ip address (which can be taken as input or sys args)
- How do you change the code to send to a IPv6 address instead of IPv4?
  - Change AF_INET to AF_INET6, struct sockaddr_in to struct sockaddr_in6, sin_addr to sin6_addr, sin_port to sin6_port
- **Bonus**: How do you change the client code to connect by hostname instead of IP address?
  - we can use getaddrinfo() function which resolves the DNS and returns a linkedlist of addrinfo structs 
  which we can iterate through and pass to connect()

## Introduction to Memory Management
- What is happening in line 26 of `tcp-echo-client.cc`? 
  `if (inet_pton(AF_INET, kServerAddress.c_str(), &address.sin_addr) <= 0) {`
  - inet_pton is 'internet presentation to networking' which converts an IP address in numbers and dots notation into either a struct in_addr or a struct in6_addr so the socket API can use it.
- What is happening in line 31 of `tcp-echo-client.cc`?
  `if (connect(my_sock, (sockaddr *)&address, sizeof(address)) < 0) {`
  - This line attempts to connect the client socket (my_sock) and the server specified by the address by establishing a TCP connection. 
- What is the difference between a pointer and a reference?
  - A pointer is a variable that holds memory address. 
    - It can be Null
    - It can be reassigned to point to some other variable
    - Required referencing using * or ->
  - A reference is an alias to an existing variable. 
    - It can't be Null, must be initialized upon creation
    - Can't be used to refer to some other variable
    - Does not need any referencing, can be used like a normal variable
- When is it better to use a pointer?
  - When you need to dynamically allocate memory on the heap or when the value can be NULL
- When is it better to use a reference?
  - When passing parameters to functions to avoid copying large objects and you know that object exists (because it can't be NULL)
- What is the difference between `std::string` and a C-style string?
  - std::string is a C++ class that manages memory automatically along with lots of useful string functions.
  - A C-style string is a char* or const char* array of characters ending with '\0'.
- What type is a C-style string?
  - It is represented as a char* or const char* pointing to the first character of the array.
- What happens when you iterate a pointer?
  - Pointer airthmetic occurs. If we add 1 to the pointer, the memory address it holds increase by the size of data type it holds. Like it it's holding an integer (4 bytes) doing ptr++ will increase the memory address by 4 bytes.
- What are the most important safety tips to know when using pointers?
  - Be extremely careful with dangling pointers
  - Always initialize the ptrs, and always delete it when allocated on heap
  - never double delete a ptr on heap
  - Check if ptr is nullptr before dereferencing it

## Learn Basics of Creating a C++ Project in Your IDE

- How do you compile and run your project in your IDE?
  - So when I do competitive programming in sublime I've a build file which does the work and I compile it using shift+f10 (custom command)
  - In VS code if it's single file using g++ commands and if their are multiple files then by creating a make file (So far I used to use AI tools to make the make file, but now as I'm learning about make I'll also understand what and how make file is doing and will write them myself)

## Improving Interactions with LLMs

- What is the most authoritative source of information about `socket()` from `<sys/socket.h>`?
  - POSIX / Single UNIX Specification and the man pages
- What is the most authoritative source of information about the TCP and IP protocols?
  - Requests for Comments (RFC) documents by Internet Engineering Task Force (IETF)
- What is the most authoritative source of information about the C++ programming language?
  - ISO/IEC C++ Standard document
  - cppreference.com (considered day-to-day gold reference)
- What information can you find about using Markdown when structuring prompts  to LLMs?
  - Structuring prompts with markdown helps us in getting better responses as the LLM is able to parse our intent much more accurately. That is mainly because LLMs are heavily trained on webdata which uses markdowns.
- What is the difference between LLM and AI?
  - AI is a broad computer science field dedicated to creating systems which is capable of performing tasks that typically require human intelligence.
  - LLM is a type/subset of AI - which is a Neural Network trained on massive amount of text data specifically designed to understand, process and generate human languages. 
- Is it grammatically correct in English to say "a LLM" or "an LLM"? Why?
  - an LLM (-el sound), because it's decided by the sound and not the first alphabet.
