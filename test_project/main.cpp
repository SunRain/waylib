#include <wserver.h>

WAYLIB_SERVER_USE_NAMESPACE

int main()
{
    // 仅用于验证“真实链接到 WaylibShared::SharedServer”（避免运行时依赖 Wayland 环境）
    (void)&WServer::staticMetaObject;
    return 0;
}
