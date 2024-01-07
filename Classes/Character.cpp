#include "Character.h"

// 초기화 함수
bool Character::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    // 플레이어 스프라이트를 추가하는 코드 등을 추가할 수 있습니다.

    return true;
}

//// 플레이어의 움직임 처리 함수
//void Character::move(cocos2d::Vec2 direction)
//{
//    // 플레이어를 주어진 방향으로 이동시키는 코드를 추가할 수 있습니다.
//}

