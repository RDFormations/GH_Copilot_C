# Exercices — Agent, Skills et Instructions

> **Contexte** — Sans Instructions, Copilot propose du code générique. Créez le fichier global avant d activer le mode Agent.

## Exercice — Instructions globales du projet

**Prérequis :** modules 1 à 3 ; dépôt de travail ouvert ; Copilot actif.

### Énoncé

1. Créez `.github/copilot-instructions.md` à la racine.
2. Documentez (≤ 40 lignes) :
 - stack **C** (C11, gcc/clang, Makefile, valgrind)
 - structure du dépôt (src/, tests/)
 - 3 conventions de nommage ou style
 - 2 règles de sécurité (secrets, validation entrées)
 - framework et emplacement des tests
3. Testez en Ask : « Quelles conventions pour ajouter un nouveau module dans src/ ? »
4. **Bonus** — esquissez un skill `lint-and-test` (name + description YAML).

**Critère de réussite :** fichier ≤ 40 lignes, 5 thèmes couverts ; réponse Ask alignée.

> **Correction** : [Accéder à la correction](../correction/fr/correction-04-agent-skills.md)
