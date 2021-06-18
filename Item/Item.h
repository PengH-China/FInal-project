/**
*@file Item.h
*@author 蔡明宏
*@date 5/28/2021
*/
#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
//#include "Role/Hero.h"
#include "Const/Const.h"

using namespace cocos2d;

/**
*@brief 物品类
*@author 蔡明宏
*/

class Item :public Node
{
public:
	/**
	*@brief 绑定精灵
	*/
	void bindSprite(Sprite* pSprite);

	/**
	*@brief 获取精灵
	*@author 蔡明宏
	*/
	Sprite* getSprite();

	/**
	*@brief 交互函数
	*@author 蔡明宏
	*/
	/*virtual void interact() = 0;*/

	/**
	*@brief 修改m_pPresentContactItem
	*@author 蔡明宏
	*/
	virtual bool onContactBegin(PhysicsContact& contact);
	virtual bool onContactSeparate(PhysicsContact& contact);

	/**
	*@brief 设置物理体
	*@author 蔡明宏
	*/
	void generatePhysicalBody(std::string message, const std::string itemName);
	/**
	*@brief 是否可打开箱子
	*@author 彭浩
	*/
	bool isAbleOpen();
protected:
	Sprite* m_pSprite;
};

/**
*@brief 辅助函数，用于显示信息
*@author 蔡明宏
*/
#endif
#pragma once
