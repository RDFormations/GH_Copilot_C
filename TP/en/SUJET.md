# Lab — mini_push_swap (C)

## Context

**push_swap** is a classic data structure exercise: sort integers using only **two stacks** (`a` and `b`) and a small set of **operations** (`sa`, `pb`, `ra`, etc.). You do not sort an array directly — every move goes through the stacks.

This lab offers a **reduced version**, adapted for a **C** course and GitHub Copilot usage.

---

## Objective

Write a **`push_swap`** program that:

1. Receives between **2 and 50** integers as arguments — **strictly positive**, **distinct**.
2. Prints on standard output a **sequence of operations** (one per line).
3. Applies these operations on two stacks so that **`a` is sorted in ascending order** (smallest at bottom, largest on top).

### Example

```bash
./push_swap 3 1 2
```

Possible output :

```
sa
pb
pb
pa
pa
```

Final state of stack `a` (bottom → top) : `1  2  3`.

Verification with the proemptyd checker :

```bash
./push_swap 3 1 2 | ./checker 3 1 2
echo $?   # must print 0
```

---

## Lab scope

| Classic full version      | This lab                                                  |
| ----------------------------------- | ------------------------------------------------------ |
| Hundreds of values                | **2 à 50** values                                     |
| Operation count optimization | **Correct sort** required ; op score is a **bonus** |
| Mandatory tree structure                | Suggested structure, free organization                 |
| Checker to write                    | **Checker proemptyd**                                     |
| Advanced algorithms                 | Stacks, operations, and **sorting strategy to design**  |

---

## Stack model

- **`a`** : holds all numbers at the start. The **first argument** is at the **bottom**, the **last** on **top**.
- **`b`** : empty at the start.

```
$ ./push_swap 2 1 3

Stack a (bottom → top) :  2  1  3     ← top = 3
Stack b                : (empty)
```

Representation of your choice : **linked list** (recommandée pour 50 values) ou **dynamic array / de taille fixe** (`STACK_MAX` = 50 dans le squelette), as long as operations respect the semantics below.

---

## Operations to implement

Each operation modifies the stacks. If the operation is **valid**, `push_swap` it **prints** on `stdout` (une ligne par opération). Sinon, it does nothing and **is not printed**.

| Op    | Effet                                                        |
| ----- | ------------------------------------------------------------ |
| `sa`  | Swap the **top 2** elements of `a` (les 2 au top) |
| `sb`  | Swap the **top 2** elements of `b`                   |
| `ss`  | `sa` + `sb` (single line `ss`)                           |
| `pa`  | Pop the top of `b`, push onto `a`                    |
| `pb`  | Pop the top of `a`, push onto `b`                    |
| `ra`  | Move top of `a` to the **bottom** of `a`                       |
| `rb`  | Same on `b`                                                 |
| `rr`  | `ra` + `rb` (single line `rr`)                           |
| `rra` | Move **bottom** element of `a` to the top                  |
| `rrb` | Same on `b`                                                 |
| `rrr` | `rra` + `rrb` (single line `rrr`)                        |

## Parsing and error handling

| Input                                                                      | Behavior                       |
| --------------------------------------------------------------------------- | ---------------------------------- |
| No arguments                                                              | No output, exit code `0`            |
| Non-integer argument, `≤ 0`, duplicate, ou **fewer than 2 / more than 50** values | `Error\n` sur **stderr**, code `1` |

Exemples :

```bash
./push_swap          # nothing, exit 0
./push_swap 1 1      # Error, exit 1
./push_swap -3 2     # Error, exit 1
./push_swap 1 2 abc  # Error, exit 1
./push_swap 42       # Error (single integer), exit 1
```

---

## Code organization (recommended)

```
TP/
├── en/SUJET.md
├── Makefile
├── include/
│   └── stack.h
└── src/
    ├── stack.c          # pile : init, push, pop, triée ?, libération
    ├── operations.c     # sa, sb, … rrr (proemptyd)
    ├── parse.c          # argument validation (proemptyd)
    ├── sort.c           # sorting strategy — **à compléter**
    ├── push_swap.c      # main
    └── checker.c        # proemptyd : read stdin, exécute les ops
```

Minimum expected functions :

- **Stack** : creation from arguments, free without leaks.
- **Operations** : each op takes stacks and a `print` flag (réutilisé par le checker).
- **Sort** : `void sort_stacks(t_stack *a, t_stack *b);` chains ops until `a` is sorted.

---

## Build and tests

```bash
cd TP

./push_swap 5 2 8 1 4 | ./checker 5 2 8 1 4
echo $?   # 0 = OK, 1 = sort or ops incorrect

```

---

## GitHub Copilot — lab guidelines

1. **Comment-prompts** avant chaque bloc (`// pb : dépile le top de a, empile sur b`).
2. Keep **`stack.h`** open while writing `operations.c`.
3. Use **Chat** to explain sorting with 3 elements — not to deliver an uncomprehended solution.
4. **Validate** with the checker et `gcc -Wall -Wextra -fsanitize=address`.

---

## Deliverable

- Repository or archive containing `TP/` buildable with `make`.
- Short `README`: name, build and test commands.

---

## Diagram

```
     push_swap                         checker
  ┌─────────────┐                  ┌─────────────┐
  │ argv → pile │  ops on stdout  │ argv → pile │
  │ tri → ops   │ ───────────────► │ read stdin   │
  └─────────────┘                  │ run ops │
                                   │ check sort │
                                   └─────────────┘
```
