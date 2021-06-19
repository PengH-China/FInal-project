
/**
*@file BattleScene.cpp
*@author 张子涵 方新宇
*@date 6/5/2021
*/

#include "BattleScene.h"

Hero* pHero = nullptr;

using namespace cocos2d;
cocos2d::Scene* BattleScene::createScene(TMXTiledMap* map)
{
	auto scene = Scene::createWithPhysics();
	auto layer = BattleScene::create(map);
	scene->addChild(layer);
	//scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

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


void BattleScene::addEdge()
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeShape = Node::create();

	edgeShape->setPhysicsBody(body);
	edgeShape->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	addChild(edgeShape);
}


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
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	//背景图片 background picture
	BattleScene::loadBackgroundMap(this);//addEdge();
	BattleScene::addPlayerAndUI();
	BattleScene::createBarrier();
	addEdge();

	BattleScene::addMonster();
	BattleScene::addBox();


	//add five dynamic bodies
	for (int i = 0; i < 5; ++i)
	{
		auto sprite = Sprite::create("player.png");
		sprite->setPosition(Vec2(visibleSize.width / 2 + cocos2d::random(-300, 300),
			visibleSize.height / 2 + cocos2d::random(-300, 300)));

		auto physicsBody = PhysicsBody::createBox(sprite->getContentSize(),
			PhysicsMaterial(0.1f, 1.0f, 0.0f));

		//set the body isn't affected by the physics world's gravitational force
		physicsBody->setGravityEnable(false);

		//set initial velocity of physicsBody
		physicsBody->setVelocity(Vec2(0, 0));


		physicsBody->setCategoryBitmask(1);
		physicsBody->setCollisionBitmask(1);
		physicsBody->setContactTestBitmask(1);

		sprite->setTag(QS::kMonsterTag);

		sprite->addComponent(physicsBody);

		addChild(sprite);
	}


	return true;
}
void  BattleScene::onEnter()
{
	Layer::onEnter();
	//添加监听器 
	auto contactListener = EventListenerPhysicsContact::create();
	//设置监听器的碰撞开始函数 
	contactListener->onContactBegin = CC_CALLBACK_1(BattleScene::onContactBegin, this);
	//添加到事件分发器中 
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//鼠标监控
	auto listenerMouse = EventListenerMouse::create();
	listenerMouse->onMouseUp = CC_CALLBACK_1(BattleScene::onMouseUp, this);
	listenerMouse->onMouseDown = CC_CALLBACK_1(BattleScene::onMouseDown, this);
	listenerMouse->onMouseMove = CC_CALLBACK_1(BattleScene::onMouseMove, this);
	//注册到场景图中
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);
}



void BattleScene::addPlayerAndUI(/*float dt*/) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto* hero = Hero::createHero(Vec2(0, 0), "Hero1");
	pHero = hero;
	globalHero = hero;
	log("i try to init the globalHero");
	if (nullptr != globalHero) {
		log("and successfully!");
	}
	hero->retain();
	if (hero == nullptr)
	{
		log("hero picture not found");
	}
	else
	{
		log("begin init hero");
		hero->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		addChild(hero, 4);
		log("end init hero");
	}
	auto* UIboard = HeroUI::create();
	if (UIboard == nullptr)
	{
		log("UI picture not found");
	}
	else
	{
		log("begin init UI");
		const Vec2 boardSize = Vec2(600, 214);
		Vec2 boardPosition = Vec2(0, 0);
		boardPosition.x = boardSize.x / 4 + 45;//35;
		boardPosition.y = this->getContentSize().height - boardSize.y / 4 - 15;
		/*log("boardSize.y %f", boardSize.y);
		log("boardSize.x %f", boardSize.x);
		log("x:%f", boardPosition.x);
		log("y:%f", boardPosition.y);*/
		//float spx = BattleMapSprite->getTextureRect().getMaxX();
		//float spy = BattleMapSprite->getTextureRect().getMaxY();
		UIboard->setPosition(boardPosition);
		addChild(UIboard, 5, QS::Name::kHeroUI);
		log("end init UI");
	}


}

