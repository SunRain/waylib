# waylib-shared

`waylib-shared/` is a lib-only aggregation repo that builds and installs:

- `waylib/` (Wayland compositor development library)
- `qwlroots/` (Qt wrapper for wlroots)

It exports standard CMake packages (`WaylibShared`, `WaylibSharedQWlroots`) and provides an in-tree minimal consumer under `test_project/` to validate `find_package()` / link / QML import.

## Dependencies

Build-time requirements (non-exhaustive):

- Qt6 (>= 6.8)
- wlroots 0.19 (pkg-config: `wlroots-0.19`)
- wayland / wayland-protocols / wlr-protocols
- pixman / xkbcommon / xcb / egl
- CMake + Ninja + pkg-config

## Build

Use the bundled submodules (default):

```sh
git clone --recursive <repo>
cmake -S waylib-shared -B build -GNinja -DWITH_SUBMODULE_WAYLIB=ON
cmake --build build
```

Install to a prefix:

```sh
cmake --install build --prefix /tmp/waylib-shared-prefix
```

### Opt-in tests/examples (default OFF)

These options are defined by the subprojects and can be passed from the top-level configure:

```sh
cmake -S waylib-shared -B build-dev -GNinja -DWITH_SUBMODULE_WAYLIB=ON \
  -DBUILD_WAYLIB_TESTS=ON -DBUILD_WAYLIB_EXAMPLES=ON \
  -DBUILD_QWLROOTS_TESTS=ON -DBUILD_QWLROOTS_EXAMPLES=ON
cmake --build build-dev
ctest --test-dir build-dev --output-on-failure
```

## Consumer verification (test_project)

Build and run the in-tree consumer against the installed prefix:

```sh
cmake -S waylib-shared/test_project -B build-tp -GNinja -DCMAKE_PREFIX_PATH=/tmp/waylib-shared-prefix
cmake --build build-tp
ctest --test-dir build-tp --output-on-failure
```

## License

Apache-2.0 OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only. See `LICENSES/` for details.
