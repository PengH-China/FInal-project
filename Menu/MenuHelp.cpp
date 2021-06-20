/**
*@file MenuHelp.cpp
*@author 张子涵
*@date 5/27/2021
*/

#include "MenuHelp.h"

Scene* MenuHelp::createScene()
{
    return MenuHelp::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MenuHelp::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    loadBackgroundPicture(this);//load background picture

    MenuItemFont::setFontName("POBG");
    MenuItemFont::setFontSize(86);

    auto introduction = Sprite::create("menu/Help/help.png");
    if (introduction == nullptr) {
        log("the help png is null");
    }
    else {
        introduction->setAnchorPoint(Vec2(0.5f, 0.5f));
        introduction->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
        addChild(introduction);
    }

    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MenuHelp::menuCloseCallback, this));

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


void MenuHelp::loadBackgroundPicture(cocos2d::Ref* pSender)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* menuBackground = Sprite::create("menu/background.jpg");
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



void MenuHelp::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}

