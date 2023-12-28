#include "ParallaxDemo.h"


USING_NS_CC;
using namespace ui;
using namespace cocostudio;

// tilemaps resource
static const char s_TilesPng[] = "TileMaps/tiles.png";
static const char s_LevelMapTga[] = "TileMaps/levelmap.tga";
static const char s_Power[] = "Images/powered.png";
static const char s_back[] = "Images/background.png";


Scene* ParallaxDemo::createScene()
{
    return ParallaxDemo::create();
}


bool ParallaxDemo::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    // Top Layer, a simple image
    //auto cocosImage = Sprite::create(s_Power);
    //// scale the image (optional)
    ////cocosImage->setScale(2.5f);
    //// change the transform anchor point to 0,0 (optional)
    //cocosImage->setAnchorPoint(Vec2(0, 0));

    // Middle layer: a Tile map atlas
    auto tilemap = TileMapAtlas::create(s_TilesPng, s_LevelMapTga, 16, 16);
    tilemap->releaseMap();

    // change the transform anchor to 0,0 (optional)
    tilemap->setAnchorPoint(Vec2(0, 0));

    // Anti Aliased images
    tilemap->getTexture()->setAntiAliasTexParameters();


    // background layer: another image
    auto background = Sprite::create(s_back);
    // scale the image (optional)
    background->setScale(1.5f);
    // change the transform anchor point (optional)
    background->setAnchorPoint(Vec2(0, 0));


    // create a void node, a parent node
    auto voidNode = ParallaxNode::create();

    // NOW add the 3 layers to the 'void' node

    // background image is moved at a ratio of 0.4x, 0.5y
    voidNode->addChild(background, -1, Vec2(0.4f, 0.5f), Vec2::ZERO);

    // tiles are moved at a ratio of 2.2x, 1.0y
    voidNode->addChild(tilemap, 1, Vec2(2.2f, 1.0f), Vec2(0, -200));

    // top image is moved at a ratio of 3.0x, 2.5y
    //voidNode->addChild(cocosImage, 2, Vec2(3.0f, 2.5f), Vec2(200, 800));


    // now create some actions that will move the 'void' node
    // and the children of the 'void' node will move at different
    // speed, thus, simulation the 3D environment
    auto goUp = MoveBy::create(4, Vec2(0, -500));
    auto goDown = goUp->reverse();
    auto go = MoveBy::create(8, Vec2(-1000, 0));
    auto goBack = go->reverse();
    auto seq = Sequence::create(goUp, go, goDown, goBack, nullptr);

    voidNode->runAction((RepeatForever::create(seq)));

    addChild(voidNode);

    return true;
}