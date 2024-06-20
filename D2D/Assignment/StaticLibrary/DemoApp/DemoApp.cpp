#include "DemoApp.h"

DemoApp::DemoApp() { }

DemoApp::~DemoApp() { }

void DemoApp::Update() {
    // Update game logic here
}

void DemoApp::Render() {
    m_renderer.BeginDraw();
    m_renderer.Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
    m_renderer.EndDraw();
}
