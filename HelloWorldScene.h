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
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	cocos2d::PhysicsWorld *world;
	void setPhysicWorld(cocos2d::PhysicsWorld *m_world)
	{
		world = m_world;
	}

};

#endif // __HELLOWORLD_SCENE_H__
