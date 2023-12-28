#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;


Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}


bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    rootNode = (Scene*) CSLoader::createNode("MainScene.csb");
    this->addChild(rootNode);


    Button* pBtn = (Button*)rootNode->getChildByName("StartBtn");
    pBtn->addClickEventListener(CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    
    timeline::ActionTimeline* _sampleAnimation;
    _sampleAnimation = cocos2d::CSLoader::createTimeline("MainScene.csb");


    _sampleAnimation->gotoFrameAndPlay(0, true);
    rootNode->runAction(_sampleAnimation);


    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //this->removeChild((Node*)rootNode);   
    rootNode->setVisible(false);

    if (!rootLayerNode)
    {
        rootLayerNode = CSLoader::createNode("Layer.csb");
        this->addChild(rootLayerNode);
    }
    else
    {
        rootLayerNode->setVisible(true);
    }   
    
        
    Button* pBtn = (Button*)rootLayerNode->getChildByName("Button_2");
    pBtn->addClickEventListener(CC_CALLBACK_1(HelloWorld::menuBackCallback, this));

}


void HelloWorld::menuBackCallback(Ref* pSender)
{
    //this->removeChild(rootLayerNode);
    rootLayerNode->setVisible(false);

    if (!rootNode)
    {
        rootNode = (Scene*)CSLoader::createNode("MainScene.csb");
        this->addChild(rootNode);
    }
    else
    {
        rootNode->setVisible(true);
    }    

    Button* pBtn = (Button*)rootNode->getChildByName("StartBtn");
    pBtn->addClickEventListener(CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    timeline::ActionTimeline* _sampleAnimation;
    _sampleAnimation = cocos2d::CSLoader::createTimeline("MainScene.csb");


    _sampleAnimation->gotoFrameAndPlay(0, true);
    rootNode->runAction(_sampleAnimation);
}
