# treeland waylib/qwlroots 同步记录（202601212031）

本文将 `helloagents/history/2026-01/202601212031_treeland_waylib_qwlroots_sync/how.md` 中与“mixed commits”相关的关键信息，整理为 `docs/` 下的独立文档，便于项目内直接查阅与追溯。

---

## 提取信息（@treeland/）

- 用于提取的分支：`master`
- 提取目录范围：`waylib/`、`qwlroots/`
- 提取范围（Git range）：
  - 起始 commit（不包含）：`7c119390156d1478b8e61f13ca21c54261f931b0`（2025-10-09 09:56:13 +0800，`fix: fix private module inclusion on lower version of Qt`）
  - 结束 commit（包含）：`3e5fdd4d32396b20dc0294b84277b831412484b3`（2026-01-19 10:25:26 +0800，`fix: compilation issues due to update in treeland-dde-shell-v1 protocol`）

---

## 提交映射（treeland → waylib-shared）

> 说明：
> - `pure`：仅触达 `waylib/`/`qwlroots/`，在 `waylib-shared` 中以 `git cherry-pick -x` 合入。
> - `mixed`：同时触达其他路径，仅提取 `waylib/`/`qwlroots/` 的 diff 合入；其余路径变更见下文清单。

| # | treeland | waylib-shared | 类型 | 路径 | 说明 |
|---:|---|---|---|---|---|
| 1 | 3f03884 | 5e87a00e | mixed | waylib | mixed：排除 3 个非目标路径文件 |
| 2 | 5bde968 | ef5f9f14 | pure | waylib | pure |
| 3 | 6547558 | dcfbdc39 | mixed | waylib | mixed：排除 3 个非目标路径文件 |
| 4 | 1866331 | 8244ae63 | pure | waylib | pure |
| 5 | 04791bc | 40935411 | pure | waylib | pure |
| 6 | f50669e | 8d996678 | mixed | waylib | mixed：排除 3 个非目标路径文件 |
| 7 | ccae4b7 | 53cb64f4 | pure | waylib+qwlroots | pure |
| 8 | cfaea20 | 579793ba | mixed | waylib | mixed：排除 24 个非目标路径文件 |
| 9 | 2faa9ad | d12394bf | pure | waylib | pure |
| 10 | 03ec65c | 6f5b1838 | pure | waylib | pure |
| 11 | 40f596a | 85fa5ce4 | mixed | waylib | mixed：排除 1 个非目标路径文件 |
| 12 | 92be3d9 | c6fb5818 | pure | waylib | pure |
| 13 | 2888fc2 | 153fdb1f | mixed | waylib | mixed：排除 9 个非目标路径文件 |
| 14 | ff33316 | 0079f393 | mixed | waylib | mixed：排除 10 个非目标路径文件 |
| 15 | 3f3d6e6 | 262ab6e0 | pure | waylib | pure |
| 16 | dd3dd7e | 3bdb3ee6 | mixed | waylib | mixed：排除 15 个非目标路径文件 |
| 17 | 972de6f | e979d558 | mixed | waylib | mixed：排除 7 个非目标路径文件 |
| 18 | e9c2991 | 940f4608 | mixed | waylib | mixed：排除 2 个非目标路径文件 |
| 19 | 8afacc5 | d0e52819 | mixed | waylib | mixed：排除 5 个非目标路径文件 |
| 20 | 2fba401 | 37fd9627 | mixed | waylib | mixed：排除 1 个非目标路径文件 |
| 21 | ef344c0 | cbee449c | mixed | waylib | mixed：排除 17 个非目标路径文件 |
| 22 | 920c53f | 2b94c05b | pure | waylib | pure |
| 23 | 2b3d917 | 1ea196c4 | pure | waylib | pure |
| 24 | 8df383a | 60cbb5c4 | pure | waylib | pure |
| 25 | 970f8cc | 7ade194e | mixed | waylib | mixed：排除 1 个非目标路径文件 |
| 26 | 661eb33 | 7607d1de | mixed | waylib | mixed：排除 9 个非目标路径文件 |

---

## mixed commits：被排除路径清单

### 3f03884 fix: fix build failure on Arch Linux

- 被排除路径（3）：
  - src/CMakeLists.txt
  - src/surface/surfacefilterproxymodel.cpp
  - src/treeland-shortcut/CMakeLists.txt

### 6547558 feat: Add per-user XWayland session management

- 被排除路径（3）：
  - src/core/treeland.cpp
  - src/seat/helper.cpp
  - src/seat/helper.h

### f50669e refactor: implement atomic multi-output configuration

- 被排除路径（3）：
  - .gitignore
  - src/seat/helper.cpp
  - src/seat/helper.h

### cfaea20 feat: support setting brightness & color temperature through treeland-output-manager-v1

- 被排除路径（24）：
  - examples/CMakeLists.txt
  - examples/test_color_control/CMakeLists.txt
  - examples/test_color_control/main.cpp
  - examples/test_primary_output/main.cpp
  - misc/dconfig/org.deepin.treeland.output.json
  - src/CMakeLists.txt
  - src/modules/CMakeLists.txt
  - src/modules/output-manager/CMakeLists.txt
  - src/modules/output-manager/impl/output_manager_impl.cpp
  - src/modules/output-manager/impl/output_manager_impl.h
  - src/modules/output-manager/outputmanagement.cpp
  - src/modules/output-manager/outputmanagement.h
  - src/modules/primary-output/CMakeLists.txt
  - src/modules/primary-output/impl/output_manager_impl.cpp
  - src/modules/primary-output/impl/output_manager_impl.h
  - src/modules/primary-output/outputmanagement.cpp
  - src/modules/primary-output/outputmanagement.h
  - src/output/backlight.cpp
  - src/output/backlight.h
  - src/output/output.cpp
  - src/output/output.h
  - src/seat/helper.cpp
  - src/seat/helper.h
  - tests/test_protocol_primary-output/main.cpp

