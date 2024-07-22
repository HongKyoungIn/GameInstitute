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
    // ���� ������Ʈ�� ���̾� ������� ����
    std::sort(mGameObjects.begin(), mGameObjects.end(), [](GameObject* a, GameObject* b) {
        return a->GetLayer() < b->GetLayer();
        });

    // ī�޶��� ���� ��ȯ ����� ����
    D2D1_MATRIX_3X2_F cameraWorldTransform = mCamera->GetWorldTransform();

    // ȭ�� �߾��� �������� ī�޶� ��ȯ ����� ����
    cameraWorldTransform._31 -= 1920.f / 2;
    cameraWorldTransform._32 -= 1080.f / 2;

    // ī�޶��� ����� ���
    D2D1InvertMatrix(&cameraWorldTransform);
    D2D1_MATRIX_3X2_F cameraInverseTransform = cameraWorldTransform;

    int renderingObject = 0;

    // �� ���� ������Ʈ�� ���� ������
    for (GameObject* gameObject : mGameObjects) {
        
        // ī�޶��� �ø� ������ �����ϴ� ���� ������Ʈ�� ������
        if (mCamera->GetCullingBounds().Intersects(gameObject->GetAABB())) {
            renderingObject++;
            // ���� ������Ʈ�� ���� ��ȯ ����� ����
            Transform* transform = gameObject->GetTransform();
            D2D1_MATRIX_3X2_F worldTransform = transform->GetWorldTransform();

            // ���� Ÿ�ٿ� ī�޶��� ������� ���� ��ȯ ����� ����
            D2D1_MATRIX_3X2_F finalTransform = worldTransform * cameraInverseTransform;
            pRenderTarget->SetTransform(finalTransform);

            // ���� ������Ʈ�� ������
            gameObject->Render(pRenderTarget);
        }
    }

    cout << "Rendering Object Count : " << renderingObject - 1<< endl;
    // ��ȯ ����� �ʱ�ȭ
    pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Scene::AddGameObject(GameObject* gameObject) {
    mGameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(GameObject* _gameObject) {
    if (!_gameObject) return;

    // �ڽ� ������Ʈ�� �ִٸ� ���� ����
    const std::vector<GameObject*>& children = _gameObject->GetChildren();
    for (size_t i = 0; i < children.size(); ++i) {
        RemoveGameObject(children[i]);  // ��������� �ڽ� ������Ʈ ����
    }

    // ���Ϳ��� ���� ������Ʈ�� ����
    for (size_t i = 0; i < mGameObjects.size(); ++i) {
        if (mGameObjects[i] == _gameObject) {
            mGameObjects.erase(mGameObjects.begin() + i);
            delete _gameObject;  // ���� ������Ʈ �޸� ����
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