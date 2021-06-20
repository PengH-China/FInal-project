
#include "MapLayer.h"
#include "Pause.h"
#include "GlobalPara/GlobalParameter.h"
Hero* pHero = nullptr;

static struct tm* beginGameTime;
static struct tm* struct_nowTime;
static int    ibeginTime = 0;


Vec2 randomPos() {
	const int maxWidth = 32 * 100;
	const int maxHeight = 32 * 100;

	const int posX = cocos2d::random(32, maxWidth - 32);
	const int posY = cocos2d::random(32, maxHeight - 32);

	Vec2 pos = Vec2(posX, posY);
	return pos;
}

bool MapLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	time_t tt;
	time(&tt);
	beginGameTime = localtime(&tt);
	ibeginTime = beginGameTime->tm_sec + beginGameTime->tm_min * 60;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	TMXTiledMap* battleMap = TMXTiledMap::create("BigMap.tmx");
	m_pMap = battleMap;
	m_pMap->setAnchorPoint(Vec2(0, 0));
	//battleMap->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	m_pMap->setPosition(Vec2(0,0));
	this->addChild(m_pMap, QS::kMapLayerPriority);
	MapLayer::createBarrier();

	MapLayer::addPlayer();
	MapLayer::addMonster();
	MapLayer::randomAddBox();

	schedule(CC_SCHEDULE_SELECTOR(MapLayer::updatePosition), 0.01f);
	schedule(CC_SCHEDULE_SELECTOR(MapLayer::updateMonster), 30.f);
	//schedule(CC_SCHEDULE_SELECTOR(MapLayer::createBarrier), 0.1f);
	return true;
}
void MapLayer::randomAddBox()
{
	const int randomBoxNum = cocos2d::random(7, 10);
	log("box number is %d", randomBoxNum);
	for (int i = 1; i <= randomBoxNum; i++) {
		addBox();
	}
}

void MapLayer::updateMonster(float dt)
{
	if (g_iDuration % 60 > 3) {
		return;
	}
	addMonster();
}

void MapLayer::updatePosition(float dt)
{
	
	mapHeight = m_pMap->getMapSize().height;
	mapWidth = m_pMap->getMapSize().width;
	tileWidth = m_pMap->getTileSize().width;
	tileHeight = m_pMap->getTileSize().height;
	
	Point heroPosition = globalHero->getSprite()->getPosition();
	//log("1.position is %d %d", globalHero->getSprite()->getPosition().x, globalHero->getSprite()->getPosition().y);
	float deltax = heroPosition.x - mapWidth * tileWidth/2 ;
	float deltay = heroPosition.y;
	//setViewPointCenter(heroPosition);
	Size s = m_pMap->getContentSize();
	Size myWinSize = Director::getInstance()->getWinSize();
	this->setPosition(Vec2(-s.width / 2 - deltax, -deltay));

	time_t nowTime;
	time(&nowTime);

	struct_nowTime = localtime(&nowTime);
	g_iDuration = struct_nowTime->tm_sec + struct_nowTime->tm_min * 60 - ibeginTime;
	//log("beginTime :::%d", ibeginTime);
	//log("nowTime :::%d", struct_nowTime->tm_sec);
	log("duration :::%d", g_iDuration);
	if (g_iDuration >= 5 * 60) {//five minutes
		Size visibleSize = Director::getInstance()->getVisibleSize();
		RenderTexture* renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
		renderTexture->begin();
		this->visit();
		renderTexture->end();
		Director::getInstance()->pushScene(GameOver::createLayer(renderTexture));
	}

	//log("now position %d %d", globalHero->getSprite()->getPosition().x, globalHero->getSprite()->getPosition().y);
	//MapLayer::createBarrier();
}
void MapLayer::setViewPointCenter(Point position)
{
	auto winSize = Director::getInstance()->getWinSize();
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, mapWidth - winSize.width / 2);
	y = MIN(y, mapHeight - winSize.height / 2);
	auto actualPosition = Point(x, y);

	auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actualPosition;
	this->setPosition(viewPoint);
}


void MapLayer::createBarrier()
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
		//log("%f %f %f %f %d", x, y, width, height, num++);

		this->addChild(tmpSprite, QS::kBarrierPriority);
	}
}



void MapLayer::addEdge()
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

