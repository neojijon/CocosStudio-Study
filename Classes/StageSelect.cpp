#include "StageSelect.h"
#include "Player.h"

Scene* StageSelect::createScene() {
    return StageSelect::create();
}

bool StageSelect::init() {
    if (!Scene::init()) {
        return false;
    }

    loadTitle();
    loadStartButton();

    m_pPlayer = Player::create();
    m_pPlayer->init();

    m_pPlayer->setPosition(0, 0);
    this->addChild(m_pPlayer);


    _listener = EventListenerKeyboard::create();

    _listener->onKeyPressed = CC_CALLBACK_2(StageSelect::onKeyPressed, this);
    _listener->onKeyReleased = CC_CALLBACK_2(StageSelect::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);

    return true;
}

void StageSelect::loadTitle() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto title = Label::createWithTTF("StageSelect", ResourceManager::getInstance()->getFontPath("mainFont"), 64);
    title->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.8));
    title->setScale(0.5f);
    this->addChild(title);
}

void StageSelect::loadStartButton() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto startButton = MenuItemImage::create(ResourceManager::getInstance()->getImagePath("BlueButonOK"), ResourceManager::getInstance()->getImagePath("Button1"), CC_CALLBACK_1(StageSelect::selectStage, this));
    startButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.2));
    startButton->setScale(0.5f);
    auto menu = Menu::create(startButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
}

void StageSelect::selectStage(Ref* sender) {
   // SceneManager::getInstance()->replaceScene(SceneType::StageSelect);
}


void StageSelect::OnEnter()
{
    Scene::onEnter();



}

void StageSelect::update(float delta)
{
    Scene::update(delta);
}

void StageSelect::OnExit()
{
    _eventDispatcher->removeEventListener(_listener);

    Scene::onExit();
}



void StageSelect::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        {
            Size size = Director::getInstance()->getVisibleSize();
            m_x -= 10;

            m_pPlayer->setPosition(Vec2(m_x, size.height / 2));
            m_pPlayer->move(Vec2(-1, 0));
            m_pPlayer->setFlippedX(true);
            break;
        }
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        {
            Size size = Director::getInstance()->getVisibleSize();
            m_x += 10;

            m_pPlayer->setPosition(Vec2(m_x, size.height / 2));
            m_pPlayer->move(Vec2(1, 0));

            m_pPlayer->setFlippedX(false);
            break;
        }
        default:
            break;
    }

}

void StageSelect::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
     /*switch (keyCode)
     {
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        {
            Size size = Director::getInstance()->getVisibleSize();
            m_x -= 10;

            m_pPlayer->setPosition(Vec2(m_x, size.height / 2));
            m_pPlayer->move(Vec2(-1, 0));
            m_pPlayer->setFlippedX(true);
            break;
        }
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        {
            Size size = Director::getInstance()->getVisibleSize();
            m_x += 10;

            m_pPlayer->setPosition(Vec2(m_x, size.height / 2));
            m_pPlayer->move(Vec2(1, 0));

            m_pPlayer->setFlippedX(false);
            break;
        }
        default:
            break;     
     }*/
    
}