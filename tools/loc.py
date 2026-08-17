#!/usr/bin/env python3
"""统计代码行数。

用法:
  tools/loc.py                  # 统计全部代码
  tools/loc.py luogu ybt        # 只统计指定目录
  tools/loc.py --no-comment     # 不算注释行（含 //、/* */ 的行）
  tools/loc.py --no-blank       # 不算空行
  tools/loc.py --top            # 只看各顶层目录汇总，不展开每题

按目录分组统计各源码文件的行数，自动跳过 .git/、build/、*.dSYM。
"""
from __future__ import annotations

import argparse
import os
import sys
from collections import defaultdict
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
SRC_EXTS = {".c", ".cc", ".cpp", ".cxx", ".h", ".hpp", ".py", ".sh", ".md"}
SKIP_DIRS = {".git", "build", "__pycache__"}
SKIP_SUFFIX = {".dSYM"}


def should_skip(path: Path) -> bool:
    return (
        path.name.startswith(".")
        or path.name in SKIP_DIRS
        or path.suffix in SKIP_SUFFIX
    )


def is_source(p: Path) -> bool:
    return p.suffix.lower() in SRC_EXTS


def count_lines(p: Path, *, count_comment: bool, count_blank: bool) -> tuple[int, int]:
    """返回 (总行数, 有效行数)。"""
    total = code = 0
    with open(p, encoding="utf-8", errors="replace") as f:
        for line in f:
            total += 1
            stripped = line.strip()
            if not count_blank and not stripped:
                continue
            if not count_comment and stripped.startswith(("//", "#", "/*", "*")):
                continue
            code += 1
    return total, code


def walk_files(roots: list[Path]) -> list[Path]:
    files: list[Path] = []
    for root in roots:
        for dirpath, dirnames, filenames in os.walk(root):
            dirpath = Path(dirpath)
            dirnames[:] = [d for d in dirnames if not should_skip(dirpath / d)]
            for name in filenames:
                p = dirpath / name
                if should_skip(p):
                    continue
                if is_source(p):
                    files.append(p)
    return sorted(files)


def format_row(cols: list[str], widths: list[int]) -> str:
    return "  ".join(c.ljust(w) for c, w in zip(cols, widths))


def main() -> int:
    parser = argparse.ArgumentParser(
        description="统计代码行数",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="示例:\n  tools/loc.py\n  tools/loc.py luogu\n  tools/loc.py --top --no-comment",
    )
    parser.add_argument("dirs", nargs="*", help="要统计的目录（默认全部）")
    parser.add_argument("--no-comment", action="store_true", help="不算注释行")
    parser.add_argument("--no-blank", action="store_true", help="不算空行")
    parser.add_argument("--top", action="store_true", help="只看顶层目录汇总")
    args = parser.parse_args()

    roots = (
        [REPO_ROOT / d for d in args.dirs]
        if args.dirs
        else [REPO_ROOT]
    )
    for r in roots:
        if not r.exists():
            print(f"错误: 目录不存在: {r}", file=sys.stderr)
            return 2

    files = walk_files(roots)
    if not files:
        print("未找到源码文件")
        return 2

    # (顶层目录, 相对路径, 总行数, 有效行数)
    rows: list[tuple[str, str, int, int]] = []
    for p in files:
        top = p.relative_to(REPO_ROOT).parts[0]
        rel = str(p.relative_to(REPO_ROOT))
        total, code = count_lines(p, count_comment=args.no_comment, count_blank=args.no_blank)
        rows.append((top, rel, total, code))

    if args.top:
        agg: dict[str, list[int]] = defaultdict(lambda: [0, 0, 0])
        for top, _, total, code in rows:
            agg[top][0] += 1
            agg[top][1] += total
            agg[top][2] += code
        header = ["目录", "文件数", "总行数", "有效行数"]
        widths = [max(len(h), max((len(k) for k in agg), default=0)) for h in header[:1]] + [
            len("文件数"),
            len("总行数"),
            len("有效行数"),
        ]
        widths[0] = max(len("目录"), *(len(k) for k in agg))
        print(format_row(header, widths))
        print(format_row(["-" * w for w in widths], widths))
        tot_f = tot_l = tot_c = 0
        for key in sorted(agg):
            n, tl, cl = agg[key]
            tot_f += n; tot_l += tl; tot_c += cl
            print(format_row([key, str(n), str(tl), str(cl)], widths))
        print(format_row(["-" * w for w in widths], widths))
        print(format_row(["合计", str(tot_f), str(tot_l), str(tot_c)], widths))
        return 0

    header = ["目录", "文件", "总行数", "有效行数"]
    widths = [8, max(len("文件"), *(len(r[1]) for r in rows)), 8, 8]
    print(format_row(header, widths))
    print(format_row(["-" * w for w in widths], widths))
    tot_f = tot_l = tot_c = 0
    for top, rel, total, code in rows:
        tot_f += 1; tot_l += total; tot_c += code
        print(format_row([top, rel, str(total), str(code)], widths))
    print(format_row(["-" * w for w in widths], widths))
    print(format_row(["合计", f"{tot_f} 个文件", str(tot_l), str(tot_c)], widths))
    return 0


if __name__ == "__main__":
    sys.exit(main())
