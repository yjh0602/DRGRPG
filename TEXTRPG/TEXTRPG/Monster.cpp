#include "Monster.h"
#include "Hero.h"

// ������

// ��� �Լ�
// ���� ���� ���
Monster::Monster(string name, string monsterSize, int hp, int minDamage ,int maxDamage, int money)
{
	this->name = name;
	this->monsterSize = monsterSize;
	this->hp = hp;
	this->minDamage = minDamage;
	this->maxDamage = maxDamage;
	this->money = money;
}
void Monster::setMonster(string name, string monsterSize, int hp, int minDamage , int maxDamage, int money)
{
	this->name = name;
	this->monsterSize = monsterSize;
	this->hp = hp;
	this->minDamage = minDamage;
	this->maxDamage = maxDamage;
	this->money = money;
	
}
void Monster::monsterAttack(Hero* hero, Monster* monster)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(monster->minDamage, monster->maxDamage);
	monster->_randomDamege = dis(gen);
	hero->hp = hero->hp - monster->_randomDamege;
	

}

	// show info monster.
void Monster::ShowMonsterInfo()
{
	cout << "-----------------------" <<endl;
	cout << "  ũ�� : " << this->monsterSize << endl;
	cout << "  �̸� : " << this->name << endl;
	cout << "  ü�� : " << this->hp << endl;
	cout << "  ���ݷ� : " << this->minDamage << " ~ " << this->maxDamage << endl;
	cout << "  ��差 : " << this->money << endl;
	cout << "-----------------------" << endl;
}
