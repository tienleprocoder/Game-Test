#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void CreatePipe(float);
	void update(float);
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	bool OnContactBegan(cocos2d::PhysicsContact&contact);
	void stopFly(float);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	cocos2d::Sprite *bird;
	cocos2d::Label *label;
	int score = 0;
	cocos2d::PhysicsWorld *world;
	void setPhysicWorld(cocos2d::PhysicsWorld *m_world)
	{
		world = m_world;
	}
	  
	bool isFalling = true;
};

#endif // __HELLOWORLD_SCENE_H__
