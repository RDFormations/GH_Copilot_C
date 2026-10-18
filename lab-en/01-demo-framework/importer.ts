export const NAME_MAX = 64;

export type Employee = {
  id: number;
  name: string;
};

export function countLines(path: string): number {
}

export function allocateEmployees(count: number): Employee[] {
}

export function fillEmployee(line: string, table: Employee[], index: number): void {
}

export function markSentinel(table: Employee[], count: number): void {
}

export function readEmployees(path: string): Employee[] {
}

export function employeeExists(directory: Employee[], employee: Employee): boolean {
}

export function addEmployee(directory: Employee[], employee: Employee): void {
}

export function importEmployees(path: string, directory: Employee[]): void {
}

const directory: Employee[] = [
  { id: 1, name: "Camille" },
  { id: 2, name: "Louis" },
  { id: 3, name: "Ines" },
  { id: 4, name: "Hugo" },
];
importEmployees("employes.csv", directory);
const ids = directory.map((employee) => employee.id);
const expected = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15];
if (ids.length !== expected.length || ids.some((id, index) => id !== expected[index])) {
  throw new Error("expected: ids 1 to 15, in order");
}
for (const employee of directory) {
  console.log(employee.id, employee.name);
}
console.log("ok");
