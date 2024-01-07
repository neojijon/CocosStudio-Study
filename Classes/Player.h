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

    // 애니메이션 실행 함수
    void playAnimation(const std::string& animationName);

    //virtual void onEnter() override;


private:
    // 애니메이션 리스트
    std::map<std::string, cocos2d::Animation*> animationList;

    // 현재 플레이 중인 애니메이션 이름
    std::string currentAnimation;

    // 애니메이션을 생성하고 애니메이션 리스트에 추가하는 함수
    void createAnimation(const std::string& animationName, const std::string& fileName, int frameCount, float delay);

};

#endif // 

