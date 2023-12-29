#include "LobbyScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "LevelSelectScene.h"
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

    rootLayerNode = (Layer*)CSLoader::createNode("Lobby.csb");
    this->addChild(rootLayerNode);

    Button* pMainBtn = (Button*)rootLayerNode->getChildByName("main_btn");
    if(pMainBtn)
        pMainBtn->addClickEventListener(CC_CALLBACK_1(LobbyScene::menuMainCallback, this));

    Button* pCloseBtn = (Button*)rootLayerNode->getChildByName("CloseBtn");
    if(pCloseBtn)
        pCloseBtn->addClickEventListener(CC_CALLBACK_1(LobbyScene::menuCloseCallback, this));

    Button* pPopupBtn = (Button*)rootLayerNode->getChildByName("PopupBtn");
    if (pPopupBtn)
        pPopupBtn->addClickEventListener(CC_CALLBACK_1(LobbyScene::menuPopupCallback, this));

    //
    //timeline::ActionTimeline* _sampleAnimation;
    //_sampleAnimation = cocos2d::CSLoader::createTimeline("MainScene.csb");

    //_sampleAnimation->gotoFrameAndPlay(0, true);
    //rootNode->runAction(_sampleAnimation);

    return true;
}

void LobbyScene::menuPopupCallback(Ref* pSender)
{
    if (!PopupNode)
    {
        PopupNode = CSLoader::createNode("Popup.csb");
        this->addChild(PopupNode);
    }
    else
    {
        PopupNode->setVisible(true);
    }

    Button* pPopupCloseBtn = (Button*)PopupNode->getChildByName("ShopCloseBtn");
    if (pPopupCloseBtn)
        pPopupCloseBtn->addClickEventListener(CC_CALLBACK_1(LobbyScene::menuShopCloseCallback, this));

}

void LobbyScene::menuShopCloseCallback(Ref* pSender)
{
    //this->removeChild(PopupNode);
    if (PopupNode)
    {
        PopupNode->setVisible(false);
    }
}

void LobbyScene::menuMainCallback(Ref* pSender)
{
    auto director = Director::getInstance();

    auto scene = LevelSelectScene::createScene();
    //director->replaceScene(TransitionCrossFade::create(2, scene));
    director->replaceScene(TransitionFade::create(2, scene, Color3B(255, 0, 0)));
}


void LobbyScene::menuCloseCallback(Ref* pSender)
{   
    auto director = Director::getInstance();
    
    auto scene = IntroScene::createScene();
    //director->replaceScene(TransitionCrossFade::create(2, scene));
    director->replaceScene(TransitionFade::create(2, scene, Color3B(255, 0, 0)));

}
