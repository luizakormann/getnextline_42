# get next line

Get Next Line is a project from **42 São Paulo**.
The get_next_line function reads a file descriptor line by line. It efficiently manages multiple file descriptors using a static linked list to preserve reading states across calls. My implementation ensures memory optimization and proper buffer handling.

## 📁 Project Structure
The project is organized as follows:

 - **bin/:** Directory where the `gnl.a` (compiled library) file will be generated.
 - **include/:** Contains the header file `get_next_line.h` with all the function declarations and necessary definitions.
 - **obj/:** Directory where object files (`.o`) are stored during compilation.
 - **src/:** Directory containing the source files (`.c`) with the function implementations.

## 🚀 Features

 - Handles multiple file descriptors simultaneously.
 - Reads from any valid file descriptor, including standard input.
 - Uses a dynamic buffer to optimize memory usage.
 - Ensures correct memory management to avoid leaks.

## 📜 Function Prototype
``` bash
char *get_next_line(int fd);
```

## 🏗️ Project Structure
``` bash
get_next_line/
│── include/
│   ├── get_next_line.h        # Header file with function prototypes and struct definition
│  
├── src/
│   ├── get_next_line.c        # Core function implementation
│   ├── read_fts.c             # Functions responsible for reading and processing buffers
│   ├── build_fts.c            # Functions to extract and manage lines
│   ├── struct_fts.c           # Linked list structure management
│   ├── utils.c                # Utility functions (string manipulation, memory handling)
│  
├── test/
│   ├── main.c                 # Test file for the function
│  
├── Makefile                    # Compilation rules
├── README.md                    # Project documentation
```

## ⚙️ Compilation and Usage
### Requirements
 - GCC or another compatible C compiler.
 - UNIX/Linux system recommended (tested in the 42 São Paulo environment).
### Available Commands
Use the `Makefile` to compile and manage the project:

| Command | Description |
|---------|-----------|
|`make`|Compiles the static library (`gnl.a`).|
|`make clean`|Removes object files (`.o`).|
|`make fclean`|Remmoves obj files and the compiled library (`gnl.a`).|
|`make re`|Recompiles everything from scratch.|

### How to Use
 1. Compile the library using `make`.
 2. Include the `get_next_line.h` header in your project.
 3. Link the `gnl.a` library when compiling your program:
``` bash
gcc -Wall -Wextra -Werror -I include/ -L bin/ -lgnl your_program.c -o your_program
```

## 🎓 Key Learnings (author's notes)
This project provided valuable insights into:

 - **Dynamic Memory Management**: Implementing `get_next_line` reinforced concepts of heap allocation, buffer manipulation, and memory safety.
 - **Linked Lists**: I deliberately used linked lists to strengthen my understanding, efficiently managing multiple file descriptors and optimizing buffer handling.
 - **Wrappers and Function Pointers**: Deepened my knowledge of modularization and abstraction in C. I leveraged `static` variables in `get_next_line` to persist data between function calls, enabling efficient buffer reuse while maintaining function scope and avoiding unnecessary global variables. This approach improved both memory efficiency and readability.
 - **Project Evolution & Optimization**: My initial implementation used a `struct` that stored data character by character. After completing the project, I refactored it to read full strings, improving efficiency and making the `gnl.a` library reusable for future projects, such as **Minitalk**, the project I am currently working on.
## 👩‍💻 Author
This project was developed by Luiza Kormann (lukorman@student.42.fr) as part of the 42 São Paulo curriculum.