bool BattleScene::addMonster()
{

	MonsterFly* monsterFly = NULL;
	monsterFly = MonsterFly::createMonster(Vec2(0, 0));
	monsterFly->retain();
	if (monsterFly == nullptr)
	{
		log("monster picture not found");
	}
	else
	{
		log("begin init monster");
		monsterFly->setPosition(Vec2(100, 100));
		addChild(monsterFly, 4);
		log("end init monster");
	}
	return true;
}

void BattleScene::addBox()
{
	auto box = TreasureBox::create();

	this->addChild(box, 4, QS::Name::kTreasure);
}


Monster* BattleScene::createMonsterRand()
{
	int randNumber = cocos2d::random(1, 4);
	if (randNumber == 1)
	{
		return MonsterFly::create();
	}
	else if (randNumber == 2)
	{
		//return MonsterPig::create();
	}
	else if (randNumber == 3)
	{
		//return MonsterCrawShoot::create();
	}
	else if (randNumber == 4)
	{
		//return MonsterWithGun::create();
	}
	return nullptr;
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

		PhysicsBody* tmpPhysicsBody = PhysicsBody::createBox(Size(width, height),
			PhysicsMaterial(100.0f, 0.0f, 0.0f));
		tmpPhysicsBody->setDynamic(false);
		tmpPhysicsBody->setCategoryBitmask(1);
		tmpPhysicsBody->setCollisionBitmask(1);
		tmpPhysicsBody->setContactTestBitmask(1);
		tmpPhysicsBody->setGravityEnable(false);

		Sprite* tmpSprite = Sprite::create();
		tmpSprite->setPosition(Vec2(x, y));
		tmpSprite->setAnchorPoint(Vec2::ZERO);
		tmpSprite->setContentSize(Size(width, height));
		tmpSprite->addComponent(tmpPhysicsBody);
		tmpSprite->setTag(QS::kBarrierTag);
		log("%f %f %f %f %d", x, y, width, height, num++);

		this->addChild(tmpSprite, 2);
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
	auto nodeA = (contact.getShapeA()->getBody()->getNode());
	auto nodeB = (contact.getShapeB()->getBody()->getNode());
	log("fuck off");
	if (nodeA != nullptr && nodeB != nullptr)
	{
		log("test1");
		if (nodeA && nodeB)
		{
			log("test2");
			log("%d %d", nodeA->getTag(), nodeB->getTag());

			//Hero punch Barrier
			if ((nodeA->getTag() == QS::kHeroTag && nodeB->getTag() == QS::kBarrierTag)
				|| (nodeB->getTag() == QS::kHeroTag && nodeA->getTag() == QS::kBarrierTag))
			{
				log("Qiuqiunile");
				if (nodeA->getTag() == QS::kHeroTag)
				{
					log("enter?");
					Sprite* pSprite = dynamic_cast<Sprite*>(nodeA);
					auto heroCopy = dynamic_cast<Hero*>(pSprite->getParent());

					heroCopy->setHitWall(true);
					log("%d %s", heroCopy->getM_nowFacing(), heroCopy->getHeroSpriteName());
					heroCopy->move(heroCopy->getM_nowFacing(), heroCopy->getHeroSpriteName());

					return true;
				}
				else
				{
					Sprite* pSprite = dynamic_cast<Sprite*>(nodeB);
					auto heroCopy = dynamic_cast<Hero*>(pSprite->getParent());

					heroCopy->setHitWall(true);
					log("%d %s", heroCopy->getM_nowFacing(), heroCopy->getHeroSpriteName());
					heroCopy->move(heroCopy->getM_nowFacing(), heroCopy->getHeroSpriteName());

					return true;
				}
			}

			// HeroBullet  punch  Monster
			else if ((nodeA->getTag() == QS::kHeroBulletTag && nodeB->getTag() == QS::kMonsterTag)
				|| (nodeB->getTag() == QS::kHeroBulletTag && nodeA->getTag() == QS::kMonsterTag))
			{
				log("Qiuqiunima");

				if (nodeA->getTag() == QS::kHeroBulletTag)
				{
					auto* bulletCopy = dynamic_cast<Bullet*>(nodeA);
					Monster* mosnterCopy = dynamic_cast<Monster*>(nodeB);

					mosnterCopy->setHealth(mosnterCopy->getHealth()- bulletCopy->getDamage());

					auto changeColor = TintTo::create(0, Color3B::RED);
					auto changeBack = TintTo::create(0.5, 255, 255, 255);

					nodeB->runAction(Sequence::create(changeColor, changeBack, nullptr));
					nodeA->removeFromParent();
					return true;
				}
				else
				{
					auto* bulletCopy = dynamic_cast<Bullet*>(nodeB);
					Monster* mosnterCopy = dynamic_cast<Monster*>(nodeA);

					mosnterCopy->setHealth(mosnterCopy->getHealth() - bulletCopy->getDamage());

					auto changeColor = TintTo::create(0, Color3B::RED);
					auto changeBack = TintTo::create(0.5, 255, 255, 255);

					nodeA->runAction(Sequence::create(changeColor, changeBack, nullptr));

					nodeB->removeFromParent();
					return true;
				}
			}
			// MonsterBullet  punch  Hero
			else if (((nodeA)->getTag() == QS::kHeroTag && (nodeB)->getTag() == QS::kMonsterBulletTag)
				|| ((nodeB)->getTag() == QS::kHeroTag && (nodeA)->getTag() == QS::kMonsterBulletTag))
			{
				log("Qiuqiunima");

				if (nodeA->getTag() == QS::kHeroTag)
				{
					nodeB->removeFromParent();

					auto changeColor = TintTo::create(0, Color3B::RED);
					auto changeBack = TintTo::create(0.5, 255, 255, 255);

					nodeA->runAction(Sequence::create(changeColor, changeBack, nullptr));
					return true;
				}
				else
				{
					nodeA->removeFromParent();

					auto changeColor = TintTo::create(0, Color3B::RED);
					auto changeBack = TintTo::create(0.5, 255, 255, 255);

					nodeB->runAction(Sequence::create(changeColor, changeBack, nullptr));
					return true;
				}
			}

			// HeroBullet  punch  Barrier
			else if (((nodeA)->getTag() == QS::kHeroBulletTag && (nodeB)->getTag() == QS::kBarrierTag)
				|| ((nodeB)->getTag() == QS::kHeroBulletTag && (nodeA)->getTag() == QS::kBarrierTag))
			{
				log("Qiuqiunima");

				if (nodeA->getTag() == QS::kHeroBulletTag)
				{
					nodeA->removeFromParent();

					return true;
				}
				else
				{
					nodeB->removeFromParent();

					return true;
				}
			}

			// MonsterBullet  punch  Barrier
			else if (((nodeA)->getTag() == QS::kMonsterBulletTag && (nodeB)->getTag() == QS::kBarrierTag)
				|| ((nodeB)->getTag() == QS::kMonsterBulletTag && (nodeA)->getTag() == QS::kBarrierTag))
			{
				log("Qiuqiunima");

				if (nodeA->getTag() == QS::kMonsterBulletTag)
				{
					nodeA->removeFromParent();

					return true;
				}
				else
				{
					nodeB->removeFromParent();

					return true;
				}
			}


			// HeroSword  punch  Monster
			else if (((nodeA)->getTag() == QS::kHeroSwordAttackingTag && (nodeB)->getTag() == QS::kMonsterTag)
				|| ((nodeB)->getTag() == QS::kHeroSwordAttackingTag && (nodeA)->getTag() == QS::kMonsterTag))
			{
				log("Qiuqiunima");

				if (nodeA->getTag() == QS::kHeroSwordAttackingTag)
				{
					nodeB->setColor(Color3B::RED);
					log("should be red");

					//two actions to change color and back with o0.5s delay
					auto changeColor = TintTo::create(0, Color3B::RED);
					auto changeBack = TintTo::create(0.5, 255, 255, 255);

					nodeB->runAction(Sequence::create(changeColor, changeBack, nullptr));

					return true;
				}
				else
				{

					log("should be red");
					//two actions to change color and back with o0.5s delay
					auto changeColor = TintTo::create(0, Color3B::RED);
					auto changeBack = TintTo::create(0.5, 255, 255, 255);

					nodeB->runAction(Sequence::create(changeColor, changeBack, nullptr));

					return true;
				}
			}

			// MonsterBullet  punch  HeroSword
			else if (((nodeA)->getTag() == QS::kMonsterBulletTag && (nodeB)->getTag() == QS::kHeroSwordAttackingTag)
			|| ((nodeB)->getTag() == QS::kMonsterBulletTag && (nodeA)->getTag() == QS::kHeroSwordAttackingTag))
			{
			log("Qiuqiunima");

			if (nodeA->getTag() == QS::kMonsterBulletTag)
			{
				nodeA->removeFromParent();

				return true;
			}
			else
			{
				nodeB->removeFromParent();

				return true;
			}
			}
		}

	}

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


	return false;
}


