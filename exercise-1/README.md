# Exercise 1

**Update this README with your answers to the questions below.**

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
   - **Phase 2: Primary-source deep dive.** I will study authoritative
     references and focus first on what I do not know. I will start with `g++`
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

       - Wasted time in thinking about project

The point of this exercise isn't to get the questions "right" — it's to notice
the gap between how you *think* you learn and how you actually do, so you can
close it.

## Learning How to Learn

- Answer the following questions in this file and commit and push your changes.
- Bonus sections are more difficult and optional.
- How can you find the information required to complete these tasks?
- How can you tell if the source of your information is good?
- How would you define "good" in this situation?

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
- [Quickstart tutorial to make](https://makefiletutorial.com/) - Learn make 
  fundamentals with practical examples and common patterns.
- How else can you learn about make?
- How can you tell if the resource you are using is correct?
- Create a makefile such that when you run `make` with no arguments, it will:
  - Create `build/` directory if it does not exist
  - Create executables **client** and **server** in `build/`, if needed
  - How does make know when it needs to rebuild the executables?
  - Change your Makefile such that `make clean` will remove `build/` and all
    its contents
- What are the most important command line arguments to learn for make?
- What are the most important directives to learn about in Makefile?
- What are the most important commands to implement in your Makefile?
- Which ones are essential, which ones are nice to haves?

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
  - clone, add, commit, push, pull, status, log, diff, branch

## Introduction to Sockets

- Read the code in `src/tcp-echo-client.cc` and add a way to change the 
  message sent using command line arguments
- **Example**: `./client "hello message from the command prompt"` should send
  `"hello message from the command prompt"` to the server
- Commit your changes into git
- What do all these headers do?
- How do you find out which part of the below code comes from which header?
- How do you change the code so that you are sending messages to servers
  other than localhost?
- How do you change the code to send to a IPv6 address instead of IPv4?
- **Bonus**: How do you change the client code to connect by hostname instead
  of IP address?
  
## Introduction to Memory Management

- What is happening in line 26 of `tcp-echo-client.cc`? 
  `if (inet_pton(AF_INET, kServerAddress.c_str(), &address.sin_addr) <= 0) {`
- What is happening in line 31 of `tcp-echo-client.cc`?
  `if (connect(my_sock, (sockaddr *)&address, sizeof(address)) < 0) {`
- What is the difference between a pointer and a reference?
- When is it better to use a pointer?
- When is it better to use a reference?
- What is the difference between `std::string` and a C-style string?
- What type is a C-style string?
- What happens when you iterate a pointer?
- What are the most important safety tips to know when using pointers?

## Learn Basics of Creating a C++ Project in Your IDE

- How do you compile and run your project in your IDE?

## Improving Interactions with LLMs

- What is the most authoritative source of information about `socket()`
  from `<sys/socket.h>`?
- What is the most authoritative source of information about the TCP and IP
  protocols?
- What is the most authoritative source of information about the C++
  programming language?
- What information can you find about using Markdown when structuring prompts 
  to LLMs?
- What is the difference between LLM and AI?
- Is it grammatically correct in English to say "a LLM" or "an LLM"? Why?
