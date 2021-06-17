#include "MyMenu.h"
#include "Scene/HomePage.h"
#include "MenuSettings.h"
#include "MenuHelp.h"
#include "cocos2d.h"
#include"SceneChangeLoad.h"

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

    MyMenu::loadBackgroundPicture(this);//加载背景图片

    //auto* startItemImage = MenuItemImage::create(
    //    "button/START-normal.png",
    //    "button/START-push.png");

    //auto startItem = MenuItemToggle::createWithCallback(
    //    CC_CALLBACK_1(MyMenu::menuStartCallback, this),
    //    startItemImage,
    //    NULL);
    //startItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4 * 3));




    //auto* settingsItemImage = MenuItemImage::create(
    //    "button/SETTINGS-normal.png",
    //    "button/SETTINGS-push.png");

    //auto settingsItem = MenuItemToggle::createWithCallback(
    //    CC_CALLBACK_1(MyMenu::menuSettingsCallback, this),
    //    settingsItemImage,
    //    NULL);
    //settingsItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));


 

    //auto* helpItemImage = MenuItemImage::create(
    //    "button/HELP-normal.png",
    //    "button/HELP-push.png");

    //auto helpItem = MenuItemToggle::createWithCallback(
    //    CC_CALLBACK_1(MyMenu::menuHelpCallback, this),
    //    helpItemImage,
    //    NULL);

    //helpItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4));

    MenuItemFont::setFontName("POBG");
    MenuItemFont::setFontSize(150);

    MenuItemFont* startItem = MenuItemFont::create("Start",
        CC_CALLBACK_1(MyMenu::menuStartCallback, this));

    MenuItemFont* joinItem = MenuItemFont::create("Join Game",
        CC_CALLBACK_1(MyMenu::menuJoinGameCallback, this));

    MenuItemFont* settingsItem = MenuItemFont::create("Settings",
        CC_CALLBACK_1(MyMenu::menuSettingsCallback, this));

    MenuItemFont* helpItem = MenuItemFont::create("Exit",
        CC_CALLBACK_1(MyMenu::menuExitCallback, this));



    Menu* mn = Menu::create(startItem, joinItem, settingsItem, helpItem, NULL);
    mn->alignItemsVertically();
    //mn->alignItemsVerticallyWithPadding(10);
    //Sprite* lcons = Sprite::create("POBG-sign.png");
    //Size WinSize = Director::getInstance()->getWinSize();
    //float winw = WinSize.width; //获取屏幕宽度
    //float winh = WinSize.height;//获取屏幕高度
    //float spx = lcons->getTextureRect().getMaxX()*4;
    //float spy = lcons->getTextureRect().getMaxY()*4;
    //lcons->setScaleX(winw / spx); //设置精灵宽度缩放比例
    //lcons->setScaleY(winh / spy);
    //lcons->setPosition(Vec2(visibleSize.width / 5, 1.5*origin.y + visibleSize.height/1.2));
    //this->addChild(lcons);
    this->addChild(mn);

    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MyMenu::menuExitCallback, this));

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


void MyMenu::menuExitCallback(Ref* pSender)
{
    Director::getInstance()->end();   
}

void MyMenu::loadBackgroundPicture(cocos2d::Ref* pSender)
{
    MenuItem* item = (MenuItem*)pSender;
    log("Touch Background MenuItem %p", item);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* menuBackground = Sprite::create("menu/MenuBackground.png");
    menuBackground->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    Size mywinsize = Director::getInstance()->getWinSize();
    float winw = mywinsize.width; //获取屏幕宽度
    float winh = mywinsize.height;//获取屏幕高度
    float spx = menuBackground->getTextureRect().getMaxX();
    float spy = menuBackground->getTextureRect().getMaxY();
    menuBackground->setScaleX(winw / spx); //设置精灵宽度缩放比例
    menuBackground->setScaleY(winh / spy);
    this->addChild(menuBackground);

}


void MyMenu::menuStartCallback(Ref* pSender)
{
    auto changeSceneAnmiate = SceneChangeLoad::createScene();
    if (changeSceneAnmiate == nullptr) {
        log("failed change scene create!");
    }
    else {
        log("123 1");
        //Director::getInstance()->pushScene(changeSceneAnmiate);
        //Director::getInstance()->replaceScene(TransitionMoveInT::create(3.0f, changeSceneAnmiate));
        //Director::getInstance()->popScene();
    }
    MenuItem* item = (MenuItem*)pSender;
    log("Touch Start MenuItem %p", item);
    auto scene = HomePage::createScene();
    Director::getInstance()->pushScene(scene);
}

void MyMenu::menuJoinGameCallback(cocos2d::Ref* pSender)
{
    MenuItem* item = (MenuItem*)pSender;
    log("Touch Join Game MenuItem %p", item);
}

void MyMenu::menuSettingsCallback(Ref* pSender)
{
    MenuItem* item = (MenuItem*)pSender;
    log("Touch Settings MenuItem %p", item);
    auto scene = MenuSettings::createScene();
    Director::getInstance()->pushScene(scene);
}

void MyMenu::menuHelpCallback(Ref* pSender)
{
    MenuItem* item = (MenuItem*)pSender;
    log("Touch Help MenuItem %p", item);
    auto scene = MenuHelp::createScene();
    Director::getInstance()->pushScene(scene);
}