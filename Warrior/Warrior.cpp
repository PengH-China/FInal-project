/**
*@file Warrior.cpp
*@author 彭浩(peng hao)
*@time 2021-05-26
*/

#include "Warrior.h"

std::string Warrior::s_roleName = "Warrior";


const char* Warrior::roleName() {
	return s_roleName.c_str();
}

Scene* Warrior::createScene()
{
    return Warrior::create();
}

bool Warrior::init()
{
    if (!Hero::init()) { return false; }
    auto role = Sprite::create("010_01.png");
    bindSprite(role);

    auto backGround = Sprite::create("background.png");
    backGround->setAnchorPoint(Vec2(0, 0));
    backGround->setPosition(0, 0);
    this->addChild(backGround, -1);


    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(Warrior::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(Warrior::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener,this);
    /*
	if (m_pPresentHero == nullptr)
	{
		m_pPresentHero = this;
		scheduleUpdate();
		m_pMoveAnimation = creatActorAnimate("010_0");
		m_pRestAnimation = creatActorAnimate("010_0");

		/*
        setMainWeapon(Gun::create());
		setSecondWeapon(Sword::create());
		m_pSecWeapon->setVisible(false);
		m_pMoveAnimate = creatActorAnimate(sk::files::kKnightMove);
		m_pRestAnimate = creatActorAnimate(sk::files::kKnightRest);
		m_skillCD = 15;
		m_skillTime = 15;
		m_skillLastTime = 5;
		m_ID = sk::HeroID::kKnight;
        
		return true;
	}
	else
	{
		return false;
	}*/
    return true;
}

void Warrior::upGrade() {
	grade++;//upgrade
	(m_health >= 100) ? NULL : m_health += 10;//increase health value
}



bool Warrior::isKeyPressed(EventKeyboard::KeyCode keyCode) {
    if (keys[keyCode]) {
        return true;
    }
    else {
        return false;
    }
}


void Warrior::update(float delta) {//detect every seconds what have done
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

void Warrior::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* events) {
    log("Pressed! %d", int(keyCode));
    keys[keyCode] = true;
}
void Warrior::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* events) {
    log("Unpressed! %d", int(keyCode));
    keys[keyCode] = false;
}

void Warrior::keyPressedDuration(EventKeyboard::KeyCode code) {
    log("keyPressedDuration");
    int offsetX = 0, offsetY = 0;
    switch (code) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW: {
            offsetX = -1;
            break;
        }
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: {
            offsetX = 1;
            break;
        }
        case EventKeyboard::KeyCode::KEY_UP_ARROW: {
            offsetY = 1;
            break;
        }
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW: {
            offsetY = -1;
            break;
        }
        default:
            offsetY = offsetX = 0;
            break;
    }
    // 0.3s duration
    auto moveTo = MoveTo::create(1.0f, Vec2(m_pRole->getPositionX() + offsetX,
                                            m_pRole->getPositionY() + offsetY));
    m_pRole->runAction(Sequence::create(moveTo, nullptr));
}