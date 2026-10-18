const read = readInvoices("factures.csv");
const real = read.filter((item) => item.id !== -1);
if (real.length !== 15 || read[read.length - 1].id !== -1) {
  throw new Error("the array read must hold 15 invoices then id -1");
}

const journal: Invoice[] = [
  { id: 1, reference: "FAC-1042" },
  { id: 2, reference: "FAC-1043" },
  { id: 3, reference: "FAC-1044" },
  { id: 4, reference: "FAC-1045" },
];
postToJournal("factures.csv", journal);
const ids = journal.map((item) => item.id);
const expected = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15];
if (ids.length !== expected.length || ids.some((id, index) => id !== expected[index])) {
  throw new Error("expected: ids 1 to 15, in order");
}
for (const already of [1, 2, 3, 4]) {
  if (ids.filter((id) => id === already).length !== 1) {
    throw new Error(`invoice ${already} must appear only once`);
  }
}

for (const item of journal) {
  console.log(item.id, item.reference);
}
console.log("ok");
