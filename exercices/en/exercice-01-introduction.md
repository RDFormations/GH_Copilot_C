# Exercices — Introduction to GitHub Copilot

> **Context** — Each developer must confirm Copilot works in **C** and produce a first utility function.

## Exercice — Setup and first completion

**Topics :** sections 1.2 to 1.3 (Copilot versions, install, inline check).

**Prerequisites :** GitHub account + Copilot license; VS Code; local working repository (or provided folder).

### Instructions

1. Install **GitHub Copilot** and **GitHub Copilot Chat**, sign in to GitHub. Check status bar icon.
2. Create `src/utils/format_id.c`.
3. Enter the signature with a comment describing `ID-00042` format (do not implement body):

```c
char* format_id(int id);
```

4. Accept completion with `Tab` (or partially `Ctrl + →`).
5. Test that `strcmp(format_id(42), "ID-00042") == 0`.
6. Note: manual edit rate (none / light / full rewrite).

**Success criteria :** Copilot connected ; runnable function ; `ID-00042` for id=42.

**Documentation :** [Set up Copilot](https://docs.github.com/copilot/how-tos/set-up/install-copilot-extension)

> **Solution** : [Accéder à la correction](../correction/en/correction-01-introduction.md)
