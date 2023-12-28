#include "LevelSelectScene.h"
#include "LobbyScene.h"


USING_NS_CC;
using namespace ui;
using namespace cocostudio;


Scene* LevelSelectScene::createScene()
{
    return LevelSelectScene::create();
}


bool LevelSelectScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    rootLayerNode = (Layer*)CSLoader::createNode("LevelSelect.csb");
    this->addChild(rootLayerNode);

    auto pPanel1 = rootLayerNode->getChildByName("Panel_1");    
    for (int i = 0; i < 5; i++)
    {
        char temp[20];
        sprintf(temp, "Lock_1_%d", i);
        
        auto pLvBtn = pPanel1->getChildByName(temp);
        if (pLvBtn)
        {
            char str[100];
            std::string strNum = itoa(i+1,str,10);
            LevelBtnInit((Button*)pLvBtn, strNum);           
        }
    }  

    auto pPanel2 = rootLayerNode->getChildByName("Panel_2");    
    for (int i = 0; i < 5; i++)
    {
        char temp[20];
        sprintf(temp, "Lock_1_%d", i);

        auto pLvBtn = pPanel2->getChildByName(temp);
        if (pLvBtn)
        {
            char str[100];
            std::string strNum = itoa(i + 6, str, 10);
            LevelBtnInit((Button*)pLvBtn, strNum);
        }
    }



    Button* pBtn = (Button*)rootLayerNode->getChildByName("Back");
    pBtn->addClickEventListener(CC_CALLBACK_1(LevelSelectScene::menuBackCallback, this));

    //
    //timeline::ActionTimeline* _sampleAnimation;
    //_sampleAnimation = cocos2d::CSLoader::createTimeline("MainScene.csb");

    //_sampleAnimation->gotoFrameAndPlay(0, true);
    //rootNode->runAction(_sampleAnimation);

    return true;
}

void LevelSelectScene::LevelBtnInit(cocos2d::ui::Button *pButton, std::string strNum)
{
    Button* plv = (Button*)pButton->getChildByName("LevelBtn");
    if (plv)
        plv->setEnabled(true);

    TextAtlas* pTextAtlas = (TextAtlas*)pButton->getChildByName("LvNum");
    if (pTextAtlas)
        pTextAtlas->setString(strNum);

    pButton->getChildByName("Lock")->setVisible(false);
}



void LevelSelectScene::menuBackCallback(Ref* pSender)
{   
    auto director = Director::getInstance();
    
    auto scene = LobbyScene::createScene();
    director->replaceScene(TransitionCrossFade::create(2, scene));
    //director->replaceScene(TransitionFade::create(2, scene, Color3B(255, 0, 0)));

}
