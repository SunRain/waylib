# waylib-shared

`waylib-shared/` 是一个 **lib-only** 聚合构建仓，默认仅构建并安装：

- `waylib/`（Wayland 合成器开发库）
- `qwlroots/`（wlroots 的 Qt 封装）

该仓导出标准 CMake 包（`WaylibShared`、`WaylibSharedQWlroots`），并提供 `test_project/` 作为 in-tree 最小消费者，用于验证 `find_package()` / 链接导出 / QML import。

## 依赖

构建期依赖（非穷举）：

- Qt6（>= 6.8）
- wlroots 0.19（pkg-config：`wlroots-0.19`）
- wayland / wayland-protocols / wlr-protocols
- pixman / xkbcommon / xcb / egl
- CMake + Ninja + pkg-config

## 构建

使用仓内子模块（默认）：

```sh
git clone --recursive <repo>
cmake -S waylib-shared -B build -GNinja -DWITH_SUBMODULE_WAYLIB=ON
cmake --build build
```

安装到某个前缀：

```sh
cmake --install build --prefix /tmp/waylib-shared-prefix
```

### 可选开启 tests/examples（默认 OFF）

这些选项由子项目定义，可从顶层配置透传：

```sh
cmake -S waylib-shared -B build-dev -GNinja -DWITH_SUBMODULE_WAYLIB=ON \
  -DBUILD_WAYLIB_TESTS=ON -DBUILD_WAYLIB_EXAMPLES=ON \
  -DBUILD_QWLROOTS_TESTS=ON -DBUILD_QWLROOTS_EXAMPLES=ON
cmake --build build-dev
ctest --test-dir build-dev --output-on-failure
```

## 消费者验收（test_project）

基于安装前缀构建并运行 in-tree consumer：

```sh
cmake -S waylib-shared/test_project -B build-tp -GNinja -DCMAKE_PREFIX_PATH=/tmp/waylib-shared-prefix
cmake --build build-tp
ctest --test-dir build-tp --output-on-failure
```

## 许可协议

Apache-2.0 OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only。详情见 `LICENSES/`。
