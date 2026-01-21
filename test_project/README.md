# WaylibShared 最小消费者示例

本目录是一个“上层程序最小消费者（consumer）”示例，用于验证：

- `find_package(WaylibShared REQUIRED COMPONENTS SharedServer)` 可用
- 仅链接 `WaylibShared::SharedServer` 即可完成编译与链接（Qt 依赖由库目标 `PUBLIC` 导出）
- QML 能 `import WaylibShared.QuickSharedServer` 并创建模块内类型（通过 `waylibshared_qml_consumer` 验证）

## 构建

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH=<WaylibShared安装前缀>
cmake --build build
```

例如（开发机使用 `/tmp/ws`）：

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH=/tmp/ws
cmake --build build
```

## 运行测试（可选）

```bash
ctest --test-dir build
```
