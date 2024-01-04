#include "MapScene.h"
#include "dataLoad.h"


USING_NS_CC;
using namespace ui;
using namespace cocostudio;


Scene* MapScene::createScene()
{
    return MapScene::create();
}


bool MapScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    Sy16 = 32;// 타일 크기

    GPlayloop();
    //GStage(0,0);

    return true;
}

void MapScene::Tileimg(int ani, int Px, int Py, int dr, float Papa, float bg)
{
    int it, iss, iee, lani;
    int Prtn;   
    float LPapa, Lpb;

    if (ani > 0)
    {
        iss = (TileData1[(ani - 1) * 18] * 7);
        iee = (TileData1[ani * 18] * 7);

        for (it = iss; it < iee; it += 7)
        {
            lani = TileData2[it];

            LPapa = Papa;  

            Lpb = bg;
            Prtn = TileData2[it + 3];  

            TileImg_rotateImage(lani, Px, sizeXXYY(TileData2[it + 1], bg), 0, sizeXXYY(TileData2[it + 2], bg) + Py, LPapa, dr, Lpb, 1, Px, sizeXXYY(TileData2[it + 2], bg) + Py, Prtn);
        }
    }
}

kSprite* MapScene::Spritecreate(const std::string& filename)
{
    kSprite* sprite = new (std::nothrow) kSprite();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->init();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

kSprite* MapScene::makeSprite(int type, std::string file, int dir)
{
    int idx = sprno[type] + sprst[type];
    kSprite* spr = nullptr;
    if (dir == 0) {
        if (type <= SPR_BG) {
            spr = Spritecreate(file);
            addChild(spr, 0, MAKET_BG(idx, 0));
        }
        else {
#ifdef USE_ATLAS
            spr = kSprite::createWithSpriteFrameName(file);
#else
            spr = kSprite::create(file);
#endif
            addChild(spr, 0, MAKET_IMG(idx, 0));
            sprDat.insert(std::pair<int, kSprite*>(MAKET_IMG(idx, 0), spr));
        }
    }
    else {
        std::string path = FileUtils::getInstance()->getWritablePath().append(file);
        Image* img = new Image();
        bool isImage = img->initWithImageFile(path);
        if (isImage == false)
            return nullptr;
        Texture2D* tex = new Texture2D();
        tex->initWithImage(img);
        tex->autorelease();

        spr = kSprite::createWithTexture(tex);
        addChild(spr, 0, MAKET_IMG(idx, 0));
        delete img;
    }
    if (++sprno[type] >= MAX_IDX) {
        sprno[type] = 0;
    }
    spr->setVisible(false);
    return spr;
}

kSprite* MapScene::createImage(std::string imgName, int im)
{
    kSprite* sprite = makeSprite(SPR_OBJ, StringUtils::format(imgName.c_str(), im));
    return sprite;
}

int MapScene::sizeXXYY(int xy, float sb)
{
    if (sb == 1) return (xy);
    else if (sb > 1) return (sb * xy);
    else return (xy - ((1 - sb) * xy));
}


void MapScene::TileImg_rotateImage(int img, int x, int x1, int x2, int y, float alfa, int dr, float bg, int dt, int rcx, int rcy, int rot)   
{

    if (img < 0 || img > 426)
    {
        img = 0;
    }

    if (TileImg_Ydata[img] == 0)     
    {
#ifdef USE_ATLAS
        TileImg[img] = createImage("bimg[%d].png", img);
#else
        TileImg[img] = createImage("img/tile/bimg[%d].png", img);    
#endif
        TileImg_Xdata[img] = TileImg[img]->getContentSize().width;
        TileImg_Ydata[img] = TileImg[img]->getContentSize().height;
    }

    if (dr == 0)
    {
        if (rot != 0) 
            TileImg[img]->drawPos(CGPointMake(x + x1 - x2, y), bzColorMake(255, 255, 255, alfa), dr, (bg), dt, rcx + x1, rcy, 0.01 * rot);
        else
            TileImg[img]->drawPos(CGPointMake(x + x1 - x2, y), bzColorMake(255, 255, 255, alfa), dr, bg);  
    }
    else
    {
        if (rot != 0)
            TileImg[img]->drawPos(CGPointMake(x - x1 + x2 - sizeXXYY(TileImg_Xdata[img], bg), y), bzColorMake(255, 255, 255, alfa), dr, (bg), dt, rcx - x1, rcy, 0.01 * (630 - rot));
        else
            TileImg[img]->drawPos(CGPointMake(x - x1 + x2 - sizeXXYY(TileImg_Xdata[img], bg), y), bzColorMake(255, 255, 255, alfa), dr, bg);  
    }
}


int MapScene::GRandom(int Ga, int Gb) 
{
    if (stState == ST_PAUSE || stState == ST_FIRSTAIDKIT || stState == ST_DRONEBONUS || stState == ST_GAMEOVER || stState == ST_DURABILITY)    
        return Ga;
    else {
        int i;

        i = ((int)getRandom(Ga) + Gb);
        return i;
    }
}



void MapScene::GStage(int sg, int ty) 
{
    int i, ii, j, jj, k, kk, h, lk, lk2;
    int Tx, Ty, hho;
    int MapTy, MapNum;
    int simni, simtim, bos;
    int test, test2;

    int Homedata[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,17,18,19,20,287,288,289,290,291,292,293,294,295 };     
    int dolldata[] = { 64,279,281,303 };     
    int Homenum[] = { 0,0,0,0,0,0,0,0,0,0,0,0 };   

    k = 0;  
    kk = 0;    

    Gstg = sg;
    MapNum = Gstg;  

    for (i = 0; i < 12; i++)
    {
        for (j = 0; j < 28; j++)
        {
            ii = Homedata[GRandom(28, 0)];
            for (jj = 0; jj < 12; jj++)
            {
                if (Homenum[jj] == ii) 
                    break;
                else if (Homenum[jj] == 0)
                {
                    Homenum[jj] = ii;
                    j = 28;
                    break;
                }
            }
        }
    }

    BGnum = data.STGData[(Gstg * 643) + 641];
    bos = data.STGData[(Gstg * 643) + 642];
    if (BGnum == 1) 
        BGnum_Y = 15;
    else
        BGnum_Y = 0;

    test = 0;
    test2 = 0;

    lk = lk2 = hho = GSKillsoo = GKills = 0;
    for (j = data.stg_Y - 1; j >= 0; j--)        
    {
        for (jj = 0; jj < data.stg_X; jj++)  
        {
            h = data.STGData[(MapNum * (data.stg_Y * data.stg_X + 3)) + jj + (j * data.stg_X)];
            for (i = 0; i < data.map_Y; i += 1)  
            {
                for (ii = 0; ii < data.map_X; ii += 1)  
                {
                    Tx = ii + (jj * data.map_X);
                    Ty = i + (j * data.map_Y);

                    MapTy = data.MapSData[ii + (i * data.map_X) + (h * (data.map_Y * data.map_X))];

                    if (MapTy == 500)                       
                    {
                        Gamemap[Tx][Ty] = MapTy;
                        MapX = (jj * 32) * 32 + 100;
                        MapY = (j * 20) * 32 + 200;

                    }
                    else if (MapTy == 415)     
                    {
                        if ((Gamemap[Tx][Ty - 1] == 64) || (jj > 2 && lk < 12 && lk2 != jj - 1))   
                        {
                            if (Gamemap[Tx][Ty - 1] == 295)
                            {
                                if (Homenum[lk] == 3 || Homenum[lk] == 19 || Homenum[lk] == 288) 
                                    Gamemap[Tx][Ty - 1] = (Homenum[lk] - 1);    
                                else 
                                    Gamemap[Tx][Ty - 1] = Homenum[lk]; 

                            }
                            else
                                Gamemap[Tx][Ty - 1] = dolldata[GRandom(4, 0)]; 

                            Gamemap[Tx][Ty] = 415 + lk - hho; 

                            lk2 = jj;
                            lk++;

                            test++;
                        }
                        else    
                        {
                            if (Gamemap[Tx][Ty - 2] == 0)
                            {
                                if (BGnum == 1)
                                    Gamemap[Tx][Ty - 2] = (491 + GRandom(2, 0));  
                                else
                                    Gamemap[Tx][Ty - 2] = (153 + GRandom(4, 0));  
                            }
                            Gamemap[Tx][Ty - 1] = 0;
                            Gamemap[Tx][Ty] = 0;
                        }
                    }
                    else if (MapTy < 0)           
                    {
                        if (MapTy == -310) 
                            Gamemap[Tx][Ty] = MapTy;
                        else if (MapNum < 5)
                        {
                            MapTy += (75 - (MapNum * 15));
                            if (MapTy > -26)  
                                MapTy = -26;

                            Gamemap[Tx][Ty] = MapTy;
                        }
                        else
                            Gamemap[Tx][Ty] = (MapTy - ((MapNum - 5) * 5));

                    }
                    else
                    {
                        if (MapTy == 501 || MapTy == 570)        
                        {
                            GKills++;

                            if ((h == 77 || h == 91) && Jumpjump != 2)                    
                            {
                                if (bos > 0 && data.STGData[(MapNum * (data.stg_Y * data.stg_X + 3)) + jj + 1 + (j * data.stg_X)] == 70)
                                {
                                    if (Gamemap[Tx - 26][Ty] == 0 && Gamemap[Tx - 26][Ty - 1] == 0)    
                                    {
                                        Gamemap[Tx - 26][Ty] = (bos + 500);
                                        Gamemap[Tx - 26][Ty - 1] = -21;
                                    }
                                    else if (Gamemap[Tx][Ty] == 0 && Gamemap[Tx][Ty - 1] == 0)
                                    {
                                        Gamemap[Tx][Ty] = (bos + 500);
                                        Gamemap[Tx][Ty - 1] = -21;
                                    }

                                }
                                else Gamemap[Tx][Ty] = 0;    
                            }
                            else 
                            {
                                if (MapTy == 570)  
                                {
                                    if (simni4 > 0 && GRandom(100, 0) < 50)
                                    {
                                        if (Gstg > 40)
                                            Gamemap[Tx][Ty] = 570;
                                        else if (Gstg > 30)
                                            Gamemap[Tx][Ty] = 572;
                                        else if (Gstg > 20)
                                            Gamemap[Tx][Ty] = 571;
                                        else
                                            GKills--;

                                        simni4--;
                                    }
                                    else
                                    {
                                        GKills--;
                                    }
                                }
                                else  Gamemap[Tx][Ty] = MapTy;
                            }
                        }
                        else Gamemap[Tx][Ty] = MapTy;
                    }
                }
            }

            test2 = 0;
        }
    }

    for (j = 0; j < MMAX_Y; j++)      
    {
        Gamemap[1][j] = 57;
        Gamemap[2][j] = 57;

        if (Gamemap[28][j] == 0) 
            Gamemap[28][j] = 57;
        if (Gamemap[29][j] == 0) 
            Gamemap[29][j] = 57;
        if (Gamemap[30][j] == 0) 
            Gamemap[30][j] = 57;
        if (Gamemap[31][j] == 0) 
            Gamemap[31][j] = 57;

        Gamemap[MMAX_X - 2][j] = 57;
        Gamemap[MMAX_X - 1][j] = 57;
    }

    for (jj = 0; jj < MMAX_X; jj++)  
    {
        Gamemap[jj][1] = 57;
        Gamemap[jj][2] = 57;

        Gamemap[jj][MMAX_Y - 2] = 57;
        Gamemap[jj][MMAX_Y - 1] = 57;
    }

    for (j = 20; j < 31; j++)
        Gamemap[j][0] = 438;  
}


kSprite* MapScene::getSprite(int type, int idx, int frm, kSprite* ori)
{
    int tag = 0;
    kSprite* spr = nullptr;

    switch (type) {
    case STYPE_BG:
        tag = MAKET_BG(idx, frm);
        spr = (kSprite*)getChildByTag(tag);
        if (spr == nullptr) {
            spr = kSprite::createWithTexture(ori->getTexture());
            addChild(spr, 0, tag);
            spr->setVisible(false);
        }
        break;
    case STYPE_IMG:
        tag = MAKET_IMG(idx, frm);
        auto it = sprDat.find(tag); 
        if (it == sprDat.end()) {
            spr = kSprite::createWithSpriteFrame(ori->getSpriteFrame());
            addChild(spr, 0, tag);
            sprDat.insert(std::pair<int, kSprite*>(tag, spr));
            spr->setVisible(false);
        }
        else {
            spr = it->second;
        }
        break;
    }
    return spr;
}


void MapScene::GPlayloop() ////////////////////////////////////////////////////////////////////// 게임루프 ( 게임이 실행되는 곳 )
{
    int i, k, kk, ii, h, hh, ii2, mmx, mmy, fori, fori2, j;
    int Mx, My;

    ii = (MapX % Sy16);
    fori = (MapX / Sy16);
    ii2 = (MapY % Sy16);
    fori2 = (MapY / Sy16);

    //LOGD(" GPlayloop 1 : %d   " , i  );

    for (k = 30; k > -5; k--)
    {
        for (i = -7; i < 44; i++)
        {
            Mx = i + fori;
            My = k + fori2;
            switch (Gamemap[Mx][My])
            {
            case 21: case 27: case 53: case 54: case 55: case 56:// 건물벽
            case 98: case 99://유리창
            case 270: case 271: case 272: case 273: case 274:  case 404://방안에벽
            case 48: case 49: case 51: case 52: //야외바닥
            case 124:// 야외 멀리있는중간에 긴풀
            case 127://야외바닥 땅속에 검은부분
            case 129: case 275: case 276: case 277: case 278://야외바닥 땅속
                Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), (int)(k * Sy16 - ii2) + TBimgY, 0, 1, TBG);// 맵 이미지
                break;
            case 478: case 479: case 480: case 481: case 482: case 483: // 숲에서 제일 뒤에 바닥에 작은나무풀
                Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), (int)(k * Sy16 - ii2) + 32 + TBimgY, 0, 1, TBG);// 맵 이미지
                break;
            }
        }
    }

    ////LOGD(" GPlayloop 2 : %d   " , i  );
    //std::vector<DataStruct> vecFirstAidKit;

    //for (k = 30; k > -5; k--) //  타일 뒤로 가는 오브젝트들
    //{
    //    for (i = -13; i < 50; i++)   // -7  ~ 44
    //    {
    //        Mx = i + fori;
    //        My = k + fori2;
    //        switch (Gamemap[Mx][My])   //
    //        {
    //        case 0:
    //        case 21: case 27: case 53: case 54: case 55: case 56:// 건물벽
    //        case 41: case 57: case 125:// 바닥이 있는 이미지 없는 타일
    //        case 89: case 90: case 91://옥상에 난간
    //        case 98: case 99://유리창
    //        case 102: case 103://도끼
    //        case 270: case 271: case 272: case 273: case 274:  case 404://방안에벽
    //        case 49: case 52: //야외바닥
    //            //case 401: case 402: case 403: //야외바닥 흙바닥
    //        case 124:// 야외 멀리있는중간에 긴풀
    //        case 127://야외바닥 땅속에 검은부분
    //        case 211:// 영사기
    //        case 129: case 275: case 276: case 277: case 278://야외바닥 땅속
    //        case 415: case 416: case 417: case 418: case 419: case 420: case 421: case 422: case 423: case 424: case 425: case 426: case 427: case 428: case 429: case 430: case 431: case 432: case 433: case 434: case 435:// 문들어갈때 아래 방번호 415 ~ 435

    //            break;
    //        case 1: case 2: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 16: case 17: case 18: case 20: // 건물
    //        case 287:  case 289: case 290: case 291: case 292: case 293: case 294: case 295: // 건물
    //            AttTileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY) + BGnum_Y, 0, 1, TBG, Mx, My);
    //            break;
    //        case 15: case 75: //나무다리
    //            if (Gamemap[Mx - 1][My] == 0 || Gamemap[Mx + 1][My] == 0)
    //            {
    //                Gamemap[Mx][My] = Gamemap[Mx][My - 1] = 0;
    //                initRest(0, 133, 311 + GRandom(12, 0), GRandom(2, 0), (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), GRandom(4, 0), 1, 0); //나무조각들
    //                initRest(0, 133, 311 + GRandom(12, 0), GRandom(2, 0), (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), GRandom(4, 0), 1, 0); //나무조각들
    //                initRest(0, 133, 311 + GRandom(12, 0), GRandom(2, 0), (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), GRandom(4, 0), 1, 0); //나무조각들
    //                initRest(0, 133, 311 + GRandom(12, 0), GRandom(2, 0), (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), GRandom(4, 0), 1, 0); //나무조각들
    //            }
    //            else  Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG);// 맵 이미지
    //            break;
    //        case 25:// 점프해서 적 난간잡기위치 >>
    //            PCMiniAni(16, (int)(i * Sy16 - ii), 13, (int)(k * Sy16 - ii2) + TBimgY, 0);
    //            break;
    //        case 60:// 점프해서 적 난간잡기위치 <<
    //            PCMiniAni(-24, (int)(i * Sy16 - ii), 13, (int)(k * Sy16 - ii2) + TBimgY, 1);
    //            break;
    //        case 29: // 유리창 아래벽
    //            Tileimg(29, (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG);// 맵 이미지
    //            break;
    //        case 42: //유리문
    //            Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG);
    //            break;
    //        case 48: case 51: // 헬기장

    //            j = 0;
    //            for (kk = 4; kk < PC_Number - 1; kk++) // 포로있나체크
    //            {
    //                if (npc[kk].Php > 1)//3
    //                {
    //                    if (npc[kk].Door != 9745)
    //                    {
    //                        if (HitCheck(npc[kk].Pjx, (int)(i * Sy16 - ii), 100) && HitCheck(npc[kk].Pjy, ((int)(k * Sy16 - ii2) + TBimgY) + 84, 60)) // 헬기장 도착
    //                        {
    //                            //NSLog(@" 헬기장 도착  kk =  %d , PC_Number = %d "  ,  kk  , PC_Number );//
    //                            npc[kk].Door = 9745;
    //                            PXYAni(kk, 45, npc[kk].Dir, 1); // 앉기
    //                            //PAniinit2( 4 , kk ,0);//숨쉬기
    //                            //j = kk;
    //                        }
    //                    }
    //                    else j = 29;//PC_Number-1;
    //                }
    //            }

    //            if (npc[j].weapon != 22 && j > 0)
    //            {
    //                //NSLog(@" 헬기  kk =  %d , j = %d "  ,  kk  , j );//
    //                npc[j].weapon = 22;
    //                npc[j].weaponup = 0;
    //                npc[j].CType = 1508;
    //                npc[j].MUDamage = 60;//data.CostData[6][22];//무기 파워
    //                npc[j].Php = 500;
    //                npc[j].Dir = 0;
    //                npc[j].alfa = 1;
    //                npc[j].PBig = 1;
    //                npc[j].Gloves = 0;
    //                npc[j].Pjx = (int)(i * Sy16 - ii);
    //                npc[j].Pjy = -100;
    //                npc[j].R = 255;
    //                npc[j].G = 255;
    //                npc[j].B = 255;
    //                PXYAni(j, 102, npc[j].Dir, 1);
    //                npc[j].OPR = 12;
    //                PHel_y = 29;
    //            }
    //            break;
    //        case 64: case 279: case 281: case 303: //////////// 들어가는 문
    //            if (npc[0].OPR < 65 && (npc[0].weapon < 21 || npc[0].weapon == 23) && HitCheck(npc[0].Pjx, (int)(i * Sy16 - ii) + 30, sizeXXYY(45, npc[0].PBig)) && HitCheck(npc[0].Pjy, ((int)(k * Sy16 - ii2) + TBimgY) + 84, 60)) // 열림
    //            {
    //                Tileimg(Gamemap[Mx][My] + 1, (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG);// 맵 이미지
    //                if (Din == 0) SoundPlay(50, -1);//사운드

    //                Din = Gamemap[Mx][My + 1];
    //            }
    //            else
    //            {
    //                if (Din != 0) SoundPlay(50, -1);//사운드
    //                Din = 0;
    //                Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG);// 맵 이미지
    //            }
    //            break;
    //        case 110:// 건너뛰다 점프 >>
    //            if (Gamemap[Mx + 1][My - 1] == 0)
    //            {
    //                if (Gamemap[Mx + 2][My - 1] == 245 && Gamemap[Mx + 3][My - 1] == 245 && Gamemap[Mx + 4][My - 1] == 245) Gamemap[Mx][My] = 0;
    //                else PCMiniAni(PC_Number, (int)(i * Sy16 - ii), 14, (int)(k * Sy16 - ii2) + TBimgY, 1);
    //            }
    //            else
    //            {
    //                if (Gamemap[Mx + 1][My - 1] == 245 && Gamemap[Mx + 2][My - 1] == 245 && Gamemap[Mx + 3][My - 1] == 245) Gamemap[Mx][My] = 0;
    //                else PCMiniAni(PC_Number, (int)(i * Sy16 - ii), 14, (int)(k * Sy16 - ii2) + TBimgY, 1);
    //            }
    //            break;
    //        case 192:// 건너뛰다 점프 <<
    //            if (Gamemap[Mx - 1][My - 1] == 0)
    //            {
    //                if (Gamemap[Mx - 2][My - 1] == 245 && Gamemap[Mx - 3][My - 1] == 245 && Gamemap[Mx - 4][My - 1] == 245) Gamemap[Mx][My] = 0;
    //                else PCMiniAni(PC_Number, (int)(i * Sy16 - ii), 15, (int)(k * Sy16 - ii2) + TBimgY, 1);
    //            }
    //            else
    //            {
    //                if (Gamemap[Mx - 1][My - 1] == 245 && Gamemap[Mx - 2][My - 1] == 245 && Gamemap[Mx - 3][My - 1] == 245) Gamemap[Mx][My] = 0;
    //                else PCMiniAni(PC_Number, (int)(i * Sy16 - ii), 15, (int)(k * Sy16 - ii2) + TBimgY, 1);
    //            }
    //            break;
    //        case 78: //없음 모름

    //            break;
    //        case 79: case 84: // 쓰레기통
    //            Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY) + 5, 0, 1, TBG);// 맵 이미지
    //            break;
    //        case 94: case 95: case 96: // 톨로문
    //            Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG);// 맵 이미지
    //            break;
    //        case 119://작은상자
    //            Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG);

    //            if (Gamemap[Mx][My + 2] == 0 && Gamemap[Mx + 1][My + 2] == 0)
    //            {
    //                Gamemap[Mx - 1][My + 1] = Gamemap[Mx - 1][My];// 상자체력복사
    //                Gamemap[Mx - 1][My] = 0;// 체력삭제

    //                Gamemap[Mx][My + 2] = Gamemap[Mx][My + 1];
    //                Gamemap[Mx + 1][My + 2] = Gamemap[Mx + 1][My + 1];
    //                Gamemap[Mx][My + 1] = Gamemap[Mx][My];
    //                Gamemap[Mx + 1][My + 1] = Gamemap[Mx + 1][My];
    //                Gamemap[Mx][My] = Gamemap[Mx + 1][My] = 0;//위부분삭제
    //            }
    //            break;
    //        case 120://큰철상자
    //            Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG);
    //            break;
    //        case 121: case 122: case 123://중간상자 종이상자임
    //            Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG);
    //            if (Gamemap[Mx + 1][My + 3] == 0 && Gamemap[Mx + 2][My + 3] == 0 && (Gamemap[Mx][My + 3] == 0 || Gamemap[Mx][My + 3] == 49))
    //            {
    //                if (Gamemap[Mx][My + 3] == 49) Gamemap[Mx][My + 3] = 52;
    //                else Gamemap[Mx][My + 3] = Gamemap[Mx][My + 2];

    //                Gamemap[Mx + 1][My + 3] = Gamemap[Mx + 1][My + 2];
    //                Gamemap[Mx + 2][My + 3] = Gamemap[Mx + 2][My + 2];
    //                Gamemap[Mx][My + 2] = Gamemap[Mx][My + 1];
    //                Gamemap[Mx + 1][My + 2] = Gamemap[Mx + 1][My + 1];
    //                Gamemap[Mx + 2][My + 2] = Gamemap[Mx + 2][My + 1];
    //                Gamemap[Mx][My + 1] = Gamemap[Mx][My];
    //                Gamemap[Mx + 1][My + 1] = Gamemap[Mx + 1][My];
    //                Gamemap[Mx + 2][My + 1] = Gamemap[Mx + 2][My];
    //                Gamemap[Mx][My] = Gamemap[Mx + 1][My] = Gamemap[Mx + 2][My] = 0;//위부분삭제
    //            }
    //            break;
    //        case 130: case 131: case 132: case 133: case 134: case 135: case 136: case 137: case 138: case 139:// 배경철골
    //            Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY) - 16, 0, 1, TBG);
    //            break;
    //        case 146: //철골 바닥
    //            Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY) - 16, 0, 1, TBG);
    //            break;
    //        case 161: case 162: case 163: case 164: case 165: case 166: case 167:
    //            Tileimg(160, (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG);// 엘리베이터 안쪽 이미지
    //            if ((npc[0].OPR == 150 && npc[0].Ptime == 0) || (npc[0].OPR == 149 && Gamemap[Mx][My] < 166))
    //            {
    //                //(npc[0].Dir*20-10)

    //                if (npc[0].weapon == 23) LPimg(0, (int)(i * Sy16 - ii) + (npc[0].Dir * 34 - 17), npc[0].Pjy - 36, 621, npc[0].Dir, npc[0].R, npc[0].G, npc[0].B, npc[0].PBig, npc[0].Gloves);//로봇
    //                else if (npc[0].weapon == 19) LPimg(0, (int)(i * Sy16 - ii) + (npc[0].Dir * 34 - 17), npc[0].Pjy - 36, 277, npc[0].Dir, npc[0].R, npc[0].G, npc[0].B, npc[0].PBig, npc[0].Gloves);//헐크
    //                else LPimg(0, (int)(i * Sy16 - ii), npc[0].Pjy - 36, 14, npc[0].Dir, npc[0].R, npc[0].G, npc[0].B, npc[0].PBig, npc[0].Gloves);

    //                WeaponAni(16, (int)(i * Sy16 - ii), Gamemap[Mx][My], npc[0].Pjy - 36);
    //            }
    //            Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG);// 엘리베이터문
    //            if (npc[0].OPR < 150 && (npc[0].weapon < 21 || npc[0].weapon == 23) && HitCheck(npc[0].Pjx, (int)(i * Sy16 - ii), sizeXXYY(35, npc[0].PBig)) && HitCheck(npc[0].Pjy, ((int)(k * Sy16 - ii2) + TBimgY) + 32, 60)) // 열림
    //            {
    //                if (Gamemap[Mx][My] < 167) Gamemap[Mx][My]++;
    //                if (Gamemap[Mx][My] == 167)
    //                {
    //                    eunmX = Mx;
    //                    eunmY = My;
    //                    Din = 1;
    //                    Din2 = 0;
    //                    if (npc[0].OPR == 149)
    //                    {
    //                        PAniinit2(4, 0, 0);//숨쉬기
    //                        WeaponAni(17, 0, 0, 0);
    //                    }
    //                }
    //            }
    //            else /////// 닫힘
    //            {
    //                if (Gamemap[Mx][My] > 161) Gamemap[Mx][My]--;
    //                Din = 0;
    //            }
    //            break;
    //        case 179:// 감옥문
    //            mmx = (int)(i * Sy16 - ii);
    //            mmy = ((int)(k * Sy16 - ii2) + TBimgY);
    //            Tileimg(178, mmx, mmy, 0, 1, TBG);// 맵 이미지
    //            TileImg_drawImage(115, mmx - 10, mmy - 45, data.KnifeColor[1][0], data.KnifeColor[1][1], data.KnifeColor[1][2], 1, 0, 1);
    //            Tileimg(179, mmx, mmy, 0, 1, TBG);// 맵 이미지
    //            if (GOrder[2] < 0 && mmx > 0 && mmx < D_H)
    //            {
    //                GOrder[2] = -2;
    //                Gord_x = mmx;
    //                Gord_Y = mmy - 70;
    //                if (HitCheck(npc[0].Pjx, mmx, 150)) Gord_zz = 2;//
    //                else Gord_zz = 0;
    //            }
    //            break;
    //        case 180:// 감옥문 부서짐
    //            mmx = (int)(i * Sy16 - ii);
    //            mmy = ((int)(k * Sy16 - ii2) + TBimgY);
    //            Tileimg(178, mmx, mmy, 0, 1, TBG);// 맵 이미지
    //            Tileimg(180, mmx, mmy, 0, 1, TBG);// 맵 이미지
    //            break;
    //        case 187: case 193: case 194:// 실험관 이미지출력이 다른다

    //            TileRGBimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 170, 5, 1, TBG);
    //            break;
    //        case 233:// 전기함

    //            Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG);
    //            if (GOrder[18] < 0 && HitCheck(npc[0].Pjx, (int)(i * Sy16 - ii), 300) && HitCheck(npc[0].Pjy, ((int)(k * Sy16 - ii2) + TBimgY) + 140, 200)) // && mmx > 0 && mmx < D_H )
    //            {
    //                GUIImg_drawImage(134, (int)(i * Sy16 - ii) - 12, ((int)(k * Sy16 - ii2) + TBimgY) - 40 - HPpinit, 255, 255, 255, 0.8, 0, 1);// V
    //                Gord_Z = 667;

    //            }
    //            else Gord_Z = 0;

    //            break;
    //        case 234: case 235: case 236:// 벽에 뷰즈박스 돈이나 보석이 들어 있음

    //            Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG);
    //            if (HitCheck(npc[0].Pjx, (int)(i * Sy16 - ii), sizeXXYY(35, npc[0].PBig)) && HitCheck(npc[0].Pjy, ((int)(k * Sy16 - ii2) + TBimgY) + 140, 80)) // 열림
    //            {
    //                //@Bump TEST
    //                cocos2d::log("Bump_Item_GetAd");
    //                if (Gamemap[Mx][My] == 234) Gold(data.STGTim[1][0] * data.STGTim[1][Gstg]);  //
    //                else if (Gamemap[Mx][My] == 235) Jewel(data.STGTim[2][0] * data.STGTim[2][Gstg]);//
    //                else WeaponAni(25, 0, 0, 1);// 약병 플러스
    //                Gamemap[Mx][My] = 238;
    //            }
    //            break;
    //        case 241: case 242: case 243:// 벽에 구급박스 돈이나 보석이 들어 있음

    //            Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG);
    //            if (HitCheck(npc[0].Pjx, (int)(i * Sy16 - ii), sizeXXYY(35, npc[0].PBig)) && HitCheck(npc[0].Pjy, ((int)(k * Sy16 - ii2) + TBimgY) + 140, 80)) // 열림
    //            {
    //                if (Gamemap[Mx][My] == 243)
    //                {
    //                    //WeaponAni( 25 , 0 , 0 , 1);// 약병 플러스
    //                    AitemSsave();
    //                    STGSsave(); // 스테이지 저장

    //                    //GetRewardAdFirstAidKit();
    //                    stState = ST_FIRSTAIDKIT;
    //                    GSbuyN = 0;

    //                    //OpenFirstAidKit(Mx, My);

    //                    mmx = (int)(i * Sy16 - ii);
    //                    mmy = ((int)(k * Sy16 - ii2) + TBimgY);
    //                    m_mmx = mmx; m_mmy = mmy;
    //                }
    //                else {
    //                    Gold(data.STGTim[1][0] * data.STGTim[1][Gstg]);  //
    //                    if (Gamemap[Mx][My] == 242)
    //                        Jewel(data.STGTim[2][0] * data.STGTim[2][Gstg]);//
    //                }
    //                Gamemap[Mx][My] = 240;
    //            }
    //            break;
    //        case 246: case 35://상자위에 유리창문
    //            mmx = (int)(i * Sy16 - ii);
    //            mmy = ((int)(k * Sy16 - ii2) + TBimgY);
    //            Tileimg(Gamemap[Mx][My], mmx, mmy, 0, 1, TBG);
    //            if (Gamemap[Mx][My + 2] == 0)
    //            {
    //                Gamemap[Mx][My - 2] = Gamemap[Mx][My - 1] = Gamemap[Mx][My] = Gamemap[Mx][My + 1] = 0;
    //                Gamemap[Mx - 1][My] = 0;
    //                for (h = 0; h < 25; h++)initRest(-GRandom(12, 6), 133, 293 + GRandom(15, 0), GRandom(2, 0), mmx + GRandom(20, -10), mmy - 50 + (h * 4), GRandom(4, 2), 1, 0); //
    //                for (h = 0; h < 14; h++)initRest(-GRandom(12, 5), 133, 293 + GRandom(15, 0), GRandom(2, 0), mmx + GRandom(20, -10), mmy - 45 + (h * 7), GRandom(4, 2), 1, 0); //
    //            }
    //            break;
    //        case 250: case 251: case 252: case 253: case 254: case 255: case 256: case 257: /////////////////철못 나오는거

    //            Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG);
    //            if (Gamemap[Mx][My] < 257) Gamemap[Mx][My]++;
    //            else if (Gamemap[Mx][My] == 257)
    //            {
    //                Gamemap[Mx][My] = 250;
    //            }
    //            break;
    //        case 262: // 타일총 출력 <<<<

    //            mmx = (int)(i * Sy16 - ii);
    //            mmy = ((int)(k * Sy16 - ii2) + TBimgY);
    //            if (npc[0].OPR != 59 && npc[0].OPR != 15) Tileimg(Gamemap[Mx][My], mmx, mmy, 0, 1, TBG);
    //            else if (npc[0].Dir == 0)  Tileimg(Gamemap[Mx][My], mmx, mmy, 0, 1, TBG);

    //            if (THin != 3)
    //            {
    //                if (npc[0].OPR < 65 && npc[0].weapon < 21 && HitCheck(npc[0].Pjx, mmx + 70, sizeXXYY(50, npc[0].PBig)) && HitCheck(npc[0].Pjy - 55, mmy, 30)) // 열림
    //                {
    //                    if (npc[0].OPR != 59) THin = 2;
    //                    THin_x = (mmx + 91);//(mmx+103);
    //                   // THin_y = mmy-25;
    //                }
    //                else THin = 0;
    //            }

    //            break;
    //        case 263: //case 262: // 타일총 출력  >>>>>

    //            mmx = (int)(i * Sy16 - ii);
    //            mmy = ((int)(k * Sy16 - ii2) + TBimgY);
    //            if (npc[0].OPR != 59 && npc[0].OPR != 15) Tileimg(Gamemap[Mx][My], mmx + 147, mmy, 1, 1, TBG);
    //            else if (npc[0].Dir == 1) Tileimg(Gamemap[Mx][My], mmx + 147, mmy, 1, 1, TBG);

    //            if (THin != 2)
    //            {
    //                if (npc[0].OPR < 65 && npc[0].weapon < 21 && HitCheck(npc[0].Pjx, mmx + 5, sizeXXYY(50, npc[0].PBig)) && HitCheck(npc[0].Pjy - 55, mmy, 30)) // 열림
    //                {
    //                    if (npc[0].OPR != 59) THin = 3;
    //                    THin_x = (mmx - 18);// (mmx-30);
    //                  //  THin_y = mmy-25;
    //                }
    //                else THin = 0;
    //            }
    //            break;
    //        case 265:// 디펜에서 유리타일 재생됨

    //            if (Gamemap[Mx][My - 1] < 0)
    //            {
    //                Gamemap[Mx][My - 1]++;
    //                if (Gamemap[Mx][My - 1] > -5) Tileimg(264, (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 0.7, TBG);
    //                else if (Gamemap[Mx][My - 1] > -10) Tileimg(264, (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 0.3, TBG);
    //            }
    //            else
    //            {
    //                Gamemap[Mx][My] = 264;
    //                Gamemap[Mx + 1][My] = 41;
    //            }

    //            break;
    //        case 266:// 디펜용 적생성
    //            if (THin_stg < 4) break;
    //        case 267:// 디펜용 적생성
    //            if (stState == ST_PLAY && (GStime < 5 || GStime > 20))
    //            {
    //                if (Gamemap[Mx + 1][My] < 0) Gamemap[Mx + 1][My]++;
    //                else
    //                {
    //                    if (THin_stg < 4) Gamemap[Mx + 1][My] = -(70 - (THin_stg * 15)); // 적이 나오는 타이머  1:55 , 2:40  , 3:25
    //                    else                Gamemap[Mx + 1][My] = -(70 - (THin_stg * 5)); //-(100-((THin_stg-2)*20)); // 4: 140 , 5: 120 , 6: 100
    //                    if (Gamemap[Mx + 1][My] > -10) Gamemap[Mx + 1][My] = -10;
    //                    Gamemap[Mx][My - 1] = -(270 + (THin_stg * 30));// 체력
    //                    ComCreate(PC_Number, Gamemap[Mx][My], -Gamemap[Mx][My - 1], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY));
    //                }
    //            }
    //            else if (GStime == 10)
    //            {
    //                for (kk = PC_Number; kk < pomsu; kk++) if (D_H + 80 < npc[kk].Pjx || -80 > npc[kk].Pjx) npc[kk].Php = 0;
    //                for (kk = 0; kk < (THin_stg * 5); kk++) initRest(-GRandom(20, 12), 134, 541 + GRandom(3, 0), GRandom(2, 0), D_H2, 50, GRandom(8, 2), 1, 0); //돈
    //                GStime--;
    //            }
    //            break;
    //        case 269:// 디펜에서 세로유리타일 재생됨

    //            if (Gamemap[Mx][My - 1] < 0)
    //            {
    //                Gamemap[Mx][My - 1]++;
    //                if (Gamemap[Mx][My - 1] > -5) Tileimg(268, (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 0.7, TBG);
    //                else if (Gamemap[Mx][My - 1] > -10) Tileimg(268, (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 0.3, TBG);
    //            }
    //            else
    //            {
    //                Gamemap[Mx][My] = 268;
    //                Gamemap[Mx][My - 1] = Gamemap[Mx][My - 2] = Gamemap[Mx][My - 3] = 57;
    //            }
    //            break;
    //        case 370: case 392:// 철퇴 움직임
    //            if (stState == ST_PLAY || stState == ST_FBook)
    //                SoundPlay(0, -1);//사운드
    //        case 351: case 352: case 353: case 354: case 355: case 356: case 357: case 358: case 359: case 360: case 361: case 362: case 363: case 364: case 365: case 366: case 367: case 368: case 369: // 철퇴 움직임
    //        case 371: case 372: case 373: case 374: case 375: case 376: case 377: case 378: case 379: case 380: case 381: case 382: case 383: case 384: case 385: case 386: case 387: case 388: case 389: case 390:
    //        case 391:  case 393: case 394:

    //            break;
    //        case 439: case 440: case 441: case 442: case 443: case 444: case 445: case 446: case 447: case 448: case 449: case 450: case 451: case 452: case 453: case 454: case 455: case 456:  // 펀치
    //            if (punchX > 0)
    //            {
    //                Tileimg(data.CostData[15 + punchDR][punchX], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG);
    //                if (data.CostData[15 + punchDR][punchX] == 439) punchX = 0;
    //                else punchX++;
    //            }
    //            else Tileimg(439, (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG);

    //            break;
    //        case 466: case 468: case 469: // 캐비넛 돈과보석이 있다

    //            Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG);
    //            if (HitCheck(npc[0].Pjx, (int)(i * Sy16 - ii), sizeXXYY(40, npc[0].PBig)) && HitCheck(npc[0].Pjy, ((int)(k * Sy16 - ii2) + TBimgY) + 64, 50)) // 열림
    //            {
    //                Gold(data.STGTim[1][0] * data.STGTim[1][Gstg]);  //
    //                if (Gamemap[Mx][My] == 466)
    //                {
    //                    Gamemap[Mx][My] = 467;

    //                    Jewel(data.STGTim[2][0] * data.STGTim[2][Gstg]);//
    //                }
    //                else if (Gamemap[Mx][My] == 469)
    //                {
    //                    Gamemap[Mx][My] = 191;
    //                    WeaponAni(25, 0, 0, 1);// 약병 플러스
    //                }
    //                else Gamemap[Mx][My] = 190;
    //            }

    //            break;
    //        case 398: case 399: case 400: case 401: case 402: case 403://나무
    //        case 473: case 474: case 475: case 476: // 나무
    //            Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + 32 + TBimgY), 0, 1, TBG);
    //            break;
    //        case 491: case 492:// 숲에서  돌
    //            Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + 32 + TBimgY) + 60, 0, 1, TBG);
    //            break;
    //        case 484: case 485: case 486: case 487: case 488: case 489: case 490: // 숲에서 앞에나오는 작은덤풀
    //            Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + 96 + TBimgY), 0, 1, TBG);
    //            break;
    //        case 500: // 주인공

    //            Gamemap[Mx][My] = 0;

    //            initPimg(0, 0, 0, 0, (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), AitemS[10], data.CostData[6][0], data.CostData[6][1], 0, 1.1, 31, 28, 1);//////캐릭터생성//// 3 , 13 , 31 , 41

    //            BGIT_y = 4160;

    //            if (stState == ST_PLAY || stState == ST_PLAY2)
    //                WeaponAni(27, 1, (int)(i * Sy16 - ii) - 50, ((int)(k * Sy16 - ii2) + TBimgY));//친구 생성

    //            if (Jumpjump == 2)
    //                initPimg(1, 26, 0, 0, (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 3000, 0, 0, 20, 1, 0, 0, 1509);////// 디펜용 국기 생성

    //            break;
    //        case 528: case 529:// 좀비 변신 단계
    //            break;
    //        case 501: //적
    //        case 502: case 503: case 504: case 505: case 506: case 507: case 508: case 509: case 510: case 511: case 512://적 약함  총
    //        case 513: case 514: case 515: case 516: case 517: case 518: case 519: case 520://맨손
    //        case 521: case 522: case 523: case 524: case 525: case 526: case 527: //좀비
    //        case 531: case 532: case 533: case 534: case 535: case 536: case 537: case 538://시민 좀비
    //        case 539: case 540: case 541: case 542: case 543: case 544: //보스들
    //        case 545: case 546: case 547: case 548: case 549: //몽둥이 약
    //        case 550: case 551: case 552: case 553: case 554: //몽둥이 강
    //        case 555: case 556: case 557: // 수류탄 약중강
    //        case 558: case 559: case 560: // 덩치 약중강
    //        case 561: case 562: case 563: // 괴물 약중강
    //        case 570: case 571: case 572:// 4발괴물
    //        case 573: case 574: case 575:// 주인공로봇
    //        case 576: case 577: case 578:// 작은로봇
    //        case 579: case 580: case 581:// 중간 로봇

    //            ComCreate(PC_Number, Gamemap[Mx][My], -Gamemap[Mx][My - 1], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY));
    //            //if ( Jumpjump == 0 )
    //            Gamemap[Mx][My] = Gamemap[Mx][My - 1] = 0;
    //            break;
    //        case 530://시민
    //            Gamemap[Mx][My] = 0;

    //            j = GRandom(8, 0);

    //            initPimg(1, 0, j + 1, !npc[0].Dir, (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), data.PCData[1][1], data.PCData[1][2], data.PCData[1][3], data.PCData[1][4], data.PCData[j + 31][5] / 10.00f, data.PCData[j + 31][6], data.PCData[j + 31][7], 1501);//// 시민
    //            break;
    //        case 700: //구급상자로 바뀌기
    //        {
    //            /*
    //            if(stState == ST_PLAY || stState == ST_FBook) {
    //                int ShowTime = 600;
    //                if(stState == ST_PLAY)
    //                    ShowTime = 600;
    //                if (GameTimer != 0 && GameTimer % ShowTime == 0) {
    //                    //캐릭터 충돌 위치와 같으면 제외
    //                    int Cx = (MapX+npc[0].Pjx)/Sy16, Cy = (MapY+npc[0].Pjy)/Sy16;
    //                    if((Jumpjump == 1 && (Cx-10 < Mx && Mx < Cx+10) && (Cy >= My && My > Cy-10)) || Jumpjump != 1)
    //                    {
    //                        if (!(HitCheck(npc[0].Pjx, (int) (i * Sy16 - ii), sizeXXYY(35, npc[0].PBig)) &&
    //                            HitCheck(npc[0].Pjy, ((int) (k * Sy16 - ii2) + TBimgY) + 140, 80)))
    //                        {
    //                            if(Mx*Sy16 > 3712 && Mx*Sy16 < 9600) {
    //                                //기존 열려있으면 제외
    //                                if (checkFirstAidKit(Mx, My) == 1) {
    //                                    DataStruct tData;
    //                                    tData.mx = Mx;
    //                                    tData.my = My;
    //                                    tData.OpenCheck = 0;
    //                                    tData.Timer = 0;

    //                                    vecFirstAidKit.push_back(tData);
    //                                }
    //                            }
    //                        }
    //                    }
    //                }
    //            }
    //            */
    //        }
    //        break;
    //        default:
    //            //  if ( Gamemap[Mx][My] > 5000 ) ;//
    //            //  else
    //            if (Gamemap[Mx][My] > 0)
    //                Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG);
    //        }
    //    }
    //}

    ////나타나는 구급상자
    //if (vecFirstAidKit.size() > 0)
    //{
    //    int max = vecFirstAidKit.size();
    //    int idx = random(0, max - 1);
    //    DataStruct t = vecFirstAidKit.at(idx);
    //    Gamemap[t.mx][t.my] = 243;
    //    Gamemap[t.mx][t.my - 1] = -60;
    //    m_listFirstAidKit.push_back(t);
    //    SoundPlay(37, -1);//사운드
    //}

    //for (k = 30; k > -5; k--) //타일 뒤로 가는 오브젝트들
    //{
    //    for (i = -13; i < 50; i++)
    //    {
    //        Mx = i + fori;
    //        My = k + fori2;
    //        switch (Gamemap[Mx][My])
    //        {
    //        case 102://도끼 오른쪽으로 날아가다 꽂히다 >>
    //            if (Gamemap[Mx + 1][My] == 0)
    //            {
    //                Gamemap[Mx][My] = 0;
    //                initRest(-GRandom(4, 0), 133, 5, 1, (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), GRandom(2, 2), 1, 0); // 도끼 튕겨나간다
    //            }
    //            else
    //                Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG);

    //            break;
    //        case 103://도끼 왼쪽으로 날아가다 꽂히다 <<

    //            if (Gamemap[Mx - 1][My] == 0)
    //            {
    //                Gamemap[Mx][My] = 0;
    //                initRest(-GRandom(4, 0), 133, 5, 0, (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), GRandom(2, 2), 1, 0); // 도끼 튕겨나간다
    //            }
    //            else
    //                Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii) + 96, ((int)(k * Sy16 - ii2) + TBimgY), 1, 1, TBG);
    //            break;
    //        case 493: case 494: case 495: case 496: // 헬기

    //            Gamemap[Mx][My]++;
    //            if (Gamemap[Mx][My] > 496) Gamemap[Mx][My] = 493;//if ( Gamemap[Mx][My] > 516 ) Gamemap[Mx][My] = 513;
    //            npc[99].alfa = 1;

    //            mmx = (int)(i * Sy16 - ii);
    //            mmy = ((int)(k * Sy16 - ii2) + TBimgY) + 32 + 96;

    //            if (Gamemap[Mx][My + 4] < 1 && Gamemap[Mx - 2][My + 4] < 1 && Gamemap[Mx + 2][My + 4] < 1)//
    //            {
    //                for (h = 4; h < 20; h++)
    //                {
    //                    if ((Gamemap[Mx][My + h] > 249 && Gamemap[Mx][My + h] < 258) || (Gamemap[Mx - 1][My + h] == 249 && Gamemap[Mx - 1][My + h] < 258) || (Gamemap[Mx + 1][My + h] > 249 && Gamemap[Mx + 1][My + h] < 258) || (Gamemap[Mx - 2][My + h] == 249 && Gamemap[Mx - 2][My + h] < 258) || (Gamemap[Mx + 2][My + h] > 249 && Gamemap[Mx + 2][My + h] < 258))// 바닥에 가시 헬기 폭파
    //                    {
    //                        mmy += ((h - 4) * 32);
    //                        LPimg(99, mmx, mmy, Gamemap[Mx][My] - 180, -Gamemap[Mx][My - 2], 255, 255, 255, 1, 0);
    //                        initRest(99, 120, 133, Gamemap[Mx][My - 2], mmx + GRandom(180, -90), mmy - GRandom(70, 0), 0, 0, 0); // 폭파
    //                        initRest(99, 120, 133, Gamemap[Mx][My - 2], mmx + GRandom(140, -70), mmy - GRandom(60, 0), 0, 0, 0); // 폭파
    //                        initRest(99, 120, 133, Gamemap[Mx][My - 2], mmx + GRandom(160, -80), mmy - GRandom(50, 0), 0, 0, 0); // 폭파

    //                        for (hh = 0; hh < 5; hh++)initRest(-GRandom(20, 12), 133, 323 + GRandom(5, 0), GRandom(2, 0), mmx + GRandom(130, -90), mmy - GRandom(40, 0), GRandom(8, 6), 1, 0); //쪼가리들
    //                        for (hh = 0; hh < 5; hh++)initRest(-GRandom(20, 12), 133, 323 + GRandom(5, 0), GRandom(2, 0), mmx + GRandom(190, -90), mmy - GRandom(80, 0), GRandom(8, 6), 1, 0); //쪼가리들
    //                        Gamemap[Mx][My] = Gamemap[Mx][My - 1] = Gamemap[Mx][My - 2] = 0;
    //                        h = 90;
    //                    }
    //                    else if (Gamemap[Mx][My + 1] == 0 && (MapNumBer(Gamemap[Mx][My + h], 1) > 49 || MapNumBer(Gamemap[Mx - 2][My + h], 1) > 49 || MapNumBer(Gamemap[Mx + 2][My + h], 1) > 49))
    //                    {
    //                        LPimg(99, mmx, mmy + 32, Gamemap[Mx][My] - 180, -Gamemap[Mx][My - 2], 255, 255, 255, 1, 0);
    //                        h -= 5;
    //                        hh = Gamemap[Mx][My];
    //                        mmx = Gamemap[Mx][My - 1];//Php
    //                        mmy = Gamemap[Mx][My - 2];//dir
    //                        Gamemap[Mx][My] = Gamemap[Mx][My - 1] = Gamemap[Mx][My - 2] = 0;
    //                        Gamemap[Mx][My + 1 + h] = hh;
    //                        Gamemap[Mx][My + h] = mmx;
    //                        Gamemap[Mx][My - 1 + h] = mmy;
    //                        h = 90;
    //                    }
    //                }
    //            }
    //            else
    //                LPimg(99, mmx, mmy, Gamemap[Mx][My] - 180, -Gamemap[Mx][My - 2], 255, 255, 255, 1, 0);

    //            if (-Gamemap[Mx][My - 2] == 1)
    //            {
    //                if (npc[0].OPR < 65 && npc[0].weapon < 21 && HitCheck(npc[0].Pjx + 30, (int)(i * Sy16 - ii), sizeXXYY(100, npc[0].PBig)) && HitCheck(npc[0].Pjy, ((int)(k * Sy16 - ii2) + TBimgY) + 64 + 96, 60)) // 열림
    //                {
    //                    eunmX = Mx;
    //                    eunmY = My;
    //                    Hin = 2;
    //                    if (npc[0].weapon < 19)
    //                        GUIImg_drawImage(134, mmx - 70, mmy - 190 - HPpinit, 0, 0, 0, 1.2, 0, 1);// V
    //                }
    //                else Hin = 0;
    //            }
    //            else
    //            {
    //                if (npc[0].OPR < 65 && npc[0].weapon < 21 && HitCheck(npc[0].Pjx - 30, (int)(i * Sy16 - ii), sizeXXYY(100, npc[0].PBig)) && HitCheck(npc[0].Pjy, ((int)(k * Sy16 - ii2) + TBimgY) + 64 + 96, 60)) // 열림
    //                {
    //                    eunmX = Mx;
    //                    eunmY = My;
    //                    Hin = 2;
    //                    if (npc[0].weapon < 19)
    //                        GUIImg_drawImage(134, mmx + 20, mmy - 190 - HPpinit, 0, 0, 0, 1.2, 0, 1);// V
    //                }
    //                else Hin = 0;
    //            }
    //            break;
    //        }
    //    }
    //}

    //// LOGD(" GPlayloop 4 : %d   " , i  );
    // //if(!(stState == ST_PAUSE || stState == ST_FIRSTAIDKIT || stState == ST_DRONEBONUS))
    //{
    //    for (i = 0; i < impsu; i++) {
    //        if (Pc_Rest[i].Php > 0 && Pc_Rest[i].Pty < 100) {
    //            if (OBJimg(i, Pc_Rest[i].Pjx, Pc_Rest[i].Pjy, Pc_Rest[i].ani, Pc_Rest[i].Dir,
    //                Pc_Rest[i].R, Pc_Rest[i].G, Pc_Rest[i].B, Pc_Rest[i].PBig) > 0)
    //                OBJChexk(i, Pc_Rest[i].ani, Pc_Rest[i].Pjx, Pc_Rest[i].Pjy, Pc_Rest[i].Dir); //오브젝트 이미지
    //            if (Pc_Rest[i].Php == 1)
    //                Pc_Rest[i].Php = 0;
    //        }
    //    }

    //    // LOGD(" GPlayloop 5 : %d   " , i  );

    //    if (npc[0].OPR == 30 || npc[0].OPR == 31 || npc[0].weapon == 22) {
    //        for (i = pomsu; i > -1; i--) {
    //            if (npc[i].Php > 0 && npc[i].OPR != 39) {
    //                //   LOGD(" 1111 npc[%d].ani = %d   " , i  , npc[i].ani  );
    //                if (LPimg(i, npc[i].Pjx, npc[i].Pjy, npc[i].ani, npc[i].Dir, npc[i].R, npc[i].G, npc[i].B, npc[i].PBig, npc[i].Gloves) > 0)
    //                    PXYChexk(i, npc[i].ani, npc[i].Pjx, npc[i].Pjy, npc[i].Dir);//타격체크
    //            }
    //        }
    //        for (i = pomsu; i >= 0; i--)//PC_Number
    //        {
    //            if (npc[i].OPR == 39 && npc[i].Php > 0) {
    //                //    LOGD(" 2222npc[%d].ani = %d   " , i  , npc[i].ani  );
    //                if (LPimg(i, npc[i].Pjx, npc[i].Pjy, npc[i].ani, npc[i].Dir, npc[i].R, npc[i].G, npc[i].B, npc[i].PBig, npc[i].Gloves) > 0)
    //                    PXYChexk(i, npc[i].ani, npc[i].Pjx, npc[i].Pjy, npc[i].Dir);//타격체크
    //            }
    //        }
    //    }
    //    else {
    //        for (i = pomsu; i > -1; i--) {
    //            if (npc[i].Php > 0 && npc[i].Pjy <= npc[0].Pjy + 30)// && npc[i].OPR != 39 )
    //            {
    //                //  LOGD(" 333npc[%d].ani = %d   " , i  , npc[i].ani  );

    //                if (LPimg(i, npc[i].Pjx, npc[i].Pjy, npc[i].ani, npc[i].Dir, npc[i].R, npc[i].G, npc[i].B, npc[i].PBig, npc[i].Gloves) > 0)
    //                    PXYChexk(i, npc[i].ani, npc[i].Pjx, npc[i].Pjy, npc[i].Dir);//타격체크
    //            }
    //        }

    //        for (i = 1; i < pomsu; i++) {
    //            if (npc[i].Php > 0 && (npc[i].Pjy > npc[0].Pjy + 30 || npc[i].OPR == 39))//&& npc[i].OPR != 39 )
    //            {
    //                //  LOGD(" 444npc[%d].ani = %d   " , i  , npc[i].ani  );
    //                if (LPimg(i, npc[i].Pjx, npc[i].Pjy, npc[i].ani, npc[i].Dir, npc[i].R, npc[i].G, npc[i].B, npc[i].PBig, npc[i].Gloves) > 0)
    //                    PXYChexk(i, npc[i].ani, npc[i].Pjx, npc[i].Pjy, npc[i].Dir);//타격체크
    //            }
    //        }
    //    }
    //}

    //for (k = 30; k > -4; k--)//for ( k = 30 ;  k > -3 ; k-- )
    //{
    //    for (i = -7; i < 44; i++)//for(i = -7; i < 44 ; i++ )
    //    {
    //        Mx = i + fori;
    //        My = k + fori2;
    //        switch (Gamemap[Mx][My])
    //        {
    //        case 0:
    //            break;
    //        case 89: case 90: case 91://옥상에 난간
    //            Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), (int)(k * Sy16 - ii2) + 64 + TBimgY, 0, 1, TBG);// 맵 이미지
    //            break;
    //        case 94: case 95: case 96: // 톨로문
    //            Tileimg(101, (int)(i * Sy16 - ii), (int)(k * Sy16 - ii2) + TBimgY, 0, 1, TBG);// 맵 이미지
    //            break;
    //        case 158:// 가로등빛
    //            if (npc[0].weapon == 22 && HitCheck(npc[0].Pjx, (int)(i * Sy16 - ii), 200) && HitCheck(npc[0].Pjy - 60, ((int)(k * Sy16 - ii2) + TBimgY), 220));
    //            else Tileimg(244, (int)(i * Sy16 - ii), (int)(k * Sy16 - ii2) + TBimgY, 0, 1, TBG);// 맵 이미지
    //            break;
    //        case 211:// 영사기
    //            Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), (int)(k * Sy16 - ii2) + TBimgY, 0, 1, TBG);// 맵 이미지
    //            break;
    //        case 208:// 전등 불빛이미지 출력
    //            Tileimg(182, (int)(i * Sy16 - ii), (int)(k * Sy16 - ii2) + TBimgY, 0, 1, TBG);// 맵 이미지
    //            break;
    //        case 229://소변보는곳
    //            //     if (  npc[0].OPR < 30 && npc[0].weapon < 21 && HitCheck( npc[0].Pjx , (int)(i*Sy16-ii)+20 , sizeXXYY( 10  , npc[0].PBig  )  ) && HitCheck( npc[0].Pjy-90 , ((int)(k*Sy16-ii2)+TBimgY) , 60 )  )  Din = 2;// 쉬보기
    //            //     else  Din = 0;/////// 닫힘
    //            break;
    //        case 250: case 251: case 252: case 253: case 254: case 255: case 256: case 257: //철못 나오는거
    //            //Tileimg( Gamemap[Mx][My]+157  , (int)(i*Sy16-ii) , ((int)(k*Sy16-ii2)+TBimgY)+64  , 0 , 1 , TBG );
    //            AttTileimg(Gamemap[Mx][My] + 157, (int)(i * Sy16 - ii), ((int)(k * Sy16 - ii2) + TBimgY), 0, 1, TBG, Mx, My);
    //            break;
    //        case 351: case 352: case 353: case 354: case 355: case 356: case 357: case 358: case 359: case 360: case 361: case 362: case 363:// 철퇴 움직임   <<<
    //        case 386: case 387: case 388: case 389: case 390: case 391: case 392: case 393: case 394: // <<<<

    //        case 364: case 365: case 366: case 367: case 368: case 369: case 370: case 371: case 372: case 373: case 374: case 375: case 376: case 377: case 378: case 379: case 380: case 381: case 382: case 383: case 384: case 385:// >>>

    //            AttTileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), (int)(k * Sy16 - ii2) + TBimgY, 0, 1, TBG, Mx, My);
    //            if (Gamemap[Mx][My] == 394) Gamemap[Mx][My] = 351;
    //            else Gamemap[Mx][My]++;
    //            break;
    //        case 397: //case 477: // 숲에서 바닥 풀
    //            Tileimg(Gamemap[Mx][My], (int)(i * Sy16 - ii), (int)(k * Sy16 - ii2) + TBimgY, 0, 1, TBG);// 맵 이미지
    //            break;
    //        case 436:// 끝에 화살표
    //            if (DComSoo == 0) // 스테이지 끝
    //            {
    //                if (npc[0].Pjx > (D_H2 + D_H2 - 100) && stState == ST_PLAY) MenutSet(4, 0, 0, 0);
    //                GUIImg_drawImage(35, D_H - 80 - Endstg, 130, 255, 255, 255, 1, 0, 1);//화살표
    //                if (Endstg > 16) Endstg = 0;
    //                else Endstg += 4;
    //            }
    //            break;
    //        case 438:// 시작 화살표

    //            GUIImg_drawImage(35, D_H - 80 - Endstg, 130, 255, 255, 255, 1, 0, 1);//화살표
    //            if (Endstg > 16) Endstg = 0;
    //            else Endstg += 4;

    //            break;
    //            //   default:

    //            //     if ( Gamemap[Mx][My] > 5000 ) ImgNumber( 3 , 20 , Gamemap[Mx][My]-5000 , 300 , 100 , 255 , 255 , 255 , 1 , 1 );//
    //        }
    //    }
    //}

    ////if(!(stState == ST_PAUSE || stState == ST_FIRSTAIDKIT || stState == ST_DRONEBONUS))
    //{
    //    for (i = 0; i < impsu; i++) {
    //        if (Pc_Rest[i].Php > 0 && Pc_Rest[i].Pty > 99)//여기 - 파편 날리거나 떨어져 있으면 속도 저하.. 그리기에 과부하라는건데..
    //        {
    //            if (OBJimg(i, Pc_Rest[i].Pjx, Pc_Rest[i].Pjy, Pc_Rest[i].ani, Pc_Rest[i].Dir,
    //                Pc_Rest[i].R, Pc_Rest[i].G, Pc_Rest[i].B, Pc_Rest[i].PBig) > 0)
    //                OBJChexk(i, Pc_Rest[i].ani, Pc_Rest[i].Pjx, Pc_Rest[i].Pjy, Pc_Rest[i].Dir); //오브젝트 이미지
    //        }
    //    }
    //}

    //TileImg_rotateImage(  325 , 100 , 0 , 0 , 100  , 1 , 0 , 1 , 1 , 200 ,300 , 0 );

    //TileImg_rotateImage(  325 , 200 , 0 , 0 , 200  , 1 , 0 , 1 , 1 , 200 ,300 , 0 );

    //Tileimg( 352  , 200, 300  , 0 , 1 , TBG );// 맵 이미지


   // AttTileimg( 352  , 400 , 300  , 0 , 1 , TBG  , Mx , My  );
}