### 40f596a fix: reload cursor image when scale changes

- 被排除路径（1）：
  - src/core/qml/PrimaryOutput.qml

### 2888fc2 fix: fix potential crash in moveResizeState surface handling

- 被排除路径（9）：
  - src/core/rootsurfacecontainer.cpp
  - src/core/shellhandler.cpp
  - src/modules/foreign-toplevel/foreigntoplevelmanagerv1.cpp
  - src/plugins/multitaskview/multitaskview.cpp
  - src/seat/helper.cpp
  - src/surface/surfacefilterproxymodel.cpp
  - src/surface/surfaceproxy.cpp
  - src/surface/surfacewrapper.cpp
  - src/surface/surfacewrapper.h

### ff33316 feat: simplify prelaunch splash icon path

- 被排除路径（10）：
  - src/core/qml/PrelaunchSplash.qml
  - src/core/qmlengine.cpp
  - src/core/qmlengine.h
  - src/core/shellhandler.cpp
  - src/core/shellhandler.h
  - src/modules/prelaunch-splash/prelaunchsplash.cpp
  - src/modules/prelaunch-splash/prelaunchsplash.h
  - src/seat/helper.cpp
  - src/surface/surfacewrapper.cpp
  - src/surface/surfacewrapper.h

### dd3dd7e fix: fix multiple code review issues

- 被排除路径（15）：
  - CMakeLists.txt
  - src/core/qml/PrelaunchSplash.qml
  - src/core/qmlengine.cpp
  - src/core/qmlengine.h
  - src/core/shellhandler.cpp
  - src/core/shellhandler.h
  - src/core/treeland.cpp
  - src/core/windowsizestore.cpp
  - src/core/windowsizestore.h
  - src/modules/app-id-resolver/appidresolver.cpp
  - src/modules/app-id-resolver/appidresolver.h
  - src/seat/helper.cpp
  - src/surface/surfacewrapper.cpp
  - src/workspace/workspace.cpp
  - tools/treeland-session-helper/main.cpp

### 972de6f fix: fix various memory and resource management issues

- 被排除路径（7）：
  - src/core/qml/PrelaunchSplash.qml
  - src/core/shellhandler.cpp
  - src/core/shellhandler.h
  - src/core/windowsizestore.h
  - src/modules/app-id-resolver/appidresolver.cpp
  - src/surface/surfacewrapper.cpp
  - tools/treeland-session-helper/main.cpp

### e9c2991 refactor: simplify buffer property handling in WBufferItem

- 被排除路径（2）：
  - src/main.cpp
  - src/modules/prelaunch-splash/prelaunchsplash.cpp

### 8afacc5 feat: optimize prelaunch splash handling and logging

- 被排除路径（5）：
  - src/core/qml/PrelaunchSplash.qml
  - src/core/shellhandler.cpp
  - src/core/windowsizestore.h
  - src/seat/helper.cpp
  - src/surface/surfacewrapper.cpp

### 2fba401 fix: correct workspace change detection logic

- 被排除路径（1）：
  - src/surface/surfacewrapper.cpp

### ef344c0 fix: clang compiler warnings

- 被排除路径（17）：
  - CMakeLists.txt
  - CMakePresets.json
  - src/core/lockscreen.cpp
  - src/core/qmlengine.cpp
  - src/core/shellhandler.cpp
  - src/core/treeland.cpp
  - src/modules/capture/capture.cpp
  - src/modules/foreign-toplevel/foreigntoplevelmanagerv1.cpp
  - src/modules/foreign-toplevel/impl/foreign_toplevel_manager_impl.cpp
  - src/modules/foreign-toplevel/impl/foreign_toplevel_manager_impl.h
  - src/modules/item-selector/itemselector.cpp
  - src/modules/personalization/impl/appearance_impl.h
  - src/modules/personalization/impl/font_impl.h
  - src/modules/personalization/impl/personalization_manager_impl.h
  - src/modules/personalization/personalizationmanager.cpp
  - src/seat/helper.cpp
  - src/xsettings/xsettings.cpp

### 970f8cc fix: avoid double removal on session destroy by requesting surface close

- 被排除路径（1）：
  - src/seat/helper.cpp

### 661eb33 feat: adopt kde-keystate-v5 to expose states of stateful keys

- 被排除路径（9）：
  - examples/CMakeLists.txt
  - examples/test_keystate/CMakeLists.txt
  - examples/test_keystate/main.cpp
  - protocols/kde-keystate.xml
  - src/modules/CMakeLists.txt
  - src/modules/keystate/CMakeLists.txt
  - src/modules/keystate/keystate.cpp
  - src/modules/keystate/keystate.h
  - src/seat/helper.cpp

---

## 冲突与处理方式

- 冲突提交：`3f03884`（`fix: fix build failure on Arch Linux`）
- 冲突文件：
  - `waylib/CMakeLists.txt`
  - `waylib/src/server/CMakeLists.txt`
- 处理方式：
  - 在应用 mixed patch 的 3-way 合并过程中出现冲突，采用人工消解后继续
  - 合并原则：以 `waylib-shared` 当前实现为准（保留既有 ECM/WaylibShared 安装目录相关逻辑），仅合入 `waylib/` 与 `qwlroots/` 目录下的上游改动
