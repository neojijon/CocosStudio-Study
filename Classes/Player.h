#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "cocos2d.h"
#include "Character.h"
USING_NS_CC;

class Player : public Character
{
public :	
	CREATE_FUNC(Player);
    
    Player();

public :
    // 초기화 함수
    virtual bool init();

    // 플레이어의 움직임 처리 함수
    void move(cocos2d::Vec2 direction);



    //virtual void onEnter() override;



};

#endif // 

