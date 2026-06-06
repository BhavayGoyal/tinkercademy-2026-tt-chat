# Exercise 5

**Update this README with your answers to the questions below.**

## Comparing File Changes

- What's an easy way to identify the changes in source code from one exercise
  to another?
  - one way is to use `diff` command to compare the files
    - for example using `diff exercise-4/src/tcp_echo_client.cpp exercise-5/src/client-main.cc`
  - VS Code has a built-in "Compare with" feature
  - Using a control system like git, we can do git diff to see differences
    
## Using Classes

- Here is one way to separate out the code into multiple files (**YUPP**)
- Is this the best way to do it?
  - While the current separation into multiple files is a good start, it isn't necessarily the "best" or most robust way. The current approach still relies on global/namespace-level functions and manual resource management (e.g., manually calling `close(sock)`). A more robust "C++ way" would be to use classes to encapsulate both the data and the lifecycle of the networking resources.
- What are the advantages and disadvantages?
  - **Advantages of Current Approach:**
    - **Modularity:** Much better than a single file. Code is better organized.
    - **Simplicity:** It's straight-forward and simple.
  - **Disadvantages of Current Approach:**
    - **Manual Resource Management:** The programmer must remember to manually call `close()` on every path (including error exits).
    - State (like the socket descriptor) is passed around manually between functions, making it harder to track.
    - **Scalability Issues:** Managing multiple connections or complex state becomes difficult without encapsulation.

## Introduction to Namespace

- There are different ways namespace is being used in this exercise (**YUPP**)
- Which way is better? What are the advantages and disadvantages?
  - Namespace aliases (namespace ttc = tt::chat;): This is the most recommended way. It gives you the convenience of shorter names without polluting the global scope.
  - Using directives (using namespace tt::chat;): This was used inside functions. Generally using it inside functions is safe, but doing it on the top of file globally is a really bad practice because it dumps all the namespace's symbols into the global namespace.

## Abstracting Code into Classes

- Abstract the client and server logic into a `Client` and `Server` class
- **Note**: You don't have to use the code in this exercise as a starting point
- You can use the code you wrote from previous exercises instead
- How should you divide the code into files?
  - The code should be divided into separate header (`.h`) and implementation (`.cc`) files for each class (e.g., `client.h`, `client.cc`, `server.h`, `server.cc`). This separates the interface from the implementation and allows for faster compilation.
- What namespace and directory structure should you use? Why?
  - **Directory Structure:** `src/net/` is a good place for these classes as they are networking-specific. This keeps the root `src/` directory clean and groups related components together.
  - **Namespace:** `tt::chat::net` is ideal. It clearly indicates the organization (`tt`), the project (`chat`), and the specific layer (`net`). Using a nested namespace prevents name collisions and makes the code's purpose self-evident.

## Programming Sense of Taste

- How do you judge what makes a particular choice of namespace and directory
  structure? 
    - A good structure should group related code together. A good directory structure instantly allows a developer to guess where a specific piece of code/logic is located without relying on global search. If by seeing the code, the developer is able to tell and identify what different things would be doing, it's usually a good sign. If it's too many things, or things are unclear then it is a sign of not so good structure.
- How do you judge what makes a good naming convention or programming style?
  - A good naming convention is a convention in which the developer by just reading the code is able to understand what's going on in the code without having to make guesses on what this variable/function might be doing. A good style is usually self-documenting and it also makes the code easy to scan.

## "Senses" in Programming

- Have you ever heard of programmers referring to "code smells"? How can code
  smell?
  - Yes. Code smells refers to when you look at the code and something seems off even when it's working. It could be due to bad structure, bad programming style like duplicated logic, vague names, overly long functions etc. It's just a sign that it's hard to understand and something should be changed.
- What does it mean to have a sense of taste in programming? How can code
  taste?
  - A sense of taste is nothing but an intuition developed over time for cute designs in the code. Code "Tastes" good when it solves a complex problem with surprisingly simple, readable, and modular logic. It feels really satisfying and robust.
- Is there an analogue for every sense?
  - Smell: "Code smells" (bad design)
  - Taste: "Good taste" (Cute nice design)
  - Sight: The visual layout, formatting and structure of the code (it's visually appealing from a bird eye's view)
  - Touch: The feel of an API. It is smooth and intutive to use and understand.
  - Hearing: Listening to user's feedback
- What other code senses can you think of?
  - 6th sense for edge cases: The feeling or intuition that this specific code might fail at some test case or edge cases.
- How many senses do humans have?
  - Traditionally we talk about 5 senses (touch, smell, taste, sight, hear) but biologically humans have even more senses.
- When would you want to see something before you touch it?
  - When working with a new library/framework, it'll be better to see the documentation before trying to impliment (touch) it and see if it fits the purpose of the application you're building or not.
- When would you want to touch something before you see it?
  - When the documentation is too abstract or untrustworthy. Or maybe when you want to test out somethinig which the documentation does not clearly specify, it might be better to touch it, quickly impliment it and test it out yourself. (Like maybe you're unsure on how this function would behave in some scenario, just impliment it out and see for yourself)