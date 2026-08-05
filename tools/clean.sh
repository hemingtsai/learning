#!/usr/bin/env bash
# 清理 C/C++ 构建产物
# 用法:
#   tools/clean.sh          清理
#   tools/clean.sh -n       预览（只列出，不删除）
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO_ROOT"

DRY_RUN=false
[[ "${1:-}" == "-n" || "${1:-}" == "--dry-run" ]] && DRY_RUN=true

# 已被 git 跟踪的文件不删，避免误伤
TRACKED="$(git ls-files)"

deleted=0
freed=0

remove_file() {
    local f="$1"
    if [[ -e "$f" ]]; then
        if $DRY_RUN; then
            echo "将删除: $f"
        else
            size=$(stat -f%z "$f" 2>/dev/null || echo 0)
            rm -f "$f"
            freed=$((freed + size))
            echo "已删除: $f"
        fi
        deleted=$((deleted + 1))
    fi
}

remove_dir() {
    local d="$1"
    if [[ -d "$d" ]]; then
        if $DRY_RUN; then
            echo "将删除: $d"
        else
            size=$(du -sk "$d" 2>/dev/null | awk '{print $1}')
            rm -rf "$d"
            freed=$((freed + size * 1024))
            echo "已删除: $d"
        fi
        deleted=$((deleted + 1))
    fi
}

# 1. dSYM 调试符号目录
while IFS= read -r d; do
    [[ -n "$d" ]] && remove_dir "$d"
done < <(find . -type d -name "*.dSYM" -not -path "./.git/*")

# 2. build.py 的统一构建目录
remove_dir "./build"

# 3. Python 缓存目录（tools/ 下的脚本产生）
while IFS= read -r d; do
    [[ -n "$d" ]] && remove_dir "$d"
done < <(find . -type d -name "__pycache__" -not -path "./.git/*")

# 3. 常见中间产物
while IFS= read -r f; do
    [[ -n "$f" ]] && remove_file "$f"
done < <(find . -type f \( -name "*.o" -o -name "*.out" -o -name "a.out" \) -not -path "./.git/*")

# 4. 与源码同名的编译产物（如 luogu/p1090 <- p1090.cpp）
while IFS= read -r src; do
    dir="$(dirname "$src")"
    bin="$dir/$(basename "${src%.*}")"
    [[ -e "$bin" && -f "$bin" ]] || continue
    # 跳过被 git 跟踪的文件
    if grep -qxF "$bin" <<<"$TRACKED"; then
        continue
    fi
    # 仅删除真正的 Mach-O 可执行文件
    if file "$bin" | grep -q "Mach-O.*executable"; then
        remove_file "$bin"
    fi
done < <(find . -type f \( -name "*.cpp" -o -name "*.c" -o -name "*.cc" -o -name "*.cxx" \) -not -path "./.git/*")

echo
if $DRY_RUN; then
    echo "预览模式：共 $deleted 项待清理"
else
    echo "清理完成：删除 $deleted 项，释放 $(numfmt --to=iec "$freed" 2>/dev/null || echo "$freed 字节")"
fi
