/**
*@file BattleScene.cpp
*@author 张子涵 方新宇
*@date 6/5/2021
*/


#include "cocos2d.h"
#include "BattleScene.h"
#include"Const/Const.h"
#include "Hero.h"
#include"Soldier.h"
#include"Role.h"


using namespace cocos2d;

cocos2d::Scene* BattleScene::createScene()
{

	//auto scene = BattleScene::createWithPhysics();
	//log("problem1!?");
	//auto layer = BattleScene::create();
	//log("scene address %p\n", &scene);
	//log("layer address %p\n", &layer);

	////scene->addChild(layer);
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
	////cocos2d::Ref * pSender=;
	//return scene;
	return BattleScene::create();
}

//BattleScene* BattleScene::create()
//{
//	BattleScene* pRet = new(std::nothrow) BattleScene();
//	if (pRet)
//	{
//		if (pRet->init())
//		{
//			pRet->autorelease();
//			return pRet;
//		}
//	}
//	//else
//	//{
//		delete pRet;
//		pRet = nullptr;
//		return nullptr;
//	//}
//}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool BattleScene::init()
{
	log("problem2!?");
	if (!Scene::init())
	{
		return false;
	}
	
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	//背景图片 background picture
	BattleScene::loadBackgroundMap(this);
	BattleScene::setGidTag();
	/*BattleScene::createWithPhysics();
	BattleScene::getPhysicsWorld()->setGravity(Vec2::ZERO);*/
	//BattleScene::createBarrier();
	BattleScene::addPlayer();
	return true;
}

void BattleScene::loadBackgroundMap(cocos2d::Ref* pSender)
{
	MenuItem* item = (MenuItem*)pSender;
	log("Touch Background MenuItem %p", item);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	TMXTiledMap* battleMap = TMXTiledMap::create("map1.tmx");
	BattleScene::setTiledMap(battleMap);
	battleMap->setAnchorPoint(Vec2(0, 0));
	//battleMap->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height / 2));
	this->addChild(battleMap);
}




void BattleScene::menuBackCallback(cocos2d::Ref* pSender)
{
	MenuItem* item = (MenuItem*)pSender;
	log("Touch back MenuItem %p", item);

	Director::getInstance()->popScene();

}

void BattleScene::setTiledMap(TMXTiledMap* map)
{
	m_pMap = map;
	/* 保存meta图层的引用 */
	this->m_pMeta = m_pMap->getLayer("meta");
	this->m_pMeta->setVisible(false);
}
void BattleScene::setGidTag()
{
	Size sizeOfMap=m_pMap->getMapSize();
	log("sizeOfMap:%f %f", sizeOfMap.width-1, sizeOfMap.height-1);
	for (int y = 0; y <= sizeOfMap.height - 1; y++) {
		for (int x = 0; x <= sizeOfMap.width - 1; x++) {
			int tiledGid = m_pMeta->getTileGIDAt(Vec2(x,y));
			/* 不为0，代表存在这个格子 */
			if (tiledGid != 0) {
				/*
				获取该地图格子的所有属性，目前我们只有一个Collidable属性
				格子是属于meta层的，但同时也是属于整个地图的，所以在获取格子的所有属性
				时，通过格子唯一标识在地图中取得
				*/
				Value properties = m_pMap->getPropertiesForGID(tiledGid);

				ValueMap propertiesMap = properties.asValueMap();

				if (propertiesMap.find("Collidable") != propertiesMap.end())
				{
					/* 取得格子的Collidable属性值 */
					Value prop = propertiesMap.at("Collidable");
					if (prop.asString().compare("true") == 0)
					{
						Sprite* gidSprite = m_pMeta->getTileAt(Vec2(x, y));
						gidSprite->setName(QS::Name::kGidTag);
						log("set (%d,%d) gid as barrier", x, y);
					}
					
		}
	}
	
			///* 判断Collidable属性是否为true，如果是，则不让玩家移动 */
			//if (prop.asString().compare("true") == 0 && isJumping == false) {
			//	isJumping = true;

			//	auto jumpBy = JumpBy::create(0.5f, Point(-100, 0), 80, 1);
			//	CallFunc* callfunc = CallFunc::create([&]() {
			//		/* 恢复状态 */
			//		isJumping = false;
			//		});

			//	/* 执行动作，碰撞到障碍物时的反弹效果 */
			//	auto actions = Sequence::create(jumpBy, callfunc, NULL);
			//	this->runAction(actions);
			}
		}
        
}
void BattleScene::addPlayer(){
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	PolygonInfo fig;
	static Hero* hero = Soldier::create();


	fig = AutoPolygon::generatePolygon(QS::kSoldier1,
		Rect(0, 0, QS::kSoldierWidth, QS::kSoldierHeight));

	Sprite* heroSprite = Sprite::create(fig);

	if (heroSprite == nullptr)
	{
		log("hero picture not found");
	}
	else
	{
		log("begin init hero");

		hero->bindSprite(heroSprite);
		//hero->genePhysicsBody();
		hero->setPosition(Point(Vec2(visibleSize.width / 2 + origin.x,
			visibleSize.height / 2 + origin.y)));
		this->addChild(hero, 0, QS::Name::kHero);
		log("end init hero");

		//hero->rest();
	   // BulletLayer* bulletLayer = BulletLayer::create();
	  //  bulletLayer->retain();
		//bulletLayer->bindHero(hero);
	   // this->addChild(bulletLayer, 10, sk::tag::kBulletLayer);

		auto keyBoardListenerHero = EventListenerKeyboard::create();
		keyBoardListenerHero->onKeyPressed = CC_CALLBACK_2(Hero::onKeyPressed, hero);
		keyBoardListenerHero->onKeyReleased = CC_CALLBACK_2(Hero::onKeyReleased, hero);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListenerHero, this);
		//this->keyBoardListenerOne = keyBoardListenerHero;


	}
	//hero->retain();
}

void BattleScene::createBarrier()
{
	auto group = m_pMap->getObjectGroup("barrier-wall");
	ValueVector barrierObjects = group->getObjects();

	for (auto barrier : barrierObjects)
	{
		ValueMap& dict = barrier.asValueMap();
		float x = dict["x"].asFloat();
		float y = dict["y"].asFloat();
		float width = dict["width"].asFloat();
		float height = dict["height"].asFloat();
		log("%f %f %f %f", x, y, width, height);

		PhysicsBody* tmpPhysicsBody = PhysicsBody::createBox(Size(width, height));
		tmpPhysicsBody->setDynamic(false);
		tmpPhysicsBody->setCategoryBitmask(QS::bitMask::kMapCategory);
		tmpPhysicsBody->setCollisionBitmask(QS::bitMask::kMapCollision);
		tmpPhysicsBody->setContactTestBitmask(QS::bitMask::kMapContact);

		Sprite* tmpSprite = Sprite::create();
		tmpSprite->setPosition(Vec2(x, y));
		tmpSprite->setAnchorPoint(Vec2::ZERO);
		tmpSprite->setContentSize(Size(width, height));
		tmpSprite->setPhysicsBody(tmpPhysicsBody);

		this->addChild(tmpSprite, 2, QS::Name::kBarrier);
	}
}

