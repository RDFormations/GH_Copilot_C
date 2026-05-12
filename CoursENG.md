# Developing in C with GitHub Copilot

---

## Module 1: Introduction to GitHub Copilot

### What is GitHub Copilot?

GitHub Copilot is an AI-powered programming assistant developed by GitHub in collaboration with OpenAI. It works as a **virtual pair-programmer** integrated directly into the code editor.

**How it works:**

- Copilot analyzes the context of code being written (open files, comments, variable names)
- It generates code suggestions in real time, directly in the editor
- The underlying model was trained on billions of lines of code from public GitHub repositories
- It is particularly effective in C thanks to the massive amount of open source C code available (Linux kernel, GNU tools, etc.)

**What Copilot is not:**

- It is not a compiler or code verifier
- It does not guarantee that generated code is correct or secure
- It does not replace the developer's understanding of the C language

### The different versions

| Version | Description | Primary use |
|---------|-------------|-------------|
| **Copilot (inline)** | Code suggestions directly in the editor | Day-to-day code writing |
| **Copilot Chat** | Integrated conversational interface | Questions, explanations, refactoring |
| **Copilot CLI** | Command-line assistant | Shell commands, compilation, debugging |

**Copilot inline** is the default mode: as soon as you type code, suggestions appear in gray. You can accept them with `Tab` or ignore them by continuing to type.

**Copilot Chat** allows you to have a conversation with the AI: explain code, request corrections, generate tests.

**Copilot CLI** helps build terminal commands:

```bash
# Example: ask Copilot CLI how to compile with debug flags
gh copilot suggest "compile main.c with debug symbols and all warnings"
# Suggestion: gcc -g -Wall -Wextra -o main main.c
```

### Installation and configuration

**Prerequisites:**

- A GitHub account with an active Copilot subscription (Individual, Business, or Enterprise)
- Visual Studio Code installed
- Microsoft C/C++ extension (for IntelliSense)

**Installation steps:**

1. Open VS Code
2. Go to Extensions (`Ctrl + Shift + X`)
3. Search for "GitHub Copilot" and install the extension
4. Also install "GitHub Copilot Chat"
5. Sign in to GitHub when VS Code prompts you
6. Check for the Copilot icon in the status bar (bottom)

**Verifying it works:**
Create a `test.c` file and start typing:

```c
#include <stdio.h>

// Function that prints Hello World
```

If Copilot is working, a suggestion should appear in gray to complete the function.

### Interface and usage statistics

To view Copilot usage statistics:

- Click the Copilot icon in the VS Code status bar
- Access the dashboard via GitHub: `Settings > Copilot > Usage`
- Available metrics: suggestion acceptance rate, lines of code generated, most used languages

In enterprise environments (Copilot Business/Enterprise), administrators have access to a detailed dashboard showing usage percentage by team and developer.

---

## Module 2: Inline suggestions and context

### Essential keyboard shortcuts

| Action | Shortcut (Windows/Linux) | Shortcut (Mac) |
|--------|--------------------------|----------------|
| Accept suggestion | `Tab` | `Tab` |
| Reject suggestion | `Esc` | `Esc` |
| Next suggestion | `Alt + ]` | `Option + ]` |
| Previous suggestion | `Alt + [` | `Option + [` |
| Accept next word | `Ctrl + →` | `Cmd + →` |
| Trigger manually | `Alt + \` | `Option + \` |
| Open suggestions panel | `Ctrl + Enter` | `Ctrl + Enter` |

The suggestions panel (`Ctrl + Enter`) opens a window with up to 10 alternative suggestions. Useful when the first suggestion doesn't fit.

### Triggering suggestions

#### Start typing a function signature

```c
int calculate_factorial(int n)
```

Copilot will suggest the function body based on the explicit name.

#### Write a descriptive comment

```c
// Bubble sort on an array of integers, returns the sorted array
void bubble_sort(int arr[], int size)
```

The comment guides Copilot on the expected algorithm.

#### Create a data structure

```c
typedef struct {
    char name[50];
    int age;
    float salary;
} Employee;
```

After defining the structure, Copilot can suggest consistent manipulation functions (create, print, free, etc.).

#### Name a variable explicitly

```c
int max_retry_count = 3;
char *error_message = NULL;
FILE *input_file = fopen("data.csv", "r");
```

Clear variable names help Copilot understand the code's intent.

### Context matters

Copilot doesn't rely solely on the current line. It analyzes a **broader context**:

**Open files in the editor:**
If you have a `utils.h` file open with prototypes, Copilot will use them to generate consistent implementations in `utils.c`.

**Includes influence suggestions:**

```c
#include <pthread.h>  // Copilot will suggest multithreaded code
#include <sys/socket.h>  // Copilot will suggest network code
#include <sqlite3.h>  // Copilot will suggest database code
```

**Surrounding code guides generation:**
If previous functions use a particular style (error handling with return codes, dynamic allocation with verification), Copilot will reproduce that pattern.

```c
// If your existing code does this:
int *ptr = malloc(sizeof(int) * n);
if (ptr == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    return -1;
}

