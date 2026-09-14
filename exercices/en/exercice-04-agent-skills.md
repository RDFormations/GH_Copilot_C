# Exercices — Agent, Skills and Instructions

> **Context** — Without Instructions, Copilot suggests generic code. Create the global file before enabling Agent mode.

## Exercice — Project global Instructions

**Prerequisites :** modules 1 to 3; working repository open; Copilot active.

### Instructions

1. Create `.github/copilot-instructions.md` à la racine.
2. Document (≤ 40 lines):
 - stack **C** (C11, gcc/clang, Makefile, valgrind)
 - repo structure (src/, tests/)
 - 3 naming or style conventions
 - 2 security rules (secrets, input validation)
 - test framework and file locations
3. Test in Ask: "What conventions for adding a new module in src/?"
4. **Bonus** — sketch a `lint-and-test` skill (YAML name + description).

**Success criteria :** file ≤ 40 lines, 5 themes covered; Ask response aligned.

> **Solution** : [Accéder à la correction](../correction/en/correction-04-agent-skills.md)
