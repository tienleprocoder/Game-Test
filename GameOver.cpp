#include "GameOver.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
	auto scene = Scene::create(); 
	auto layer = GameOver::create();
	scene->addChild(layer);
	return scene;
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto sprite = Sprite::create("gameover.png");
	sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(sprite);
return true;
}
