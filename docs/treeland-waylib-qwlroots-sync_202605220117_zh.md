# treeland waylib/qwlroots 同步记录（202605220117）

本文记录将 `treeland/` 仓库 `master` 分支在区间 `e408649542182c55773b38a2d97b40765eb6a59b..fe6eb9bf634e43532fcbdacd67ed6c19e025c7ad`（左开右闭）内，涉及 `waylib/` 与 `qwlroots/` 的改动同步合入 `waylib-shared/` 仓库 `waylibshared-merge` 分支的范围、裁剪规则与追溯信息。

---

## 提取信息（@treeland/）

- 用于提取的分支：`master`
- 提取目录范围：`waylib/`、`qwlroots/`
- 提取范围（Git range）：
  - 起始 commit（不包含）：`e408649542182c55773b38a2d97b40765eb6a59b`
  - 结束 commit（包含）：`fe6eb9bf634e43532fcbdacd67ed6c19e025c7ad`
- 相关提交数：`26`
- 说明：区间内并非所有提交都触达 `waylib/`/`qwlroots/`；下文仅列出触达目标目录并参与同步的提交。

---

## 合入策略

- `pure`：仅触达 `waylib/`/`qwlroots/`，按原提交顺序限域回放。
- `mixed`：同时触达其他路径，仅保留 `waylib/`/`qwlroots/` 的 diff 合入，其余路径变更全部丢弃。
- 所有同步提交都必须包含：原始提交信息、`[treeland-sync] : drop files list`、本文档 `Refs` 和 `Treeland-Commit`。
- 本文档作为同步提交的追溯引用，单独提交；后续 26 个同步提交不得夹带 `docs/` 变更。

---

## 提交映射（treeland → waylib-shared）

| # | treeland | waylib-shared | 类型 | 路径 | 原始 subject |
|---:|---|---|---|---|---|
| 1 | `86fc904c` | 待回放 | mixed | waylib | fix: qw_buffer metatype handling for Clang builds |
| 2 | `687959ca` | 待回放 | pure | qwlroots | fix: correct CMake config name for submodule build |
| 3 | `ab189f52` | 待回放 | mixed | waylib | refactor: remove unnecessary destructor and use project export macro |
| 4 | `31cea608` | 待回放 | pure | waylib | chore: fix clang-tidy findings in waylib |
| 5 | `d7651471` | 待回放 | mixed | waylib | feat: implement multi-seat support |
| 6 | `67d388ba` | 待回放 | pure | qwlroots | fix(qwlroots): fix crash on stale QQmlData pointer in qw_object::on_destroy |
| 7 | `f420ca99` | 待回放 | pure | waylib | fix: adapt to Qt 6.11 RasterGLSurface deprecation |
| 8 | `84905692` | 待回放 | pure | waylib | fix(textinputv2): don't kill client on missing WSurface in enable/disable |
| 9 | `cc81b07f` | 待回放 | pure | qwlroots | fix: qw_object::on_destroy() use deleteLater() instead of delete this |
| 10 | `5aa0ee60` | 待回放 | pure | waylib | fix: WSurfaceItemContent buffer lifecycle management |
| 11 | `c5fa8a27` | 待回放 | mixed | waylib | chore: refine decoration handling logic |
| 12 | `96689426` | 待回放 | pure | waylib | fix: prevent deadlock during Wayland client destruction |
| 13 | `64d4dcfd` | 待回放 | pure | waylib | fix: prevent crash during Wayland client destruction |
| 14 | `3dea85c9` | 待回放 | mixed | waylib | refactor: Make `interfaceName()` public in WServerInterface implementations |
| 15 | `91fd6ee0` | 待回放 | mixed | waylib | fix: fix multiple crashes caused by thread affinity and use-after-free issues |
| 16 | `d2038012` | 待回放 | mixed | waylib | fix(build): add missing headers for gcc 16 compatibility |
| 17 | `8bee60bc` | 待回放 | mixed | qwlroots+waylib | fix: fix build errors with GCC 16.1.1 and Qt 6.11.1 on Arch Linux |
| 18 | `f1daab4d` | 待回放 | pure | waylib | fix: avoid crash on invalid image capture buffer |
| 19 | `bf2d46f6` | 待回放 | pure | waylib | fix(woutputrenderwindow): destroy wlr layers before invalidating output on removal |
| 20 | `f60590fb` | 待回放 | pure | waylib | fix(render): fix texture copy crash when window partially off-screen |
| 21 | `674e6cfd` | 待回放 | pure | qwlroots+waylib | refactor: replace #define-private-public hacks with template accessor pattern |
| 22 | `e31a9db0` | 待回放 | pure | waylib | refactor(platformplugin): remove unused isMaster/proxy QPA mode |
| 23 | `a27de6af` | 待回放 | pure | waylib | fix: remove unused lambda capture in live test |
| 24 | `549d6a9c` | 待回放 | mixed | waylib | ci: add unit test step to archlinux build workflows |
| 25 | `f1de8e6c` | 待回放 | pure | waylib | fix(wsocket): fix WClient::get() returning null during client teardown |
| 26 | `88c558e6` | 待回放 | mixed | waylib | fix(output): fix crash on screen copy mode when hot-plugging |

