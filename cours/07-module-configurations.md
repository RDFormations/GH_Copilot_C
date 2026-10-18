---
title: "Module 6 — Les configurations"
description: "Trois prompts, trois moments."
published: false
editor: markdown
---

# Module 6 — Les configurations

Une configuration est un prompt. Il entre dans la requête à un moment précis.

```mermaid
flowchart TB
  E["Édition"] --> A["applyTo"] --> I["Instruction"]
  C["Choix"] --> G["Agent"]
  T["Tâche"] --> S["Skill"]
```

- Les instructions ne partent pas à chaque requête.
- Elles partent quand une édition part.
- Seulement si le fichier touché correspond au `applyTo`.

> [!note] Définition — applyTo
> Motif de chemin.
> Fichier `*.instructions.md`.
> L'instruction part si le fichier correspond.

- Un agent configuré part au moment du choix.
- Il porte le rôle et la liste des outils.
- Il ne part pas avant ce choix.
- Un skill part si la tâche correspond à sa description.
- L'instruction est payée en tokens sur cette édition.
- Le skill est payé seulement s'il est chargé.

| Configuration | Fichier |
| ------------- | ------- |
| Instruction | `.github/instructions/`<br>`*.instructions.md` |
| Agent | `.github/agents/`<br>`*.agent.md` |
| Skill | `.github/skills/<nom>/`<br>`SKILL.md` |

## Les en-têtes

- Chaque type a sa liste d'en-têtes.
- La page donne la liste complète.

| Type | En-têtes | Liste |
| ---- | -------- | ----- |
| Instruction | `name`<br>`description`<br>`applyTo` | [Liste des en-têtes](https://code.visualstudio.com/docs/agent-customization/custom-instructions#_instructions-file-format) |
| Agent | `description`<br>`name`<br>`tools` | [Liste des en-têtes](https://code.visualstudio.com/docs/agent-customization/custom-agents#_header-optional) |
| Skill | `name`<br>`description` | [Liste des en-têtes](https://code.visualstudio.com/docs/agent-customization/agent-skills#_header-required) |
