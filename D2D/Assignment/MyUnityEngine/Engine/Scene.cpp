#include "Scene.h"
#include "sstream"

Scene::Scene() { }

Scene::~Scene() {
    // std::cout << "Releasing Scene: " << mName << std::endl;
    for(GameObject* gameObject : mGameObjects) {
        std::cout << "Releasing GameObject: " << gameObject->GetName() << std::endl;
        delete gameObject;
    }
    mGameObjects.clear();
}

void Scene::Update() {
    for(GameObject* gameObject : mGameObjects) {
        gameObject->Update();
    }
}

void Scene::Render(ID2D1HwndRenderTarget* pRenderTarget) {
    std::sort(mGameObjects.begin(), mGameObjects.end(), [](GameObject* a, GameObject* b) {
        return a->GetLayer() < b->GetLayer();
        });

    for(GameObject* gameObject : mGameObjects) {
        gameObject->Render(pRenderTarget);
    }
}

void Scene::AddGameObject(GameObject* gameObject) {
    mGameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(GameObject* _gameObject) {
    if(!_gameObject) return;

    // 자식 오브젝트가 있다면 먼저 삭제
    const std::vector<GameObject*>& children = _gameObject->GetChildren();
    for(size_t i = 0; i < children.size(); ++i) {
        RemoveGameObject(children[i]);  // 재귀적으로 자식 오브젝트 삭제
    }

    // 벡터에서 게임 오브젝트를 삭제
    for(size_t i = 0; i < mGameObjects.size(); ++i) {
        if(mGameObjects[i] == _gameObject) {
            mGameObjects.erase(mGameObjects.begin() + i);
            delete _gameObject;  // 게임 오브젝트 메모리 해제
            return;
        }
    }
}

void Scene::RemoveSpecificGameObject(const std::string& name) {
    auto it = std::remove_if(mGameObjects.begin(), mGameObjects.end(),
        [&name](GameObject* gameObject) {
            if(gameObject->GetName() == name) {
                delete gameObject;
                return true;
            }
            return false;
        });
    mGameObjects.erase(it, mGameObjects.end());

    /*for(auto it = mGameObjects.rbegin(); it != mGameObjects.rend(); ++it) {
        if((*it)->GetName() == name) {
            RemoveGameObject(*it);
            break;
        }
    }*/
}
