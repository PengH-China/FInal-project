/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software i
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SecondScene.h"
#include "2d/CCScene.h"
#include "AudioEngine.h"
#include "cocos-ext.h"
#include <cocos/ui/UIScale9Sprite.h>
//#define __cocos2d_libs__UIScale9Sprite__
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
    //return HelloWorld::create();  原函数只有这一句
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

#define schedule_selector(_SELECTOR) static_cast<cocos2d::SEL_SCHEDULE>(&_SELECTOR)

void HelloWorld::backhome()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Label* label = Label::createWithSystemFont("I am home!", "Arial", 35);
    label->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(label);
}
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    /*Layer hello = Layer::Layer();
    if (!hello.init())
        return false; 直接layer::init不可行 只能先实例化 */
    if (!Scene::init())
    {
        return false;
    }

    

    /*ui::Scale9Sprite* btnNormal = ui::Scale9Sprite::create("buttonnormal.png");
    ui::Scale9Sprite* btnDown = ui::Scale9Sprite::create("buttonstop.png");
    Label* title = Label::createWithSystemFont("Touch me!", "Marker Felt", 30);
    ControlButton* controlBtn = ControlButton::create(title, btnDown);
    controlBtn->setBackgroundSpriteForState(btnNormal, Control::State::HIGH_LIGHTED);
    controlBtn->setPosition(Point(200, 100));
    controlBtn->setPreferredSize(Size(256, 256));
    this->addChild(controlBtn);九妹 图片伸缩（未学ui设置）*/

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* xiaoRuo1 = Sprite::create("cat.png");
    //xiaoRuo->setPosition(Point(50, 180));
    xiaoRuo1->setPosition(Point(visibleSize.width *0.5f, visibleSize.height *0.5f));
    this->addChild(xiaoRuo1);

    Sprite* xiaoRuo2 = Sprite::create("virus.png");
    xiaoRuo2->setPosition(Point(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
    this->addChild(xiaoRuo2);
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan= CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchEnded=CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, xiaoRuo1);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), xiaoRuo2);
    
    



    //MoveTo* movetohome = MoveTo::create(10.0f, Point(visibleSize.width, visibleSize.height / 2));
    //auto callbackFunc = [&]() {backhome(); }; //backhome的作用是创建文字标签 callbackFunc为回调函数
    //CallFunc* callFunc = CallFunc::create(callbackFunc);
    //Action* actions = Sequence::create(movetohome, callFunc, NULL);
    //xiaoRuo->runAction(actions);

    //学习回调函数lambda为匿名函数  important
    /*auto func = []() {log("Normal"); };*/
   /* Sprite* xiaoRuo = Sprite::create("cat.png");
    xiaoRuo->setPosition(Point(200, 200));
    this->addChild(xiaoRuo);
    auto func = [=]() {
        xiaoRuo->setScale(2);
    };
     CallFunc* callFunc = CallFunc::create(func);
    this->runAction(callFunc);*/
   
    //MoveBy* moveby = MoveBy::create(2.2f, Point(40, 20));
    //JumpBy* jumpby = JumpBy::create(3.0f, Point(50, 1), 100, 5);
    //RotateBy* rotateby = RotateBy::create(2.5f, 220, 10);//旋转
    //Action* actions = Spawn::create(moveby, jumpby, rotateby, NULL); spawn让动作一起播放
    //Action* actions = Sequence::create(moveby, jumpby, rotateby, NULL);sequence让动作逐个播放
    //xiaoRuo->runAction(actions);

    /*JumpBy* jumpby = JumpBy::create(3.0f, Point(50, 1), 100, 1);
    RepeatForever* repeatforeverAction = RepeatForever::create(jumpby);
    Repeat* repeatAction = Repeat::create(jumpby, 3);
    xiaoRuo->runAction(repeatAction);实现固定次数的弹跳 改成repeatforeverAction就是弹无数次*/

    /*ccBezierConfig bezier;
    bezier.controlPoint_1 = Point(100, 0);
    bezier.controlPoint_2 = Point(200, 250);
    bezier.endPosition = Point(300, 0);
    BezierBy* bezierBy = BezierBy::create(4.0f, bezier);
    xiaoRuo->runAction(bezierBy);按照贝塞尔曲线移动*/


    /*Blink* blink = Blink::create(15.0f, 15);
    xiaoRuo->runAction(blink);*/
    /*ScaleTo* scaleTo = ScaleTo::create(2.8f, 0.4f, 1.0f);
    xiaoRuo->runAction(scaleTo);*/
    /*MoveBy* moveBy = MoveBy::create(0.9f, Point(250, 150));
    xiaoRuo->runAction(moveBy);*/



    
    // 教程中设置label及菜单
    ////获取屏幕大小
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    ////创建一个菜单项，类型为图片菜单类型
    //MenuItemImage* pCloseItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    ////创建一个标签
    //Label* label = Label::createWithSystemFont("I am Label Item.", "Arial", 30);
    ////用标签对象创建一个标签菜单项
    //MenuItemLabel* pLabelItem = MenuItemLabel::create(label);
    ////创建菜单（虚拟），用于存放各种菜单项
    //Menu* pMenu = Menu::create(pCloseItem, pLabelItem, NULL);
    ////让所有的菜单项在垂直方向上自动排列
    //pMenu->alignItemsVertically();
    ////设置菜单的坐标
    //pMenu->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    ////添加菜单到层里
    //this->addChild(pMenu, 1); 

    /*Sprite* sprite = Sprite::create("CloseNormal.png");
    sprite->setPosition(Point(200, 200));
    this->addChild(sprite);添加精灵*/
    
    /*auto backgroundAudioID=AudioEngine::play2d("Cornfield?Chase.mp3",true);
    AudioEngine::setVolume(backgroundAudioID, 1);播放音乐（放不出来）*/

    return true;

}
//bool HelloWorld::init()
//{
//    //////small game
//    //// 1
//    //if (!Scene::init()) {
//    //    return false;
//    //}
//    //// 2
//    //auto origin = Director::getInstance()->getVisibleOrigin();
//    //auto winSize = Director::getInstance()->getVisibleSize();
//    //// 3
//    //auto background = DrawNode::create();
//    //background->drawSolidRect(origin, winSize, Color4F(0.6, 0.6, 0.6, 1.0));
//    //this->addChild(background);
//    //// 4
//    //_player = Sprite::create("cat.png");
//    //_player->setPosition(Vec2(winSize.width * 0.25, winSize.height * 0.5));
//    //this->addChild(_player);
//
//    //srand((unsigned int)time(nullptr));
//    //this->schedule(schedule_selector(HelloWorld::addMonster), 1.5);
//    //srand((unsigned int)time(nullptr));
//
//    //auto eventListener = EventListenerTouchOneByOne::create();
//    //eventListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
//    //this->getEventDispatcher() -> addEventListenerWithSceneGraphPriority(eventListener, _player);
//    //return true;
//
//    //////////////////////////////
//    // 1. super init first
//    if ( !Scene::init() )
//    {
//        return false;
//    }
//
//    auto visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//
//    /////////////////////////////
//    // 2. add a menu item with "X" image, which is clicked to quit the program
//    //    you may modify it.
//
//    // add a "close" icon to exit the progress. it's an autorelease object
//    auto closeItem = MenuItemImage::create(
//                                           "CloseNormal.png",
//                                           "CloseSelected.png",
//                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
//
//    if (closeItem == nullptr ||
//        closeItem->getContentSize().width <= 0 ||
//        closeItem->getContentSize().height <= 0)
//    {
//        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
//    }
//    else
//    {
//        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
//        float y = origin.y + closeItem->getContentSize().height/2;
//        closeItem->setPosition(Vec2(x,y));
//    }
//
//    // create menu, it's an autorelease object
//    auto menu = Menu::create(closeItem, NULL);
//    menu->setPosition(Vec2::ZERO);
//    this->addChild(menu, 1);
//
//    /////////////////////////////
//    // 3. add your codes below...
//
//    // add a label shows "Hello World"
//    // create and initialize a label
//
//    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
//    if (label == nullptr)
//    {
//        problemLoading("'fonts/Marker Felt.ttf'");
//    }
//    else
//    {
//        // position the label on the center of the screen
//        label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                                origin.y + visibleSize.height - label->getContentSize().height));
//
//        // add the label as a child to this layer
//        this->addChild(label, 1);
//    }
//
//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//    if (sprite == nullptr)
//    {
//        problemLoading("'HelloWorld.png'");
//    }
//    else
//    {
//        // position the sprite on the center of the screen
//        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//        // add the sprite as a child to this layer
//        this->addChild(sprite, 0);
//    }
//    return true;
//}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    //*/Director::getInstance()->end();原
    //Director::getInstance()->replaceScene(TransitionSlideInT::create(3.0f,SecondScene::createScene()));初转场
    Director::getInstance()->pushScene(SecondScene::createScene());
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}