---

## commits：保留路径与 drop files list

### 1. `86fc904c61158914a0db3dbf631043da9f90235f` — fix: qw_buffer metatype handling for Clang builds

- 原始提交时间：2026-03-04 18:14:43 +0800
- 保留路径：
  - `waylib/src/server/qtquick/wbufferitem.h`
- drop files list：
  - `src/main.cpp`
  - `src/modules/prelaunch-splash/prelaunchsplash.h`

### 2. `687959ca63c65e2cb5d7c2236423a75328f46f49` — fix: correct CMake config name for submodule build

- 原始提交时间：2026-03-05 13:12:05 +0800
- 保留路径：
  - `qwlroots/src/CMakeLists.txt`
- drop files list：
  - none

### 3. `ab189f528880fd1b8a52716ff2dce7902f23bb1c` — refactor: remove unnecessary destructor and use project export macro

- 原始提交时间：2026-03-06 16:52:58 +0800
- 保留路径：
  - `waylib/src/server/kernel/private/wglobal_p.h`
  - `waylib/src/server/kernel/private/wtoplevelsurface_p.h`
- drop files list：
  - `src/wallpaper/wallpapersurface.cpp`

### 4. `31cea6080d447d1f9d04a7f640ab63f157f689f3` — chore: fix clang-tidy findings in waylib

- 原始提交时间：2026-03-10 09:38:57 +0800
- 保留路径：
  - `waylib/src/server/kernel/wseat.cpp`
  - `waylib/src/server/qtquick/private/wrenderbuffernode.cpp`
  - `waylib/src/server/qtquick/woutputitem.cpp`
- drop files list：
  - none

### 5. `d7651471f542f9c23d108b2185056a67593a86f4` — feat: implement multi-seat support

- 原始提交时间：2026-03-23 13:53:50 +0800
- 保留路径：
  - `waylib/src/server/kernel/wcursor.cpp`
  - `waylib/src/server/kernel/winputdevice.cpp`
  - `waylib/src/server/kernel/winputdevice.h`
  - `waylib/src/server/kernel/wseat.cpp`
  - `waylib/src/server/kernel/wseat.h`
  - `waylib/src/server/protocols/winputmethodhelper.cpp`
- drop files list：
  - `src/CMakeLists.txt`
  - `src/common/treelandlogging.cpp`
  - `src/common/treelandlogging.h`
  - `src/core/rootsurfacecontainer.cpp`
  - `src/core/rootsurfacecontainer.h`
  - `src/input/inputdevice.cpp`
  - `src/seat/helper.cpp`
  - `src/seat/helper.h`
  - `src/seat/seatsmanager.cpp`
  - `src/seat/seatsmanager.h`
  - `src/surface/seatsurfacemanager.cpp`
  - `src/surface/seatsurfacemanager.h`

### 6. `67d388bafed2da1ad2dee2a0de3f7984ecf37cdb` — fix(qwlroots): fix crash on stale QQmlData pointer in qw_object::on_destroy

- 原始提交时间：2026-03-25 18:12:45 +0800
- 保留路径：
  - `qwlroots/src/CMakeLists.txt`
  - `qwlroots/src/qwobject.cpp`
  - `qwlroots/src/qwobject.h`
- drop files list：
  - none

### 7. `f420ca993369bf5df2b27b26e096f7ea9c35b009` — fix: adapt to Qt 6.11 RasterGLSurface deprecation

- 原始提交时间：2026-03-27 15:02:10 +0800
- 保留路径：
  - `waylib/src/server/platformplugin/qwlrootsintegration.cpp`
- drop files list：
  - none

### 8. `849056928426a42df38771911921db89691378fe` — fix(textinputv2): don't kill client on missing WSurface in enable/disable

- 原始提交时间：2026-03-30 09:46:43 +0800
- 保留路径：
  - `waylib/src/server/protocols/private/wtextinputv2.cpp`
- drop files list：
  - none

### 9. `cc81b07fba28a07d25c6f072635ca43768eaa43f` — fix: qw_object::on_destroy() use deleteLater() instead of delete this

- 原始提交时间：2026-04-02 17:31:11 +0800
- 保留路径：
  - `qwlroots/src/qwobject.h`
- drop files list：
  - none

### 10. `5aa0ee60143f5f5156c5dabccfb0f5a2e26e86ac` — fix: WSurfaceItemContent buffer lifecycle management

