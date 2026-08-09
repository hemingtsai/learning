#!/usr/bin/env bash
# 清理所有构建产物并提交当前改动
# 用法:
#   tools/commit.sh            清理 + 提交（提交信息由编辑器填写）
#   tools/commit.sh "消息"     清理 + 用给定消息提交
#   tools/commit.sh -n         仅预览清理结果，不提交
#   tools/commit.sh --amend    清理 + 追加到最近一次提交
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO_ROOT"

DRY_RUN=false
AMEND=false
MSG=""

while [[ $# -gt 0 ]]; do
    case "$1" in
        -n|--dry-run) DRY_RUN=true; shift ;;
        --amend)      AMEND=true; shift ;;
        *)            MSG="$1"; shift ;;
    esac
done

echo "==> 清理构建产物"
if $DRY_RUN; then
    tools/clean.sh -n
    echo "预览模式，不提交"
    exit 0
fi
tools/clean.sh

echo "==> 暂存改动"
git add -A

if git diff --cached --quiet; then
    echo "没有需要提交的改动"
    exit 0
fi

echo "==> 提交"
if $AMEND; then
    if [[ -n "$MSG" ]]; then
        git commit --amend -m "$MSG"
    else
        git commit --amend --no-edit
    fi
elif [[ -n "$MSG" ]]; then
    git commit -m "$MSG"
else
    git commit
fi

echo
echo "==> 完成"
git log --oneline -1