// Copilot will reproduce this verification pattern in subsequent suggestions
```

---

## Module 3: Prompting techniques

### The art of the comment-prompt

In C, comments are the main lever for guiding Copilot. A well-written comment produces better quality code than a function name alone.

**Vague comment → imprecise result:**

```c
// sort the array
```

**Precise comment → targeted result:**

```c
// Insertion sort on an array of integers in ascending order
// Complexity: O(n²) worst case, O(n) best case
// Modifies the array in place
void insertion_sort(int arr[], int n)
```

### Basic principles

**Be specific and precise:**

```c
// ❌ Vague
// read a file

// ✅ Precise
// Read a text file line by line, store each line in a dynamic
// array of strings, return the number of lines read
// Returns -1 on file open error
int read_lines(const char *filename, char ***lines)
```

**Provide context:**

```c
// This function is part of a custom memory allocator
// It searches for a free block of sufficient size in the free list
// Uses the first-fit strategy
void *find_free_block(size_t size)
```

**Break down complex problems:**
Rather than requesting a monolithic function, split into steps:

```c
// Step 1: Parse the CSV line into tokens separated by commas
char **parse_csv_line(const char *line, int *count);

// Step 2: Convert tokens to an Employee structure
Employee token_to_employee(char **tokens);

// Step 3: Insert the employee into the dynamic array
int insert_employee(Employee **employees, int *size, int *capacity, Employee emp);
```

**Iterate on suggestions:**
If the first suggestion doesn't fit, use `Alt + ]` to see alternatives, or rephrase the comment.

### Structure of a good prompt

An effective prompt for Copilot follows the **What / How / Constraints** structure:

```c
/**
 * WHAT: Search for an element in a sorted array
 * HOW: Uses binary search
 * CONSTRAINTS:
 *   - The array must be sorted in ascending order
 *   - Returns the element's index or -1 if not found
 *   - Works for arrays up to INT_MAX elements
 */
int binary_search(const int arr[], int size, int target)
```

Another example with memory management:

```c
/**
 * WHAT: Create a deep copy of a linked list
 * HOW: Iterative traversal with allocation of new nodes
 * CONSTRAINTS:
 *   - Returns NULL if source list is NULL or on malloc failure
 *   - The caller is responsible for freeing the copy with free_list()
 *   - Data (char*) is duplicated with strdup
 */
Node *deep_copy_list(const Node *head)
```

### Iteration and refinement

**Partially accept a suggestion:**
Use `Ctrl + →` (accept word by word) when the beginning of the suggestion is good but the rest diverges. This allows you to keep control while benefiting from the assistance.

**Modify and retrigger to refine:**

```c
// First attempt - suggestion too simple
// Sort an array
// → Copilot generates a basic bubble sort

