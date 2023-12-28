#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__

#include "cocos2d.h"

class LobbyScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuMainCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(LobbyScene);

private:
    /*Scene* rootNode;*/
    Node* rootLayerNode;

};

#endif  
