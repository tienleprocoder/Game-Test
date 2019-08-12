#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);//set khung duong vien
	auto layer = HelloWorld::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 5);
	edgeBody->setCollisionBitmask(1);
	edgeBody->setContactTestBitmask(true);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(edgeBody);
	addChild(edgeNode);
	this->schedule( schedule_selector (HelloWorld::CreatePipe), 0.005*visibleSize.width);
    return true;
}
void HelloWorld::CreatePipe(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto topPipe = Sprite::create("top.png");
	auto bottomPipe = Sprite::create("bottom.png");

	auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());
	topPipeBody->setCollisionBitmask(2);
	topPipeBody->setContactTestBitmask(true);

	auto bottomPipeBody = PhysicsBody::createBox(bottomPipe->getContentSize());
	bottomPipeBody->setCollisionBitmask(2);
	bottomPipeBody->setContactTestBitmask(true);


	auto random = CCRANDOM_0_1();// tao 1 bien random ,random tu 0 den 1 kieu so thuc
	if (random < 0,35) // set ti le nho nhat cua top.no se chiem 0.35 thuc 35% man hinh .neu nho hon van gan bang 0.35
	{
		random = 0,35;
	}
	else
		if (random > 0,65) // set ti le lon nhat cua top.png
		{
			random = 0,65;
		}
	auto topPipePosition = visibleSize.height*random + topPipe->getContentSize().height / 2;
	topPipe->setPosition(Vec2(visibleSize.width + topPipe->getContentSize().width, topPipePosition));
	bottomPipe->setPosition(Vec2(topPipe->getPositionX(), topPipePosition - (( Sprite::create("bird.png")->getContentSize().height * 5)) - topPipe->getContentSize().height));
	addChild(topPipe);
	addChild(bottomPipe);

	// tao chuyen dong cho ong nuoc
	auto topMove = MoveBy::create(0.01*visibleSize.width, Vec2(-visibleSize.width*1.5, 0 ));
	auto bottomMove = MoveBy::create(0.01*visibleSize.width, Vec2(-visibleSize.width*1.5, 0));
	topPipe->runAction(topMove);
	bottomPipe->runAction(bottomMove);

 




	





}