bool BattleScene::onMouseDown(EventMouse* e)
{
	log("mouseDown");
	auto curTime = clock();
	if (pHero->getMainWeapon() != nullptr) {
		if (static_cast<double>(curTime - m_lastShotTime) / CLOCKS_PER_SEC
			< pHero->getMainWeapon()->getInterval())
		{
			return true;
		}
		m_lastShotTime = curTime;
		if (pHero->getMainWeapon()->getBulletCount() == 0)
		{
			//pHero->throwMainWeapon();
		}
		else
			//枪有子弹的时候
		{
			//人物精灵在场景中的坐标
			Vec2 heroPos = pHero->getPosition() + pHero->getSprite()->getPosition();
			//获取鼠标位置，并修正纵轴位置
			Vec2 mousePos = e->getLocationInView();
			//死也不要改这里980
			mousePos.y += 980;
			//射击方向
			Vec2 dire = mousePos - heroPos;

			log("mousePos at: %f, %f", mousePos.x, mousePos.y);
			log("  Hero at: %f, %f", heroPos.x, heroPos.y);
			log("  dire at: %f, %f", dire.x, dire.y);
			Bullet* pBullet = pHero->getMainWeapon()->createBullet();
			this->addChild(pBullet, 5);
			pBullet->setPosition(heroPos);
			pBullet->attack(dire.x, dire.y, heroPos, pHero->getM_nowFacing());
			log("BulletCount: %d", pHero->getMainWeapon()->getBulletCount());
		}
	}
	return true;
}

