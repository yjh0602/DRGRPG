#pragma once
#include "header.h"

// �����
class Hero;

class Monster
{
public:

	// ���� �����
	string name;
	string monsterSize;
	int hp;
	int minDamage;
	int maxDamage;
	int money;
	int _randomDamege;
	int GolemCountMonster = 1;
	int SlimeCountMonster = 1;
	int GoblinCountMonster = 1;
	Monster(string name, string monsterSize, int hp, int minDamage, int maxDamage,int money);
	// ��� �Լ�
	// ���� ���� ���
	void setMonster(string name, string monsterSize, int hp ,int minDamage,int maxDamage, int money);
	//���� ������
	void monsterAttack(Hero* hero, Monster* monster);

	// show info monster.
	void ShowMonsterInfo();
};

