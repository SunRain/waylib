---
name: treeland-waylib-qwlroots-sync
description: 将 treeland/master 指定 commit 区间内涉及 qwlroots/ 与 waylib/ 的变更，限域同步到 waylib-shared/waylibshared-merge，并保持 waylib-shared 的 CMake、安装、public header 路径、核心 target、导出 namespace 与 package config 合同不变。
---

# treeland-waylib-qwlroots-sync

## 目标

把 `treeland/` 仓库 `master` 分支中指定 commit 区间内，触达 `qwlroots/` 与 `waylib/` 的变更，同步合入 `waylib-shared/` 仓库 `waylibshared-merge` 分支。

同步必须满足：

- 只保留 `qwlroots/` 与 `waylib/` 内的变更。
- 丢弃 `treeland/src/`、`.github/`、顶层 `CMakePresets.json`、打包、翻译、外层示例工程等非目标路径。
- 按 `treeland/master` 原始提交顺序回放。
- 每个目标提交必须能追溯到原始 treeland commit。
- 默认保持 treeland commit 与 waylib-shared commit 的 1:1 映射。
- 不改变 `waylib-shared` 现有 CMake / 安装合同。
- 不改变安装后的 public header 路径合同。
- 不改变核心 CMake target、导出 target、导出 namespace 或 package config 合同。
- 不远程 push，除非用户单独明确授权。

## 输入变量

执行前必须由用户或方案包明确以下信息：

```yaml
source_repo: treeland
source_branch: master
target_repo: waylib-shared
target_branch: waylibshared-merge
range_base: <下界 commit，不包含>
range_head: <上界 commit，包含>
source_range: "(<range_base>..<range_head>]"
target_paths:
  - qwlroots/
  - waylib/
work_branch: sync/treeland-qwlroots-waylib-<short-base>-<short-head>
refs_doc: <可选追溯文档路径；不得夹带到同步提交中，除非用户明确放宽路径边界>
```

参考历史区间：

```yaml
previous_range_1:
  source_range: "(3e5fdd4d..e4086495]"
  expected_related_commits: 14
  original_strategy: format-patch(pathspec) + git am -3
  target_branch: waylibshared-merge

previous_range_2:
  source_range: "(e408649542182c55773b38a2d97b40765eb6a59b..fe6eb9bf634e43532fcbdacd67ed6c19e025c7ad]"
  expected_related_commits: 26
  preferred_strategy: 逐提交限域回放 + 提交信息规范化
  final_target_head: d2495eb491b0ff56dc3e3ca8c14d6be04ca92c35
```

## 基线冻结

执行开始前必须冻结来源与目标基线：

```bash
target_base_commit="$(git -C "waylib-shared" rev-parse "waylibshared-merge")"
source_head_commit="$(git -C "treeland" rev-parse "master")"
```

后续所有 diff 审计必须使用：

```bash
git -C "waylib-shared" diff "<target_base_commit>..HEAD"
```

不得依赖可移动的：

```bash
git -C "waylib-shared" diff "waylibshared-merge..HEAD"
```

原因：

- `waylibshared-merge` 可能在执行中移动。
- 合并回目标分支后，`waylibshared-merge..HEAD` 可能失效或为空。
- 二次执行、复核或回滚时，固定基线更可审计。

## 执行前审计

先确认来源范围和相关 commit 数：

```bash
git -C "treeland" rev-list --reverse "<range_base>..<range_head>" -- "qwlroots/" "waylib/"
git -C "treeland" rev-list --count "<range_base>..<range_head>" -- "qwlroots/" "waylib/"
```

然后为每个相关 commit 生成 inventory：

```text
- 原始 commit hash
- 原始 subject
- 原始改动文件列表
- 保留路径列表：qwlroots/**、waylib/**
- drop files list：所有非 qwlroots/**、waylib/** 路径
- 是否触达 CMake / install / target / namespace / public header 路径合同
```

如果实际 commit 数与方案包记录不一致，必须停止并回到规划或人工确认，不得自行删减 commit。

## 裁剪规则

每个 treeland commit 只允许同步这些路径：

```text
qwlroots/**
waylib/**
```

必须丢弃：

```text
.github/**
src/**
docs/**                  # 除非用户单独授权，不得夹带到同步提交
CMakePresets.json         # 顶层文件
packaging/**
translations/**
非 qwlroots/waylib 的任何路径
```

