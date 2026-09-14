# Solution — Introduction to GitHub Copilot

> **Exercise** : [Revoir l'énoncé](../exercices/en/exercice-01-introduction.md)

## Context

Verify Copilot works before continuing to the next modules.

## Detailed solution

### Step 1 — Setup

**Expected :** Copilot + Chat extensions installed; icon active.

### Step 2 — Signature and comment

```c
/** Format ticket ID: FB- prefix, 5-digit zero-padded number. */
char* format_id(int id); {
```

### Step 3 — Accept and test

**Verification :** `strcmp(format_id(42), "ID-00042") == 0`

## Common pitfalls

| Symptom | Fix |
| -------- | ----- |
| No suggestion | Check Copilot license and GitHub sign-in |
| Wrong format (FB-42) | Specify zero-padding in comment |


## Documentation

| Topic | Link |
| ----- | ---- |
| Best practices | [Best practices](https://docs.github.com/copilot/get-started/best-practices-for-using-github-copilot) |
