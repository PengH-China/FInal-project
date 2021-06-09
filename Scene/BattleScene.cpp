/**
*@file BattleScene.cpp
*@author ���Ӻ� ������
*@date 6/5/2021
*/


#include "cocos2d.h"
#include "BattleScene.h"
#include"Const/Const.h"
#include "Hero.h"
#include"Soldier.h"
#include"Role.h"


using namespace cocos2d;

//cocos2d::Scene* BattleScene::createScene()
//{
//	auto scene = BattleScene::createWithPhysics();
//	log("problem1!?");
//	auto layer = BattleScene::create();
//	log("scene address %p\n", &scene);
//	log("layer address %p\n", &layer);
//
//	//scene->addChild(layer);
//	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
//	scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
//	//cocos2d::Ref * pSender=;
//	return scene;
//	//return BattleScene::create();
//}
cocos2d::Scene* BattleScene::createScene(TMXTiledMap* map)
{
	auto scene = Scene::createWithPhysics();
	auto layer = BattleScene::create(map);
	scene->addChild(layer);
	scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
	return scene;
}
BattleScene* BattleScene::create(TMXTiledMap* map)
{
	auto* pRet = new(std::nothrow) BattleScene(map);
	if (pRet)
	{
		if (pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
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

	//����ͼƬ background picture
	BattleScene::loadBackgroundMap(this);
	//BattleScene::setGidTag();
	/*BattleScene::createWithPhysics();
	BattleScene::getPhysicsWorld()->setGravity(Vec2::ZERO);*/
	BattleScene::createBarrier();
	BattleScene::addPlayer(); 
	/*static Hero* hero = Soldier::create();
	auto keyBoardListenerHero = EventListenerKeyboard::create();
	keyBoardListenerHero->onKeyPressed = CC_CALLBACK_2(Hero::onKeyPressed, hero);
	keyBoardListenerHero->onKeyReleased = CC_CALLBACK_2(Hero::onKeyReleased, hero);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListenerHero, this);*/
	auto contactListener = EventListenerPhysicsContact::create();
	log("create contactListener");
	contactListener->onContactBegin = CC_CALLBACK_1(BattleScene::onContactBegin, this);
	log("CC_CALLBACK_1 IS USING");
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	log("addEventListener");
	//schedule(CC_SCHEDULE_SELECTOR(BattleScene::addPlayer), 0.3f);
	this->scheduleUpdate();
	//log("scheduleUpdate");
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
	/* ����metaͼ������� */
	//this->m_pMeta = m_pMap->getLayer("meta");
	//this->m_pMeta->setVisible(false);
}
void BattleScene::setGidTag()
{
	Size sizeOfMap=m_pMap->getMapSize();
	log("sizeOfMap:%f %f", sizeOfMap.width-1, sizeOfMap.height-1);
	for (int y = 0; y <= sizeOfMap.height - 1; y++) {
		for (int x = 0; x <= sizeOfMap.width - 1; x++) {
			int tiledGid = m_pMeta->getTileGIDAt(Vec2(x,y));
			/* ��Ϊ0���������������� */
			if (tiledGid != 0) {
				/*
				��ȡ�õ�ͼ���ӵ��������ԣ�Ŀǰ����ֻ��һ��Collidable����
				����������meta��ģ���ͬʱҲ������������ͼ�ģ������ڻ�ȡ���ӵ���������
				ʱ��ͨ������Ψһ��ʶ�ڵ�ͼ��ȡ��
				*/
				Value properties = m_pMap->getPropertiesForGID(tiledGid);

				ValueMap propertiesMap = properties.asValueMap();

				if (propertiesMap.find("Collidable") != propertiesMap.end())
				{
					/* ȡ�ø��ӵ�Collidable����ֵ */
					Value prop = propertiesMap.at("Collidable");
					if (prop.asString().compare("true") == 0)
					{
						Sprite* gidSprite = m_pMeta->getTileAt(Vec2(x, y));
						gidSprite->setName(QS::Name::kGidTag);
						log("set (%d,%d) gid as barrier", x, y);
					}
					
		}
	}
	
			///* �ж�Collidable�����Ƿ�Ϊtrue������ǣ���������ƶ� */
			//if (prop.asString().compare("true") == 0 && isJumping == false) {
			//	isJumping = true;

			//	auto jumpBy = JumpBy::create(0.5f, Point(-100, 0), 80, 1);
			//	CallFunc* callfunc = CallFunc::create([&]() {
			//		/* �ָ�״̬ */
			//		isJumping = false;
			//		});

			//	/* ִ�ж�������ײ���ϰ���ʱ�ķ���Ч�� */
			//	auto actions = Sequence::create(jumpBy, callfunc, NULL);
			//	this->runAction(actions);
			}
		}
        
}
void BattleScene::addPlayer(/*float dt*/){
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//PolygonInfo fig;
	static Hero* hero = Soldier::create();


	//fig = AutoPolygon::generatePolygon(QS::kSoldier1,Rect(0, 0, QS::kSoldierWidth, QS::kSoldierHeight));

	Sprite* heroSprite = Sprite::create("player.png");

	if (heroSprite == nullptr)
	{
		log("hero picture not found");
	}
	else
	{
		log("begin init hero");

		hero->bindSprite(heroSprite);
		hero->genePhysicsBody();
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

	for (auto &barrier : barrierObjects)
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
		//tmpSprite->setPosition(Vec2(x, y));
		//tmpSprite->setAnchorPoint(Vec2::ZERO);
		//tmpSprite->setContentSize(Size(width, height));
		tmpSprite->setPhysicsBody(tmpPhysicsBody);

		this->addChild(tmpSprite, /*2*/0, QS::Name::kBarrier);
	}
}
bool BattleScene::onContactBegin(PhysicsContact& contact)
{
	log("onContactBegin is functioning");
	
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != nullptr && nodeB != nullptr)
	{
		if ((nodeA->getName() == QS::Name::kHero && nodeB->getName() == QS::Name::kBarrier)
			|| (nodeB->getName() == QS::Name::kHero && nodeA->getName() == QS::Name::kBarrier))
		{
			if (nodeA->getName() == QS::Name::kHero)
			{
				log("test node A is Hero");
				auto v = nodeA->getPhysicsBody()->getVelocity();
				v.normalize();
				nodeA->setPosition(-50 * v);
				nodeA->getPhysicsBody()->setVelocity(-50 * v);
				return true;
			}
			else
			{
				log("test node B is Hero");
				auto v = nodeB->getPhysicsBody()->getVelocity();
				v.normalize();
				nodeB->setPosition(-50 * v);
				nodeB->getPhysicsBody()->setVelocity(-50 * v);
				return true;
			}
		}
		/*if ((nodeA->getName() == QS::Name::kMonster && nodeB->getName() == QS::Name::kBarrier)
			|| (nodeB->getName() == QS::Name::kMonster && nodeA->getName() == QS::Name::kBarrier))
		{
			if (nodeA->getName() == QS::Name::kMonster)
			{
				auto v = nodeA->getPhysicsBody()->getVelocity();
				nodeA->getPhysicsBody()->setVelocity(-v);
				return true;
			}
			else
			{
				auto v = nodeB->getPhysicsBody()->getVelocity();
				nodeB->getPhysicsBody()->setVelocity(-v);
				return true;
			}
		}*/
	}
	return false;
}

//bool init()
//{
//	//create a static PhysicsBody
//	auto sprite = addSpriteAtPosition(s_centre, 1);
//	sprite->setTag(10);
//	sprite->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
//	sprite->getPhysicsBody()->setDynamic(false);
//
//	//adds contact event listener
//	auto contactListener = EventListenerPhysicsContact::create();
//	contactListener->onContactBegin = CC_CALLBACK_1(BattleScene::onContactBegin, this);
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
//
//	schedule(CC_SCHEDULE_SELECTOR(PhysicsDemoCollisionProcessing::tick), 0.3f);
//	return true;
//
//	return false;
//}
//
//void tick(float dt)
//{
//	auto sprite1 = addSpriteAtPosition(Vec2(s_centre.x + cocos2d::random(-300, 300),
//		s_centre.y + cocos2d::random(-300, 300)));
//	auto physicsBody = sprite1->getPhysicsBody();
//	physicsBody->setVelocity(Vec2(cocos2d::random(-500, 500), cocos2d::random(-500, 500)));
//	physicsBody->setContactTestBitmask(0xFFFFFFFF);
//}
//
//bool onContactBegin(PhysicsContact& contact)
//{
//	auto nodeA = contact.getShapeA()->getBody()->getNode();
//	auto nodeB = contact.getShapeB()->getBody()->getNode();
//
//	if (nodeA && nodeB)
//	{
//		if (nodeA->getTag() == 10)
//		{
//			nodeB->removeFromParentAndCleanup(true);
//		}
//		else if (nodeB->getTag() == 10)
//		{
//			nodeA->removeFromParentAndCleanup(true);
//		}
//	}
//
//	//bodies can collide
//	return true;
//}