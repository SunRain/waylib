# treeland-waylib-qwlroots-sync CLI Skill

本目录提供一个可安装的 CLI skill，用于把 `treeland/master` 指定 commit 区间内涉及 `qwlroots/` 与 `waylib/` 的变更，限域同步到 `waylib-shared/waylibshared-merge`。

该 skill 会强制保护：

- CMake / install 合同
- public header 安装路径
- 核心 CMake target
- `WaylibShared::*` 导出 namespace
- package config / targets 文件名
- treeland commit 到 waylib-shared commit 的追溯映射

## 安装

### 复制安装

从 `waylib-shared` 仓库根目录执行：

```bash
mkdir -p "$HOME/.codex/skills/treeland-waylib-qwlroots-sync"
cp "docs/skills/treeland-waylib-qwlroots-sync/SKILL.md" \
   "$HOME/.codex/skills/treeland-waylib-qwlroots-sync/SKILL.md"
```

### 软链接安装

如果希望仓库内 skill 更新后本地 CLI 自动使用最新版：

```bash
mkdir -p "$HOME/.codex/skills/treeland-waylib-qwlroots-sync"
ln -sf "$PWD/docs/skills/treeland-waylib-qwlroots-sync/SKILL.md" \
       "$HOME/.codex/skills/treeland-waylib-qwlroots-sync/SKILL.md"
```

如果你的 CLI 使用自定义 skill 目录，请把 `$HOME/.codex/skills` 替换成实际目录：

```text
<CLI_SKILLS_DIR>/treeland-waylib-qwlroots-sync/SKILL.md
```

## 安装验证

```bash
test -f "$HOME/.codex/skills/treeland-waylib-qwlroots-sync/SKILL.md"
sed -n '1,12p' "$HOME/.codex/skills/treeland-waylib-qwlroots-sync/SKILL.md"
```

应能看到：

```yaml
---
name: treeland-waylib-qwlroots-sync
description: ...
---
```

## 使用方式

在 CLI 对话中显式点名 skill：

```text
使用 $treeland-waylib-qwlroots-sync。

source_repo: treeland
source_branch: master
target_repo: waylib-shared
target_branch: waylibshared-merge
range_base: <下界 commit，不包含>
range_head: <上界 commit，包含>
refs_doc: docs/skills/treeland-waylib-qwlroots-sync/SKILL.md

要求：
- 只同步 qwlroots/ 与 waylib/
- 不改变 CMake / install / public header / target / namespace 合同
- 输出 treeland commit -> waylib-shared commit 完整映射表
- 不远程 push
```

## 参数说明

```yaml
source_repo: treeland
source_branch: master
target_repo: waylib-shared
target_branch: waylibshared-merge
range_base: <下界 commit，不包含>
range_head: <上界 commit，包含>
work_branch: sync/treeland-qwlroots-waylib-<short-base>-<short-head>
refs_doc: docs/skills/treeland-waylib-qwlroots-sync/SKILL.md
```

## 示例

```text
使用 $treeland-waylib-qwlroots-sync。

source_repo: treeland
source_branch: master
target_repo: waylib-shared
target_branch: waylibshared-merge
range_base: e408649542182c55773b38a2d97b40765eb6a59b
range_head: fe6eb9bf634e43532fcbdacd67ed6c19e025c7ad
refs_doc: docs/skills/treeland-waylib-qwlroots-sync/SKILL.md

按原始提交顺序同步 qwlroots/ 与 waylib/，保留 drop list、adaptation notes 和 Treeland-Commit，不改变 CMake/install/public header/target/namespace 合同，不远程 push。
```

## 更新

如果使用复制安装，重新复制即可：

```bash
cp "docs/skills/treeland-waylib-qwlroots-sync/SKILL.md" \
   "$HOME/.codex/skills/treeland-waylib-qwlroots-sync/SKILL.md"
```

如果使用软链接安装，不需要额外更新；仓库内 `SKILL.md` 更新后自动生效。

## 使用边界

该 skill 是执行规则，不是无条件自动合并脚本。遇到以下情况必须停止：

- commit 数与预期不一致。
- diff 出现 `qwlroots/`、`waylib/` 之外路径。
- 需要改变 CMake install/export/package 合同。
- 需要改变 public header 安装路径。
- 需要改变核心 target 或 `WaylibShared::*` namespace。
- `skipped` commit 没有用户授权或方案包授权。
- 用户没有授权远程 push。
