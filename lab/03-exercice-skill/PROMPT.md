- Exercice — obtenir le skill slides
  - But
    - Coller la prompt ci-dessous dans le chat de l'agent
    - Joindre en même temps les deux fichiers : le template PowerPoint ST, et la layout library
    - L'agent écrit le skill. Les stagiaires ne l'écrivent pas à la main
  - Ce que cet exercice n'est pas
    - On ne demande pas à l'agent d'écrire l'import des employés ni le passage des factures au journal
    - La prompt ne contient pas le skill. Elle le fait produire
  - Avant de coller
    - Les deux fichiers sont bien en pièces jointes du message
    - Rien d'autre n'est joint

---

Crée un skill Copilot qui produit des présentations PowerPoint ST. Écris le skill. Ne te contente pas de le décrire.

Les deux fichiers joints à ce message sont les seules sources de la charte :

- le template PowerPoint ST
- la layout library

Lis-les en entier avant de créer un fichier. La charte, c'est ce que ces deux fichiers disent : masters, layouts, couleurs, polices, logo, marges, tailles, et le rôle de chaque layout. N'invente aucune couleur, aucune police, aucun logo, aucune marge, aucun layout. Si un choix n'est pas dans ces fichiers, arrête-toi et demande. Ne prends pas une valeur par défaut.

Copie ces deux fichiers dans le skill, sous `assets/`, pour que le skill fonctionne encore quand la conversation sera finie.

Range le skill ici, et seulement ici :

```text
.github/skills/st-slides/
├── SKILL.md
├── assets/                  # le template ST et la layout library, copiés
├── scripts/build_deck.py    # le seul générateur de pptx
├── examples/brief.yaml      # le brief de preuve ci-dessous, adapté aux vrais ids
└── requirements.txt
```

`SKILL.md` a ce frontmatter, avec une description qui cite les mots slides, PPTX, présentation, deck et PowerPoint, en français et en anglais :

```yaml
---
name: st-slides
description: >
  Produit un PPTX à la charte ST à partir d'un brief, via scripts/build_deck.py.
  Use when the user asks for slides, a deck, a PPTX, a PowerPoint, or a presentation.
---
```

Le corps de `SKILL.md` dit à l'agent, pour chaque demande de slides :

1. Lire le brief de l'utilisateur.
2. Choisir un layout réel de la layout library pour chaque slide. Si aucun layout ne correspond, demander, ne pas en fabriquer un.
3. Lancer `python scripts/build_deck.py` avec le brief, le template et la layout library. Ne pas écrire le PPTX à la main, ni en XML, ni dans le chat.
4. Vérifier le fichier produit avant de répondre.

Le script Python est le seul endroit qui construit le fichier. Il utilise `python-pptx`. Il ouvre le template ST comme base. Il ne part pas d'une présentation vide. Il ne pilote pas PowerPoint par COM.

Contrat du script :

```text
python scripts/build_deck.py \
  --brief examples/brief.yaml \
  --template assets/<template ST> \
  --layouts assets/<layout library> \
  --out examples/preuve.pptx
```

Règles de rendu, à écrire dans le script et dans `SKILL.md` :

- Chaque slide utilise un layout qui existe dans la layout library. Le script affiche, pour chaque slide, l'identifiant de layout choisi.
- Toute valeur numérique du brief est dessinée comme un graphique : un compte, un montant, un pourcentage, une durée, une série. Le nombre n'est pas une puce, ni un tableau de chiffres, ni une phrase.
- Une série dans le temps devient une courbe. Des parts d'un total deviennent un graphique en secteurs, ou un empilé si la library n'a que celui-là. Des catégories comparées deviennent des barres.
- Le type de graphique et sa position viennent de la layout library. S'il n'existe aucun layout de graphique, arrête-toi et dis-le. Ne place pas un graphique en coordonnées inventées.
- Le texte hors chiffres suit le layout choisi : titre, sous-titre, puces. Pas de zone de texte posée en dehors des emplacements du layout.
- Les couleurs du graphique viennent du template. Ne pose pas une palette à la main.

Brief de preuve. Les identifiants de layout de cet exemple sont fictifs : remplace-les par des identifiants lus dans la layout library. Garde les chiffres, ce sont eux qui doivent devenir des graphiques.

```yaml
title: Qualité du trimestre
slides:
  - intent: ouverture
    title: Qualité du trimestre
    subtitle: Démonstration du skill
  - intent: serie-temporelle
    title: Défauts ouverts
    series:
      - name: Critiques
        points: { T1: 12, T2: 7, T3: 4 }
      - name: Majeurs
        points: { T1: 30, T2: 28, T3: 21 }
  - intent: parts
    title: Répartition des défauts au T3
    parts: { Critiques: 4, Majeurs: 21, Mineurs: 15 }
  - intent: cloture
    title: Lecture
    bullets:
      - Les critiques baissent sur trois trimestres
      - Les majeurs restent le premier volume
```

Avant de terminer, exécute le script sur ce brief et ne réponds que si les quatre points sont vrais :

- `examples/preuve.pptx` existe et s'ouvre avec `python-pptx`
- le nombre de slides est égal au nombre d'entrées du brief
- le pptx contient au moins deux graphiques, un pour la série temporelle et un pour les parts
- aucun des nombres 12, 7, 4, 30, 28, 21, 15 n'apparaît comme texte seul dans une puce ou un titre

Si un point échoue, corrige le script et relance. Ne déclare pas le skill prêt avant cette preuve.
