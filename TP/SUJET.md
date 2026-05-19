# TP — mini_push_swap

## Contexte

Le **push_swap** est un exercice classique de manipulation de structures de données : trier des entiers en n'utilisant que **deux piles** (`a` et `b`) et un petit ensemble d'**opérations** (`sa`, `pb`, `ra`, etc.). On ne trie pas directement un tableau : chaque déplacement passe par les piles.

Ce TP en propose une **version réduite**, adaptée à un cours C et à l'usage de GitHub Copilot.

---

## Objectif

Écrire un programme **`push_swap`** qui :

1. Reçoit entre **2 et 50** entiers **strictement positifs**, tous **distincts**, en arguments.
2. Affiche sur la sortie standard une **suite d'opérations** (une par ligne).
3. Applique ces opérations sur deux piles pour que **`a` soit triée en ordre croissant** (du plus petit en bas au plus grand au sommet).

### Exemple

```bash
./push_swap 3 1 2
```

Sortie possible :

```
sa
pb
pb
pa
pa
```

État final de la pile `a` (bas → haut) : `1  2  3`.

Vérification avec le checker fourni :

```bash
./push_swap 3 1 2 | ./checker 3 1 2
echo $?   # doit afficher 0
```

---

## Périmètre du TP

| Version « complète » classique      | Ce TP                                                  |
| ----------------------------------- | ------------------------------------------------------ |
| Centaines de valeurs                | **2 à 50** valeurs                                     |
| Optimisation du nombre d'opérations | **Tri correct** obligatoire ; score d'ops en **bonus** |
| Arborescence imposée                | Structure suggérée, organisation libre                 |
| Checker à écrire                    | **Checker fourni**                                     |
| Algorithmes avancés                 | Piles, opérations et **stratégie de tri à concevoir**  |

---

## Modèle des piles

- **`a`** : contient tous les nombres au départ. Le **premier argument** est en **bas**, le **dernier** au **sommet**.
- **`b`** : vide au départ.

```
$ ./push_swap 2 1 3

Pile a (bas → haut) :  2  1  3     ← sommet = 3
Pile b                : (vide)
```

Représentation au choix : **liste chaînée** (recommandée pour 50 valeurs) ou **tableau dynamique / de taille fixe** (`STACK_MAX` = 50 dans le squelette), tant que les opérations respectent la sémantique ci-dessous.

---

## Opérations à implémenter

Chaque opération modifie les piles. Si l'opération est **valide**, `push_swap` l'**affiche** sur `stdout` (une ligne par opération). Sinon, elle ne fait rien et **n'est pas affichée**.

| Op    | Effet                                                        |
| ----- | ------------------------------------------------------------ |
| `sa`  | Échange les **2 premiers** éléments de `a` (les 2 au sommet) |
| `sb`  | Échange les **2 premiers** éléments de `b`                   |
| `ss`  | `sa` + `sb` (une seule ligne `ss`)                           |
| `pa`  | Retire le sommet de `b`, l'empile sur `a`                    |
| `pb`  | Retire le sommet de `a`, l'empile sur `b`                    |
| `ra`  | Sommet de `a` envoyé en **bas** de `a`                       |
| `rb`  | Idem sur `b`                                                 |
| `rr`  | `ra` + `rb` (une seule ligne `rr`)                           |
| `rra` | Élément du **bas** de `a` remonté au sommet                  |
| `rrb` | Idem sur `b`                                                 |
| `rrr` | `rra` + `rrb` (une seule ligne `rrr`)                        |

## Parsing et gestion d'erreurs

| Entrée                                                                      | Comportement                       |
| --------------------------------------------------------------------------- | ---------------------------------- |
| Aucun argument                                                              | Pas de sortie, code `0`            |
| Argument non entier, `≤ 0`, doublon, ou **moins de 2 / plus de 50** valeurs | `Error\n` sur **stderr**, code `1` |

Exemples :

```bash
./push_swap          # rien, exit 0
./push_swap 1 1      # Error, exit 1
./push_swap -3 2     # Error, exit 1
./push_swap 1 2 abc  # Error, exit 1
./push_swap 42       # Error (un seul entier), exit 1
```

---

## Organisation du code (recommandée)

```
TP/
├── SUJET.md
├── Makefile
├── include/
│   └── stack.h
└── src/
    ├── stack.c          # pile : init, push, pop, triée ?, libération
    ├── operations.c     # sa, sb, … rrr (fourni)
    ├── parse.c          # validation des arguments (fourni)
    ├── sort.c           # stratégie de tri — **à compléter**
    ├── push_swap.c      # main
    └── checker.c        # fourni : lit stdin, exécute les ops
```

Fonctions minimales attendues :

- **Pile** : création depuis les arguments, libération sans fuite.
- **Opérations** : chaque op prend les piles et un flag `print` (réutilisé par le checker).
- **Tri** : `void sort_stacks(t_stack *a, t_stack *b);` enchaîne les ops jusqu'à `a` triée.

---

## Compilation et tests

```bash
cd TP

./push_swap 5 2 8 1 4 | ./checker 5 2 8 1 4
echo $?   # 0 = OK, 1 = tri ou ops incorrects

```

---

## GitHub Copilot — consignes du TP

1. **Commentaires-prompts** avant chaque bloc (`// pb : dépile le sommet de a, empile sur b`).
2. Garder **`stack.h`** ouvert pendant l'écriture de `operations.c`.
3. Utiliser le **Chat** pour expliquer le tri à 3 éléments, pas pour livrer une solution non comprise.
4. **Valider** avec le checker et `gcc -Wall -Wextra -fsanitize=address`.

---

## Rendu

- Dépôt ou archive contenant `TP/` compilable avec `make`.
- Court `README` : nom, commandes de compilation et de test.

---

## Schéma

```
     push_swap                         checker
  ┌─────────────┐                  ┌─────────────┐
  │ argv → pile │  ops sur stdout  │ argv → pile │
  │ tri → ops   │ ───────────────► │ lit stdin   │
  └─────────────┘                  │ exécute ops │
                                   │ vérifie tri │
                                   └─────────────┘
```
