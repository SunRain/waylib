# treeland waylib/qwlroots 同步记录（202607122330）

本文记录将 `treeland/` 的逻辑范围 `(fe6eb9bf634e43532fcbdacd67ed6c19e025c7ad..7da2254d386935f753ed907f8d6e76c1639d01a9]` 中涉及 `qwlroots/` 与 `waylib/` 的改动，经过历史重写归一化后，同步到 `waylib-shared/waylibshared-merge` 的范围、裁剪规则、提交映射、适配和验证结果。

> **结论：同步通过。** 39 个来源提交均按原顺序形成 1:1 目标提交；37 个直接应用，2 个合同适配，0 个空提交，0 个跳过。同步完成节点为 `71f98e4b`，未执行远程 push。

---

## 同步结论

- 历史映射门禁：`PASS`。
- 逻辑来源范围：`(fe6eb9bf634e43532fcbdacd67ed6c19e025c7ad..7da2254d386935f753ed907f8d6e76c1639d01a9]`。
- 规范化来源范围：`(7a8bb04b37e7bff0b3a6b0cfb3f72421f31271c2..7da2254d386935f753ed907f8d6e76c1639d01a9]`。
- 目标路径：`qwlroots/**`、`waylib/**`。
- 来源提交数：`39`。
- 目标提交数：`39`。
- action：`37 applied / 2 adapted / 0 empty / 0 skipped`。
- 目标冻结基线：`a5a8663c1defb2d4ae59668d57d334ca0d872b0c`。
- 同步完成节点：`71f98e4b51800dce5e689d571c979ac85fe6a28e`。
- 工作分支：`sync/treeland-qwlroots-waylib-fe6eb9bf-7da2254d`。
- 合入分支：`waylibshared-merge`。
- 远程推送：`no`。
- 执行检查时间：`2026-07-14T08:37:19+08:00`。

---

## 提取信息（@treeland/）

- 来源事实使用精确 commit hash，不使用本地旧 `master`。
- 用户下界（不包含）：`fe6eb9bf634e43532fcbdacd67ed6c19e025c7ad`。
- 当前主线等价下界（不包含）：`7a8bb04b37e7bff0b3a6b0cfb3f72421f31271c2`。
- 固定终点（包含）：`7da2254d386935f753ed907f8d6e76c1639d01a9`。
- 提取目录：`qwlroots/`、`waylib/`。
- 规范化范围相关提交数：`39`。
- 有序来源 commit 清单 SHA-256：`aff86eef88dfa6371b3b69a96bb2f5777311c24b8142283f1929f784926c8338`。
- 其中 19 个提交同时触达非目标路径，必须逐项裁剪。
- 其中 6 个是旧历史重写后的等价提交，33 个产生于旧线快照之后。

---

## 历史映射与上一轮连续性

`treeland/origin/master` 在 2026-07-12 被非快进替换。旧线与新线没有共同祖先，不能直接使用 `fe6eb9bf..7da2254d` 枚举提交；该错误范围会得到 850 个目标路径提交。

| 语义 | 旧线 | 新线 | 证据 |
|---|---|---|---|
| 用户下界 | `fe6eb9bf` | `7a8bb04b` | stable patch-id 均为 `317e77ba8274dde33a901a3d66898e5960a7105d` |
| 上一轮最后一个目标提交 | `88c558e6` | `05105eea` | stable patch-id 均为 `9643aa4a75d384b3d1ba40c2071dbf5abdecb880`；`05105eea` 是 `7a8bb04b` 的父提交 |
| 旧线映射区间 | `fe6eb9bf..1c6e6555` | `7a8bb04b..9079d1eb` | `range-diff` 共 31 项，全部为 `=` |

旧线下界之后触达目标路径的 6 个提交均完成 stable patch-id 和文件列表逐项映射。完整门禁、漂移规则和阻断条件见 `docs/treeland-waylib-qwlroots-history-mapping-gate_20260713_zh.md`。

---

## 合入策略

- 先执行历史映射门禁；未得到 `PASS` 时不得创建工作分支或回放提交。
- 每个来源提交只保留 `qwlroots/**` 与 `waylib/**` 的 diff。
- 同时触达其它路径的提交，把非目标路径完整写入 `[treeland-sync] : drop files list`。
- 39 个来源提交必须按原顺序形成 39 个独立目标提交，不 squash、不静默 skip。
- 每个目标提交记录原始提交信息、drop files list、adaptation notes、`Refs` 和完整 `Treeland-Commit`。
- `Refs` 固定指向 `docs/treeland-waylib-qwlroots-history-mapping-gate_20260713_zh.md`。
- 冲突和适配只能修改 `qwlroots/**` 或 `waylib/**`，不得把 `docs/**` 或 treeland 外层文件混入同步提交。
- 保持 `WaylibShared::*`、`WaylibSharedQWlroots::*`、核心 target、package config、QML URI 和安装目录合同。
- 门禁全部通过后快进合回 `waylibshared-merge`，不执行远程 push。

action 定义：

- `applied`：限域提取后可直接应用，不需要目标仓合同调整。
- `adapted`：保留来源语义，同时为目标仓既有安装、导出或文本卫生合同做等价调整。
- `empty`：来源补丁已由目标仓等价实现；本轮未出现。
- `skipped`：跳过来源提交；本轮未出现，也未授权。

---

## 提交映射（treeland → waylib-shared）

