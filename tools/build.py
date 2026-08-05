#!/usr/bin/env python3
"""一键编译刷题代码。

用法:
  tools/build.py luogu/p1004.cpp                 # 编译到 build/luogu/p1004
  tools/build.py a.cpp b.cpp -o main             # 多文件链接，输出 build/main
  tools/build.py luogu/p1004.cpp -g              # 调试模式（加 -g）
  tools/build.py luogu/p1004.cpp -- -fsanitize=address   # 追加任意编译选项
  tools/build.py --clean                         # 清空 build 目录

输出统一放在仓库 build/ 目录，保持与源码相同的相对路径，不污染源码目录。
"""
from __future__ import annotations

import argparse
import os
import shutil
import subprocess
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
BUILD_DIR = REPO_ROOT / "build"
DEFAULT_FLAGS = ["-std=c++17", "-O2", "-Wall"]


def compiler_for(src: Path) -> str:
    """按源码后缀选择编译器，可用 CC/CXX 环境变量覆盖。"""
    if src.suffix.lower() == ".c":
        return os.environ.get("CC", "cc")
    return os.environ.get("CXX", "g++")


def output_path(src: Path) -> Path:
    """源码 -> 可执行文件路径，如 luogu/p1004.cpp -> build/luogu/p1004。"""
    try:
        rel = src.resolve().relative_to(REPO_ROOT.resolve())
    except ValueError:
        # 源码在仓库外时退化为 build/<文件名>
        rel = Path(src.name)
    return BUILD_DIR / rel.with_suffix("")


def compile_sources(
    sources: list[Path],
    *,
    extra_flags: list[str] = (),
    debug: bool = False,
    out_name: str | None = None,
    quiet: bool = False,
) -> tuple[int, Path | None]:
    """编译一组源文件。返回 (退出码, 可执行文件路径)。"""
    sources = [s for s in sources if s.exists()]
    if not sources:
        print("错误: 源文件不存在", file=sys.stderr)
        return 2, None

    if out_name:
        out = BUILD_DIR / out_name
    else:
        out = output_path(sources[0])

    out.parent.mkdir(parents=True, exist_ok=True)

    # 默认用第一个源文件的语言/编译器，混合语言场景一般不会出现
    compiler = compiler_for(sources[0])
    cmd = [compiler, *DEFAULT_FLAGS]
    if debug:
        cmd.append("-g")
    cmd.extend(extra_flags)
    cmd.extend(str(s) for s in sources)
    cmd.extend(["-o", str(out)])

    if not quiet:
        print("编译: " + " ".join(cmd))
    rc = subprocess.run(cmd).returncode
    if rc != 0:
        print("编译失败", file=sys.stderr)
        return rc, None
    if not quiet:
        print(f"成功: {out}")
    return 0, out


def main() -> int:
    parser = argparse.ArgumentParser(
        description="一键编译刷题代码",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="示例:\n  tools/build.py luogu/p1004.cpp -g\n  tools/build.py a.cpp b.cpp -o main\n  tools/build.py x.cpp -- -O0",
    )
    parser.add_argument("sources", nargs="*", help="源文件（.c/.cpp/.cc/.cxx）")
    parser.add_argument("-g", dest="debug", action="store_true", help="调试模式，加 -g")
    parser.add_argument("-o", dest="out", metavar="NAME", help="输出文件名（位于 build/ 下）")
    parser.add_argument("--clean", action="store_true", help="清空 build 目录")
    parser.add_argument("--", dest="extra", nargs=argparse.REMAINDER, help="追加到编译命令的选项")
    args = parser.parse_args()

    if args.clean:
        if BUILD_DIR.exists():
            shutil.rmtree(BUILD_DIR)
            print(f"已清空 {BUILD_DIR}")
        else:
            print("build/ 目录不存在")
        return 0

    if not args.sources:
        parser.error("需要至少一个源文件（或用 --clean）")

    extra = args.extra or []
    # argparse.REMAINDER 可能带一个前导 "--"
    if extra and extra[0] == "--":
        extra = extra[1:]

    sources = [Path(s) for s in args.sources]
    return compile_sources(
        sources,
        extra_flags=extra,
        debug=args.debug,
        out_name=args.out,
    )[0]


if __name__ == "__main__":
    sys.exit(main())
