#include "DemoApp.h"
#include "../Engine/D2DRenderer.h"

void DemoApp::Update()
{

}

void DemoApp::Render()
{
	d2dRenderer->GetRendererTarget()->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));
}
