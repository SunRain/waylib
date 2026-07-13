# treeland waylib/qwlroots 历史映射门禁（20260713）

本文定义 `treeland` 历史重写后，把 `qwlroots/` 与 `waylib/` 变更同步到 `waylib-shared` 前必须通过的历史映射门禁。

适用同步范围：

- 用户逻辑范围：`(fe6eb9bf634e43532fcbdacd67ed6c19e025c7ad..7da2254d386935f753ed907f8d6e76c1639d01a9]`
- 当前主线规范化范围：`(7a8bb04b37e7bff0b3a6b0cfb3f72421f31271c2..7da2254d386935f753ed907f8d6e76c1639d01a9]`
- 目标路径：`qwlroots/**`、`waylib/**`
- 预期相关提交数：`39`
- 规划时目标仓快照（本文档落地前）：`waylib-shared/waylibshared-merge` 的 `8023150cefcc9e8b597858880dc1375902e97e11`

本门禁是同步执行的阻断性前置条件。未得到 `PASS` 时，不得创建同步工作分支，不得回放提交，不得修改 `waylib-shared/qwlroots/**` 或 `waylib-shared/waylib/**`。

本文档属于同步外的独立追溯文档。它必须先进入目标基线，后续 39 个同步提交不得夹带 `docs/**` 变更。

---

## 已确认的历史事实

### 远端引用发生非快进替换

本地 `treeland` reflog 记录：

```text
refs/remotes/origin/master@{2026-07-12T22:49:17+08:00}  7da2254d  fetch origin: forced-update
refs/remotes/origin/master@{2026-05-31T22:00:46+08:00}  1c6e6555  fetch origin: fast-forward
refs/remotes/origin/master@{2026-05-21T22:58:32+08:00}  fe6eb9bf  fetch origin: fast-forward
```

`2026-07-12T22:49:17+08:00` 是本地观察到非快进更新的时间，不等同于远端实际执行 force-push 的时间。仅凭本地数据无法区分远端使用了 `git push --force`、`--force-with-lease` 还是服务端引用替换，但其 Git 语义都是历史非快进替换。

### 新旧历史没有共同祖先

- 旧线 tip：`1c6e6555db0ce3ab5d2b041e6ce3063b71ed3f71`
- 新线 tip：`7da2254d386935f753ed907f8d6e76c1639d01a9`
- `git merge-base`：无共同祖先
- 旧线根提交：`9064cc10846a288d113504599a4964b74f06b292`
- 新线根提交：`2282fbcdc9932e2a25c802591ebcbbd9908d103f`、`9f47c18134ef33cda126b47839d88c9da9393df0`

新线包含两父提交 `99c7f1b74171266c85884c97cca2f487f4cdef8d`：

```text
refactor: merge qwlroots and waylib source code into treeland
```

该提交明确记录：qwlroots 和 waylib 从子模块改为源码及历史直接合入 treeland。新父链由此重建，旧提交的补丁被保留，但 commit hash 发生变化。

---

## 固定映射

### 边界和上一轮同步连续性

| 语义 | 旧线提交 | 新线提交 | stable patch-id | 关系 |
|---|---|---|---|---|
| 用户下界，范围不包含 | `fe6eb9bf634e43532fcbdacd67ed6c19e025c7ad` | `7a8bb04b37e7bff0b3a6b0cfb3f72421f31271c2` | `317e77ba8274dde33a901a3d66898e5960a7105d` | 等价 |
| 上一轮最后一个目标提交 | `88c558e65c60b14847d939dd2fab3331308e05c1` | `05105eea97bb0939bcbcbd354b413e9cdaab4ae8` | `9643aa4a75d384b3d1ba40c2071dbf5abdecb880` | 等价 |

`05105eea` 是 `7a8bb04b` 的直接父提交。因此，规范化范围从 `7a8bb04b` 之后开始，不会重复上一轮同步，也不会遗漏用户下界后的目标路径变更。

### 旧线 `fe6eb9bf` 之后的 6 个目标提交