- 原始提交时间：2026-04-08 15:13:57 +0800
- 保留路径：
  - `waylib/src/server/qtquick/wsurfaceitem.cpp`
- drop files list：
  - none

### 11. `c5fa8a270dcb687c835b8011887351dea967a295` — chore: refine decoration handling logic

- 原始提交时间：2026-04-10 17:52:22 +0800
- 保留路径：
  - `waylib/src/server/protocols/wxdgdecorationmanager.cpp`
- drop files list：
  - `src/seat/helper.cpp`

### 12. `96689426c8e4f9fe14ce94c45f69fc4fd6410f36` — fix: prevent deadlock during Wayland client destruction

- 原始提交时间：2026-04-17 16:04:38 +0800
- 保留路径：
  - `waylib/src/server/kernel/private/wserver_p.h`
  - `waylib/src/server/kernel/wserver.cpp`
- drop files list：
  - none

### 13. `64d4dcfd2d977afd88bcf383d7aea190ace59852` — fix: prevent crash during Wayland client destruction

- 原始提交时间：2026-04-23 09:24:39 +0800
- 保留路径：
  - `waylib/src/server/kernel/wsocket.cpp`
  - `waylib/src/server/protocols/private/wtextinputv1.cpp`
  - `waylib/src/server/protocols/private/wtextinputv2.cpp`
- drop files list：
  - none

### 14. `3dea85c9afddbdf371fa40fcfa758e74530892ba` — refactor: Make `interfaceName()` public in WServerInterface implementations

- 原始提交时间：2026-04-24 11:12:47 +0800
- 保留路径：
  - `waylib/src/server/kernel/wbackend.h`
  - `waylib/src/server/kernel/wseat.h`
- drop files list：
  - `src/modules/app-id-resolver/appidresolver.h`
  - `src/modules/dde-shell/ddeshellmanagerinterfacev1.h`
  - `src/modules/prelaunch-splash/prelaunchsplash.h`
  - `src/modules/virtual-output/virtualoutputmanagerinterfacev1.h`
  - `src/modules/wallpaper-color/wallpapercolorinterfacev1.h`
  - `src/modules/wallpaper/wallpapermanagerinterfacev1.h`
  - `src/modules/wallpaper/wallpapernotifierinterfacev1.h`
  - `src/modules/wallpaper/wallpapershellinterfacev1.h`
  - `src/modules/window-management/windowmanagementinterfacev1.h`

### 15. `91fd6ee0bc4c2289471d30a238b261a997c37767` — fix: fix multiple crashes caused by thread affinity and use-after-free issues

- 原始提交时间：2026-05-09 18:03:08 +0800
- 保留路径：
  - `waylib/src/server/kernel/wsocket.cpp`
  - `waylib/src/server/kernel/wsocket.h`
  - `waylib/src/server/qtquick/wtextureproviderprovider.cpp`
  - `waylib/src/server/utils/wextimagecapturesourcev1impl.cpp`
- drop files list：
  - `src/modules/capture/capture.cpp`
  - `src/surface/surfacewrapper.cpp`

### 16. `d2038012c18ea85e9d75183649d3a3ceeabbef0a` — fix(build): add missing headers for gcc 16 compatibility

- 原始提交时间：2026-05-09 22:45:09 +0800
- 保留路径：
  - `waylib/examples/tinywl/helper.cpp`
  - `waylib/src/server/kernel/wserver.cpp`
  - `waylib/src/server/kernel/wsocket.cpp`
  - `waylib/src/server/protocols/wxwaylandsurface.cpp`
- drop files list：
  - `src/seat/helper.cpp`
  - `src/xwayland.cpp`

### 17. `8bee60bca06699ee0da40f7ebafb8054451400b2` — fix: fix build errors with GCC 16.1.1 and Qt 6.11.1 on Arch Linux

- 原始提交时间：2026-05-18 17:24:37 +0800
- 保留路径：
  - `qwlroots/CMakePresets.json`
  - `qwlroots/src/qwglobal.h`
  - `qwlroots/src/util/qwsignalconnector.h`
  - `waylib/CMakePresets.json`
  - `waylib/src/server/kernel/wsocket.cpp`
- drop files list：
  - `.github/workflows/qwlroots-archlinux-build.yml`
  - `.github/workflows/treeland-archlinux-build.yml`
  - `.github/workflows/waylib-archlinux-build.yml`
  - `CMakePresets.json`

### 18. `f1daab4d0fc30b2aec0c06a080010df704238f62` — fix: avoid crash on invalid image capture buffer

- 原始提交时间：2026-05-20 14:49:44 +0800
- 保留路径：
  - `waylib/src/server/utils/wextimagecapturesourcev1impl.cpp`
- drop files list：
  - none

### 19. `bf2d46f6b0c0ee98167ef999b02d7834dee336d1` — fix(woutputrenderwindow): destroy wlr layers before invalidating output on removal

