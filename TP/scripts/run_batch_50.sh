#!/usr/bin/env bash
# Lance push_swap sur plusieurs jeux aléatoires de 50 valeurs.
# Usage : ./scripts/run_batch_50.sh [nombre_de_lances]
#   RUNS=10 ./scripts/run_batch_50.sh
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TP_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
# shellcheck source=gen_50_args.sh
source "$SCRIPT_DIR/gen_50_args.sh"

cd "$TP_DIR"

PUSH_SWAP="${PUSH_SWAP:-./push_swap}"
RUNS="${1:-${RUNS:-5}}"

if [[ ! -x "$PUSH_SWAP" ]]; then
	echo "Erreur: $PUSH_SWAP introuvable. Lancez 'make' dans $TP_DIR." >&2
	exit 1
fi

if ! [[ "$RUNS" =~ ^[1-9][0-9]*$ ]]; then
	echo "Usage: $0 [nombre_de_lances]" >&2
	exit 1
fi

echo "=== push_swap — $RUNS lance(s) avec 50 valeurs ==="
echo

total_ops=0
errors=0

for ((i = 1; i <= RUNS; i++)); do
	args="$(gen_50_args_line)"
	tmp="$(mktemp)"
	# shellcheck disable=SC2086
	if ! "$PUSH_SWAP" $args > "$tmp" 2>/dev/null; then
		echo "Lance $i/$RUNS : ERREUR (push_swap a échoué)"
		errors=$((errors + 1))
		rm -f "$tmp"
		continue
	fi
	ops="$(wc -l < "$tmp" | tr -d ' ')"
	rm -f "$tmp"
	total_ops=$((total_ops + ops))
	first="${args%% *}"
	echo "Lance $i/$RUNS : $ops opération(s)  (première valeur: $first)"
done

echo
if [[ "$errors" -gt 0 ]]; then
	echo "Lances en erreur : $errors"
fi
success=$((RUNS - errors))
if [[ "$success" -gt 0 ]]; then
	avg=$((total_ops / success))
	echo "Total opérations : $total_ops"
	echo "Moyenne          : $avg opérations / lance réussie"
fi
