#ifndef _ITEM_H_
#define _ITEM_H_

#include "cocos2d.h"
#include "Const/Const.h"
#include "ui/CocosGUI.h"


using namespace cocos2d;

/**
*@brief 物品类
*/
class Item :public Node
{
public:
	/**
	*@brief 绑定精灵
	*/
	void bindSprite(Sprite* pSprite);

	Sprite* getSprite();



	virtual bool onContactBegin(PhysicsContact& contact);
	virtual bool onContactSeparate(PhysicsContact& contact);

	/**
	*@brief 设置物理体
	*/
	void generatePhysicalBody(std::string message, int itemTag);

protected:
	Sprite* m_pSprite;
};

#endif
#pragma once
