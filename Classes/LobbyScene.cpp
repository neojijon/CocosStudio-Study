#include "LobbyScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "IntroScene.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;


Scene* LobbyScene::createScene()
{
    return LobbyScene::create();
}


bool LobbyScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    rootLayerNode = (Layer*)CSLoader::createNode("Layer.csb");
    this->addChild(rootLayerNode);

    Button* pBtn = (Button*)rootLayerNode->getChildByName("CloseBtn");
    pBtn->addClickEventListener(CC_CALLBACK_1(LobbyScene::menuCloseCallback, this));

    //
    //timeline::ActionTimeline* _sampleAnimation;
    //_sampleAnimation = cocos2d::CSLoader::createTimeline("MainScene.csb");

    //_sampleAnimation->gotoFrameAndPlay(0, true);
    //rootNode->runAction(_sampleAnimation);

    return true;
}


void LobbyScene::menuCloseCallback(Ref* pSender)
{   
    auto director = Director::getInstance();
    
    auto scene = IntroScene::createScene();
    //director->replaceScene(TransitionCrossFade::create(2, scene));
    director->replaceScene(TransitionFade::create(2, scene, Color3B(255, 0, 0)));


    ////this->removeChild(rootLayerNode);

    //rootLayerNode->setVisible(false);
    ////rootNode = (Scene*)CSLoader::createNode("MainScene.csb");
    ////this->addChild(rootNode);

    //if (rootNode)
    //{
    //    rootNode->setVisible(true);
    //}
    //else
    //{
    //    rootNode = (Scene*)CSLoader::createNode("MainScene.csb");
    //    this->addChild(rootNode);
    //}
    //

    //Button* pBtn = (Button*)rootNode->getChildByName("StartBtn");
    //pBtn->addClickEventListener(CC_CALLBACK_1(LobbyScene::menuCloseCallback, this));

    //timeline::ActionTimeline* _sampleAnimation;
    //_sampleAnimation = cocos2d::CSLoader::createTimeline("MainScene.csb");


    //_sampleAnimation->gotoFrameAndPlay(0, true);
    //rootNode->runAction(_sampleAnimation);
}
