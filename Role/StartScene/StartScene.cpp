#include "startscene.h"
#include "GameOver\GameOver.h"
#include "RoleMoveKeyBoard/RoleMove.h"
USING_NS_CC;
const int  myWeapen = 10;
const int  enemyWeapen = 20;
const int  Me = 100;
const int  Enemy = 200;

Scene* StartScene::createScene()
{
    return StartScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
    if (!Scene::init()){
        return false;
    }
    if (!Scene::initWithPhysics()){
        return false;
    }
    
    auto winSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // set Background with map
    auto backGround = Sprite::create("background.png");
    backGround->setAnchorPoint(Vec2(0,0));
    backGround->setPosition(0,0);
    this->addChild(backGround,-1);

    //add the ninja(role)
    m_pRole = Sprite::create("role.png");
    m_pRole->setPosition(30, winSize.height / 2);
    // Add _player's physicsBody
    //set role physics nature
    auto physicsBody = PhysicsBody::createBox(m_pRole->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(5);
    physicsBody->setContactTestBitmask(1);
    m_pRole->setPhysicsBody(physicsBody);
    m_pRole->setTag(Me);

    addChild(m_pRole);

    //appear the monster
    this->schedule(CC_SCHEDULE_SELECTOR(StartScene::addMonster), 1.5);//schedule :ide could play a function every specific time(the second assignment)
    //this->schedule(schedule_selector(StartScene::addMonster), 1.5);//old

    //click and shoot
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = CC_CALLBACK_2(StartScene::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, m_pRole);

    /*
    auto listenerKey = EventListenerKeyboard::create();
    listenerKey->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        log("key pressed");
        keys[keyCode] = true;

    };
    listenerKey->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        keys[keyCode] = false;
        log("key unpress!");
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);
     */

    auto keyListener = EventListenerKeyboard::create();
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    keyListener->onKeyPressed = CC_CALLBACK_2(StartScene::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(StartScene::onKeyReleased, this);

    dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
    

    this->scheduleUpdate();


    // press keyboard and move  1.0
    /*
   
    auto keyListener = EventListenerKeyboard::create();

    keyListener->onKeyPressed = CC_CALLBACK_2(StartScene::onKeyPressed,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
    */


    return true;
}




void StartScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}


void StartScene::addMonster(float dt) {

    auto monster = Sprite::create("monster.png");
    monster->setTag(Enemy);
    // Add monster
    auto monsterContentSize = monster->getContentSize();
    auto selfContentSize = this->getContentSize();
    int minY = monsterContentSize.height / 2;
    int maxY = selfContentSize.height - minY;
    int rangeY = maxY - minY;
    int randomY = (rand() % rangeY) + minY;
    monster->setPosition(Vec2(selfContentSize.width + monsterContentSize.width / 2, randomY));

    auto physicsBody = PhysicsBody::createBox(monster->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
    physicsBody->setDynamic(false);
    physicsBody->setContactTestBitmask(0xFF);
    physicsBody->setCategoryBitmask(3);       // 0011
    physicsBody->setContactTestBitmask(1);    // 0001
    monster->setPhysicsBody(physicsBody);

    this->addChild(monster);


    int maxX = selfContentSize.width;
    int randomX = maxX - (rand() % (int)(maxX / 2));
    float monsterSpeed = 160;
    float randomDuration2 = (float)randomX / monsterSpeed;
    float randomDuration1 = (float)(maxX - randomX) / monsterSpeed;
    auto move1 = MoveTo::create(randomDuration1, Vec2(randomX, randomY));
    auto move2 = MoveTo::create(randomDuration2, Vec2(-monsterContentSize.width , randomY));

    
    /*
    // Let monster run // a failed try
    int maxX = selfContentSize.width;

    int randomX = maxX - (rand() % (int)(maxX / 2));

 
    const float monsterSpeed = 130;
    const float randomDuration2 = (float)randomX / monsterSpeed;
    const float randomDuration1 = (float)(maxX - randomX) / monsterSpeed;
    auto move1 = MoveTo::create(randomDuration1, Vec2(randomX, 
                                                      m_pRole->getPosition().y));
    auto move2 = MoveTo::create(randomDuration2, m_pRole->getPosition());
    */
    // remove the monster
    auto actionRemove = RemoveSelf::create();

    // Shoot Enemy's Projectile
    auto shootStar = CallFunc::create([=]() {

        
        // creat weapen
        Sprite* weapen = Sprite::create("weapen.png");
        weapen->setPosition(monster->getPosition());
        weapen->setTag(enemyWeapen);
        log("ememyWeapen= %d",weapen->getTag());
        // Add Enemy's weapen's physicsBody
        auto physicsBody = PhysicsBody::createBox(weapen->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
        physicsBody->setDynamic(false);
        physicsBody->setCategoryBitmask(3);
        physicsBody->setContactTestBitmask(4);
        weapen->setPhysicsBody(physicsBody);
        weapen->setTag(1);
        this->addChild(weapen);
        // shoot
        float starSpeed = 120;
        float starDuration = (float)randomX / starSpeed;
        auto weapenMove = MoveTo::create(starDuration, m_pRole->getPosition());
        auto weapenRemove = RemoveSelf::create();
        weapen->runAction(Sequence::create(weapenMove, weapenRemove, nullptr));
                                      });
    
    auto delay = DelayTime::create(0.1f);
    monster->runAction(Sequence::create(move1, delay, shootStar, move2, actionRemove, nullptr));

}

// HelloWorldScene.cpp
bool StartScene::onTouchBegan(Touch* touch, Event* unused_event) {
    // 1 - Just an example for how to get the player object
    // 说明一下作为第二个参数传递给addEventListenerWithSceneGraphPriority(eventListener, _player)的_player对象被访问的方式。
    // auto node = unused_event->getcurrentTarget();

    // 2.the click position
    Vec2 touchLocation = touch->getLocation();
    Vec2 offset = touchLocation - m_pRole->getPosition();
    
    if (offset.x < 0) {
        return true;
    }//you can not shoot towards your back

    // 3.add its weapen
    auto weapen = Sprite::create("weapen.png");
    weapen->setPosition(m_pRole->getPosition());
    weapen->setTag(myWeapen);

    auto physicsBody = PhysicsBody::createBox(weapen->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
    physicsBody->setDynamic(false);
    physicsBody->setContactTestBitmask(0xFF);
    physicsBody->setCategoryBitmask(5);       // 0101
    physicsBody->setContactTestBitmask(2);    // 0010
    weapen->setPhysicsBody(physicsBody);
    weapen->setTag(10);
   
    this->addChild(weapen);

    // 4.change its length to 1
    offset.normalize();
    // to insure the shoot could cross the whole windows
    auto shootAmount = offset * 1000;
    // the final destination
    auto realDest = shootAmount + weapen->getPosition();

    // 5.creat an action and remove itself
    auto actionMove = MoveTo::create(2.0f, realDest);
    auto actionRemove = RemoveSelf::create();
    weapen->runAction(Sequence::create(actionMove, actionRemove, nullptr));

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(StartScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
  

    return true;
}


bool StartScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA && nodeB)
    {
        int tagA = nodeA->getTag();
        int tagB = nodeB->getTag();
        log("onContact!! tagA = %d, tagB = %d", tagA, tagB);
        if (tagA == Me || tagB == Me) {
            log("Game over");
            Director::getInstance()->replaceScene(GameOver::createScene());               
        }// 当player碰到碰到敌人或者敌人的飞镖，GameOver处理

        // 当player的飞镖碰到敌人或者敌人的飞镖，将它们杀死
        if (tagA == myWeapen|| tagB == myWeapen) {
            nodeB->removeFromParentAndCleanup(true);
            nodeA->removeFromParentAndCleanup(true);
        }
        
        
    }
    return true;
}

//the first version of keyboard control
/*
void StartScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* events)
{

    log("Key with keycode %d pressed", keyCode);

    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_D:
        {
            auto moveBy = MoveBy::create(0.2f, Vec2(20, 0));
            m_pRole->runAction(Sequence::create(moveBy, nullptr));
            break;
        }
        case EventKeyboard::KeyCode::KEY_A:
        {
            auto moveBy = MoveBy::create(0.2f, Vec2(-20, 0));
            m_pRole->runAction(Sequence::create(moveBy, nullptr));
            break;
        }
        case EventKeyboard::KeyCode::KEY_W:
        {
            auto moveBy = MoveBy::create(0.2f, Vec2(0, 20));
            m_pRole->runAction(Sequence::create(moveBy, nullptr));
            break;
        }
        case EventKeyboard::KeyCode::KEY_S:
        {
            auto moveBy = MoveBy::create(0.2f, Vec2(0, -20));
            m_pRole->runAction(Sequence::create(moveBy, nullptr));
            break;
        }
        default:
            break;
    }

}
*/
//normal contact
#if 0
bool StartScene::onContactBegin(PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA && nodeB)
    {
        nodeB->removeFromParentAndCleanup(true);
        nodeA->removeFromParentAndCleanup(true);
    }

    return true;
}
#endif

//if you is presssing the keyboard all the time
bool StartScene::isKeyPressed(EventKeyboard::KeyCode keyCode) {
    if (keys[keyCode]) {
        return true;
    }
    else {
        return false;
    }
}


void StartScene::update(float delta) {
    Node::update(delta);
    const auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW,
        rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
        upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW,
        downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
    //log("update");
    if (isKeyPressed(leftArrow)) {
        log("Left!!");
        keyPressedDuration(leftArrow);
        return;
    }
    else if (isKeyPressed(rightArrow)) {
        keyPressedDuration(rightArrow);
        log("Right!!");
        return;
    }
    else if (isKeyPressed(upArrow)) {
        keyPressedDuration(upArrow);
        log("Up!!");
        return;
    }
    else if (isKeyPressed(downArrow)) {
        keyPressedDuration(downArrow);
        log("Down!!");
        return;
    }
    else {
        return;
    }
}

void StartScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* events) {
    log("Pressed! %d",int(keyCode));
    keys[keyCode] = true;
}
void StartScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* events) {
    log("Unpressed! %d", int(keyCode));
    keys[keyCode] = false;
}

void StartScene::keyPressedDuration(EventKeyboard::KeyCode code) {
    log("keyPressedDuration");
    int offsetX = 0, offsetY = 0;
    switch (code) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW: {
            offsetX = -3;
            break;
        }            
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: {
            offsetX = 3;
            break;
        }           
        case EventKeyboard::KeyCode::KEY_UP_ARROW: {
            offsetY = 3;
            break;
            }
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW: {
            offsetY = -3;
            break;
        }
        default:
            offsetY = offsetX = 0;
            break;
    }
    // 0.3s duration
    auto moveTo = MoveTo::create(1.0f, Vec2(m_pRole->getPositionX() + offsetX,
                                           m_pRole->getPositionY() + offsetY));
    m_pRole->runAction(Sequence::create(moveTo,nullptr));
    m_pRole->stopAction(moveTo);
    log("x: %d, y: %d", m_pRole->getPosition().x, m_pRole->getPosition().y);
}