#include "DemoApp.h"
#include "../Engine/D2DRenderer.h"

void DemoApp::Update() {
    // 업데이트 로직을 추가할 수 있습니다.
}

void DemoApp::Render() {
    mD2DRenderer->GetRenderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));

    // 추가 렌더링 작업을 여기에 추가할 수 있습니다.
}
