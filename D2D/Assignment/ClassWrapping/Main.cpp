#include "DemoApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    DemoApp app;
    if(!app.Initialize(hInstance, nCmdShow)) {
        return FALSE;
    }

    app.Run();
    app.Uninitialize();

    return 0;
}
