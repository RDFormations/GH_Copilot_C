# Exercices — Inline completions and context

> **Context** — You implement utility functions in **C**. Vague comments produce generic code.

## Exercise — Algorithm comment-prompts

**Topics :** sections 2.5–2.6 (What/How/Constraints, iteration).

### Instructions

1. Create `src/sort.c`.
2. **Stub A** — copy the vague stub, trigger completion (`Alt + \\`), note why the suggestion is insufficient:

```c
/* trier un tableau */
int insertion_sort(const int* values, int count, int* out);
```

3. Replace with structured What/How/Constraints (insertion sort, immutable copy):

```c
/**
 * QUOI : Tri par insertion sur tableau de nombres
 * COMMENT : parcours O(n²), copie immuable
 * CONTRAINTES : retourne 0 si OK, -1 si erreur
 */
int insertion_sort(const int* values, int count, int* out);
```

4. **Stub B** — same approach for binary search (sorted array, return index or -1):

```c
/* recherche dichotomique */
int binary_search(const int* values, int count, int target);
```

5. For each stub, document iterations before an acceptable suggestion.

**Success criteria :** two functions with precise prompts; correct algorithm; iteration log documented.

**Documentation :** [Best practices](https://docs.github.com/copilot/get-started/best-practices-for-using-github-copilot)

> **Solution** : [View solution](../correction/en/correction-02-completions-inline.md)
