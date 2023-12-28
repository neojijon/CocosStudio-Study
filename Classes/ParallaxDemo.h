#ifndef __LEVELSELECT_SCENE_H__
#define __LEVELSELECT_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Renderer/CCTextureAtlas.h"

class ParallaxDemo : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    
    CREATE_FUNC(ParallaxDemo);

protected:
    cocos2d::TextureAtlas* _atlas;

    cocos2d::Node* _root;
    cocos2d::Node* _target;
    cocos2d::MotionStreak* _streak;

};

#endif  