void  MapLayer::onEnter()
{
	Layer::onEnter();
	//添加监听器 
	auto contactListener = EventListenerPhysicsContact::create();
	//设置监听器的碰撞开始函数 
	contactListener->onContactBegin = CC_CALLBACK_1(MapLayer::onContactBegin, this);
	//添加到事件分发器中 
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//鼠标监控
	auto listenerMouse = EventListenerMouse::create();
	listenerMouse->onMouseUp = CC_CALLBACK_1(MapLayer::onMouseUp, this);
	listenerMouse->onMouseDown = CC_CALLBACK_1(MapLayer::onMouseDown, this);
	listenerMouse->onMouseMove = CC_CALLBACK_1(MapLayer::onMouseMove, this);
	//注册到场景图中
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);
}



void MapLayer::addPlayer(/*float dt*/) {
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
		addChild(hero, QS::kHeroPriority);
		log("end init hero");
	}
	


}
bool MapLayer::addMonster()
{
	int monsterNum = 0;
	const int minNum = 6;
	const int maxNum = 8;
	monsterNum = cocos2d::random(minNum, maxNum);

	for (int i = 1; i <= monsterNum; i++) {
		Monster* monster = NULL;
		int randMonster = cocos2d::random(0, 3);
		enum { fly, blueOne, crawl, blueTwo };
		switch (randMonster) {
			case fly: {
				monster = MonsterFly::createMonster(Vec2(0, 0));
				if (monster == nullptr)
				{
					log("monster picture not found");
				}
				else
				{
					monster->retain();
					monster->setPosition(randomPos());
					addChild(monster, 5);
					break;
				}
			}
			case blueOne: {
				monster = MonsterBlueOne::createMonster(Vec2(0, 0));
				if (monster == nullptr)
				{
					log("monster picture not found");
				}
				else
				{
					monster->retain();
					monster->setPosition(randomPos());
					addChild(monster, 5);

				}
			}
			case crawl: {
				monster = MonsterCrawl::createMonster(Vec2(0, 0));
				if (monster == nullptr)
				{
					log("monster picture not found");
				}
				else
				{
					monster->retain();
					monster->setPosition(randomPos());
					addChild(monster, 5);

				}
			}
			case blueTwo: {
				monster = MonsterBlueTwo::createMonster(Vec2(0, 0));
				if (monster == nullptr)
				{
					log("monster picture not found");
				}
				else
				{
					monster->retain();
					monster->setPosition(randomPos());
					addChild(monster, 5);

				}
			}
		}
	}

	return true;
}


void MapLayer::addBox()
{
	auto box = TreasureBox::create();

	this->addChild(box, QS::kBoxPriority, QS::Name::kTreasure);
}




void MapLayer::menuBackCallback(cocos2d::Ref* pSender)
{
	MenuItem* item = (MenuItem*)pSender;
	log("Touch back MenuItem %p", item);

	Director::getInstance()->popScene();

}

