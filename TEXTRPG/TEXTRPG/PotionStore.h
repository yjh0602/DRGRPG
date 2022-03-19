#pragma once
#include"header.h"
#include"Hero.h"


class PotionStore
{
public:
	string name;
	int hill;
	int price;

	void PotionInfo(string name, int hill, int price);
	void Potion(Hero* hero);
};