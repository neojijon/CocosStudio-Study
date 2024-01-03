#ifndef __MAP_SCENE_H__
#define __MAP_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Renderer/CCTextureAtlas.h"
#include "kSprite.h"
#include "kScene.h"
#include<string>
#include "dataLoad.h"


//
//#define getRandom(v)            random(0,(v)-1)
//
//
#define ST_AND 1000
#define ST_LOAD 1
#define ST_LOGO 0
#define ST_MENU 2
#define ST_EXITGAME 999
#define ST_GAME_BUY 23

#define ST_UnitShop 3
#define ST_ItemShop 4
#define ST_StageMenu 5
#define ST_UnitMenu 6
#define ST_UnitWindo 19 //이벤트
#define ST_FBook 22

#define ST_OPTION 7
#define ST_HELP 8
#define ST_NewGAME 9
#define ST_Description 24

#define ST_ReadyGO 10
#define ST_PLAY 11
#define ST_PLAY2 21
#define ST_PlayShop 12 //아이템구매  // ST_RePLAY 12
#define ST_PAUSE 13
#define ST_GAME_Clear 14
#define ST_GAMEOVER 20

#define ST_MAP_Editor 15
#define ST_MAP_World 16

#define ST_GAME_More 17
#define ST_GAME_OPTION 18

#define ST_GAME_AD 25

#define ST_TEST 18

#define ST_PLAY3 27
#define ST_Banner 50
#define ST_Daily 51

#define ST_FIRSTAIDKIT 70 //구급상자
#define ST_MAINREWARD 71 //메인화면 보상
#define ST_MAINREWARDLVUP 72 //메인화면 보상 레벨업
#define ST_DRONEBONUS 73 //드론보너스
#define ST_DURABILITY 74 //무기내구도


#define MMAX_X 2640
#define MMAX_Y 170


class MapScene : public kScene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void Tileimg(int ani, int Px, int Py, int dr, float Papa, float bg);

    Sprite* Spritecreate(const std::string& filename);

    Sprite* makeSprite(int type, std::string file, int dir);

    Sprite* createSpriteImage(std::string imgName, int im);

    void TileImg_rotateImage(int img, int x, int x1, int x2, int y, float alfa, int dr, float bg, int dt, int rcx, int rcy, int rot);

    int GRandom(int Ga, int Gb);

    void GStage(int sg, int ty);

    void GPlayloop();
    
    CREATE_FUNC(MapScene);

    dataLoad data;


protected:
    int TileData1[14000]; //타일 데이타1
    int TileData2[16000]; //타일 데이타2

    kSprite* TileImg[550];//타일 이미지  426
    int TileImg_Xdata[550];// 타일이미지 사이즈
    int TileImg_Ydata[550];// 타일이미지 사이즈

    int Gamemap[2700][180];   
    int Gstg = 0, Gstgtim = 0, Endstg = 0;
    int BGnum = 0, BGnum_Y = 0;
    int GSKillsoo = 0, GKills = 0; 
    int simni4 = 0;// 4발괴물 갯수
    int MapX = 0, MapY = 0;
    int Sy16 = 0;
    float TBG = 0.0f;
    int preState, stState;
    int vibnum = 0, TBimgX = 0, TBimgY = 0;//진동시

    int Jumpjump = 0;//점퍼점프 구분용 

};

#endif  
