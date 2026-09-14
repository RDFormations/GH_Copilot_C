# Exercices — Agent, Skills and Instructions

> **Context** — Without Instructions, Copilot suggests generic code. Create the global file before using Agent mode.

## Exercise — Instructions and domain skill

**Topics :** sections 4.2 (Instructions), 4.3 (Skills), 4.6 (minimal setup).

**Prerequisites :** modules 1 to 3; working repo open; Copilot active.

### Instructions

1. Create `.github/copilot-instructions.md` à la racine.
2. Document (≤ 40 lines):
   - stack **C** (C11, gcc/clang, Makefile, valgrind)
   - repo structure (src/, tests/)
   - 3 naming or style conventions
   - 2 security rules (secrets, input validation)
   - test framework and file locations
3. Test in Ask: "What conventions for adding a new utility module?"
4. **Bonus** — create `.github/skills/lint-and-check/SKILL.md` (YAML name + description).

**Success criteria :** file ≤ 40 lines, 5 themes covered; Ask response aligned.

> **Solution** : [View solution](../correction/en/correction-04-agent-skills.md)
