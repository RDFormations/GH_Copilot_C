- Exercise — get the slides skill
  - Goal
    - Paste the prompt below into the agent chat
    - Attach both files at the same time: the ST PowerPoint template, and the layout library
    - The agent writes the skill. The trainees do not write it by hand
  - What this exercise is not
    - Do not ask the agent to write the employee import or the invoice posting
    - The prompt does not contain the skill. It makes the agent produce it
  - Before pasting
    - Both files are attached to the message
    - Nothing else is attached

---

Create a Copilot skill that produces ST PowerPoint presentations. Write the skill. Do not only describe it.

The two files attached to this message are the only sources of the charter:

- the ST PowerPoint template
- the layout library

Read them in full before creating a file. The charter is what these two files say: masters, layouts, colors, fonts, logo, margins, sizes, and the role of each layout. Do not invent a color, a font, a logo, a margin, or a layout. If a choice is not in these files, stop and ask. Do not take a default value.

Copy these two files into the skill, under `assets/`, so the skill still works when the conversation is over.

Put the skill here, and only here:

```text
.github/skills/st-slides/
├── SKILL.md
├── assets/                  # the ST template and the layout library, copied
├── scripts/build_deck.py    # the only pptx generator
├── examples/brief.yaml      # the proof brief below, adapted to the real ids
└── requirements.txt
```

`SKILL.md` has this frontmatter, with a description that cites the words slides, PPTX, présentation, deck, and PowerPoint, in French and in English:

```yaml
---
name: st-slides
description: >
  Builds an ST-charter PPTX from a brief, via scripts/build_deck.py.
  Produit un PPTX à la charte ST à partir d'un brief, via scripts/build_deck.py.
  Use when the user asks for slides, a deck, a PPTX, a PowerPoint, a presentation, or une présentation.
---
```

The body of `SKILL.md` tells the agent, for each slides request:

1. Read the user's brief.
2. Choose a real layout from the layout library for each slide. If no layout matches, ask. Do not make one up.
3. Run `python scripts/build_deck.py` with the brief, the template, and the layout library. Do not write the PPTX by hand, nor in XML, nor in the chat.
4. Check the file produced before answering.

The Python script is the only place that builds the file. It uses `python-pptx`. It opens the ST template as the base. It does not start from an empty presentation. It does not drive PowerPoint through COM.

Script contract:

```text
python scripts/build_deck.py \
  --brief examples/brief.yaml \
  --template assets/<ST template> \
  --layouts assets/<layout library> \
  --out examples/preuve.pptx
```

Rendering rules, to write in the script and in `SKILL.md`:

- Each slide uses a layout that exists in the layout library. For each slide, the script prints the chosen layout identifier.
- Every numeric value in the brief is drawn as a chart: a count, an amount, a percentage, a duration, a series. The number is not a bullet, nor a table of figures, nor a sentence.
- A series over time becomes a line chart. Shares of a total become a pie chart, or a stacked chart if the library only has that one. Compared categories become bars.
- The chart type and its position come from the layout library. If no chart layout exists, stop and say so. Do not place a chart at invented coordinates.
- Text that is not a number follows the chosen layout: title, subtitle, bullets. No text box placed outside the layout placeholders.
- Chart colors come from the template. Do not set a palette by hand.

Proof brief. The layout identifiers in this example are fictional: replace them with identifiers read from the layout library. Keep the numbers. They are what must become charts.

```yaml
title: Quality of the quarter
slides:
  - intent: opening
    title: Quality of the quarter
    subtitle: Skill demonstration
  - intent: time-series
    title: Open defects
    series:
      - name: Critical
        points: { Q1: 12, Q2: 7, Q3: 4 }
      - name: Major
        points: { Q1: 30, Q2: 28, Q3: 21 }
  - intent: parts
    title: Defect split in Q3
    parts: { Critical: 4, Major: 21, Minor: 15 }
  - intent: closing
    title: Reading
    bullets:
      - Critical defects fall over three quarters
      - Major defects stay the largest volume
```

Before finishing, run the script on this brief and answer only if the four points are true:

- `examples/preuve.pptx` exists and opens with `python-pptx`
- the slide count equals the number of brief entries
- the pptx contains at least two charts, one for the time series and one for the shares
- none of the numbers 12, 7, 4, 30, 28, 21, 15 appears as text alone in a bullet or a title

If a point fails, fix the script and run it again. Do not declare the skill ready before this proof.
