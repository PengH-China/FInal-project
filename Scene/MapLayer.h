#ifndef __MAPLAYER_H__
#define __MAPLAYER_H__

#include "cocos2d.h"
#include "GlobalPara/GlobalParameter.h"
#include "Role/Hero.h"
#include"Const/Const.h"
#include "Monster/MonsterGroup.h"
#include "Role/HeroUI.h"
#include "Item/TreasureBox.h"



using namespace cocos2d;
class MapLayer :public cocos2d::Layer 
{
private:
	TMXTiledMap* m_pMap=nullptr;
	//TMXLayer* meta;

	float mapHeight, mapWidth;
	float tileHeight, tileWidth;
	clock_t m_lastShotTime;

	//Character* hunter;

	////add map information
	//MapInformation save_map;
	////add enemies

	//const int m_enemy_number = 10;
	//const int m_weapon_number = 20;
	//const int m_bandage_number = 30;
	//const int m_ammunition_number = 30;
	//clock_t t1 = clock(), t2;

	////add items
	//std::vector<Character*> m_enemy;
	//std::vector<Weapon*> weapons;
	//std::vector<Bandage*> m_bandage;
	//std::vector<Ammunition*> m_ammunition;

	//std::array <Bullet*, 60> bullets;

public:

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

	//load bakground picture
	//void loadBackgroundMap(cocos2d::Ref* pSender);
	//init m_map and m_map
	//back to menu
	void menuBackCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	//void addPlayerAndUI();

	void createBarrier();

	void addPlayer();
	bool addMonster();
	virtual void updateMonster(float dt);
	Monster* createMonsterRand();
	//void addBox();


	bool onContactBegin(PhysicsContact& contact);

	//Êó±êÊÂ¼þ
	bool onMouseDown(EventMouse* event);
	void onMouseUp(EventMouse* event);
	void onMouseMove(EventMouse* event);


	
};
#endif // !__MAPLAYER_H__