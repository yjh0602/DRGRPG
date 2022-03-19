#include "header.h"
#include "WeaponStore.h"
#include "Hero.h"

void WeaponStore::Waepon(Hero* hero)
{
	hero->minDamage = hero->minDamage + this->minDamage;
	hero->maxDamage = hero->maxDamage + this->maxDamage;
}

void WeaponStore::WaeponInfo(string name, int minDamage, int maxDamage,int price)
{
	this->name = name;    //�̸�
	this->minDamage = minDamage;//������
	this->maxDamage = maxDamage;
	this->price = price;  //����
}
