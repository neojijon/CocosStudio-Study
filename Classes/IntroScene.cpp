#include "IntroScene.h"
#include "LobbyScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;


Scene* IntroScene::createScene()
{
    return IntroScene::create();
}


bool IntroScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }


    rootNode = (Scene*) CSLoader::createNode("MainScene.csb");
    this->addChild(rootNode);


    Button* pBtn = (Button*)rootNode->getChildByName("StartBtn");
    pBtn->addClickEventListener(CC_CALLBACK_1(IntroScene::menuCloseCallback, this));

    
    timeline::ActionTimeline* _sampleAnimation;
    _sampleAnimation = cocos2d::CSLoader::createTimeline("MainScene.csb");

    _sampleAnimation->gotoFrameAndPlay(0, true);
    rootNode->runAction(_sampleAnimation);


    return true;
}


void IntroScene::menuCloseCallback(Ref* pSender)
{    
    auto director = Director::getInstance();
    //director->popScene();

    auto scene = LobbyScene::createScene();    
    director->replaceScene(TransitionCrossFade::create(2,scene));
    //director->replaceScene(TransitionFade::create(2, scene, Color3B(255, 0, 0)));
}

void IntroScene::onExit()
{    
    Node::onExit();
}

