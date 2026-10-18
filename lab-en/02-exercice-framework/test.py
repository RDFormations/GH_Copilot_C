def check():
    read = read_invoices("factures.csv")
    real = [item for item in read if item.id != -1]
    if len(real) != 15 or read[-1].id != -1:
        raise SystemExit("the array read must hold 15 invoices then id -1")

    journal = [
        Invoice(1, "FAC-1042"),
        Invoice(2, "FAC-1043"),
        Invoice(3, "FAC-1044"),
        Invoice(4, "FAC-1045"),
    ]
    post_to_journal("factures.csv", journal)
    ids = [item.id for item in journal]
    if ids != list(range(1, 16)):
        raise SystemExit("expected: ids 1 to 15, in order")
    for already in range(1, 5):
        if ids.count(already) != 1:
            raise SystemExit(f"invoice {already} must appear only once")

    for item in journal:
        print(item.id, item.reference)
    print("ok")


if __name__ == "__main__":
    check()