| # | 旧线提交 | 新线提交 | stable patch-id | 文件列表 |
|---:|---|---|---|---|
| 1 | `d2c146714ccef67ccea21f17bf5bbad005818b33` | `f5d691158b21337755b0567d961ba0eeb2b3a589` | `1a760c51cd5953fc635b1b3216da0ad4fc7a2384` | 相同 |
| 2 | `64f528cc05da2ce00cbbfeb985c7be4f0c91eb16` | `b04afc1ca7995eb158643765acc33ee6e26aff43` | `24c1327f80ca6fe462eafb31a8ac7fa1d4dc4c91` | 相同 |
| 3 | `a4637d5017ae4097c56e98829267d56367819453` | `4459834533da62bdcbe07e777beb88a305f00097` | `7153fd0c30c38a7ce283caa515b3402a588877a0` | 相同 |
| 4 | `b142fe2f612ad2ad0d6077702ad743fb9c7b851a` | `5ff7f8d7addbfe2c45ad84db95aa37dfd9c0566e` | `ca80820f44df09ac885b7cd7c3c8be4e51323a7f` | 相同 |
| 5 | `4a85cd5c8d54475a4157569797e0824874d0baf1` | `c651335a5823c60e2c12a273cab9cc358014d411` | `1f6dd45bb4440c0f20ea9b1f8d5b186009cf115e` | 相同 |
| 6 | `e589f62da469bf16412237331ef20bcea0d47ef0` | `6c907f3b7544241d868b805b5afa0b92aabf6b55` | `4e7368d0ef3f19a411b28a124893bd0b0623fb2b` | 相同 |

`git range-diff` 对旧线 `fe6eb9bf..1c6e6555` 和新线 `7a8bb04b..9079d1eb` 的 31 个提交逐项输出 `=`。上表 6 个提交是其中触达 `qwlroots/` 或 `waylib/` 的部分。

### 规范化范围组成

- 重写等价提交：`6`
- 旧线快照之后新增的目标提交：`33`
- 总计：`39`
- 39 个 commit hash 按顺序拼接并换行后的 SHA-256：`aff86eef88dfa6371b3b69a96bb2f5777311c24b8142283f1929f784926c8338`

直接使用错误范围 `fe6eb9bf..7da2254d` 会枚举 `850` 个目标路径提交。该结果说明 Git 正在比较两个不相干的历史集合，不能用于同步。

---

## 门禁执行

以下命令均从 `HA-waylibshared` 工作区根目录执行。

### 1. 对象和来源引用

```bash
git -C "treeland" cat-file -e "fe6eb9bf634e43532fcbdacd67ed6c19e025c7ad^{commit}"
git -C "treeland" cat-file -e "7a8bb04b37e7bff0b3a6b0cfb3f72421f31271c2^{commit}"
git -C "treeland" cat-file -e "7da2254d386935f753ed907f8d6e76c1639d01a9^{commit}"
git -C "treeland" merge-base --is-ancestor "7a8bb04b37e7bff0b3a6b0cfb3f72421f31271c2" "7da2254d386935f753ed907f8d6e76c1639d01a9"
```

PASS 条件：三个对象都存在，祖先检查退出码为 `0`。

禁止使用本地 `master`。当前本地 `master` 仍指向旧线 `1c6e6555`，来源事实必须使用精确哈希。

### 2. 边界 patch-id

```bash
git -C "treeland" show --pretty=format: "fe6eb9bf634e43532fcbdacd67ed6c19e025c7ad" | git patch-id --stable
git -C "treeland" show --pretty=format: "7a8bb04b37e7bff0b3a6b0cfb3f72421f31271c2" | git patch-id --stable
git -C "treeland" show --pretty=format: "88c558e65c60b14847d939dd2fab3331308e05c1" | git patch-id --stable
git -C "treeland" show --pretty=format: "05105eea97bb0939bcbcbd354b413e9cdaab4ae8" | git patch-id --stable
```

PASS 条件：两组结果分别等于固定映射表中的 patch-id。

### 3. 旧线重放完整性

```bash
git -C "treeland" range-diff --no-color \
  "fe6eb9bf634e43532fcbdacd67ed6c19e025c7ad..1c6e6555db0ce3ab5d2b041e6ce3063b71ed3f71" \
  "7a8bb04b37e7bff0b3a6b0cfb3f72421f31271c2..9079d1eb142059e54c6759524260bfcfa87cf2cc"
```

PASS 条件：共 31 项，全部使用 `=` 映射；不得出现 `<`、`>` 或 `!`。

对上表 6 组提交逐项执行以下模板，并比较输出：

