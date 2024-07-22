#include "Scene.h"
#include <algorithm>
#include <iostream>

Scene::Scene() : mMainCameraObject(nullptr), mCamera(nullptr) {
    mMainCameraObject = new GameObject("MainCamera");
    mCamera = mMainCameraObject->AddComponent<Camera>();
    AddGameObject(mMainCameraObject);
}

Scene::~Scene() {
    for (GameObject* gameObject : mGameObjects) {
        std::cout << "Releasing GameObject: " << gameObject->GetName() << std::endl;
        delete gameObject;
    }
    mGameObjects.clear();
}

void Scene::Update() {
    for (GameObject* gameObject : mGameObjects) {
        gameObject->Update();
    }

    if (mMainCameraObject) {
        Transform* cameraTransform = mMainCameraObject->GetTransform();
        mCamera->SetPosition(mCamera->GetWorldTransform()._31, mCamera->GetWorldTransform()._32);
    }
}

void Scene::Render(ID2D1HwndRenderTarget* pRenderTarget) {
    std::cout << "Camera ViewBoundBox Center: (" << mCamera->GetCullingBounds().GetCenter().x << ", " << mCamera->GetCullingBounds().GetCenter().y << ")" << std::endl;
    // 게임 오브젝트를 레이어 순서대로 정렬
    std::sort(mGameObjects.begin(), mGameObjects.end(), [](GameObject* a, GameObject* b) {
        return a->GetLayer() < b->GetLayer();
        });

    // 카메라의 월드 변환 행렬을 얻음
    D2D1_MATRIX_3X2_F cameraWorldTransform = mCamera->GetWorldTransform();

    // 화면 중앙을 기준으로 카메라 변환 행렬을 조정
    cameraWorldTransform._31 -= 1920.f / 2;
    cameraWorldTransform._32 -= 1080.f / 2;

    // 카메라의 역행렬 계산
    D2D1InvertMatrix(&cameraWorldTransform);
    D2D1_MATRIX_3X2_F cameraInverseTransform = cameraWorldTransform;

    int renderingObject = 0;

    // 각 게임 오브젝트에 대해 렌더링
    for (GameObject* gameObject : mGameObjects) {
        
        // 카메라의 컬링 범위와 교차하는 게임 오브젝트만 렌더링
        if (mCamera->GetCullingBounds().Intersects(gameObject->GetAABB())) {
            renderingObject++;
            // 게임 오브젝트의 월드 변환 행렬을 얻음
            Transform* transform = gameObject->GetTransform();
            D2D1_MATRIX_3X2_F worldTransform = transform->GetWorldTransform();

            // 렌더 타겟에 카메라의 역행렬을 곱한 변환 행렬을 설정
            D2D1_MATRIX_3X2_F finalTransform = worldTransform * cameraInverseTransform;
            pRenderTarget->SetTransform(finalTransform);

            // 게임 오브젝트를 렌더링
            gameObject->Render(pRenderTarget);
        }
    }

    cout << "Rendering Object Count : " << renderingObject - 1<< endl;
    // 변환 행렬을 초기화
    pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Scene::AddGameObject(GameObject* gameObject) {
    mGameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(GameObject* _gameObject) {
    if (!_gameObject) return;

    // 자식 오브젝트가 있다면 먼저 삭제
    const std::vector<GameObject*>& children = _gameObject->GetChildren();
    for (size_t i = 0; i < children.size(); ++i) {
        RemoveGameObject(children[i]);  // 재귀적으로 자식 오브젝트 삭제
    }

    // 벡터에서 게임 오브젝트를 삭제
    for (size_t i = 0; i < mGameObjects.size(); ++i) {
        if (mGameObjects[i] == _gameObject) {
            mGameObjects.erase(mGameObjects.begin() + i);
            delete _gameObject;  // 게임 오브젝트 메모리 해제
            return;
        }
    }
}

void Scene::RemoveSpecificGameObject(const std::string& name) {
    auto it = std::remove_if(mGameObjects.begin(), mGameObjects.end(),
        [&name](GameObject* gameObject) {
            if (gameObject->GetName() == name) {
                delete gameObject;
                return true;
            }
            return false;
        });
    mGameObjects.erase(it, mGameObjects.end());
}