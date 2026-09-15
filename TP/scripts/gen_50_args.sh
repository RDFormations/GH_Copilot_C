#!/usr/bin/env bash
# Génère 50 entiers strictement positifs, tous distincts (un par ligne ou sur une ligne).
set -euo pipefail

gen_50_args_line() {
	if command -v python3 >/dev/null 2>&1; then
		python3 -c "import random; print(' '.join(map(str, random.sample(range(1, 1_000_001), 50))))"
	elif command -v python >/dev/null 2>&1; then
		python -c "import random; print(' '.join(map(str, random.sample(range(1, 1000001), 50))))"
	else
		echo "Erreur: python3 requis pour générer 50 valeurs distinctes." >&2
		return 1
	fi
}