void BattleScene::onMouseUp(EventMouse* event)
{
	log("mouseUp");
}


void BattleScene::onMouseMove(EventMouse* e)
{
	//log("mouseMove");
	////获得openGL的坐标
	//Vec2 pos = this->convertToNodeSpaceAR(e->getLocation());
	////注意父节点人物虚拟的是定坐标的，我们操纵的是实物人物精灵图片在计算
	//Vec2 vecHero = this->convertToNodeSpaceAR(m_pHeroSprite->getPosition());
	////鼠标相对于人物的位置向量
	//Vec2 dirTo = pos - vecHero;
	////武器相对于父节点人物的位置向量
	//Vec2 dirFrom = this->convertToNodeSpaceAR(this->getMainWeapon()->getPosition());
	//log("pos x: %d ,y: %d", pos.x, pos.y);
	//log("vecHero x: %d ,y: %d", vecHero.x, vecHero.y);
	//log("dirTo x: %d ,y: %d", dirTo.x, dirTo.y);
	//log("disFrom x: %d ,y: %d", dirFrom.x, dirFrom.y);
	//Vec2 now = this->getMainWeapon()->getPosition();
	//0<=jiaodu<=pi
	/*float jiaodu = angle(dirTo, dirFrom);
	this->getMainWeapon()->setRotation(jiaodu);*/

}
