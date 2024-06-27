#pragma once

#include "resource.h"
#include "../Engine/GameApp.h"

class DemoApp : public GameApp {

public:
	void Update() override;  // 오버라이드 추가
	void Render() override;  // 오버라이드 추가
};
