#include "MyMenu.h"
#include "MenuSettings.h"
#include "MenuHelp.h"
#include "cocos2d.h"

USING_NS_CC;

Scene* MyMenu::createScene()
{
    return MyMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MyMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* menuBackground = Sprite::create("menu/background.jpg");
    menuBackground->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    this->addChild(menuBackground);


    MenuItemFont::setFontName("POBG");
    MenuItemFont::setFontSize(86);

    MenuItemFont* item1 = MenuItemFont::create("Start",
        CC_CALLBACK_1(MyMenu::menuItem1Callback, this));

    MenuItemFont* item2 = MenuItemFont::create("Settings",
        CC_CALLBACK_1(MyMenu::menuItem2Callback, this));

    MenuItemFont* item3 = MenuItemFont::create("Help",
        CC_CALLBACK_1(MyMenu::menuItem3Callback, this));

    Menu* mn = Menu::create(item1, item2, item3, NULL);
    mn->alignItemsVertically();
    this->addChild(mn);

    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MyMenu::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}


void MyMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application

    //auto mt = MyMenu::createScene();
    //Director::getInstance()->pushScene(mt);

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    EventCustom customEndEvent("game_scene_close_event");
    _eventDispatcher->dispatchEvent(&customEndEvent);
}


void MyMenu::menuItem1Callback(Ref* pSender)
{
    MenuItem* item = (MenuItem*)pSender;
    log("Touch Start MenuItem %p", item);
}

void MyMenu::menuItem2Callback(Ref* pSender)
{
    MenuItem* item = (MenuItem*)pSender;
    log("Touch Settings MenuItem %p", item);
    auto scene = MenuSettings::createScene();
    Director::getInstance()->pushScene(scene);
}

void MyMenu::menuItem3Callback(Ref* pSender)
{
    MenuItem* item = (MenuItem*)pSender;
    log("Touch Help MenuItem %p", item);
    auto scene = MenuHelp::createScene();
    Director::getInstance()->pushScene(scene);
}