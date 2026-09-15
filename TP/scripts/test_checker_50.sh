#!/usr/bin/env bash
# Lance push_swap | checker avec 50 valeurs aléatoires.
# Usage : ./scripts/test_checker_50.sh [nombre_de_tests]
#   RUNS=3 ./scripts/test_checker_50.sh
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TP_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
# shellcheck source=gen_50_args.sh
source "$SCRIPT_DIR/gen_50_args.sh"

cd "$TP_DIR"

PUSH_SWAP="${PUSH_SWAP:-./push_swap}"
CHECKER="${CHECKER:-./checker}"
RUNS="${1:-${RUNS:-1}}"

if [[ ! -x "$PUSH_SWAP" ]]; then
	echo "Erreur: $PUSH_SWAP introuvable. Lancez 'make' dans $TP_DIR." >&2
	exit 1
fi

if [[ ! -x "$CHECKER" ]]; then
	echo "Erreur: $CHECKER introuvable. Lancez 'make' dans $TP_DIR." >&2
	exit 1
fi

if ! [[ "$RUNS" =~ ^[1-9][0-9]*$ ]]; then
	echo "Usage: $0 [nombre_de_tests]" >&2
	exit 1
fi

echo "=== push_swap | checker — $RUNS test(s) à 50 valeurs ==="
echo

ok=0
fail=0
tmp="$(mktemp)"
trap 'rm -f "$tmp"' EXIT

for ((i = 1; i <= RUNS; i++)); do
	args="$(gen_50_args_line)"
	# shellcheck disable=SC2086
	result="$("$PUSH_SWAP" $args | "$CHECKER" $args)"
	if [[ "$result" != "OK" ]]; then
		echo "Test $i/$RUNS : FAIL"
		fail=$((fail + 1))
	else
		echo "Test $i/$RUNS : OK"
		ok=$((ok + 1))
	fi
done

echo
echo "Résultat : $ok OK, $fail FAIL sur $RUNS test(s)"
[[ "$fail" -eq 0 ]]
