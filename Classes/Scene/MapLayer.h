#ifndef __MAPLAYER_H__
#define __MAPLAYER_H__

#include "cocos2d.h"
#include "GlobalPara/GlobalParameter.h"
#include "Role/Hero.h"
#include"Const/Const.h"
#include "Monster/MonsterGroup.h"
#include "Role/HeroUI.h"
#include "Item/TreasureBox.h"
#include "Role/AIHero.h"


using namespace cocos2d;
class MapLayer :public cocos2d::Layer 
{
private:
	TMXTiledMap* m_pMap=nullptr;
	//TMXLayer* meta;

	float mapHeight, mapWidth;
	float tileHeight, tileWidth;
	clock_t m_lastShotTime;


public:

	void addAIHero();
	virtual bool init();
	//Scene* createScene(TMXTiledMap* map);
	//static MapLayer* create(TMXTiledMap* map);
	CREATE_FUNC(MapLayer);
	virtual void updatePosition(float dt);
	void setViewPointCenter(Point position);
	

	//bool MapLayer::perspectiveJump(float x, float y);

	//BattleScene* createWithPhysics();

	void onEnter();

	void addEdge();

	void randomAddBox();
	void addBox();

	
	//back to menu
	void menuBackCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	//void addPlayerAndUI();

	void createBarrier();

	void addPlayer();
	bool addMonster();
	virtual void updateMonster(float dt);
	Monster* createMonsterRand();

	bool onContactBegin(PhysicsContact& contact);

	//Êó±êÊÂ¼þ
	bool onMouseDown(EventMouse* event);

};
#endif // !__MAPLAYER_H__