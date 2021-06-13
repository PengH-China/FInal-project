/**
*@file BattleScene.cpp
*@author 张子涵 方新宇
*@date 6/5/2021
*/


#include "cocos2d.h"
#include "BattleScene.h"
#include "Role/Hero.h"
//#include "Role/HeroUI.h"

using namespace cocos2d;
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

//cocos2d::Scene* BattleScene::createScene()
//{
//	return BattleScene::create();
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
	BattleScene::addPlayerAndUI();
	BattleScene::createBarrier();
	auto contactListener = EventListenerPhysicsContact::create();
	log("create contactListener");
	contactListener->onContactBegin = CC_CALLBACK_1(BattleScene::onContactBegin, this);
	log("CC_CALLBACK_1 IS USING");
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}
void BattleScene::addPlayerAndUI(/*float dt*/) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto* hero = Hero::createHero(Vec2(180, 100));

	if (hero == nullptr)
	{
		log("hero picture not found");
	}
	else
	{
		log("begin init hero");
		addChild(hero, 4, QS::Name::kHero);
		log("end init hero");
	}
	//HeroUI* UIboard = HeroUI::create();
	//if (UIboard == nullptr)
	//{
	//	log("UI picture not found");
	//}
	//else
	//{
	//	log("begin init UI");
	//	const Vec2 boardSize = Vec2(600, 214);
	//	Vec2 boardPosition = Vec2(0, 0);
	//	boardPosition.x = boardSize.x / 4 + 42;//35;
	//	boardPosition.y = this->getContentSize().height - boardSize.y / 4 - 15;
	//	/*log("boardSize.y %f", boardSize.y);
	//	log("boardSize.x %f", boardSize.x);
	//	log("x:%f", boardPosition.x);
	//	log("y:%f", boardPosition.y);*/
	//	//float spx = BattleMapSprite->getTextureRect().getMaxX();
	//	//float spy = BattleMapSprite->getTextureRect().getMaxY();
	//	UIboard->setPosition(boardPosition);
	//	addChild(UIboard, 5, QS::Name::kHeroUI);
	//	log("end init UI");
	//}

	//hero->retain();
}
void BattleScene::loadBackgroundMap(cocos2d::Ref* pSender)
{
	MenuItem* item = (MenuItem*)pSender;
	log("Touch Background MenuItem %p", item);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	TMXTiledMap* battleMap = TMXTiledMap::create("map1.tmx");
	BattleScene::setTiledMap(battleMap);
	Sprite* BattleMapSprite = Sprite::create("map1.png");
	Size mywinsize = Director::getInstance()->getWinSize();
	float winw = mywinsize.width; //获取屏幕宽度
	float winh = mywinsize.height;//获取屏幕高度
	float spx = BattleMapSprite->getTextureRect().getMaxX();
	float spy = BattleMapSprite->getTextureRect().getMaxY();
	battleMap->setScaleX(winw / spx); //设置缩放比例
	battleMap->setScaleY(winh / spy);
	battleMap->setAnchorPoint(Vec2(0, 0));
	//battleMap->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height / 2));
	this->addChild(battleMap);
}

void BattleScene::createBarrier()
{
	auto group = m_pMap->getObjectGroup("wall");
	ValueVector barrierObjects = group->getObjects();
	int num = 0;
	for (auto barrier : barrierObjects)
	{
		ValueMap& dict = barrier.asValueMap();
		float x = dict["x"].asFloat();
		float y = dict["y"].asFloat();
		float width = dict["width"].asFloat();
		float height = dict["height"].asFloat();

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
		log("%f %f %f %f %d", x, y, width, height,num++);
		
		this->addChild(tmpSprite, 2, QS::Name::kBarrier);
	}
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
}

bool BattleScene::onContactBegin(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != nullptr && nodeB != nullptr)
	{
		log("test1");
		if (nodeA && nodeB)
		{
			log("test2");
			log("%s %s", nodeA->getName(), nodeB->getName());
			if ((nodeA->getName() == QS::Name::kHero && nodeB->getName() == QS::Name::kBarrier)
				|| (nodeB->getName() == QS::Name::kHero && nodeA->getName() == QS::Name::kBarrier))
			{
				log("Hit Wall!!!");
				if (nodeA->getName() == QS::Name::kHero)
				{
					dynamic_cast<Hero*>(nodeA)->setHitWall(true);
					auto v = nodeA->getPhysicsBody()->getVelocity();
					v.normalize();
					nodeA->setPosition(-50 * v);
					nodeA->getPhysicsBody()->setVelocity(-10 * v);
					return true;
				}
				else
				{
					dynamic_cast<Hero*>(nodeB)->setHitWall(true);
					auto v = nodeB->getPhysicsBody()->getVelocity();
					v.normalize();
					nodeB->setPosition(-50 * v);
					nodeB->getPhysicsBody()->setVelocity(-10 * v);
					return true;
				}
			}
		}
		/*if ((nodeA->getTag() == sk::tag::kHero && nodeB->getTag() == sk::tag::kDoor)
			|| (nodeB->getTag() == sk::tag::kHero && nodeA->getTag() == sk::tag::kDoor))
		{
			m_mapNumber++;
			if (m_mapNumber == 10)
			{
				return true;
			}
			auto map = createTiled(m_mapNumber);
			if (!map)
			{
				return false;
			}
			auto nextRoom = createScene(map);
			auto hero = Hero::getInstance();
			hero->retain();
			hero->removeFromParentAndCleanup(false);
			hero->setPosition(640.f, 100.f);
			hero->generatePhysics();
			nextRoom->addChild(Hero::getInstance(), 3);
			auto keyBoardListener = EventListenerKeyboard::create();
			keyBoardListener->onKeyPressed = CC_CALLBACK_2(Hero::onKeyPressed, hero);
			keyBoardListener->onKeyReleased = CC_CALLBACK_2(Hero::onKeyReleased, hero);
			_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, nextRoom);

			BulletLayer* bulletLayer = BulletLayer::create();
			bulletLayer->retain();
			bulletLayer->bindHero(hero);
			nextRoom->addChild(bulletLayer, 8, 450);
			Director::getInstance()->replaceScene(nextRoom);

			Buff::getInstance()->flamingEnd();
			Buff::getInstance()->flamingEnd();
			Buff::getInstance()->rootedEnd(100.f);

			return true;
		}*/
		
		/*if ((nodeA->getTag() == sk::tag::kMonster && nodeB->getTag() == sk::tag::kBarrier)
			|| (nodeB->getTag() == sk::tag::kMonster && nodeA->getTag() == sk::tag::kBarrier))
		{
			if (nodeA->getTag() == sk::tag::kMonster)
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
