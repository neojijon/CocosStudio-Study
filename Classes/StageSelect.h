#ifndef  _STAGESELECT_SCENE_H_
#define  _STAGESELECT_SCENE_H_

#include "kconst.h"
#include "Player.h"
using namespace cocos2d;

class StageSelect : public Scene {
public:
    static Scene* createScene();
    virtual bool init();

    void loadTitle();
    void loadStartButton();
        
    void selectStage(Ref* sender);

    virtual void OnEnter();
    virtual void update(float delta);
    virtual void OnExit();

    cocos2d::EventListenerKeyboard* _listener;
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    float m_x;
    Player* m_pPlayer;

private:
    

public:
    CREATE_FUNC(StageSelect);
};
#endif
