# get_next_line

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
├── Makefile                    # Compilation rules
├── README.md                    # Project documentation
```

## 🌀 Project Flow
Find below a detailed explanation of how the data flows through the various functions in the project:

### 1. **Main Entry**: `get_next_line(int fd)`

The entry point of the program is the `get_next_line` function. It takes a file descriptor (`fd`) as input and returns a line of text read from the file associated with that descriptor.

*   **Input:** A file descriptor (`fd`) representing the file or input stream to read from.
*   **Output:** A line of text, including the newline character if present, or `NULL` if no more data is available.

#### Flow:

1.  **Find or Create Node**: The function first checks if a node corresponding to the file descriptor exists. If not, it creates a new node in a static linked list (`find_or_create_node`).
2.  **Read to Buffer**: The function then attempts to read data into the buffer (`read_to_buffer`). If the buffer contains a newline character (`\n`), it stops reading further.
3.  **Extract Line**: Once data is in the buffer, the `extract_line` function is called to retrieve the first line from the content stored in the node.
4.  **Memory Management**: If the line is successfully extracted, the function returns it. If no more content is available or an error occurs, the corresponding node is freed (`free_node`), and `NULL` is returned.

### 2. **Node Management: `find_or_create_node` and `free_node`**

*   **Input:** A file descriptor (`fd`).
*   **Output:** A pointer to the existing or newly created node, or the freed memory of the node.

#### Flow:

1.  **Find or Create Node**: The `find_or_create_node` function checks if there is an existing node for the given file descriptor. If it exists, it returns the node. If the node does not exist, a new node is created, initialized with the given `fd`, and added to the linked list.
2.  **Free Node**: The `free_node` function is used to free the memory allocated for a node once it is no longer needed, ensuring no memory leaks.

### 3. **Buffer Handling: `read_to_buffer` and `process_buffer`**

*   **Input:** File descriptor (`fd`), a pointer to the content buffer.
*   **Output:** The number of bytes read, or `-1` if there’s an error.

#### Flow:

1.  **Buffer Allocation**: The `read_to_buffer` function allocates memory for a buffer.
2.  **Read Data**: It repeatedly calls `process_buffer` to read data into the buffer until a newline character is found or the end of the file is reached.
3.  **Memory Management**: The function ensures that the content buffer is dynamically updated and freed as necessary.

### 4. **Line Extraction: `extract_line`**

*   **Input:** A pointer to the content buffer.
*   **Output:** A string containing the extracted line, or `NULL` if no line is available.

#### Flow:

1.  **Find Line**: The function scans the content buffer for a newline character (`\n`) or the end of the string.
2.  **Create Line**: Once a line is found, a new string containing the line is created (`gnl_substr`), and the remaining content is stored back into the node.
3.  **Return Line**: The function returns the extracted line, or `NULL` if no more data is available.

### 5. **Utility Functions**

Various utility functions (`gnl_memcpy`, `gnl_strdup`, `gnl_strjoin`, etc.) are used throughout the project to manage strings and memory:

*   **`gnl_memcpy`**: Copies memory between two buffers.
*   **`gnl_strdup`**: Duplicates a string.
*   **`gnl_strjoin`**: Joins two strings.
*   **`gnl_strlen`**: Returns the length of a string.

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
 - **Modularization and Use of static Variables**: Deepened my knowledge of modularization and abstraction in C by using `static` variables in `get_next_line` to persist data between function calls, enabling efficient buffer reuse while maintaining function scope and avoiding unnecessary global variables. This approach improved both memory efficiency and readability.
 - **Project Evolution & Optimization**: My initial implementation used a `struct` that stored data character by character. After completing the project, I refactored it to read full strings, improving efficiency and making the `gnl.a` library reusable for future projects, such as **Minitalk**, the project I am currently working on.
## 👩‍💻 Author
This project was developed by Luiza Kormann (lukorman@student.42.fr) as part of the 42 São Paulo curriculum.