注意：

- `qwlroots/CMakePresets.json`、`waylib/CMakePresets.json` 虽在目标路径内，但仍属于构建配置，必须按“CMake / install / target 合同门禁”单独审计。
- `waylib/tests/**` 位于目标路径内，可以同步，但不得因此改变默认安装合同、核心 target 合同或 public header 安装合同。
- 空补丁、已被目标仓覆盖的补丁，默认仍要保留 1:1 追溯映射。

## 1:1 追溯映射

默认要求每个相关 treeland commit 都对应一个 waylib-shared 目标提交。

最终必须输出映射表：

```markdown
| treeland commit | waylib-shared commit | action | drop files list | adaptation notes |
|---|---|---|---|---|
| <hash> | <hash> | applied/adapted/empty/skipped | <list> | <notes> |
```

`action` 只允许：

- `applied`：路径裁剪后正常应用。
- `adapted`：应用时做了目标仓等价适配。
- `empty`：目标仓已等价包含，但保留空提交或追溯提交。
- `skipped`：明确跳过；必须有用户授权或方案包授权。

默认不允许静默 skip。

如果某个 treeland commit 在目标仓已等价存在：

1. 优先创建包含追溯信息的空提交。
2. 或记录为 `empty`，并明确对应的目标仓已有 commit。
3. 只有用户或方案包明确允许时，才真正 `skipped`。

## CMake / install / target 合同门禁

同步过程中不得改变 `waylib-shared` 的稳定构建与安装合同。

以下变化必须阻断，除非用户显式放宽：

```text
- 新增、删除、重命名核心 target。
- 改变 WaylibShared::* 导出 namespace。
- 改变 install(TARGETS)。
- 改变 install(FILES)。
- 改变 install(DIRECTORY)。
- 改变 install(EXPORT)。
- 改变 public header 安装 destination。
- 改变 PUBLIC / INTERFACE include 路径。
- 改变 package config / targets 文件名。
- 改变 configure_package_config_file(...) 输出合同。
- 改变 write_basic_package_version_file(...) 输出合同。
- 改变 EXPORT_NAME。
- 改变 OUTPUT_NAME。
- 改变 PUBLIC_HEADER。
- 把 private header 暴露为 public install header。
```

允许的 CMake 改动仅限：

```text
- PRIVATE 编译依赖。
- PRIVATE include。
- 测试 target。
- private header 列表。
- 为保持 waylib-shared 既有 target/package 命名而做的等价适配。
- 不影响 install/export/package/public header 的内部构建修正。
```

审计命令：

```bash
git -C "waylib-shared" diff "<target_base_commit>..HEAD" -- \
  "CMakeLists.txt" \
  "qwlroots/**/CMakeLists.txt" \
  "waylib/**/CMakeLists.txt" \
  "qwlroots/**/*.cmake" \
  "waylib/**/*.cmake" \
  "qwlroots/**/CMakePresets.json" \
  "waylib/**/CMakePresets.json"
```

审查重点：

```text
- 是否新增、删除、重命名核心 target。
- 是否改变 WaylibShared::* 导出 namespace。
- 是否改变 install(EXPORT) 或 install(TARGETS)。
- 是否改变 public header 安装 destination。
- 是否改变 PUBLIC / INTERFACE include 路径。
- 是否改变 package config / targets 文件名。
- 是否把 private header 安装成 public header。
```

历史适配参考：

- `test_qsgrenderer_accessor` 链接目标应适配为 `WaylibShared::SharedServer`，不得照搬 treeland 的目标命名。
- 涉及 `WaylibSharedQWlroots` / qwlroots config 命名时，应保留 waylib-shared 现有命名合同。

## public header 安装路径门禁

如果 CMake/install 相关文件有变化，必须额外验证安装后的 public header 路径没有变化。

推荐做法：

```bash
cmake -S "waylib-shared" -B "waylib-shared/build-sync" -DCMAKE_BUILD_TYPE=Release
cmake --build "waylib-shared/build-sync"
cmake --install "waylib-shared/build-sync" --prefix "/tmp/waylib-shared-install-after"
find "/tmp/waylib-shared-install-after" -type f | sort
```

复核重点：

