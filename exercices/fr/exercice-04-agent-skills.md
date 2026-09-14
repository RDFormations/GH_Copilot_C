# Exercices — Agent, Skills et Instructions

> **Contexte** — Sans Instructions, Copilot propose du code générique. Créez le fichier global avant d activer le mode Agent.

## Exercice — Instructions et skill métier

**Notions mobilisées :** sections 4.2 (Instructions), 4.3 (Skills), 4.6 (mise en place).

**Prérequis :** modules 1 à 3 ; dépôt de travail ouvert ; Copilot actif.

### Énoncé

1. Créez `.github/copilot-instructions.md` à la racine.
2. Documentez (≤ 40 lignes) :
 - stack **C** (C11, gcc/clang, Makefile, valgrind)
 - structure du dépôt (src/, tests/)
 - 3 conventions de nommage ou style
 - 2 règles de sécurité (secrets, validation entrées)
 - framework et emplacement des tests
3. Testez en Ask : « Quelles conventions pour ajouter un nouveau module utilitaire ? »
4. **Bonus** — créez `.github/skills/lint-and-check/SKILL.md` (name + description YAML).

**Critère de réussite :** fichier ≤ 40 lignes, 5 thèmes couverts ; réponse Ask alignée.

> **Correction** : [Accéder à la correction](../correction/fr/correction-04-agent-skills.md)
