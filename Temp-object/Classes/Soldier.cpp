/**
*@file Soldier.cpp
*@author 彭浩(peng hao)
*@time 2021-05-26
*/

#include "Soldier.h"

std::string Soldier::s_roleName = "Soldier";


bool Soldier::init()
{
	return true;
}

const char* Soldier::roleName() {
	return s_roleName.c_str();
}


//bool Soldier::init()
//{
//    if (!Hero::init()) { return false; }
//    auto role = Sprite::create("010_01.png");
//    bindSprite(role);
//
//    auto backGround = Sprite::create("background.png");
//    backGround->setAnchorPoint(Vec2(0, 0));
//    backGround->setPosition(0, 0);
//    this->addChild(backGround, -1);
//
//
//    auto keyListener = EventListenerKeyboard::create();
//    keyListener->onKeyPressed = CC_CALLBACK_2(Soldier::onKeyPressed, this);
//    keyListener->onKeyReleased = CC_CALLBACK_2(Soldier::onKeyReleased, this);
//
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener,this);
//    
//    return true;
//}