```text
- public header 路径不新增非预期目录。
- private header 不进入 install 结果。
- include 根路径不变化。
- package config 暴露的 include 路径不变化。
- 安装后的 *Config.cmake / *Targets.cmake 文件名不变化。
```

如果已有历史安装清单或基线安装目录，必须对比 before/after：

```bash
find "/tmp/waylib-shared-install-before" -type f | sort > /tmp/waylib-shared-install-before.txt
find "/tmp/waylib-shared-install-after" -type f | sort > /tmp/waylib-shared-install-after.txt
diff -u /tmp/waylib-shared-install-before.txt /tmp/waylib-shared-install-after.txt
```

没有 before 清单时，必须至少人工复核 after 清单，并在交付结论中说明无法做 before/after 自动对比。

## namespace 门禁

任何 namespace 变化都必须单独解释，并证明不改变 public/exported namespace。

审计命令：

```bash
git -C "waylib-shared" diff "<target_base_commit>..HEAD" -- '*.h' '*.hpp' '*.cpp' \
  | grep -E '^[+-].*namespace[[:space:]]+|^[+-].*namespace[[:space:]]*\{'
```

若命令有输出，必须逐项分类：

```text
- public namespace：默认阻断。
- exported API namespace：默认阻断。
- private/internal namespace：允许，但必须记录 adaptation note。
- 匿名 namespace / 局部实现 namespace：允许，但必须确认不影响 public ABI/API。
```

不得因为 treeland 外层工程语义而改变 waylib-shared 的 public namespace、exported namespace 或 installed header namespace。

## 合入策略

推荐策略：**逐提交限域回放 + 提交信息规范化**。

不要默认使用整包 `git am` 后统一补救。原因：

- 每个 commit 都需要 drop list。
- CMake/install/target/public header/namespace 合同需要逐 commit 审计。
- 冲突修正需要保留原始 treeland hash。
- 空补丁、等价补丁、手工适配需要逐条记录。
- 1:1 commit 映射更利于后续复核。

执行流程：

```text
1. 确认 target_repo 当前在 waylibshared-merge。
2. 确认工作区干净。
3. 冻结 target_base_commit 与 source_head_commit。
4. 从 waylibshared-merge 创建工作分支。
5. 按 treeland 原始顺序遍历相关 commit。
6. 对每个 commit 只抽取 qwlroots/ 与 waylib/ diff。
7. 应用到 waylib-shared。
8. 冲突只允许在 qwlroots/ 与 waylib/ 内解决。
9. 审计该 commit 是否越界。
10. 审计该 commit 是否改变 CMake/install/target/public header/namespace 合同。
11. 生成规范化提交信息。
12. 记录 treeland commit -> waylib-shared commit 映射。
13. 全部完成后运行路径、提交信息、CMake 合同、public header 安装、namespace、构建和测试门禁。
14. 合并回 waylibshared-merge。
15. 不执行远程 push。
```

## 提交信息格式

目标提交 subject 优先保留原始 treeland subject。必要时最小化改成 conventional commit：

```text
<type>(<scope>): <summary>
```

当 commit 存在路径裁剪、冲突修正、空补丁记录、CMake/target 适配、namespace 复核或 subject 规范化时，提交正文必须包含：

```text
Original treeland commit:
<原始 treeland commit message，保留 subject/body；无 body 时至少保留 subject>

[treeland-sync] : drop files list
- <被丢弃路径；无则写 none>

[treeland-sync] : adaptation notes
- <无适配则写 none>
- <若保留 waylib-shared CMake/install/target/header/namespace 合同，在这里说明>

Refs: <refs_doc 或方案包路径>
Treeland-Commit: <完整 treeland commit hash>
```

示例：

```text
fix(qwlroots): fix crash on stale QQmlData pointer in qw_object::on_destroy

Original treeland commit:
fix(qwlroots): fix crash on stale QQmlData pointer in qw_object::on_destroy

[treeland-sync] : drop files list
- none

[treeland-sync] : adaptation notes
- Preserved waylib-shared CMake target/export/install contracts.
- No public header install path changes.
- No public/exported namespace changes.

Refs: .helloagents/archive/2026-05/202605220117_treeland-qwlroots-waylib-e4086495-fe6eb9bf/
Treeland-Commit: 67d388bafed2da1ad2dee2a0de3f7984ecf37cdb
```