void HelloWorld::addMonster(float dt) {
    auto monster = Sprite::create("virus.png");

    // 1
    auto monsterContentSize = monster->getContentSize();
    auto selfContentSize = this->getContentSize();
    int minY = monsterContentSize.height / 2;
    int maxY = selfContentSize.height - monsterContentSize.height / 2;
    int rangeY = maxY - minY;
    int randomY = (rand() % rangeY) + minY;

    monster->setPosition(Vec2(selfContentSize.width-1 /*+ monsterContentSize.width / 2*/, randomY));
    this->addChild(monster);

    // 2
    int minDuration = 2.0;
    int maxDuration = 4.0;
    int rangeDuration = maxDuration - minDuration;
    int randomDuration = (rand() % rangeDuration) + minDuration;

    // 3
    auto actionMove = MoveTo::create(randomDuration, Vec2(-monsterContentSize.width / 2, randomY));
    auto actionRemove = RemoveSelf::create();
    monster->runAction(Sequence::create(actionMove, actionRemove, nullptr));
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event/*unused_event*/)
{
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
    if (target->getBoundingBox().containsPoint(pos))
    {
        target->setOpacity(100);
        return true;
    }
    return false;
    ///below are little game
    //// 1  - Just an example for how to get the  _player object
    ////auto node = unused_event->getCurrentTarget();

    //// 2
    //Vec2 touchLocation = touch->getLocation();
    //Vec2 offset = touchLocation - _player->getPosition();

    //// 3
    //if (offset.x < 0) {
    //    return true;
    //}

    //// 4
    //auto projectile = Sprite::create("Syringes.png");
    //projectile->setPosition(_player->getPosition());
    //this->addChild(projectile);

    //// 5
    //offset.normalize();
    //auto shootAmount = offset * 1000;

    //// 6
    //auto realDest = shootAmount + projectile->getPosition();

    //// 7
    //auto actionMove = MoveTo::create(2.0f, realDest);
    //auto actionRemove = RemoveSelf::create();
    //projectile->runAction(Sequence::create(actionMove, actionRemove, nullptr));

    //return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event/*unused_event*/)
{
    log("HelloWorldScene onTouchMoved");
}
void HelloWorld::onTouchEnded(Touch* touch, Event* event/*unused_event*/)
{
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    target->setOpacity(255);
}