// Second attempt - more precise
// Quicksort with median-of-three pivot, Lomuto partition
// Handle arrays of size < 10 with insertion sort
void quicksort(int arr[], int low, int high)
```

**Combine multiple suggestions:**
Accept a suggestion for the function skeleton, then delete certain parts and ask Copilot to regenerate them with a more specific comment.

---

## Module 4: Copilot Chat and interaction modes

### Conversational interface

Open the Chat panel: `Ctrl + Shift + I` (or `Cmd + Shift + I` on Mac).

Copilot Chat allows you to ask questions in natural language directly in VS Code:

**Examples of useful questions in C:**

- "Explain what this function does"
- "Why does this code cause a segfault?"
- "How to implement a thread pool in C?"
- "Generate unit tests for this function"
- "Optimize this loop to reduce cache misses"

**Getting detailed explanations:**
Select a complex code block then ask in the chat:
"Explain this code step by step, particularly the memory management"

### Slash commands

Slash commands are shortcuts for frequent actions:

| Command | Action |
|---------|--------|
| `/explain` | Explains the selected code |
| `/fix` | Suggests a fix for the selected code |
| `/tests` | Generates tests for the selected code |
| `/doc` | Generates documentation (Doxygen comments in C) |
| `/new` | Creates a new file/project |
| `/clear` | Clears chat history |

**Example with `/doc` on a C function:**

```c
// Before /doc
int add_node(LinkedList *list, void *data, size_t data_size);

// After /doc - Copilot generates:
/**
 * @brief Adds a new node at the head of the linked list
 * @param list Pointer to the linked list
 * @param data Pointer to the data to copy into the node
 * @param data_size Size in bytes of the data to copy
 * @return 0 on success, -1 on allocation error
 */
int add_node(LinkedList *list, void *data, size_t data_size);
```

### Context selection

**Select code before asking a question:**
Highlight a code block, then open the chat → Copilot understands the question is about that specific code.

**Use `@workspace` to reference the project:**

```
@workspace How is the project structured? What are the main modules?
@workspace Find all functions that allocate memory without freeing it
```

**Use `@file` to target a specific file:**

```
@file:src/parser.c Explain the parsing algorithm used here
@file:include/types.h Generate initialization functions for each structure
```

### Plan, Agent, Chat, and Ask modes

**Chat mode (default):**
Classic question/answer conversation. Suggested code is not automatically applied.

**Ask mode:**
Read-only mode. Copilot answers questions without proposing modifications. Ideal for understanding existing code.

**Edit mode:**
Copilot can directly modify open files. After describing what you want, it proposes modifications you can accept or reject.

**Agent mode:**
The most autonomous mode. Copilot can:

- Execute terminal commands (compilation, tests)
- Modify multiple files in sequence
- Iterate until solving a problem

Example in C:

```
Agent mode: "Fix all memory leaks detected by Valgrind in this project"
→ Copilot runs Valgrind, analyzes the output, fixes the files, recompiles, verifies
```

### Cloud mode (preview)

Cloud mode allows executing Copilot tasks on GitHub infrastructure:

- Long-running tasks that run in the background
- No need to keep VS Code open
- Results available via notification or PR
- Useful for massive refactoring or code migrations

---

## Module 5: Advanced features

### Agents, Skills, Prompts, and Instructions

**Custom instructions:**
Create a `.github/copilot-instructions.md` file at the project root to guide Copilot:

```markdown
# Instructions for this C project

- Use the C11 standard
- Always check malloc return values (return NULL on failure)
- Naming conventions: snake_case for functions and variables
- Prefix public functions with the module name (e.g.: list_add, list_remove)
- Document with Doxygen format
- Error handling via return codes (0 = success, negative = error)
```

**Reusable prompt files (`.github/prompts/`):**
Create saved prompts for recurring tasks:

```markdown
<!-- .github/prompts/new-module.prompt.md -->

Create a new C module with:

- A header file (.h) with include guards
- A source file (.c) with implementations
- Module init and cleanup functions
- Doxygen documentation for each public function
```

### Automatic commit

Copilot can automatically generate relevant commit messages:

- Click the Copilot icon in the Source Control view
- Copilot analyzes the changes (diff) and proposes a message
- The message follows project conventions (Conventional Commits if configured)

Example:

```
feat(parser): add CSV parsing with quoted field support

