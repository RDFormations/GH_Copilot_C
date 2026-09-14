# Correction — Completions inline et contexte

> **Exercice** : [Revoir l'énoncé](../exercices/fr/exercice-02-completions-inline.md)

## Correction détaillée

### Étape 2 — Stub A vague

**Analyse :** avec `// trier`, Copilot propose souvent un `.sort()` générique sans précision sur l'algorithme ni l'immutabilité.

### Étape 3 — Prompt structuré (stub A)

**Vérification :** algorithme de tri explicite (insertion ou bubble), copie non mutante, complexité mentionnée.

### Étape 5 — Stub B recherche dichotomique

**Corps type :** boucle while avec indices gauche/droite, retourne -1 si non trouvé.

## Pièges fréquents

| Symptôme | Piste |
| -------- | ----- |
| Tri in-place non voulu | Préciser « copie immuable » dans CONTRAINTES |
| Index -1 absent | Expliciter dans le commentaire |
