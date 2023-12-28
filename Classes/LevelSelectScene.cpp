#include "LevelSelectScene.h"
#include "LobbyScene.h"

#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"
#include "VisibleRect.h"


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

    //선그리기
    auto s = Director::getInstance()->getWinSize();
    auto draw = DrawNode::create();
    this->addChild(draw, 10);
    //점을 찍는함수
    draw->drawPoint(Vec2(120, 120), 10, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));

    // draw 4 small points
    Vec2 position[] = { Vec2(60,60), Vec2(70,70), Vec2(60,70), Vec2(70,60) };
    draw->drawPoints(position, 4, 5, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));

    // draw a line
    draw->drawLine(Vec2(0, 0), Vec2(s.width, s.height), Color4F(1.0, 0.0, 0.0, 0.5));

    // draw a rectangle
    draw->drawRect(Vec2(23, 23), Vec2(7, 7), Color4F(1, 1, 0, 1));

    // draw a circle
    draw->drawCircle(VisibleRect::center() + Vec2(140, 0), 100, CC_DEGREES_TO_RADIANS(90), 50, true, 1.0f, 2.0f, Color4F(1.0f, 0.0f, 0.0f, 0.5f));

    // Draw some beziers
    draw->drawQuadBezier(Vec2(s.width - 150, s.height - 150), Vec2(s.width - 70, s.height - 10), Vec2(s.width - 10, s.height - 10), 10, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5f));



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
