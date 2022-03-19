#include "header.h"
#include "PotionStore.h"
#include "Hero.h"


void PotionStore::Potion(Hero* hero)
{

	hero->hp = hero->hp + this->hill ;

}
void PotionStore::PotionInfo(string name, int hill,int price)
{
	this->name = name;
	this->hill = hill;
	this->price = price;
}
