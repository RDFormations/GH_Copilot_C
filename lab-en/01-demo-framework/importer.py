NAME_MAX = 64


class Employee:
    def __init__(self, id=0, name=""):
        self.id = id
        self.name = name


def count_lines(path):
    pass


def allocate_employees(count):
    pass


def fill_employee(line, table, index):
    pass


def mark_sentinel(table, count):
    pass


def read_employees(path):
    pass


def employee_exists(directory, employee):
    pass


def add_employee(directory, employee):
    pass


def import_employees(path, directory):
    pass


def main():
    directory = [
        Employee(1, "Camille"),
        Employee(2, "Louis"),
        Employee(3, "Ines"),
        Employee(4, "Hugo"),
    ]
    import_employees("employes.csv", directory)
    ids = [employee.id for employee in directory]
    if ids != list(range(1, 16)):
        raise SystemExit("expected: ids 1 to 15, in order")
    for employee in directory:
        print(employee.id, employee.name)
    print("ok")


if __name__ == "__main__":
    main()
