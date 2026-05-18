#!/usr/bin/env python3
import sys
import os


def remove_comments(code: str) -> str:
    res = []
    i = 0
    n = len(code)
    in_string = False
    string_char = ''
    escaped = False
    in_single = False
    in_multi = False
    while i < n:
        c = code[i]
        nxt = code[i + 1] if i + 1 < n else ''
        if in_single:
            if c == '\n':
                in_single = False
                res.append(c)
            i += 1
            continue
        if in_multi:
            if c == '*' and nxt == '/':
                in_multi = False
                i += 2
            else:
                i += 1
            continue
        if in_string:
            res.append(c)
            if escaped:
                escaped = False
            else:
                if c == '\\':
                    escaped = True
                elif c == string_char:
                    in_string = False
            i += 1
            continue
        # not in comment or string
        if c == '/' and nxt == '/':
            in_single = True
            i += 2
            continue
        if c == '/' and nxt == '*':
            in_multi = True
            i += 2
            continue
        if c == '"' or c == "'":
            in_string = True
            string_char = c
            res.append(c)
            i += 1
            continue
        res.append(c)
        i += 1
    return ''.join(res)


def process_file(src_path: str, dst_path: str) -> None:
    with open(src_path, 'r', encoding='utf-8') as f:
        code = f.read()
    out = remove_comments(code)
    with open(dst_path, 'w', encoding='utf-8') as f:
        f.write(out)


def main():
    if len(sys.argv) < 3:
        print('Usage: remove_comments.py <src_dir> <dst_dir>')
        sys.exit(1)
    src_dir = sys.argv[1]
    dst_dir = sys.argv[2]
    if not os.path.isdir(src_dir):
        print(f"Source directory not found: {src_dir}")
        sys.exit(1)
    os.makedirs(dst_dir, exist_ok=True)
    count = 0
    for root, _, files in os.walk(src_dir):
        rel = os.path.relpath(root, src_dir)
        target_root = os.path.join(dst_dir, rel) if rel != '.' else dst_dir
        os.makedirs(target_root, exist_ok=True)
        for fname in files:
            if fname.endswith('.c') or fname.endswith('.h'):
                src_path = os.path.join(root, fname)
                dst_path = os.path.join(target_root, fname)
                process_file(src_path, dst_path)
                count += 1
    print(f"Processed {count} files into {dst_dir}")


if __name__ == '__main__':
    main()