bool MapLayer::onContactBegin(PhysicsContact& contact)
{
	//获取相撞的两个物体
	auto nodeA = (contact.getShapeA()->getBody()->getNode());
	auto nodeB = (contact.getShapeB()->getBody()->getNode());
	log("punch togethor");
	if (nodeA != nullptr && nodeB != nullptr)
	{
		log("%d %d", nodeA->getTag(), nodeB->getTag());

		//Hero punch Barrier
		if ((nodeA->getTag() == QS::kHeroTag && nodeB->getTag() == QS::kBarrierTag)
			|| (nodeB->getTag() == QS::kHeroTag && nodeA->getTag() == QS::kBarrierTag))
		{
			log("Qiuqiunile");
			if (nodeA->getTag() == QS::kHeroTag)
			{
				log("enter?");
				//获取英雄
				Sprite* pSprite = dynamic_cast<Sprite*>(nodeA);
				auto heroCopy = dynamic_cast<Hero*>(pSprite->getParent());
				//英雄相对于障碍物后退
				heroCopy->setHitWall(true);
				log("%d %s", heroCopy->getM_nowFacing(), heroCopy->getHeroSpriteName());
				heroCopy->move(heroCopy->getM_nowFacing(), heroCopy->getHeroSpriteName());

				return true;
			}
			else
			{
				//获取英雄
				Sprite* pSprite = dynamic_cast<Sprite*>(nodeB);
				auto heroCopy = dynamic_cast<Hero*>(pSprite->getParent());
				//英雄相对于障碍物后退
				heroCopy->setHitWall(true);
				log("%d %s", heroCopy->getM_nowFacing(), heroCopy->getHeroSpriteName());
				heroCopy->move(heroCopy->getM_nowFacing(), heroCopy->getHeroSpriteName());

				return true;
			}
		}

		//Monster punch Barrier
		if ((nodeA->getTag() == QS::kMonsterTag && nodeB->getTag() == QS::kBarrierTag)
			|| (nodeB->getTag() == QS::kMonsterTag && nodeA->getTag() == QS::kBarrierTag))
		{
			log("Qiuqiunile");
			if (nodeA->getTag() == QS::kMonsterTag)
			{
				log("monster punch barrier?");
				//获取monster
				auto monsterCopy = dynamic_cast<Monster*>(nodeA->getParent());
				//monster相对于障碍物后退
				log("%d", monsterCopy->getMonsterFacing());
				monsterCopy->backIntoMap(monsterCopy->getMonsterFacing());

				return true;
			}
			else
			{
				log("monster punch barrier?");
				//获取monster
				auto monsterCopy = dynamic_cast<Monster*>(nodeB->getParent());
				//monster相对于障碍物后退
				log("%d", monsterCopy->getMonsterFacing());
				monsterCopy->backIntoMap(monsterCopy->getMonsterFacing());

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
				auto* bulletCopy = dynamic_cast<Bullet*>(nodeA->getParent());
				Monster* mosnterCopy = dynamic_cast<Monster*>(nodeB->getParent());

				if (nullptr == bulletCopy)//子弹异常消失
				{
					return false;
				}

				mosnterCopy->setHealth(mosnterCopy->getHealth() - bulletCopy->getDamage());

				//受伤时的颜色转变
				auto changeColor = TintTo::create(0, Color3B::RED);
				auto changeBack = TintTo::create(0.5, 255, 255, 255);
				nodeB->runAction(Sequence::create(changeColor, changeBack, nullptr));

				//子弹消失
				nodeA->retain();
				nodeA->removeFromParent();
				return true;
			}
			else
			{
				auto* bulletCopy = dynamic_cast<Bullet*>(nodeB->getParent());
				Monster* mosnterCopy = dynamic_cast<Monster*>(nodeA->getParent());

				if (nullptr == bulletCopy)//子弹异常消失
				{
					return false;
				}

				//怪物受伤扣血
				mosnterCopy->setHealth(mosnterCopy->getHealth() - bulletCopy->getDamage());

				//受伤时的颜色转变
				auto changeColor = TintTo::create(0, Color3B::RED);
				auto changeBack = TintTo::create(0.5, 255, 255, 255);
				nodeA->runAction(Sequence::create(changeColor, changeBack, nullptr));

				//remove子弹
				nodeB->retain();
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
				auto* bulletCopy = dynamic_cast<MonsterBullet*>(nodeB->getParent());
				auto* heroCopy = dynamic_cast<Hero*>(nodeA->getParent());


				if (nullptr == bulletCopy)//子弹异常消失
				{
					return false;
				}

				if (heroCopy->getArmor() >= bulletCopy->getDamage())//护甲大于伤害
				{
					heroCopy->setArmor(heroCopy->getArmor() - bulletCopy->getDamage());
				}
				else if (heroCopy->getArmor() < bulletCopy->getDamage() && heroCopy->getArmor() > 0)//护甲不为零且小于伤害
				{
					heroCopy->setHealth(heroCopy->getHealth() + heroCopy->getArmor() - bulletCopy->getDamage());
					heroCopy->setArmor(0);
				}
				else //护甲为0
				{
					heroCopy->setHealth(heroCopy->getHealth() - bulletCopy->getDamage());
				}

				auto changeColor = TintTo::create(0, Color3B::RED);
				auto changeBack = TintTo::create(0.5, 255, 255, 255);

				nodeA->runAction(Sequence::create(changeColor, changeBack, nullptr));

				nodeB->retain();
				nodeB->removeFromParent();
				return true;
			}
			else
			{
				auto* bulletCopy = dynamic_cast<MonsterBullet*>(nodeA->getParent());
				auto* heroCopy = dynamic_cast<Hero*>(nodeB->getParent());

				if (nullptr == bulletCopy)//子弹异常消失
				{
					return false;
				}

				if (heroCopy->getArmor() >= bulletCopy->getDamage())//护甲大于伤害
				{
					heroCopy->setArmor(heroCopy->getArmor() - bulletCopy->getDamage());
				}
				else if (heroCopy->getArmor() < bulletCopy->getDamage() && heroCopy->getArmor() > 0)//护甲不为零且小于伤害
				{
					heroCopy->setHealth(heroCopy->getHealth() + heroCopy->getArmor() - bulletCopy->getDamage());
					heroCopy->setArmor(0);
				}
				else //护甲为0
				{
					heroCopy->setHealth(heroCopy->getHealth() - bulletCopy->getDamage());
				}


				auto changeColor = TintTo::create(0, Color3B::RED);
				auto changeBack = TintTo::create(0.5, 255, 255, 255);

				nodeB->runAction(Sequence::create(changeColor, changeBack, nullptr));

				nodeA->retain();
				nodeA->removeFromParent();
				return true;
			}
		}

		// Monster  punch  Hero
		else if (((nodeA)->getTag() == QS::kHeroTag && (nodeB)->getTag() == QS::kMonsterTag)
		|| ((nodeB)->getTag() == QS::kHeroTag && (nodeA)->getTag() == QS::kMonsterTag))
		{
		log("Qiuqiunima");

		if (nodeA->getTag() == QS::kHeroTag)
		{
			auto* heroCopy = dynamic_cast<Hero*>(nodeA->getParent());

			if (heroCopy->getArmor() >= 1)//护甲大于伤害
			{
				heroCopy->setArmor(heroCopy->getArmor() - 1);
			}
			else //护甲为0
			{
				heroCopy->setHealth(heroCopy->getHealth() - 1);
			}

			auto changeColor = TintTo::create(0, Color3B::RED);
			auto changeBack = TintTo::create(0.5, 255, 255, 255);

			nodeA->runAction(Sequence::create(changeColor, changeBack, nullptr));
			return true;
		}
		else
		{
			auto* heroCopy = dynamic_cast<Hero*>(nodeB->getParent());

			if (heroCopy->getArmor() >= 1)//护甲大于伤害
			{
				heroCopy->setArmor(heroCopy->getArmor() - 1);
			}
			else //护甲为0
			{
				heroCopy->setHealth(heroCopy->getHealth() - 1);
			}

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
				nodeA->retain();
				nodeA->removeFromParent();

				return true;
			}
			else
			{
				nodeB->retain();
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
				nodeA->retain();
				nodeA->removeFromParent();

				return true;
			}
			else
			{
				nodeB->retain();
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
				auto* SwordCopy = dynamic_cast<Sword*>(nodeA->getParent());
				Monster* mosnterCopy = dynamic_cast<Monster*>(nodeB->getParent());

				mosnterCopy->setHealth(mosnterCopy->getHealth() - SwordCopy->getDamage());


				//two actions to change color and back with o0.5s delay
				auto changeColor = TintTo::create(0, Color3B::RED);
				auto changeBack = TintTo::create(0.5, 255, 255, 255);

				nodeB->runAction(Sequence::create(changeColor, changeBack, nullptr));

				return true;
			}
			else
			{

				log("should be red");

				auto* SwordCopy = dynamic_cast<Sword*>(nodeB->getParent());
				Monster* mosnterCopy = dynamic_cast<Monster*>(nodeA->getParent());

				mosnterCopy->setHealth(mosnterCopy->getHealth() - SwordCopy->getDamage());


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
				nodeA->retain();
				nodeA->removeFromParent();

				return true;
			}
			else
			{
				nodeB->retain();
				nodeB->removeFromParent();

				return true;
			}
		}


		// Hero  punch  BulletBox
		else if (((nodeA)->getTag() == QS::kBulletBoxTag && (nodeB)->getTag() == QS::kHeroTag)
			|| ((nodeB)->getTag() == QS::kBulletBoxTag && (nodeA)->getTag() == QS::kHeroTag))
		{
			log("Qiuqiunima");

			if (nodeA->getTag() == QS::kBulletBoxTag)
			{
				auto* heroCopy = dynamic_cast<Hero*>(nodeB->getParent());
				heroCopy->setBulletCountInHero(heroCopy->getBulletCountInHero() + 50);


				nodeA->retain();
				nodeA->removeFromParent();

				return true;
			}
			else
			{
				auto* heroCopy = dynamic_cast<Hero*>(nodeA->getParent());
				heroCopy->setBulletCountInHero(heroCopy->getBulletCountInHero() + 50);


				nodeB->retain();
				nodeB->removeFromParent();

				return true;
			}
		}

		// Hero  punch  HealthBox
		else if (((nodeA)->getTag() == QS::kHealthBoxTag && (nodeB)->getTag() == QS::kHeroTag)
			|| ((nodeB)->getTag() == QS::kHealthBoxTag && (nodeA)->getTag() == QS::kHeroTag))
		{
			log("Qiuqiunima");

			if (nodeA->getTag() == QS::kHealthBoxTag)
			{
				auto* heroCopy = dynamic_cast<Hero*>(nodeB->getParent());
				heroCopy->setHealth(heroCopy->getMaxHealth());


				nodeA->retain();
				nodeA->removeFromParent();

				return true;
			}
			else
			{
				auto* heroCopy = dynamic_cast<Hero*>(nodeA->getParent());
				heroCopy->setHealth(heroCopy->getMaxHealth());

				nodeB->retain();
				nodeB->removeFromParent();

				return true;
			}
		}
		// Hero  punch  CapacityBox
		else if (((nodeA)->getTag() == QS::kCapacityBoxTag && (nodeB)->getTag() == QS::kHeroTag)
		|| ((nodeB)->getTag() == QS::kCapacityBoxTag && (nodeA)->getTag() == QS::kHeroTag))
		{
		log("Qiuqiunima");

		if (nodeA->getTag() == QS::kCapacityBoxTag)
		{
			auto* heroCopy = dynamic_cast<Hero*>(nodeB->getParent());
			heroCopy->getMainWeapon()->setBulletCountMax(heroCopy->getMainWeapon()->getBulletCountMax()+10);

			nodeA->retain();
			nodeA->removeFromParent();

			return true;
		}
		else
		{
			auto* heroCopy = dynamic_cast<Hero*>(nodeA->getParent());
			heroCopy->getMainWeapon()->setBulletCountMax(heroCopy->getMainWeapon()->getBulletCountMax() + 10);


			nodeB->retain();
			nodeB->removeFromParent();

			return true;
		}
		}
	}


	return false;
}

