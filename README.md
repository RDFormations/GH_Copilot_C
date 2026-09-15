# GH Copilot — laboratoire C

Formation GitHub Copilot adaptée au **C** : cours (FR + EN), exercices guidés et TP mini push_swap.

## Contenu

| Dossier | Description |
| ------- | ----------- |
| `Cours.md` / `Cours.pdf` | Support FR (6 modules) |
| `CoursENG.md` / `CoursENG.pdf` | Course material EN |
| `exercices/fr/` | Énoncés FR + fichiers `.c` |
| `exercices/en/` | Exercise sheets EN + same `.c` stubs |
| `correction/fr/` | Corrections FR |
| `correction/en/` | Solutions EN |
| `TP/fr/SUJET.md` | Énoncé TP (français) |
| `TP/en/SUJET.md` | Lab assignment (English) |

## Exercices

Fichiers code : `exercices/fr/*.c` (identiques dans `en/`).

Énoncés :
- Français : `exercices/fr/exercice-*.md`
- English : `exercices/en/exercice-*.md`

## TP push_swap

Voir `TP/fr/SUJET.md` ou `TP/en/SUJET.md`.

```bash
cd TP
./push_swap 5 2 8 1 4 | ./checker 5 2 8 1 4
echo $?   # 0 = OK
```
