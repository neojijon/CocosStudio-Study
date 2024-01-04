#ifndef __KSPRITE_H__
#define __KSPRITE_H__


#include "cocos2d.h"
#include "kConst.h"


USING_NS_CC;

extern int zorder;
class kSprite : public Sprite {
public:
    virtual bool init() override;
    CREATE_FUNC(kSprite);
    static kSprite* create(const std::string& filename);
    static kSprite* createWithSpriteFrame(SpriteFrame *spriteFrame);
    static kSprite* createWithSpriteFrameName(const std::string& spriteFrameName);
    static kSprite* createWithTexture(Texture2D *texture);
    virtual void setVisible(bool bVisible) override;

    int frm;
    cocos2d::Rect ori;

    float getWidth() { return ori.size.width; }//getContentSize().width
    float getHeight() { return ori.size.height; }//getContentSize().height

    void drawPos(Vec2 pos);
    void drawPos(Vec2 pos, Color4F color);
    void drawPos(Vec2 pos, int img_d, float img_s);
    void drawPos(Vec2 pos, int img_d, int drawType, float img_s);
    void drawPos(Vec2 pos, Color4F color, int img_d, float img_s);
    void drawPos(Vec2 pos, Color4F color, int drawType);
    void drawPos(Vec2 pos, int img_d, float img_s, int drawType);
    void drawPos(Vec2 pos, Color4F color, int img_d, float img_s, int drawType, int cx, int cy, float rotate);
    
    void convertScreenCoord(Vec2& pos);
    void convertScreenCoord(float& x, float& y);

    void drawPos(Vec2 pos, int tx, int ty, int tw, int th);
    void drawPos(Vec2 pos, int tx, int ty, int tw, int th, float img_s);
    void drawPos(Vec2 pos, int tx, int ty, int tw, int th, int drawType);
    void drawPos(Vec2 pos, int tx, int ty, int tw, int th, float img_s, int drawType);
    void drawPos(Vec2 pos, int tx, int ty, int tw, int th, Color4F color, int img_d, float img_s);
    void drawPos(Vec2 pos, int tx, int ty, int tw, int th, Color4F color, int img_d, float img_s, int drawType, int cx, int cy, float rotate);

    //void drawRect(Rect rect);
    //void drawRect(Rect rect, Color4F color);
};

#endif /* defined(__KSPRITE_H__) */