bool MapLayer::onMouseDown(EventMouse* e)
{
	
	log("mouseDown");
	auto curTime = clock();
	if (static_cast<double>(curTime - m_lastShotTime) / CLOCKS_PER_SEC
		< globalHero->getMainWeapon()->getInterval())
	{
		return true;
	}
	m_lastShotTime = curTime;
	if (globalHero->getMainWeapon()->getBulletCount() == -1)
	{
		globalHero->getMainWeapon()->getSprite()->setVisible(false);
		Bullet* pBullet = globalHero->getMainWeapon()->createBullet();
		//pBullet->attack(0, 0, pHero->getSprite()->getPosition(), pHero->getM_nowFacing());
		//this->addChild(pBullet, 5);
		globalHero->getMainWeapon()->getSprite()->setVisible(true);
	}
	else if(globalHero->getMainWeapon()->getBulletCount() > 0 )
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		//人物精灵在场景中的坐标，再加一点修正
		Vec2 heroPos = globalHero->getPosition() + globalHero->getSprite()->getPosition()-Vec2(0,8.7f);
		//Vec2 heroPos = globalHero->getPosition() + globalHero->getSprite()->getPosition();
		//获取鼠标位置，并修正纵轴位置
		Vec2 mousePos = e->getLocationInView();
		//死也不要改这里980
		mousePos.y += 980;
		//mousePos.y = -mousePos.y;
		//射击方向
		Vec2 dire = mousePos - globalHero->getPosition();

		log("mousePos at: %f, %f", mousePos.x, mousePos.y);
		log("  Hero at: %f, %f", heroPos.x, heroPos.y);
		log("  dire at: %f, %f", dire.x, dire.y);
		Bullet* pBullet = globalHero->getMainWeapon()->createBullet();
		this->addChild(pBullet, QS::kBulletPriority);
		pBullet->setPosition(heroPos);
		pBullet->attack(dire.x, dire.y, heroPos, globalHero->getM_nowFacing());

	}
	return true;
}

void MapLayer::onMouseUp(EventMouse* event)
{
	log("mouseUp");

}


void MapLayer::onMouseMove(EventMouse* e)
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
