# treeland waylib/qwlroots 同步记录（202603031800）

本文记录将 `treeland/` 仓库 `master` 分支在区间 `3e5fdd4d..e4086495`（左开右闭）内，涉及 `waylib/` 与 `qwlroots/` 的改动同步合入 `waylib-shared/` 仓库 `waylibshared-merge` 分支的过程与关键信息，便于后续追溯。

---

## 提取信息（@treeland/）

- 用于提取的分支：`master`
- 提取目录范围：`waylib/`、`qwlroots/`
- 提取范围（Git range）：
  - 起始 commit（不包含）：`3e5fdd4d32396b20dc0294b84277b831412484b3`（2026-01-19 10:25:26 +0800，`fix: compilation issues due to update in treeland-dde-shell-v1 protocol`）
  - 结束 commit（包含）：`e408649542182c55773b38a2d97b40765eb6a59b`（2026-03-03 16:45:02 +0800，`chore: remove wallpaper controller`）
- 说明：区间内并非所有提交都触达 `waylib/`/`qwlroots/`；下文仅列出触达目标目录并参与同步的提交。

---

## 合入策略

> 说明：
> - `pure`：仅触达 `waylib/`/`qwlroots/`，直接合入。
> - `mixed`：同时触达其他路径，仅保留 `waylib/`/`qwlroots/` 的 diff 合入，其余路径变更全部丢弃；被丢弃路径见下文清单。

---

## 提交映射（treeland → waylib-shared）

| # | treeland | waylib-shared | 类型 | 路径 | 说明 |
|---:|---|---|---|---|---|
| 1 | d934caa | 2f213647 | mixed | waylib | mixed：排除 34 个非目标路径文件 |
| 2 | da62dec | 27a35e4a | pure | waylib | pure |
| 3 | 7353097 | 471fdd7a | mixed | waylib | mixed：排除 1 个非目标路径文件 |
| 4 | 6518589 | 5716e010 | pure | qwlroots | pure |
| 5 | 82e447b | 0014f564 | pure | waylib | pure |
| 6 | cd4c365 | cf034512 | mixed | waylib | mixed：排除 1 个非目标路径文件 |
| 7 | b9c988d | 8d8690c4 | pure | waylib | pure |
| 8 | 646ee9f | e24fc793 | mixed | waylib | mixed：排除 13 个非目标路径文件 |
| 9 | 64ad615 | c6f8b282 | pure | waylib | pure |
| 10 | ce633b8 | 1b95cfcf | pure | qwlroots | pure |
| 11 | b55f2bd | 6ed51953 | mixed | waylib | mixed：排除 2 个非目标路径文件 |
| 12 | c03310d | ce266d5a | mixed | waylib | mixed：排除 4 个非目标路径文件 |
| 13 | a0a0107 | c40b07f2 | pure | waylib | pure |
| 14 | ceac255 | — | mixed | waylib | waylib 侧改动在 `waylib-shared` 已存在（提示文案不同但均为 `QML_UNCREATABLE`），未产生新提交 |

---

## mixed commits：被排除路径清单

### d934caa feat: implement wallpaper management system

- 被排除路径（34）：
  - misc/dconfig/org.deepin.dde.treeland.user.json
  - misc/systemd/treeland.service.in
  - src/CMakeLists.txt
  - src/core/qml/Effects/LaunchpadCover.qml
  - src/core/qml/PrimaryOutput.qml
  - src/core/qml/WorkspaceSwitcher.qml
  - src/core/shellhandler.cpp
  - src/core/shellhandler.h
  - src/core/treeland.cpp
  - src/greeter/usermodel.cpp
  - src/modules/wallpaper/wallpapershellinterfacev1.cpp
  - src/modules/wallpaper/wallpapershellinterfacev1.h
  - src/plugins/lockscreen/qml/Greeter.qml
  - src/plugins/multitaskview/qml/MultitaskviewProxy.qml
  - src/plugins/multitaskview/qml/WorkspaceSelectionList.qml
  - src/seat/helper.cpp
  - src/seat/helper.h
  - src/session/session.cpp
  - src/session/session.h
  - src/wallpaper/wallpaperconfig.cpp
  - src/wallpaper/wallpaperconfig.h
  - src/wallpaper/wallpaperimage.cpp
  - src/wallpaper/wallpaperimage.h
  - src/wallpaper/wallpaperitem.cpp
  - src/wallpaper/wallpaperitem.h
  - src/wallpaper/wallpaperlauncher.cpp
  - src/wallpaper/wallpaperlauncher.h
  - src/wallpaper/wallpapermanager.cpp
  - src/wallpaper/wallpapermanager.h
  - src/wallpaper/wallpapersurface.cpp
  - src/wallpaper/wallpapersurface.h
  - src/workspace/workspace.cpp
  - src/workspace/workspace.h
  - wallpaper-factory/mpvvideoitem.cpp

### 7353097 fix: SessionManager: correct destruction routine of WXWayland instances

- 被排除路径（1）：
  - src/session/session.cpp

### cd4c365 fix: lower classed QML element waylib being non-addressable in QML

- 被排除路径（1）：
  - src/core/qml/Decoration.qml

### 646ee9f fix: improve Qt6 private module compatibility

- 被排除路径（13）：
  - examples/test_capture/CMakeLists.txt
  - examples/test_multitaskview/CMakeLists.txt
  - examples/test_show_desktop/CMakeLists.txt
  - examples/test_super_overlay_surface/CMakeLists.txt
  - examples/test_virtual_output/CMakeLists.txt
  - examples/test_window_bg/CMakeLists.txt
  - examples/test_window_overlapped/CMakeLists.txt
  - examples/test_window_picker/CMakeLists.txt
  - src/CMakeLists.txt
  - src/modules/capture/CMakeLists.txt
  - src/treeland-shortcut/CMakeLists.txt
  - tests/test_window_picker/CMakeLists.txt
  - wallpaper-factory/CMakeLists.txt

### b55f2bd feat: replace assert with runtime error handling for output commit

- 被排除路径（2）：
  - src/output/output.cpp
  - src/seat/helper.cpp

### c03310d fix: clean up all treeland originated warnings on treeland startup

- 被排除路径（4）：
  - misc/systemd/treeland.service.in
  - src/core/qml/Decoration.qml
  - src/plugins/lockscreen/qml/SessionList.qml
  - src/surface/surfacecontainer.cpp

### ceac255 fix: clean up warnings on treeland startup

- 被排除路径（4）：
  - src/output/output.cpp
  - src/plugins/lockscreen/qml/ControlAction.qml
  - src/seat/helper.cpp
  - src/seat/helper.h

---

## 结果检查（@waylib-shared/）

- `waylibshared..waylibshared-merge` 的变更文件数：24
- 路径范围检查：仅包含 `waylib/` 与 `qwlroots/`（无其他目录路径被引入）

