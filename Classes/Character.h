#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
USING_NS_CC;

class Character : public Sprite
{
public:
    CREATE_FUNC(Character);
    // 초기화 함수
    virtual bool init();

    // 플레이어의 움직임 처리 함수
    //void move(cocos2d::Vec2 direction);

};

#endif // 

