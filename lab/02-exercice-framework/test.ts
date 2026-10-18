const lues = lireFactures("factures.csv");
const reelles = lues.filter((item) => item.id !== -1);
if (reelles.length !== 15 || lues[lues.length - 1].id !== -1) {
  throw new Error("le tableau lu doit contenir 15 factures puis id -1");
}

const journal: Facture[] = [
  { id: 1, reference: "FAC-1042" },
  { id: 2, reference: "FAC-1043" },
  { id: 3, reference: "FAC-1044" },
  { id: 4, reference: "FAC-1045" },
];
comptabiliser("factures.csv", journal);
const ids = journal.map((item) => item.id);
const attendu = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15];
if (ids.length !== attendu.length || ids.some((id, index) => id !== attendu[index])) {
  throw new Error("attendu : les ids 1 à 15, dans l'ordre");
}
for (const deja of [1, 2, 3, 4]) {
  if (ids.filter((id) => id === deja).length !== 1) {
    throw new Error(`la facture ${deja} ne doit apparaître qu'une fois`);
  }
}

for (const item of journal) {
  console.log(item.id, item.reference);
}
console.log("ok");
