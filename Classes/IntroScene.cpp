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

    m_pSprite = Sprite::create();

    addChild(m_pSprite,9999);

    Size size = Director::getInstance()->getVisibleSize();

    m_x = size.width / 2.0f;
    m_pSprite->setPosition(Vec2(m_x, size.height/2));

    Vector<SpriteFrame*> animFrames;

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("loadingsp.plist");

    for (int i = 0; i < 24; i++)
    {
        char sbName[100] = { 0, };
        sprintf(sbName, "loading/Loading_%02d.png", i);
        //SpriteFrame* spFrame = SpriteFrame::create(sbName, Rect(0, 0, 100, 101));

        SpriteFrame* spFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(sbName);

        animFrames.pushBack(spFrame);
    }

    Animation* amin = Animation::createWithSpriteFrames(animFrames, 0.2f, 1);
    Animate* animate = Animate::create(amin);

    m_pSprite->runAction(RepeatForever::create(animate));

 /*  
    auto rotation = RotateBy::create(1.5f, 90);
    auto movement = MoveTo::create(10, Vec2(960, 620));
    auto resetPosition = MoveTo::create(0, Vec2(size.width / 2, size.height / 2));
    
    auto sequence = Sequence::create(rotation,movement, resetPosition, NULL);
    m_pSprite->runAction(RepeatForever::create(sequence));*/


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


void IntroScene::onEnter()
{
    Scene::onEnter();

    _listener = EventListenerKeyboard::create();

    _listener->onKeyPressed = CC_CALLBACK_2(IntroScene::onKeyPressed, this);
    _listener->onKeyReleased = CC_CALLBACK_2(IntroScene::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
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
    _eventDispatcher->removeEventListener(_listener);

    Scene::onExit();
}



void IntroScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        {
            Size size = Director::getInstance()->getVisibleSize();
            m_x -= 10;
             
            m_pSprite->setPosition(Vec2(m_x, size.height / 2));
            m_pSprite->setFlippedX(true);
            break;
        }
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        {
            Size size = Director::getInstance()->getVisibleSize();
            m_x += 10;

            m_pSprite->setPosition(Vec2(m_x, size.height / 2));
            m_pSprite->setFlippedX(false);
            break;
        }
        default:
            break;
    }
    
}

void IntroScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    {
        //Ethan->stopAllActions();
        break;
    }
    default:
        break;
    }    
}


