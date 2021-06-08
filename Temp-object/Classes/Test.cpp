#include "Test.h"
#include "Hero.h"
#include "Soldier.h"
cocos2d::Scene* Test::createScene()
{
	return Test::create();
}

EventListenerKeyboard* Test::keyBoardListenerOne = nullptr;

bool Test::init()
{
    

    if (!Scene::init()) { return false; }

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
   
    TMXTiledMap* battleMap = TMXTiledMap::create("map1.tmx");
    battleMap->setAnchorPoint(Vec2(0, 0));
    this->addChild(battleMap,-1);
	/*auto back = Sprite::create("menu/RoomBackground.png");
	back->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	addChild(back, -1);*/
    //this->scheduleUpdate();//we want to call the update funtion which belongs to class hero,so it is not necessary to open scheduleUpdate here.
        
    addPlayer();//add a player in a special scene
	return true;
}

void Test::menuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}
void Test::addPlayer()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    PolygonInfo fig;
    Hero* hero = new Soldier;


    fig = AutoPolygon::generatePolygon(QS::kSoldier1, 
                                       Rect(0,0,QS::kSoldierWidth,QS::kSoldierHeight));

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
        hero->setPosition(Point(Vec2(visibleSize.width / 2 + origin.x ,
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
        this->keyBoardListenerOne = keyBoardListenerHero;

        
    }
    //hero->retain();
    
}