| # | treeland | waylib-shared | action | 原始 subject |
|---:|---|---|---|---|
| 1 | `f5d69115` | `12e1c713` | `applied` | fix: input popup positioning and enum flags |
| 2 | `b04afc1c` | `08be9620` | `applied` | fix(csd-popup): correct popup position for CSD surfaces |
| 3 | `44598345` | `dcc88a38` | `applied` | feat(wayland): add xdg-toplevel-tag-v1 protocol support |
| 4 | `5ff7f8d7` | `863f6ac3` | `applied` | fix: null check in input method grab |
| 5 | `c651335a` | `d8f9cf4d` | `applied` | fix: use safe xwayland surface signals |
| 6 | `6c907f3b` | `d1861209` | `applied` | feat(input): added implementation logic for treeland-input-manager. |
| 7 | `3f74ffd2` | `434449a9` | `applied` | fix: resolve splash transition size issue |
| 8 | `3bdd9dda` | `f56ac141` | `applied` | fix(vt): switch VT through wlroots session (#913) |
| 9 | `bcac250e` | `378c963c` | `applied` | fix: correct xwayland child change detection logic |
| 10 | `7cfe8783` | `6a6e35ef` | `applied` | fix: skip update on destroyed xwayland parent |
| 11 | `8edea9af` | `2c80769d` | `applied` | refactor(wine): clean up naming and use std::ranges in wine modules |
| 12 | `e0e96a4f` | `9dbdaa60` | `applied` | feat(input): add keyboard group support to WSeat |
| 13 | `5d095bdd` | `ef8e6227` | `applied` | fix(surface): keep subsurface registry in sync |
| 14 | `47bd7538` | `046cfa1a` | `applied` | test(surface): add below subsurface test case |
| 15 | `c1a34d06` | `6c772ce6` | `applied` | feat(input): support virtual keyboard in keyboard group |
| 16 | `ad1121ed` | `fcc268c6` | `applied` | fix: decouple title bar palette from DTK style constants |
| 17 | `3038fc4a` | `8cb0302f` | `applied` | fix(surface): fullscreen window size reduced by titlebar height |
| 18 | `192242b3` | `066ed988` | `applied` | feat(input): distinguishing between libinput mouse and touchpad functions |
| 19 | `715c9863` | `326b5a52` | `applied` | feat: disable maximize for non-maximizable windows |
| 20 | `c3bd7b4e` | `957f1f1f` | `applied` | fix(qtquick): create RHI textures from DRM formats |
| 21 | `921e15bc` | `dbf749ea` | `applied` | fix: add idle event dispatch to resolve lock screen time refresh issue |
| 22 | `6f0755ce` | `cfadaeb7` | `applied` | fix: improve hardware cursor size selection for large cursors |
| 23 | `d630db23` | `7a694f3b` | `applied` | fix: apply cursor settings without restart |
| 24 | `b203b109` | `b9a4d065` | `applied` | fix(qtquick): disconnect positionChanged before cursor cleanup |
| 25 | `1ab095e2` | `f7579892` | `applied` | fix: use std::as_const or const auto for range-for loops to prevent Qt container detachment |
| 26 | `08de629d` | `5f5f1a4b` | `applied` | fix: init QStyleHints on main thread at startup |
| 27 | `8eceafaf` | `30605cfc` | `adapted` | refactor: unify waylib logging category system |
| 28 | `42421160` | `ada803da` | `applied` | feat(im-candidate-panel): support tag-based and xprop-based IM candidate panel |
| 29 | `f6774c2b` | `2c5398a9` | `applied` | feat(xwayland): add async X11 property reading for IM candidate panel |
| 30 | `48f949d2` | `a9525ac4` | `applied` | fix: safe iteration with removeAt in waylib modules |
| 31 | `ea36fe5a` | `accd24bf` | `applied` | chore(wxwayland): remove unused Xcb::Property class and fix range-for |
| 32 | `d9a34c7e` | `269cc14d` | `applied` | fix(waylib): prevent stale subsurface access |
| 33 | `d3b1a1be` | `0acc3b32` | `applied` | fix(output): avoid crash when unplugging DP monitor |
| 34 | `57e4ed63` | `4e7db4a6` | `applied` | ci(debian): enable -Werror in qwlroots and waylib deb builds |
| 35 | `84e682d6` | `202f3cfe` | `applied` | fix(input): sync pressed keys on keyboard focus changes |
| 36 | `3a23d73b` | `d62bfba6` | `applied` | fix(waylib): guard text-input-v3 focus transitions |
| 37 | `64c204b0` | `4030a6a7` | `adapted` | feat: implement xdg-dialog-v1 protocol with KWin-style modal linkage |
| 38 | `6a1be427` | `7707daa7` | `applied` | feat(popup): replace mouse-intercept popup handling with keyboard grab tracking |
| 39 | `6c1b307e` | `71f98e4b` | `applied` | feat(effects): implement iOS 26 Liquid Glass effect with reusable components |

---

## commits：保留路径与 drop files list

以下内容是执行后的最终记录。保留路径来自归档方案 inventory；drop files list、action 和适配说明来自实际执行证据。

### 1. `f5d691158b21337755b0567d961ba0eeb2b3a589` → `12e1c713d7a34b7e3b470ae2401391909114f46e` — fix: input popup positioning and enum flags

- action：`applied`
- 保留路径：
  - `waylib/src/server/protocols/private/wtextinput_p.h`
- drop files list：
  - `src/core/shellhandler.cpp`
  - `src/output/output.cpp`
- adaptation notes：
  - none

### 2. `b04afc1ca7995eb158643765acc33ee6e26aff43` → `08be9620b1f1d645b21bbed1d4c0b27ddee8a45a` — fix(csd-popup): correct popup position for CSD surfaces

- action：`applied`
- 保留路径：
  - `waylib/src/server/qtquick/wsurfaceitem.cpp`
  - `waylib/src/server/qtquick/wsurfaceitem.h`
- drop files list：
  - `src/output/output.cpp`
  - `src/surface/surfacewrapper.cpp`
- adaptation notes：
  - none

### 3. `4459834533da62bdcbe07e777beb88a305f00097` → `dcc88a380668735873d59f678f563a0629393eb5` — feat(wayland): add xdg-toplevel-tag-v1 protocol support

- action：`applied`
- 保留路径：
  - `waylib/src/server/CMakeLists.txt`
  - `waylib/src/server/protocols/wxdgtoplevelsurface.cpp`
  - `waylib/src/server/protocols/wxdgtoplevelsurface.h`
  - `waylib/src/server/protocols/wxdgtopleveltagmanager.cpp`
  - `waylib/src/server/protocols/wxdgtopleveltagmanager.h`
- drop files list：
  - `examples/CMakeLists.txt`
  - `examples/test_toplevel_tag/CMakeLists.txt`
  - `examples/test_toplevel_tag/main.cpp`
  - `src/seat/helper.cpp`
  - `src/seat/helper.h`
- adaptation notes：
  - none

### 4. `5ff7f8d7addbfe2c45ad84db95aa37dfd9c0566e` → `863f6ac38beadea325b8d57e6d274fbbedbc22d2` — fix: null check in input method grab

- action：`applied`
- 保留路径：
  - `waylib/src/server/protocols/winputmethodhelper.cpp`
- drop files list：
  - none
- adaptation notes：
  - none

### 5. `c651335a5823c60e2c12a273cab9cc358014d411` → `d8f9cf4d5d75fe1e04e7a17ebd867c2e1ef3923b` — fix: use safe xwayland surface signals

- action：`applied`
- 保留路径：
  - `waylib/src/server/protocols/wxwaylandsurface.cpp`
  - `waylib/src/server/protocols/wxwaylandsurface.h`
- drop files list：
  - `src/core/shellhandler.cpp`
- adaptation notes：
  - none

### 6. `6c907f3b7544241d868b805b5afa0b92aabf6b55` → `d18612091f09f7e211f3d9e24774c74ef486a2ba` — feat(input): added implementation logic for treeland-input-manager.

- action：`applied`
- 保留路径：
  - `waylib/src/server/kernel/private/wcursor_p.h`
  - `waylib/src/server/kernel/wcursor.cpp`
  - `waylib/src/server/kernel/wcursor.h`
- drop files list：
  - `misc/dconfig/org.deepin.dde.treeland.json`
  - `src/CMakeLists.txt`
  - `src/input/inputdevice.cpp`
  - `src/input/inputdevice.h`
  - `src/input/inputmanager.cpp`
  - `src/input/inputmanager.h`
  - `src/modules/input-manager/inputmanagerinterfacev1.cpp`
  - `src/modules/input-manager/inputmanagerinterfacev1.h`
  - `src/seat/helper.cpp`
  - `src/seat/helper.h`
- adaptation notes：
  - none

### 7. `3f74ffd26de8b2270d0d1250f8ea6318fbeaa93e` → `434449a9e3930a566410a477b1d8e80501999a86` — fix: resolve splash transition size issue

- action：`applied`
- 保留路径：
  - `waylib/src/server/qtquick/private/wsurfaceitem_p.h`
  - `waylib/src/server/qtquick/wsurfaceitem.cpp`
  - `waylib/src/server/qtquick/wsurfaceitem.h`
- drop files list：
  - `src/surface/surfacewrapper.cpp`
- adaptation notes：
  - none

### 8. `3bdd9dda53a6e7fbbec1f65cf69501652ab3f80b` → `f56ac14179aa41b5a6b784f6b50976e3453aa86c` — fix(vt): switch VT through wlroots session (#913)

- action：`applied`
- 保留路径：
  - `waylib/src/server/kernel/wseat.cpp`
- drop files list：
  - `debian/control`
  - `misc/systemd/treeland.service.in`
  - `src/modules/ddm/ddminterfacev1.cpp`
  - `src/modules/ddm/ddminterfacev1.h`
  - `src/seat/helper.cpp`
- adaptation notes：
  - none

### 9. `bcac250e3c41859fff2d46821d5b40995b33a317` → `378c963c435b00e342cc9214a6d7f864a1efbe80` — fix: correct xwayland child change detection logic

- action：`applied`
- 保留路径：
  - `waylib/src/server/protocols/wxwaylandsurface.cpp`
- drop files list：
  - none
- adaptation notes：
  - none

### 10. `7cfe8783bb82b50d52cd4d0759c4dc14c832c2fa` → `6a6e35effaa71b05ca9b5d6f889c0e4d21a6a41a` — fix: skip update on destroyed xwayland parent

- action：`applied`
- 保留路径：
  - `waylib/src/server/protocols/wxwaylandsurface.cpp`
- drop files list：
  - none
- adaptation notes：
  - none

### 11. `8edea9af12ba14e4b816842b8dee20bd04140f73` → `2c80769de47ade56bab8404b387d56c6312bee08` — refactor(wine): clean up naming and use std::ranges in wine modules

- action：`applied`
- 保留路径：
  - `waylib/src/server/qtquick/woutputrenderwindow.cpp`
- drop files list：
  - `examples/test_virtual_output/virtualclient.cpp`
  - `src/core/shellhandler.cpp`
  - `src/core/shellhandler.h`
  - `src/modules/wine-window-management/winewindowmanagement.cpp`
  - `src/modules/wine-window-management/winewindowmanagement.h`
  - `src/modules/wine-window-state/winewindowstate.cpp`
- adaptation notes：
  - none

### 12. `e0e96a4f38ac16e33ced50b786cef76655cf994e` → `9dbdaa607e81d98d342ccd18354f755b1729535e` — feat(input): add keyboard group support to WSeat

- action：`applied`
- 保留路径：
  - `waylib/src/server/kernel/wseat.cpp`
- drop files list：
  - none
- adaptation notes：
  - none

### 13. `5d095bdda4decb395972c95ad984576d74d57cba` → `ef8e622751c19f6975bf107210fcaea01f4c69de` — fix(surface): keep subsurface registry in sync

- action：`applied`
- 保留路径：
  - `waylib/src/server/qtquick/private/wsurfaceitem_p.h`
  - `waylib/src/server/qtquick/wsurfaceitem.cpp`
- drop files list：
  - none
- adaptation notes：
  - none

### 14. `47bd753823c08b2ae0e83becf8021965e80f08d0` → `046cfa1a0c37702773e77597fd613c8551e7e42a` — test(surface): add below subsurface test case

- action：`applied`
- 保留路径：
  - `waylib/src/server/qtquick/wsurfaceitem.cpp`
  - `waylib/tests/manual/subsurface/Main.qml`
  - `waylib/tests/manual/subsurface/window.h`
- drop files list：
  - none
- adaptation notes：
  - none

### 15. `c1a34d0685f69998f6b1fb7837f21f2a888857bf` → `6c772ce6696bb133df07deb16cd74ba5551fe072` — feat(input): support virtual keyboard in keyboard group

- action：`applied`
- 保留路径：
  - `waylib/src/server/kernel/winputdevice.cpp`
  - `waylib/src/server/kernel/winputdevice.h`
  - `waylib/src/server/kernel/wseat.cpp`
  - `waylib/src/server/kernel/wseat.h`
  - `waylib/src/server/protocols/winputmethodhelper.cpp`
- drop files list：
  - `src/input/inputmanager.cpp`
  - `src/modules/keyboard-state-notify/keyboardstatenotifymanagerinterfacev1.cpp`
- adaptation notes：
  - none

### 16. `ad1121ed52d32ffde9f70413b84a60564721aa66` → `fcc268c6ee1561b1fc3a216e9ca4629944932979` — fix: decouple title bar palette from DTK style constants

- action：`applied`
- 保留路径：
  - `waylib/src/server/kernel/wserver.cpp`
  - `waylib/src/server/kernel/wserver.h`
  - `waylib/src/server/platformplugin/qwlrootsintegration.cpp`
  - `waylib/src/server/platformplugin/qwlrootsintegration.h`
- drop files list：
  - `src/CMakeLists.txt`
  - `src/core/qml/TitleBar.qml`
  - `src/main.cpp`
  - `src/modules/personalization/personalizationmanagerinterfacev1.cpp`
  - `src/seat/helper.cpp`
  - `src/seat/helper.h`
- adaptation notes：
  - none

### 17. `3038fc4ab82e11550abb5d41af309bf36ab764cc` → `8cb0302f91e5230c574d4df658eacbf5f6dea3b9` — fix(surface): fullscreen window size reduced by titlebar height

- action：`applied`
- 保留路径：
  - `waylib/src/server/qtquick/wsurfaceitem.cpp`
  - `waylib/src/server/qtquick/wsurfaceitem.h`
- drop files list：
  - `src/surface/surfacewrapper.cpp`
  - `src/surface/surfacewrapper.h`
- adaptation notes：
  - none

### 18. `192242b3de5ca842c3e31b29fd470e5c6420337a` → `066ed9883091d70536b5f2c1f57b0dd07e7bff88` — feat(input): distinguishing between libinput mouse and touchpad functions

- action：`applied`
- 保留路径：
  - `waylib/src/server/kernel/winputdevice.cpp`
  - `waylib/src/server/kernel/winputdevice.h`
- drop files list：
  - none
- adaptation notes：
  - none

### 19. `715c98638164076095a001cea3a625eab3e45f67` → `326b5a52876f18fdbd5f0cfe947fbd996afc164e` — feat: disable maximize for non-maximizable windows

- action：`applied`
- 保留路径：
  - `waylib/src/server/kernel/wtoplevelsurface.h`
  - `waylib/src/server/protocols/winputpopupsurface.cpp`
  - `waylib/src/server/protocols/wlayersurface.cpp`
  - `waylib/src/server/protocols/wxdgpopupsurface.cpp`
  - `waylib/src/server/protocols/wxdgtoplevelsurface.cpp`
  - `waylib/src/server/protocols/wxwaylandsurface.cpp`
- drop files list：
  - `src/core/qml/TitleBar.qml`
  - `src/core/qml/WindowMenu.qml`
  - `src/modules/shortcut/shortcutrunner.cpp`
  - `src/surface/surfacewrapper.cpp`
  - `src/surface/surfacewrapper.h`
- adaptation notes：
  - none

### 20. `c3bd7b4eb43e5ed0940bb23ba9d8f5a803156505` → `957f1f1f966311507375f6e12a382f7048cfad80` — fix(qtquick): create RHI textures from DRM formats

- action：`applied`
- 保留路径：
  - `waylib/src/server/qtquick/private/wrenderbuffernode.cpp`
  - `waylib/src/server/qtquick/wrenderhelper.cpp`
  - `waylib/src/server/qtquick/wrenderhelper.h`
- drop files list：
  - none
- adaptation notes：
  - none

### 21. `921e15bc45f9bcd009bd757598105c32788b330d` → `dbf749ea2651b1daa72eff1b0bbf06cfe3d8127c` — fix: add idle event dispatch to resolve lock screen time refresh issue

- action：`applied`
- 保留路径：
  - `waylib/src/server/kernel/private/wserver_p.h`
  - `waylib/src/server/kernel/wserver.cpp`
  - `waylib/src/server/kernel/wserver.h`
- drop files list：
  - none
- adaptation notes：
  - none

### 22. `6f0755ce38d9f246057df2b33dbcba124f35bfee` → `cfadaeb713555ddf85868eaf639d4e5f1aafd924` — fix: improve hardware cursor size selection for large cursors

- action：`applied`
- 保留路径：
  - `waylib/src/server/qtquick/woutputrenderwindow.cpp`
- drop files list：
  - none
- adaptation notes：
  - none

### 23. `d630db23f9fc57afd7969cdcc0713e151b309a4f` → `7a694f3b9e35927aaa30052abd1b35fb469c9374` — fix: apply cursor settings without restart

- action：`applied`
- 保留路径：
  - `waylib/src/server/qtquick/wquickcursor.cpp`
- drop files list：
  - `src/seat/helper.cpp`
  - `src/session/session.cpp`
  - `src/session/session.h`
  - `src/xsettings/settingmanager.cpp`
- adaptation notes：
  - none

### 24. `b203b10960be5713d89c70aa57e677c2c30cff75` → `b9a4d065b8d09c51413cc371b8a2a9680fc51699` — fix(qtquick): disconnect positionChanged before cursor cleanup

- action：`applied`
- 保留路径：
  - `waylib/src/server/qtquick/woutputitem.cpp`
- drop files list：
  - none
- adaptation notes：
  - none

### 25. `1ab095e20d2de52827f7a2519be7ab0a852425fb` → `f7579892d1a4eb0fc19742b3594c79a729d9a0c3` — fix: use std::as_const or const auto for range-for loops to prevent Qt container detachment

- action：`applied`
- 保留路径：
  - `waylib/src/server/kernel/winputdevice.cpp`
  - `waylib/src/server/protocols/wsessionlock.cpp`
  - `waylib/src/server/qtquick/woutputlayoutitem.cpp`
  - `waylib/src/server/qtquick/woutputrenderwindow.cpp`
  - `waylib/src/server/qtquick/wqmlcreator.cpp`
  - `waylib/src/server/qtquick/wsurfaceitem.cpp`
- drop files list：
  - `examples/test_color_control/main.cpp`
  - `examples/test_set_wallpaper/main.cpp`
  - `examples/test_wallpaper_color/main.cpp`
  - `src/core/layersurfacecontainer.cpp`
  - `src/core/popupsurfacecontainer.cpp`
  - `src/core/rootsurfacecontainer.cpp`
  - `src/greeter/usermodel.cpp`
  - `src/input/inputmanager.cpp`
  - `src/modules/dde-shell/ddeshellmanagerinterfacev1.cpp`
  - `src/modules/foreign-toplevel/foreigntoplevelmanagerv1.cpp`
  - `src/modules/personalization/personalizationmanagerinterfacev1.cpp`
  - `src/output/output.cpp`
  - `src/output/outputlifecyclemanager.cpp`
  - `src/seat/helper.cpp`
  - `src/seat/seatsmanager.cpp`
  - `src/session/session.cpp`
  - `src/surface/seatsurfacemanager.cpp`
  - `src/surface/surfacecontainer.cpp`
  - `src/surface/surfacewrapper.cpp`
  - `src/systemd-socket.cpp`
  - `src/treeland-shortcut/shortcut.cpp`
  - `src/workspace/workspace.cpp`
  - `src/workspace/workspacemodel.cpp`
  - `src/xsettings/xresource.cpp`
  - `src/xsettings/xsettings.cpp`
  - `wallpaper-factory/treelandwallpapernotifierclient.cpp`
- adaptation notes：
  - none

### 26. `08de629dcdd618a7f0492fc72276554108515c3f` → `5f5f1a4b7de823814d6adbce4392ea123d9998be` — fix: init QStyleHints on main thread at startup

- action：`applied`
- 保留路径：
  - `waylib/src/server/platformplugin/qwlrootsintegration.cpp`
- drop files list：
  - none
- adaptation notes：
  - none

### 27. `8eceafaf187c478e7c645c957ca3b1c926070a05` → `30605cfc1f330f1fe6597731ba218a633f2c6f97` — refactor: unify waylib logging category system

- action：`adapted`
- 保留路径：
  - `waylib/src/server/CMakeLists.txt`
  - `waylib/src/server/kernel/wcursor.cpp`
  - `waylib/src/server/kernel/winputdevice.cpp`
  - `waylib/src/server/kernel/woutput.cpp`
  - `waylib/src/server/kernel/wseat.cpp`
  - `waylib/src/server/kernel/wsocket.cpp`
  - `waylib/src/server/platformplugin/qwlrootsintegration.cpp`
  - `waylib/src/server/protocols/private/winputmethodv2.cpp`
  - `waylib/src/server/protocols/private/wtextinputv2.cpp`
  - `waylib/src/server/protocols/private/wtextinputv3.cpp`
  - `waylib/src/server/protocols/private/wvirtualkeyboardv1.cpp`
  - `waylib/src/server/protocols/wextforeigntoplevellistv1.cpp`
  - `waylib/src/server/protocols/wforeigntoplevelv1.cpp`
  - `waylib/src/server/protocols/winputmethodhelper.cpp`
  - `waylib/src/server/protocols/wlayershell.cpp`
  - `waylib/src/server/protocols/wlayersurface.cpp`
  - `waylib/src/server/protocols/wxdgdecorationmanager.cpp`
  - `waylib/src/server/protocols/wxdgoutput.cpp`
  - `waylib/src/server/qtquick/private/wbufferrenderer.cpp`
  - `waylib/src/server/qtquick/private/wrenderbuffernode.cpp`
  - `waylib/src/server/qtquick/wbufferitem.cpp`
  - `waylib/src/server/qtquick/woutputhelper.cpp`
  - `waylib/src/server/qtquick/woutputlayer.cpp`
  - `waylib/src/server/qtquick/woutputrenderwindow.cpp`
  - `waylib/src/server/qtquick/wqmlcreator.cpp`
  - `waylib/src/server/qtquick/wquickcursor.cpp`
  - `waylib/src/server/qtquick/wrenderhelper.cpp`
  - `waylib/src/server/qtquick/wsgtextureprovider.cpp`
  - `waylib/src/server/qtquick/wsurfaceitem.cpp`
  - `waylib/src/server/qtquick/wtextureproviderprovider.cpp`
  - `waylib/src/server/utils/wbufferdumper.cpp`
  - `waylib/src/server/utils/wcursorimage.cpp`
  - `waylib/src/server/utils/wextimagecapturesourcev1impl.cpp`
  - `waylib/src/server/utils/wextimagecapturesourcev1impl.h`
  - `waylib/src/server/utils/wthreadutils.h`
  - `waylib/src/server/wayliblogging.cpp`
  - `waylib/src/server/wayliblogging.h`
- drop files list：
  - none
- adaptation notes：
  - 清理迁移日志语句中的行尾空白；运行行为和日志分类标识不变。
  - 保持既有公共头安装根、目标名、导出命名空间、包文件名和 QML URI。

### 28. `4242116024cdeea9ecb564c47c3534be0c0aa244` → `ada803dae32d89bb133338cc0c98cdf630a67f98` — feat(im-candidate-panel): support tag-based and xprop-based IM candidate panel

- action：`applied`
- 保留路径：
  - `waylib/src/server/protocols/winputmethodhelper.cpp`
  - `waylib/src/server/protocols/winputmethodhelper.h`
  - `waylib/src/server/protocols/wxwayland.cpp`
  - `waylib/src/server/protocols/wxwayland.h`
- drop files list：
  - `src/CMakeLists.txt`
  - `src/core/imcandidatepanelmanager.cpp`
  - `src/core/imcandidatepanelmanager.h`
  - `src/core/shellhandler.cpp`
  - `src/core/shellhandler.h`
  - `src/output/output.cpp`
  - `src/output/output.h`
  - `src/seat/helper.cpp`
  - `src/surface/surfacewrapper.cpp`
  - `src/surface/surfacewrapper.h`
- adaptation notes：
  - none

### 29. `f6774c2b246701d7208d8675ea26dd7ecbac2932` → `2c5398a94b921e357b24b7dbd0eefb1282e4e22c` — feat(xwayland): add async X11 property reading for IM candidate panel

- action：`applied`
- 保留路径：
  - `waylib/src/server/protocols/wxwayland.cpp`
  - `waylib/src/server/protocols/wxwayland.h`
- drop files list：
  - `src/core/imcandidatepanelmanager.cpp`
  - `src/core/imcandidatepanelmanager.h`
  - `src/core/shellhandler.cpp`
  - `src/core/shellhandler.h`
- adaptation notes：
  - none

### 30. `48f949d2a46163a85cb1804baab78dd858fa4f8e` → `a9525ac440c7fcdd854c785d71389e604845884c` — fix: safe iteration with removeAt in waylib modules

- action：`applied`
- 保留路径：
  - `waylib/src/server/kernel/wglobal.cpp`
  - `waylib/src/server/kernel/wseat.cpp`
  - `waylib/src/server/qtquick/private/wbufferrenderer.cpp`
- drop files list：
  - none
- adaptation notes：
  - none

### 31. `ea36fe5a66dc2458fedb911c1d3f5c08bc774b50` → `accd24bfbbdce7eadee4f80376e79c597520ab96` — chore(wxwayland): remove unused Xcb::Property class and fix range-for

- action：`applied`
- 保留路径：
  - `waylib/src/server/protocols/wxwayland.cpp`
  - `waylib/src/server/protocols/wxwayland.h`
- drop files list：
  - none
- adaptation notes：
  - none

### 32. `d9a34c7e2cff9fc83b6ebc404c130ee8e0de9026` → `269cc14d7a6953e465504c083b6badd66963b562` — fix(waylib): prevent stale subsurface access

- action：`applied`
- 保留路径：
  - `waylib/src/server/qtquick/wsurfaceitem.cpp`
- drop files list：
  - none
- adaptation notes：
  - none

### 33. `d3b1a1beb0aeb6b5d1471e92ecde8e52f9ecd6ad` → `0acc3b320a6b2ab43262fa98cfd43d8fe6ac467b` — fix(output): avoid crash when unplugging DP monitor

- action：`applied`
- 保留路径：
  - `waylib/src/server/qtquick/woutputrenderwindow.cpp`
- drop files list：
  - none
- adaptation notes：
  - none

### 34. `57e4ed63776d0f3ab4c0e8043be3ccc904c87b6a` → `4e7db4a6d8c6ce6a54ef19312d56cf6a96ae35e7` — ci(debian): enable -Werror in qwlroots and waylib deb builds

- action：`applied`
- 保留路径：
  - `qwlroots/debian/rules`
  - `waylib/debian/rules`
- drop files list：
  - none
- adaptation notes：
  - none

### 35. `84e682d6ecda234ee5d9140c6cac7a89af68bb96` → `202f3cfeb1a3b4bd10b75d965bbbf93498a8b358` — fix(input): sync pressed keys on keyboard focus changes

- action：`applied`
- 保留路径：
  - `waylib/src/server/kernel/wseat.cpp`
- drop files list：
  - none
- adaptation notes：
  - none

### 36. `3a23d73b545afb8b79f11c74746d2ac7faff101a` → `d62bfba6767ac914eb032f9213c775a02390883d` — fix(waylib): guard text-input-v3 focus transitions

- action：`applied`
- 保留路径：
  - `waylib/src/server/protocols/private/wtextinputv3.cpp`
  - `waylib/src/server/protocols/winputmethodhelper.cpp`
- drop files list：
  - none
- adaptation notes：
  - none

### 37. `64c204b00e9790f08b810f71cbd51b405f6bea42` → `4030a6a7032b4350581e72251a87463cfc5ff70c` — feat: implement xdg-dialog-v1 protocol with KWin-style modal linkage

- action：`adapted`
- 保留路径：
  - `qwlroots/.clang-format`
  - `qwlroots/src/CMakeLists.txt`
  - `qwlroots/src/types/qwxdgdialogv1.h`
  - `waylib/src/server/CMakeLists.txt`
  - `waylib/src/server/protocols/wxdgdialogmanagerv1.cpp`
  - `waylib/src/server/protocols/wxdgdialogmanagerv1.h`
  - `waylib/src/server/wayliblogging.cpp`
  - `waylib/src/server/wayliblogging.h`
- drop files list：
  - `src/core/qml/WindowMenu.qml`
  - `src/seat/helper.cpp`
  - `src/seat/helper.h`
  - `src/surface/surfacewrapper.cpp`
  - `src/surface/surfacewrapper.h`
  - `src/workspace/workspace.cpp`
- adaptation notes：
  - 为 Qt 6.10+ 的静态 qwlroots 导出补齐 Qt6 CorePrivate 条件依赖发现，修复安装后 consumer 配置失败。
  - 保持 WaylibShared 目标名、导出命名空间、包文件名、QML URI、安装目录和公共头根路径不变。
  - 清理新增 qwlroots wrapper 头文件中的一处行尾空白。

### 38. `6a1be4276741ccc34d9fee6d4e14d0d9e447f02e` → `7707daa72fe294e8284d6c53a94212390e42ccf3` — feat(popup): replace mouse-intercept popup handling with keyboard grab tracking

- action：`applied`
- 保留路径：
  - `waylib/src/server/protocols/winputmethodhelper.cpp`
  - `waylib/src/server/protocols/wxdgpopupsurface.cpp`
- drop files list：
  - `src/CMakeLists.txt`
  - `src/common/treelandlogging.cpp`
  - `src/common/treelandlogging.h`
  - `src/core/popupfocusmanager.cpp`
  - `src/core/popupfocusmanager.h`
  - `src/core/popupsurfacecontainer.cpp`
  - `src/core/popupsurfacecontainer.h`
  - `src/core/shellhandler.cpp`
  - `src/core/shellhandler.h`
  - `src/seat/helper.cpp`
  - `src/seat/helper.h`
  - `src/surface/surfacewrapper.cpp`
  - `src/workspace/workspace.cpp`
- adaptation notes：
  - none

### 39. `6c1b307ef625f8850d472b7ec6697eff914d4627` → `71f98e4b51800dce5e689d571c979ac85fe6a28e` — feat(effects): implement iOS 26 Liquid Glass effect with reusable components

- action：`applied`
- 保留路径：
  - `waylib/src/server/qtquick/wrenderbufferblitter.cpp`
- drop files list：
  - `.github/workflows/treeland-archlinux-build.yml`
  - `debian/control`
  - `examples/CMakeLists.txt`
  - `examples/test_glass/CMakeLists.txt`
  - `examples/test_glass/Main.qml`
  - `examples/test_glass/assets/default-glass-background.jpg`
  - `examples/test_glass/helper.cpp`
  - `examples/test_glass/helper.h`
  - `examples/test_glass/main.cpp`
  - `misc/dconfig/org.deepin.dde.treeland.user.json`
  - `misc/shaders/liquidglass.frag`
  - `misc/shaders/liquidglass.vert`
  - `src/CMakeLists.txt`
  - `src/core/qml/Effects/Blur.qml`
  - `src/core/qml/Effects/GlassEffect.qml`
  - `src/plugins/lockscreen/qml/RoundBlur.qml`
  - `tests/CMakeLists.txt`
  - `tests/test_effect_glass/CMakeLists.txt`
  - `tests/test_effect_glass/GlassEffectScene.qml`
  - `tests/test_effect_glass/TestHelper.cpp`
  - `tests/test_effect_glass/TestHelper.h`
  - `tests/test_effect_glass/TestWindow.qml`
  - `tests/test_effect_glass/main.cpp`
- adaptation notes：
  - none

---

## 关键适配说明

### `8eceafaf` — 日志分类统一

- 目标提交：`30605cfc1f330f1fe6597731ba218a633f2c6f97`。
- 清理迁移日志语句中的行尾空白，不改变运行逻辑和日志分类标识。
- `wayliblogging.h` 继续安装到既有 `include/waylibshared/waylibserver/` 根路径。
- target、导出命名空间、package 文件名和 QML URI 保持不变。

### `64c204b0` — xdg-dialog-v1

- 目标提交：`4030a6a7032b4350581e72251a87463cfc5ff70c`。
- 为 Qt 6.10+ 的静态 qwlroots 导出补齐 Qt6 CorePrivate 条件依赖发现。
- 该适配修复安装后 consumer 在 CMake generate 阶段找不到 imported private target 的问题。
- 清理新增 qwlroots wrapper 头文件中的一处行尾空白。
- `WaylibShared::*`、`WaylibSharedQWlroots::*`、package 文件名、安装目录和 QML URI 保持不变。

---

## 合同与安装审计

- 路径边界：`PASS`。冻结基线到同步完成节点的业务 diff 仅包含 `qwlroots/**` 与 `waylib/**`。
- 1:1 追溯：`PASS`。39 个目标提交的 `Treeland-Commit` 顺序与来源一致。
- drop files list：`PASS`。逐提交与来源非目标路径集合一致。
- CMake / target / export：`PASS`。核心 target、`EXPORT_NAME`、`OUTPUT_NAME`、namespace 与 QML URI 未漂移。
- 安装清单：`PASS`。同步基线与同步完成节点的安装条目由 218 增至 222，无删除。
- private header：`PASS`。安装清单不包含 `private/` 或 `*_p.h`。
- package 文件名：`PASS`。before/after 完全一致。
- public/exported namespace：`PASS`。最终适配 diff 没有命名空间声明变化。
- 文本卫生：`PASS`。`git diff --check` 无输出。

本轮新增的公共头文件：

- `include/waylibshared/qwlroots/qwxdgdialogv1.h`
- `include/waylibshared/waylibserver/wayliblogging.h`
- `include/waylibshared/waylibserver/wxdgdialogmanagerv1.h`
- `include/waylibshared/waylibserver/wxdgtopleveltagmanager.h`

---

## 验证结果

同步完成时的 deep QA 结果：

- 历史映射脚本：`PASS`。
- Release core-only configure/build：`PASS`。
- tests-enabled configure/build：`PASS`。
- `test_qwobject`：4 passed。
- `test_wwrappointer`：6 passed。
- `test_qsgrenderer_accessor`：7 passed。
- QtTest 合计：17 passed。
- 安装后 consumer configure/build：`PASS`。
- consumer CTest：2/2 passed（CMake 链接与 QML import）。
- 综合静态审计：`PASS`。

同步执行时系统尚未安装 Vulkan headers。验证从 pacman 缓存解压到 `/tmp/ha-vulkan-headers`，通过 `CPLUS_INCLUDE_PATH` 使用，没有修改系统环境。

---

## 同步后收敛与当前状态

同步完成节点固定为 `71f98e4b`。随后 `waylibshared-merge` 增加了两项独立收敛修订，它们不属于 39 项 treeland 同步映射：

- `f57855c16b1fce253e2b5219ab4b89c26deae24c` — `fix(cmake): 强化安装与消费端契约`。
- `ccb49b2a9302671f58fadfdad4c088fe828b7215` — `fix(qml): 明确不可创建类型的诊断信息`。

系统安装 Vulkan headers 后执行的最终全量回归结果：

- Release 全量配置和构建：`PASS`，CMake 识别 `WrapVulkanHeaders: /usr/include`。
- `<build>/waylib` CTest：3/3 passed。
- 三个 QtTest 程序：17/17 passed。
- 安装后 CMake target、pkg-config、QML import consumer：3/3 passed。
- 原生编译器直接消费 `pkg-config --cflags --libs WaylibSharedServer`：编译和运行通过。
- 安装结果：220 个普通文件、2 个共享库符号链接、0 个 private header。

顶层构建目录当前没有聚合 CTest；项目测试必须从 `<build>/waylib` 执行。这是既有测试注册边界，不影响本次同步和后续收敛的通过结论。

---

## 结果检查（@waylib-shared/）

后续复核本次同步时，应同时满足：

- `a5a8663c..71f98e4b` 的业务变更只包含 `qwlroots/` 与 `waylib/`。
- 39 个目标提交均可通过 `Treeland-Commit` 回溯来源。
- 目标提交顺序与规范化来源范围一致。
- `applied / adapted / empty / skipped` 数量为 `37 / 2 / 0 / 0`。
- 所有 mixed 提交的 drop files list 与来源非目标路径一致。
- 4 个新增公共头均位于既有 `waylibshared/` 安装根目录。
- 不存在新增 private header、package 文件名漂移、导出命名空间漂移或 QML URI 漂移。
- 构建、项目测试和安装后 consumer 仍可通过。

---

## 关联文档与证据

- 历史映射门禁：`docs/treeland-waylib-qwlroots-history-mapping-gate_20260713_zh.md`
- 上一轮同步记录：`docs/treeland-waylib-qwlroots-sync_202605220117_zh.md`
- 同步策略：`docs/skills/treeland-waylib-qwlroots-sync/SKILL.md`
- 归档方案包：父工作区 `.helloagents/archive/2026-07/202607122330_treeland-qwlroots-waylib-fe6eb9bf-7da2254d/`
- 执行审计：父工作区 `.helloagents/sessions/waylibshared/host-e94c0ac2/artifacts/treeland-qwlroots-waylib-sync-audit.json`
- 完整映射：父工作区 `.helloagents/sessions/waylibshared/host-e94c0ac2/artifacts/treeland-qwlroots-waylib-sync-mapping.md`
- 执行报告：父工作区 `.helloagents/sessions/waylibshared/host-e94c0ac2/artifacts/treeland-qwlroots-waylib-sync-report.md`
