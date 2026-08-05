#!/usr/bin/env python3
"""一键编译并测试刷题代码。

用法:
  tools/test.py luogu/p1004.cpp            # 编译（如需要）并运行全部测试数据
  tools/test.py luogu/p1004.cpp --rebuild  # 强制重新编译
  tools/test.py luogu/p1004.cpp --strict   # 严格逐字节对比输出
  tools/test.py luogu/p1004.cpp --timeout 5   # 单用例超时（秒）

测试数据约定（放在源码同目录）:
  p1004.in / p1004.out                     # 单用例
  p1004.1.in / p1004.1.out ...             # 多用例（编号从 1 开始）
  p1004/1.in / 1.out ...                   # 或用子目录形式
  .out 也可用 .ans 结尾

退出码: 0 全部通过, 1 有用例失败, 2 未执行（无数据/未编译等）。
"""
from __future__ import annotations

import argparse
import difflib
import os
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402  (复用编译逻辑)

DEFAULT_TIMEOUT = 10.0
MAX_DIFF_LINES = 20


def discover_cases(src: Path) -> list[tuple[Path, Path]]:
    """按约定查找 (输入, 期望输出) 用例，去重并保持顺序。"""
    d, base = src.parent, src.stem
    cases: list[tuple[Path, Path]] = []

    # 形式 1: base.in + base.out/.ans
    inp = d / f"{base}.in"
    for ext in (".out", ".ans"):
        out = d / f"{base}{ext}"
        if inp.exists() and out.exists():
            cases.append((inp, out))
            break

    # 形式 2: base.N.in + base.N.out/.ans
    numbered = []
    for p in d.glob(f"{base}.*.in"):
        n = p.name[len(base) + 1 : -3]
        if n.isdigit():
            numbered.append((int(n), p))
    for _, p in sorted(numbered):
        out = d / f"{base}.{p.name[len(base)+1:-3]}.out"
        if not out.exists():
            out = d / f"{base}.{p.name[len(base)+1:-3]}.ans"
        if out.exists():
            cases.append((p, out))

    # 形式 3: base/1.in + 1.out/.ans
    sub = d / base
    if sub.is_dir():
        for p in sorted(sub.glob("*.in")):
            out = p.with_suffix(".out")
            if not out.exists():
                out = p.with_suffix(".ans")
            if out.exists():
                cases.append((p, out))

    seen: set[tuple[Path, Path]] = set()
    result = []
    for c in cases:
        if c not in seen:
            seen.add(c)
            result.append(c)
    return result


def normalize(text: str) -> list[str]:
    """宽松对比：统一换行、去行尾空白、忽略末尾空行。"""
    lines = [ln.rstrip() for ln in text.replace("\r\n", "\n").replace("\r", "\n").split("\n")]
    while lines and lines[-1] == "":
        lines.pop()
    return lines


def compare(actual: str, expected: str, strict: bool) -> bool:
    if strict:
        return actual == expected
    return normalize(actual) == normalize(expected)


def show_diff(actual: str, expected: str, limit: int = MAX_DIFF_LINES) -> str:
    exp_lines = expected.rstrip("\n").split("\n")
    act_lines = actual.rstrip("\n").split("\n")
    diff = list(
        difflib.unified_diff(
            exp_lines, act_lines, fromfile="期望", tofile="实际", lineterm=""
        )
    )
    lines = diff[:limit]
    if len(diff) > limit:
        lines.append(f"... 共 {len(diff)} 行差异，仅显示前 {limit} 行")
    return "\n".join(lines)


def main() -> int:
    parser = argparse.ArgumentParser(
        description="一键编译并测试刷题代码",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="测试数据约定见脚本顶部注释。",
    )
    parser.add_argument("source", help="源文件路径，如 luogu/p1004.cpp")
    parser.add_argument("--rebuild", action="store_true", help="强制重新编译")
    parser.add_argument("--no-build", action="store_true", help="跳过编译（直接跑已有可执行文件）")
    parser.add_argument("--strict", action="store_true", help="严格逐字节对比")
    parser.add_argument("--timeout", type=float, default=DEFAULT_TIMEOUT, help=f"单用例超时秒数（默认 {DEFAULT_TIMEOUT:.0f}）")
    args = parser.parse_args()

    src = Path(args.source)
    if not src.exists():
        print(f"错误: 源文件不存在: {src}", file=sys.stderr)
        return 2

    # ---- 编译 ----
    binary = None
    if args.no_build:
        binary = build.output_path(src)
        if not binary.exists():
            print(f"错误: 可执行文件不存在: {binary}（去掉 --no-build 试试）", file=sys.stderr)
            return 2
    else:
        need = args.rebuild or not build.output_path(src).exists()
        if not need:
            try:
                src_mtime = src.stat().st_mtime
                bin_mtime = build.output_path(src).stat().st_mtime
                need = src_mtime > bin_mtime
            except OSError:
                need = True
        if need:
            rc, binary = build.compile_sources([src])
            if rc != 0:
                return rc
        else:
            binary = build.output_path(src)
            print(f"无需重编译: {binary}")

    # ---- 找测试数据 ----
    cases = discover_cases(src)
    if not cases:
        print(
            "未找到测试数据。约定: 在源码同目录放 p1004.in/p1004.out，\n"
            "多用例用 p1004.1.in/p1004.1.out ... 或 p1004/1.in/1.out 目录。",
            flush=True,
        )
        return 2

    # ---- 运行 ----
    n_pass = n_fail = 0
    for idx, (inp, out) in enumerate(cases, 1):
        expected = out.read_text(encoding="utf-8", errors="replace")
        label = f"用例 {idx} ({inp.name})"
        try:
            with open(inp, "rb") as f:
                start = time.perf_counter()
                proc = subprocess.run(
                    [str(binary)],
                    stdin=f,
                    capture_output=True,
                    timeout=args.timeout,
                )
                elapsed = time.perf_counter() - start
            actual = proc.stdout.decode("utf-8", errors="replace")
        except subprocess.TimeoutExpired:
            print(f"✗ {label}: 超时（>{args.timeout:.0f}s）")
            n_fail += 1
            continue

        if compare(actual, expected, args.strict):
            print(f"✓ {label}: 通过 ({elapsed*1000:.0f}ms)")
            n_pass += 1
        else:
            print(f"✗ {label}: 失败 ({elapsed*1000:.0f}ms)")
            if proc.returncode != 0:
                print(f"  退出码: {proc.returncode}")
            if proc.stderr:
                print("  stderr: " + proc.stderr.decode("utf-8", errors="replace").strip()[:300])
            print(show_diff(actual, expected))
            n_fail += 1

    total = n_pass + n_fail
    print(f"\n结果: {n_pass}/{total} 通过")
    return 0 if n_fail == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