## 验证门禁

路径越界审计必须无输出：

```bash
git -C "waylib-shared" diff --name-only "<target_base_commit>..HEAD" | grep -Ev '^(qwlroots|waylib)/'
```

提交数量与顺序复核：

```bash
git -C "treeland" rev-list --reverse "<range_base>..<range_head>" -- "qwlroots/" "waylib/"
git -C "waylib-shared" log --format='%H%x09%B' "<target_base_commit>..HEAD"
```

提交信息必须逐条包含：

```text
Original treeland commit
[treeland-sync] : drop files list
[treeland-sync] : adaptation notes
Refs
Treeland-Commit
```

CMake / install / target 合同复核：

```bash
git -C "waylib-shared" diff "<target_base_commit>..HEAD" -- \
  "CMakeLists.txt" \
  "qwlroots/**/CMakeLists.txt" \
  "waylib/**/CMakeLists.txt" \
  "qwlroots/**/*.cmake" \
  "waylib/**/*.cmake" \
  "qwlroots/**/CMakePresets.json" \
  "waylib/**/CMakePresets.json"
```

public header 安装路径复核：

```bash
cmake --install "waylib-shared/build-sync" --prefix "/tmp/waylib-shared-install-after"
find "/tmp/waylib-shared-install-after" -type f | sort
```

namespace 复核：

```bash
git -C "waylib-shared" diff "<target_base_commit>..HEAD" -- '*.h' '*.hpp' '*.cpp' \
  | grep -E '^[+-].*namespace[[:space:]]+|^[+-].*namespace[[:space:]]*\{'
```

基础构建门禁：

```bash
cmake -S "waylib-shared" -B "waylib-shared/build-sync" -DCMAKE_BUILD_TYPE=Release
cmake --build "waylib-shared/build-sync"
ctest --test-dir "waylib-shared/build-sync" --output-on-failure
```

如果没有可运行测试，必须记录具体原因，不能静默跳过。

## 阻断条件

出现以下情况必须停止：

- commit 数与预期不一致，且没有人工确认。
- 最终 diff 出现 `qwlroots/`、`waylib/` 之外路径。
- 需要修改 docs、CI、顶层 CMakePresets、外层 src，但用户没有单独授权。
- 同步会改变 CMake install/export/package 合同。
- 同步会改变 public header 安装路径。
- 同步会改变核心 target。
- 同步会改变 `WaylibShared::*` 导出 namespace。
- 同步会改变 public/exported namespace。
- 冲突无法限制在 `qwlroots/` 与 `waylib/` 内解决。
- 构建失败且无法证明失败与本次同步无关。
- 目标 commit 无法追溯到原始 treeland commit。
- `skipped` commit 没有用户授权或方案包授权。

## 输出要求

最终交付必须包含：

```text
1. source range 与目标分支
2. target_base_commit 与 source_head_commit
3. treeland 相关 commit 数
4. 成功同步的目标 commit 数
5. treeland commit -> waylib-shared commit 完整映射表
6. applied / adapted / empty / skipped 列表
7. 每个有裁剪的 commit 的 drop files list
8. 每个有适配的 commit 的 adaptation notes
9. CMake/install/target 合同复核结论
10. public header 安装路径复核结论
11. namespace 复核结论
12. 路径越界审计结果
13. 构建/测试结果
14. 最终 waylib-shared HEAD
15. 是否执行远程 push：必须为 no，除非用户单独授权
```

## 推荐交付格式

```markdown
## 同步结论

- source range: (<range_base>..<range_head>]
- target branch: waylibshared-merge
- target_base_commit: <hash>
- final HEAD: <hash>
- related treeland commits: <count>
- target commits: <count>
- remote push: no

## 追溯映射

| treeland commit | waylib-shared commit | action | drop files list | adaptation notes |
|---|---|---|---|---|

## 合同复核

- CMake/install/target contract: PASS / BLOCKED
- public header install path contract: PASS / BLOCKED
- namespace contract: PASS / BLOCKED
- path boundary: PASS / BLOCKED

## 验证结果

- path audit: PASS / FAIL
- cmake configure: PASS / FAIL
- build: PASS / FAIL
- ctest: PASS / FAIL / SKIPPED with reason
```