- Handle escaped quotes within fields
- Support multiline values enclosed in quotes
- Add error reporting with line numbers
```

### Code review on pending commits

Copilot can review code before committing:

- In the Source Control tab, use "Review Changes" with Copilot
- It identifies: potential bugs, memory leaks, style issues, improvement suggestions
- Particularly useful in C for detecting:
  - Out-of-bounds array access
  - Uninitialized pointers
  - Double free / use after free
  - Buffer overflows

### Fine tuning and customization

**Adapt Copilot to the project style:**

- `.github/copilot-instructions.md` files influence all suggestions
- Copilot learns from existing code in the project (patterns propagate)
- Use example files as "templates" that Copilot will reproduce

**Exclude files from indexing:**
In `.gitattributes`:

```
# Do not use these files as context for Copilot
vendor/** linguist-generated
generated/** linguist-generated
```

---

## Module 6: Best practices and productivity

### Validating generated code

Code produced by Copilot in C requires particular vigilance:

**Always verify:**

- Memory management (malloc/free, no leaks, no double free)
- Array access (no out-of-bounds)
- Pointers (NULL check before dereferencing)
- Types and casting (integer overflow, truncation)
- Error handling (system function return values)

**Validation tools:**

```bash
# Compilation with strict warnings
gcc -Wall -Wextra -Werror -fsanitize=address,undefined -g -o prog main.c

# Static analysis
cppcheck --enable=all --inconclusive src/

# Memory leak detection
valgrind --leak-check=full --show-leak-kinds=all ./prog
```

### When to use Copilot

**Repetitive or boilerplate code:**

```c
// Copilot excels at generating similar CRUD functions
Employee *employee_create(const char *name, int age, float salary);
void employee_destroy(Employee *emp);
void employee_print(const Employee *emp);
int employee_serialize(const Employee *emp, FILE *out);
Employee *employee_deserialize(FILE *in);
```

**Classic algorithm implementation:**
Sorting, searching, graph traversal, hash tables — Copilot knows the standard implementations.

**Documentation and comments:**
Use `/doc` to generate Doxygen documentation for existing functions.

**Unit tests:**

```c
// Ask Copilot: "Generate tests for the binary_search function"
// It produces relevant test cases:
void test_binary_search_found(void) {
    int arr[] = {1, 3, 5, 7, 9, 11};
    assert(binary_search(arr, 6, 7) == 3);
}

void test_binary_search_not_found(void) {
    int arr[] = {1, 3, 5, 7, 9, 11};
    assert(binary_search(arr, 6, 4) == -1);
}

void test_binary_search_empty(void) {
    int arr[] = {};
    assert(binary_search(arr, 0, 5) == -1);
}
```

**Exploring new APIs:**
When using an unfamiliar library (libcurl, OpenSSL, SQLite), Copilot helps write the initialization boilerplate.

### When to be cautious

**Security-critical code:**
Cryptography, authentication, user input parsing — always manually review and test thoroughly.

**Complex business logic:**
Project-specific business rules are not known to Copilot. It may generate syntactically correct but semantically wrong code.

**Code with specific constraints:**
Embedded systems with limited memory, real-time code, compliance with standards (MISRA C, DO-178C) — Copilot is unaware of these constraints.

**Critical performance optimizations:**
Copilot generates functional but rarely optimal code. For performance-critical code (inner loops, SIMD, cache-friendly), human expertise remains indispensable.

### Optimal productivity

**Use Copilot as an assistant, not a replacement:**

- Read and understand each suggestion before accepting it
- Never blindly accept code you don't understand
- Copilot accelerates writing, it doesn't exempt you from thinking

**Learn from suggestions to improve:**

- Copilot can show patterns or standard library functions you don't know
- Observing suggestions is a form of passive learning
- Example: discovering `qsort`, `bsearch`, `strtok_r` through suggestions

**Adapt your workflow progressively:**

1. Start by accepting suggestions for boilerplate only
2. Gradually use comment-prompts for entire functions
3. Integrate Copilot Chat for debugging and documentation
4. Use Agent mode for complex multi-file tasks

---
