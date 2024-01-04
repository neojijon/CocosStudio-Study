#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__

#include "cocos2d.h"

class IntroScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    virtual void onEnter();
    virtual void onExit();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    //void menuBackCallback(cocos2d::Ref* pSender);


    cocos2d::EventListenerKeyboard* _listener;
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    float m_x;
    
    CREATE_FUNC(IntroScene);

private:
    Scene* rootNode;
    Node* rootLayerNode;

    cocos2d::Sprite* m_pSprite;

};

#endif  
