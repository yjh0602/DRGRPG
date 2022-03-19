#include<iostream>
#include "Monster.h"
#include "Hero.h"
#include<string>


void FinishMonster(Monster* monster, Hero* hero)
{
	cout << " 마을 귀환 몬스터 정보   " << endl;
	cout << "-----------------------" << endl;

	cout << monster[1].name << "남은 체력 " << monster[1].hp << '\n';
	cout << monster[2].name << "남은 체력 " << monster[2].hp << '\n';
	cout << monster[3].name << "남은 체력 " << monster[3].hp << '\n';


	cout << "-----------------------" << endl;
	cout << "       사망 정보        " << endl;
	cout << "-----------------------" << endl;

	for (int i = 1; i <= 3; i++)
	{
		if (monster[i].hp <= 0)
		{
			cout << monster[i].name << "사망 했습니다." << endl;
		}
	}

	cout << "-----------------------" << '\n' << '\n';
	cout << " 물약 마시기 1 " << endl;
	cout << " 그냥 나가기 2 " << endl;
	int i;
	cin >> i;
	if (i == 1)
	{
		hero->potion();
		cout << hero->name << "의 체력 +100" << endl;
	}

}