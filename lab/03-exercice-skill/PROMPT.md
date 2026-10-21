- Exercice — obtenir le skill slides
  - But
    - Coller la prompt ci-dessous dans le chat de l'agent
    - Joindre en même temps les deux fichiers : le template PowerPoint ST, et la layout library
    - L'agent écrit le skill de bout en bout. Il ne s'arrête pas pour poser une question
  - Ce que cet exercice n'est pas
    - On ne demande pas à l'agent d'écrire l'import des employés ni le passage des factures au journal
    - La prompt ne contient pas le skill. Elle le fait produire
  - Avant de coller
    - Les deux fichiers sont bien en pièces jointes du message
    - Rien d'autre n'est joint

---

Crée le skill Copilot `st-slides`. Écris-le. Exécute-le. Corrige-le jusqu'à la preuve. Tu travailles seul, de bout en bout. Tu ne poses aucune question. Tu ne t'arrêtes pas pour demander un choix.

Les deux fichiers joints sont la charte :

- le template PowerPoint ST
- la layout library

Lis-les en entier avant de créer un fichier. Copie-les dans le skill, sous `assets/`. La charte, c'est ce que ces deux fichiers disent : masters, layouts, couleurs, polices, logo, marges, tailles, et le rôle de chaque layout. N'invente aucune couleur, aucune police, aucun logo, aucune marge.

Chaque slide utilise un layout qui existe dans la layout library. Le script lit cette library. Il affiche, pour chaque slide, l'identifiant de layout choisi. Il refuse un identifiant absent de la library.

Le template et la layout library ne contiennent pas de graphique. C'est normal. Ne cherche pas un layout de graphique. Ne t'arrête pas. Ne le signale pas comme un blocage. Un graphique n'est pas un layout.

Pour une slide qui porte des nombres :

1. Prends dans la layout library un layout qui a un titre et une zone de corps.
2. Lis la position et la taille du placeholder de corps.
3. Dessine le graphique avec `python-pptx` dans ce rectangle.
4. Mets le titre dans le placeholder de titre.

Une série dans le temps devient une courbe. Des parts d'un total deviennent un graphique en secteurs. Des catégories comparées deviennent des barres. Les couleurs du graphique viennent du template.

Le texte hors chiffres va dans les placeholders du layout choisi. Pas de zone de texte posée à côté.

Le contenu se génère en JSON. Pas de YAML. Pas de Markdown.

`scripts/build_deck.py` est écrit une seule fois, pendant la création du skill. Il prend ce JSON et le transforme directement en PPTX. Les textes et les chiffres viennent du JSON. Ils ne sont pas écrits en dur dans le script.

L'agent qui utilisera le skill ensuite ne recrée pas de script. Il écrit un nouveau JSON. Il relance le même `build_deck.py`. Il ne le réécrit pas. Il ne le modifie pas pour changer de présentation. `SKILL.md` l'interdit.

Range le skill ici, et seulement ici :

```text
.github/skills/st-slides/
├── SKILL.md
├── assets/                  # le template ST et la layout library, copiés
├── scripts/build_deck.py    # écrit une fois : JSON vers PPTX, réutilisé tel quel
├── examples/brief.json      # le contenu de preuve, en JSON
└── requirements.txt
```

`SKILL.md` a ce frontmatter, avec une description qui cite les mots slides, PPTX, présentation, deck et PowerPoint, en français et en anglais :

```yaml
---
name: st-slides
description: >
  Produit un PPTX à la charte ST à partir d'un contenu JSON, via scripts/build_deck.py.
  Use when the user asks for slides, a deck, a PPTX, a PowerPoint, or a presentation.
---
```

Le corps de `SKILL.md` dit à l'agent, pour chaque demande de slides :

1. Écrire seulement un JSON de contenu. Ne pas écrire de Python.
2. Ne pas créer un autre script. Ne pas modifier `scripts/build_deck.py`.
3. Lancer le script déjà présent : `python scripts/build_deck.py`. Ne pas écrire le PPTX à la main, ni en XML, ni dans le chat.
4. Si le JSON a `series` ou `parts`, la slide contient un graphique dans la zone de corps. Ces nombres ne sont pas des puces.

Le script Python est le seul endroit qui construit le fichier. Il utilise `python-pptx`. Il ouvre le template ST comme base. Il ne part pas d'une présentation vide. Il ne pilote pas PowerPoint par COM. Il parcourt les slides du JSON. Un autre JSON, avec d'autres titres et d'autres chiffres, passe par le même script sans le modifier.

Contrat du script :

```text
python scripts/build_deck.py \
  --content examples/brief.json \
  --template assets/<template ST> \
  --layouts assets/<layout library> \
  --out examples/preuve.pptx
```

JSON de preuve. Remplace les identifiants de layout par des identifiants lus dans la layout library. Garde les chiffres : ce sont eux qui deviennent des graphiques.

```json
{
  "title": "Qualité du trimestre",
  "slides": [
    {
      "intent": "ouverture",
      "title": "Qualité du trimestre",
      "subtitle": "Démonstration du skill"
    },
    {
      "intent": "serie-temporelle",
      "title": "Défauts ouverts",
      "series": [
        { "name": "Critiques", "points": { "T1": 12, "T2": 7, "T3": 4 } },
        { "name": "Majeurs", "points": { "T1": 30, "T2": 28, "T3": 21 } }
      ]
    },
    {
      "intent": "parts",
      "title": "Répartition des défauts au T3",
      "parts": { "Critiques": 4, "Majeurs": 21, "Mineurs": 15 }
    },
    {
      "intent": "cloture",
      "title": "Lecture",
      "bullets": [
        "Les critiques baissent sur trois trimestres",
        "Les majeurs restent le premier volume"
      ]
    }
  ]
}
```

Avant de terminer, exécute le script sur ce JSON. Ne réponds que si les quatre points sont vrais :

- `examples/preuve.pptx` existe et s'ouvre avec `python-pptx`
- le nombre de slides est égal au nombre d'entrées du JSON
- le pptx contient au moins deux graphiques : une courbe pour la série, un secteur pour les parts
- aucun des nombres 12, 7, 4, 30, 28, 21, 15 n'apparaît comme texte seul dans une puce ou un titre

Si un point échoue, corrige le script et relance. Ne déclare pas le skill prêt avant cette preuve.