```bash
git -C "treeland" show --pretty=format: "<old-commit>" | git patch-id --stable
git -C "treeland" show --pretty=format: "<new-commit>" | git patch-id --stable
git -C "treeland" show --format= --name-status "<old-commit>"
git -C "treeland" show --format= --name-status "<new-commit>"
```

PASS 条件：每组 patch-id 和文件列表均相同。

### 4. 范围数量和顺序

```bash
git -C "treeland" rev-list --count \
  "7a8bb04b37e7bff0b3a6b0cfb3f72421f31271c2..7da2254d386935f753ed907f8d6e76c1639d01a9" \
  -- "qwlroots/" "waylib/"

git -C "treeland" rev-list --reverse \
  "7a8bb04b37e7bff0b3a6b0cfb3f72421f31271c2..7da2254d386935f753ed907f8d6e76c1639d01a9" \
  -- "qwlroots/" "waylib/" | sha256sum
```

PASS 条件：数量为 `39`，SHA-256 为 `aff86eef88dfa6371b3b69a96bb2f5777311c24b8142283f1929f784926c8338`。

### 5. 目标连续性

```bash
git -C "waylib-shared" rev-parse "waylibshared-merge"
git -C "waylib-shared" status --short --branch
git -C "waylib-shared" log --all --format='%(trailers:key=Treeland-Commit,valueonly)' \
  | grep -F "88c558e65c60b14847d939dd2fab3331308e05c1"
```

PASS 条件：

- `8023150cefcc9e8b597858880dc1375902e97e11` 是实际执行基线的祖先；若不是，必须重新审计目标历史。
- 目标仓工作区干净。
- 上一轮最后一个目标提交存在 `88c558e6` 追溯记录。
- 本文档已经通过独立文档提交进入目标分支；随后冻结该提交或其后继提交为实际 `target_base_commit`。
- 后续同步 diff 以实际 `target_base_commit` 为起点，不包含 `docs/**`。

---

## 来源引用漂移规则

执行前比较 `origin/master` 与固定终点 `7da2254d`：

- `origin/master == 7da2254d`：继续。
- `7da2254d` 是 `origin/master` 的祖先：远端发生普通快进；继续使用固定终点 `7da2254d`，不得自动扩大范围。
- `7da2254d` 不是 `origin/master` 的祖先：再次发生非快进替换；门禁判定为 `BLOCKED`，重新建立边界映射、commit inventory 和数量证据。
- 固定对象不存在：`BLOCKED`，不得用新的分支头猜测替代。

---

## 判定

以下条件全部满足时，历史映射门禁为 `PASS`：

- 固定对象存在，`7a8bb04b` 是 `7da2254d` 的祖先。
- 两组边界 patch-id 与本文一致。
- 31 个旧线提交在 `range-diff` 中全部为 `=`。
- 6 组目标提交的 patch-id 和文件列表逐项一致。
- 规范化范围恰好为 39 个提交，顺序 SHA-256 一致。
- 上一轮同步边界可追溯，目标基线已重新冻结。
- 本文档已独立进入目标基线，目标仓工作区干净。

任一条件不满足时，门禁为 `BLOCKED`。不得通过跳过提交、改用本地 `master`、改用移动的 `origin/master`、放宽路径范围或接受 `850` 个提交来绕过。

执行证据至少记录：

```text
history_mapping_gate: PASS / BLOCKED
checked_at: <ISO-8601>
old_base: fe6eb9bf634e43532fcbdacd67ed6c19e025c7ad
normalized_base: 7a8bb04b37e7bff0b3a6b0cfb3f72421f31271c2
fixed_head: 7da2254d386935f753ed907f8d6e76c1639d01a9
related_commit_count: 39
ordered_commit_sha256: aff86eef88dfa6371b3b69a96bb2f5777311c24b8142283f1929f784926c8338
target_base_commit: <执行时冻结值>
notes: <无则写 none>
```

## 关联文档

- 同步策略：`docs/skills/treeland-waylib-qwlroots-sync/SKILL.md`
- 上一轮同步记录：`docs/treeland-waylib-qwlroots-sync_202605220117_zh.md`
- 当前方案包：父工作区 `.helloagents/plans/202607122330_treeland-qwlroots-waylib-fe6eb9bf-7da2254d/`
