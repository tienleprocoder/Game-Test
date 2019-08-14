#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameOver.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);//set khung duong vien
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
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
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto background = Sprite::create("anhnen1.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background);
	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 5);
	edgeBody->setCollisionBitmask(1);
	edgeBody->setContactTestBitmask(true);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(edgeBody);
	addChild(edgeNode);

	bird = Sprite::create("bird.png");
	bird->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto birdPhysic = PhysicsBody::createBox(bird->getContentSize());

	birdPhysic->setContactTestBitmask(true);
	birdPhysic->setCollisionBitmask(4);
	bird->setPhysicsBody(birdPhysic);

	addChild(bird);
	__String *tempScore = __String::createWithFormat("%i", score);//ep kieu 
	label = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", visibleSize.height*0.1); //chon cho no 1 font chu ,va size cua font chu
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.8));
	label->setColor(Color3B::GRAY);
	addChild(label);


	this->scheduleUpdate();
	this->schedule(schedule_selector(HelloWorld::CreatePipe), 0.005*visibleSize.width);

	// dang ki su kien lang nghe khi touch vao man hinh
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::OnContactBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	return true;
}
void HelloWorld::CreatePipe(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto topPipe = Sprite::create("top1.png");
	auto bottomPipe = Sprite::create("bottom.png");

	auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());
	topPipeBody->setCollisionBitmask(2);
	topPipeBody->setContactTestBitmask(true);
	topPipeBody->setDynamic(false);// khong chiu tac dong cua moi truong vat ly
	topPipe->setPhysicsBody(topPipeBody);

	auto bottomPipeBody = PhysicsBody::createBox(bottomPipe->getContentSize());
	bottomPipeBody->setCollisionBitmask(2);
	bottomPipeBody->setContactTestBitmask(true);
	bottomPipeBody->setDynamic(false);
	bottomPipe->setPhysicsBody(bottomPipeBody);

	auto random = CCRANDOM_0_1();// tao 1 bien random ,random tu 0 den 1 kieu so thuc
	if (random < 0.35) // set ti le nho nhat cua top.no se chiem 0.35 thuc 35% man hinh .neu nho hon van gan bang 0.35
	{
		random = 0.35;
	}
	else
		if (random > 0.65) // set ti le lon nhat cua top.png
		{
			random = 0.65;
		}
	auto topPipePosition = (visibleSize.height*random) + (topPipe->getContentSize().height *0.5);// CHIEU CAO MAN HINH

	topPipe->setPosition(Vec2(visibleSize.width + topPipe->getContentSize().width, topPipePosition));
	bottomPipe->setPosition(Vec2(topPipe->getPositionX(), topPipePosition - ((Sprite::create("bird.png")->getContentSize().height * 5))
		- topPipe->getContentSize().height));// VI TRI BOTTOMPIPE = VI TRI TOP THEO TRUC X, VA BANG CHIEU CAO MAN HINH - KHOANG TRONG (KT CHIM x5 LAN)- chieu cao cua topPipe
	addChild(topPipe);
	addChild(bottomPipe);

	// tao chuyen dong cho ong nuoc
	auto topMove = MoveBy::create(0.01*visibleSize.width, Vec2(-visibleSize.width*1.5, 0));
	auto bottomMove = MoveBy::create(0.01*visibleSize.width, Vec2(-visibleSize.width*1.5, 0));
	topPipe->runAction(topMove);
	bottomPipe->runAction(bottomMove);


	auto PointNode = Node::create();
	PointNode->setPosition(Vec2(topPipe->getPositionX(), topPipe->getPositionY() - topPipe->getContentSize().height / 2
		- (Sprite::create("bird.png")->getContentSize().height * 5) / 2));

	auto PointBody = PhysicsBody::createBox(Size(1, (Sprite::create("bird.png")->getContentSize().height * 5)));// tao moi truong vat ly cho pointnode
	PointBody->setDynamic(false);// ko chiu anh huong mt vat ly
	PointBody->setContactTestBitmask(true); //set va cham
	PointBody->setCollisionBitmask(3);//dat ten cho moi truong vat ly
	PointNode->setPhysicsBody(PointBody);//add bien moi truong vat ly vao doi tuong

	auto NodeMove = MoveBy::create(0.01*visibleSize.width, Vec2(-visibleSize.width*1.5, 0));//di chuyen theo ong nuoc
	PointNode->runAction(NodeMove);// cho hanh dong cho point
	addChild(PointNode);
}
void HelloWorld::update(float dt)// set trang thai cho conchim
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	if (isFalling == true)
	{
		bird->setPositionX(visibleSize.width / 2);
		bird->setPositionY(bird->getPositionY() - visibleSize.height*0.015);
	}
	else
	{
		bird->setPositionX(visibleSize.width / 2);
		bird->setPositionY(bird->getPositionY() + visibleSize.height*0.015);
	}
}
void HelloWorld::stopFly(float dt)
{
	isFalling = true;
}
bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	isFalling = false;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/touch.mp3");
	this->scheduleOnce(schedule_selector(HelloWorld::stopFly), 0.25);// khi touch 0.25s thi chim roi xuong
	return true;
}
bool HelloWorld::OnContactBegan(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	if (a->getCollisionBitmask() == 4 && b->getCollisionBitmask() == 3 ||
		a->getCollisionBitmask() == 3 && b->getCollisionBitmask() == 4)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/point.mp3");
		++score;
		__String *tempScore = __String::createWithFormat("%i", score);//tao label moi  ep kieu sang int
		label->setString(tempScore->getCString());//set cho label moi 
	}
	else
	{
		if (a->getCollisionBitmask() == 4 && b->getCollisionBitmask() == 2 ||
			a->getCollisionBitmask() == 2 && b->getCollisionBitmask ()== 4)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/hit.mp3");
			auto sqe = GameOver::createScene();
			Director::getInstance()->replaceScene(sqe);
		}
	}
	return true;
}