#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__

#include "cocos2d.h"

class IntroScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    //void menuBackCallback(cocos2d::Ref* pSender);

    virtual void onExit() override;
    
    CREATE_FUNC(IntroScene);

private:
    Scene* rootNode;
    Node* rootLayerNode;

};

#endif  
