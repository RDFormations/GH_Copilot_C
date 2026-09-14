# Correction — Introduction à GitHub Copilot

> **Exercice** : [Revoir l'énoncé](../exercices/fr/exercice-01-introduction.md)

## Contexte

Vérifiez que Copilot est opérationnel avant de poursuivre les modules suivants.

## Correction détaillée

### Étape 1 — Installation

**Attendu :** extensions Copilot + Chat installées ; icône active.

### Étape 2 — Signature et commentaire

```c
/** Formate un ID ticket : préfixe FB-, numéro sur 5 chiffres. */
char* format_id(int id); {
```

### Étape 3 — Acceptation et test

**Vérification :** `strcmp(format_id(42), "ID-00042") == 0`

## Pièges fréquents

| Symptôme | Piste |
| -------- | ----- |
| Pas de suggestion | Vérifier licence Copilot et connexion GitHub |
| Format incorrect (FB-42) | Préciser zéros à gauche dans le commentaire |


## Documentation

| Sujet | Lien |
| ----- | ---- |
| Bonnes pratiques | [Best practices](https://docs.github.com/copilot/get-started/best-practices-for-using-github-copilot) |