- 原始提交时间：2026-05-20 14:59:18 +0800
- 保留路径：
  - `waylib/src/server/qtquick/woutputrenderwindow.cpp`
- drop files list：
  - none

### 20. `f60590fb1fbea78b8f03f0b2fa54e953745d3b6b` — fix(render): fix texture copy crash when window partially off-screen

- 原始提交时间：2026-05-20 15:26:40 +0800
- 保留路径：
  - `waylib/src/server/qtquick/private/wrenderbuffernode.cpp`
- drop files list：
  - none

### 21. `674e6cfde9925fa2f6b4cb0e49625bee05b8d941` — refactor: replace #define-private-public hacks with template accessor pattern

- 原始提交时间：2026-05-20 18:14:27 +0800
- 保留路径：
  - `qwlroots/src/util/qwsignalconnector.h`
  - `waylib/src/server/CMakeLists.txt`
  - `waylib/src/server/kernel/private/wprivateaccessor_p.h`
  - `waylib/src/server/kernel/wcursor.cpp`
  - `waylib/src/server/kernel/wserver.cpp`
  - `waylib/src/server/platformplugin/qwlrootsintegration.cpp`
  - `waylib/src/server/platformplugin/qwlrootsintegration.h`
  - `waylib/src/server/qtquick/private/wbufferrenderer.cpp`
  - `waylib/src/server/qtquick/private/wbufferrenderer_p.h`
  - `waylib/src/server/qtquick/private/wqmlhelper.cpp`
  - `waylib/src/server/qtquick/private/wqmlhelper_p.h`
  - `waylib/src/server/qtquick/private/wrenderbuffernode.cpp`
  - `waylib/src/server/qtquick/woutputrenderwindow.cpp`
  - `waylib/src/server/qtquick/wqmlcreator.cpp`
  - `waylib/tests/unit_tests/CMakeLists.txt`
  - `waylib/tests/unit_tests/test_qsgrenderer_accessor/CMakeLists.txt`
  - `waylib/tests/unit_tests/test_qsgrenderer_accessor/main.cpp`
  - `waylib/tests/unit_tests/test_qsgrenderer_accessor/qsgrenderer_direct.cpp`
- drop files list：
  - none

### 22. `e31a9db03d2eebcfa8c1b6e3bb49e026b8cc561d` — refactor(platformplugin): remove unused isMaster/proxy QPA mode

- 原始提交时间：2026-05-20 18:14:27 +0800
- 保留路径：
  - `waylib/src/server/kernel/wserver.cpp`
  - `waylib/src/server/kernel/wserver.h`
  - `waylib/src/server/platformplugin/qwlrootsintegration.cpp`
  - `waylib/src/server/platformplugin/qwlrootsintegration.h`
- drop files list：
  - none

### 23. `a27de6af6930ddce2e23faf55830107675d635cc` — fix: remove unused lambda capture in live test

- 原始提交时间：2026-05-20 18:14:27 +0800
- 保留路径：
  - `waylib/tests/manual/live/main.cpp`
- drop files list：
  - none

### 24. `549d6a9ce5b30bc45f984a4680cd42be79a72cff` — ci: add unit test step to archlinux build workflows

- 原始提交时间：2026-05-21 13:30:24 +0800
- 保留路径：
  - `waylib/CMakePresets.json`
- drop files list：
  - `.github/workflows/treeland-archlinux-build.yml`
  - `.github/workflows/waylib-archlinux-build.yml`
  - `CMakePresets.json`

### 25. `f1de8e6c9ac56835b820648500affaea7db26682` — fix(wsocket): fix WClient::get() returning null during client teardown

- 原始提交时间：2026-05-21 13:30:58 +0800
- 保留路径：
  - `waylib/src/server/kernel/wsocket.cpp`
- drop files list：
  - none

### 26. `88c558e65c60b14847d939dd2fab3331308e05c1` — fix(output): fix crash on screen copy mode when hot-plugging

- 原始提交时间：2026-05-21 18:55:14 +0800
- 保留路径：
  - `waylib/src/server/qtquick/private/woutputitem_p.h`
  - `waylib/src/server/qtquick/woutputitem.cpp`
- drop files list：
  - `src/core/layersurfacecontainer.cpp`
  - `src/output/output.cpp`
  - `src/seat/helper.cpp`


---

## 结果检查（@waylib-shared/）

执行完成后必须复核：

- `waylibshared-merge..HEAD` 的最终业务变更仅包含 `waylib/` 与 `qwlroots/`。
- 每个同步提交都能通过 `Treeland-Commit` 回溯到上游提交。
- 对 `mixed` 提交，drop files list 与原始提交的非目标路径一致。
- 基础 CMake 配置、构建和可用 CTest 通过。
