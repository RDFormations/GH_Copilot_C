# Solution — Inline completions and context

> **Exercise** : [Revoir l'énoncé](../exercices/en/exercice-02-completions-inline.md)

## Context

Precise comments significantly improve the quality of generated suggestions.

## Detailed solution

### Step 2 — Vague stub A

**Analysis :** with a vague comment, Copilot often suggests an incomplete algorithm — insufficient.

### Step 3 — Structured prompt (stub A)

```c
/**
 * QUOI : Tri par insertion sur tableau de nombres
 * COMMENT : parcours O(n²), copie immuable
 * CONTRAINTES : retourne 0 si OK, -1 si erreur
 */
int insertion_sort(const int* values, int count, int* out);
```

**Verification :** correct sort algorithm with immutable copy.

### Step 5 — Binary search stub B

**Typical body :** search on sorted array, return index or -1.

## Common pitfalls

| Symptom | Fix |
| -------- | ----- |
| Sort mutates source array | Specify immutable copy in COMMENT |
| Missing -1 return | Specify sorted array in COMMENT |


## Documentation

| Topic | Link |
| ----- | ---- |
| Best practices | [Best practices](https://docs.github.com/copilot/get-started/best-practices-for-using-github-copilot) |
