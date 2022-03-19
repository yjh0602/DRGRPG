#include"BattleSet.h"
#include"Hero.h"
#include"Monster.h"



void BattleSet(Monster* monster, Hero* hero)
{
	while (true)
	{
		cout << monster->name << "의 남은 체력 : " << monster->hp << endl;
		cout << hero->name << "의 남은 체력 : " << hero->hp << endl;
		cout << "     공격  0" << endl;
		cout << "  그만두기  1" << endl;
		

		switch (selBattle)
		{
		case 0:
		{
			hero->Attack(monster);
			monster->monsterAttack(hero);
			if (monster->hp <= 0)
			{
				cout << "   " << monster->name << "이 사망 했습니다." << endl;
				return;
			}

			else if (hero->hp <= 0)
			{
				cout << "   " << hero->name << "이 사망 했습니다." << endl;
				return;
			}
			break;
		}
		case 1:
		{
			return;
		}
		}
	}
}