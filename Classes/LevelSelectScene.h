#ifndef __LEVELSELECT_SCENE_H__
#define __LEVELSELECT_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ui/UITextAtlas.h"

class LevelSelectScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void LevelBtnInit(cocos2d::ui::Button* pButton, std::string strNum);
    
    void menuBackCallback(cocos2d::Ref* pSender);    
    
    CREATE_FUNC(LevelSelectScene);

private:
    /*Scene* rootNode;*/
    Node* rootLayerNode;

};

#endif  
