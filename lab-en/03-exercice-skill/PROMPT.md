- Exercise — get the slides skill
  - Goal
    - Paste the prompt below into the agent chat
    - Attach both files at the same time: the ST PowerPoint template, and the layout library
    - The agent writes the skill from start to finish. It does not stop to ask a question
  - What this exercise is not
    - Do not ask the agent to write the employee import or the invoice posting
    - The prompt does not contain the skill. It makes the agent produce it
  - Before pasting
    - Both files are attached to the message
    - Nothing else is attached

---

Create the Copilot skill `st-slides`. Write it. Run it. Fix it until the proof passes. You work alone, from start to finish. You ask no question. You do not stop to request a choice.

The two attached files are the charter:

- the ST PowerPoint template
- the layout library

Read them in full before creating a file. Copy them into the skill, under `assets/`. The charter is what these two files say: masters, layouts, colors, fonts, logo, margins, sizes, and the role of each layout. Do not invent a color, a font, a logo, or a margin.

Each slide uses a layout that exists in the layout library. The script reads that library. For each slide, it prints the chosen layout identifier. It rejects an identifier that is not in the library.

The template and the layout library contain no chart. That is expected. Do not look for a chart layout. Do not stop. Do not report it as a blocker. A chart is not a layout.

For a slide that carries numbers:

1. Take a layout from the layout library that has a title and a body area.
2. Read the position and the size of the body placeholder.
3. Draw the chart with `python-pptx` inside that rectangle.
4. Put the title in the title placeholder.

A series over time becomes a line chart. Shares of a total become a pie chart. Compared categories become bars. Chart colors come from the template.

Text that is not a number goes into the placeholders of the chosen layout. No text box placed beside them.

Content is generated as JSON. No YAML. No Markdown. The script reads only that JSON. It does not rebuild the slides from free text.

Put the skill here, and only here:

```text
.github/skills/st-slides/
├── SKILL.md
├── assets/                  # the ST template and the layout library, copied
├── scripts/build_deck.py    # the only pptx generator
├── examples/brief.json      # the proof content, as JSON
└── requirements.txt
```

`SKILL.md` has this frontmatter, with a description that cites the words slides, PPTX, présentation, deck, and PowerPoint, in French and in English:

```yaml
---
name: st-slides
description: >
  Builds an ST-charter PPTX from JSON content, via scripts/build_deck.py.
  Produit un PPTX à la charte ST à partir d'un contenu JSON, via scripts/build_deck.py.
  Use when the user asks for slides, a deck, a PPTX, a PowerPoint, a presentation, or une présentation.
---
```

The body of `SKILL.md` tells the agent, for each slides request:

1. Write the content as JSON.
2. Choose a real layout from the layout library for each slide.
3. Run `python scripts/build_deck.py`. Do not write the PPTX by hand, nor in XML, nor in the chat.
4. If the JSON has `series` or `parts`, the slide contains a chart in the body area. Those numbers are not bullets.

The Python script is the only place that builds the file. It uses `python-pptx`. It opens the ST template as the base. It does not start from an empty presentation. It does not drive PowerPoint through COM.

Script contract:

```text
python scripts/build_deck.py \
  --content examples/brief.json \
  --template assets/<ST template> \
  --layouts assets/<layout library> \
  --out examples/preuve.pptx
```

Proof JSON. Replace the layout identifiers with identifiers read from the layout library. Keep the numbers: they are what becomes charts.

```json
{
  "title": "Quality of the quarter",
  "slides": [
    {
      "intent": "opening",
      "title": "Quality of the quarter",
      "subtitle": "Skill demonstration"
    },
    {
      "intent": "time-series",
      "title": "Open defects",
      "series": [
        { "name": "Critical", "points": { "Q1": 12, "Q2": 7, "Q3": 4 } },
        { "name": "Major", "points": { "Q1": 30, "Q2": 28, "Q3": 21 } }
      ]
    },
    {
      "intent": "parts",
      "title": "Defect split in Q3",
      "parts": { "Critical": 4, "Major": 21, "Minor": 15 }
    },
    {
      "intent": "closing",
      "title": "Reading",
      "bullets": [
        "Critical defects fall over three quarters",
        "Major defects stay the largest volume"
      ]
    }
  ]
}
```

Before finishing, run the script on this JSON. Answer only if the four points are true:

- `examples/preuve.pptx` exists and opens with `python-pptx`
- the slide count equals the number of JSON entries
- the pptx contains at least two charts: a line chart for the series, a pie chart for the shares
- none of the numbers 12, 7, 4, 30, 28, 21, 15 appears as text alone in a bullet or a title

If a point fails, fix the script and run it again. Do not declare the skill ready before this proof.
