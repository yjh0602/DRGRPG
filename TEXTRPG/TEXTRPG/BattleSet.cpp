#include"BattleSet.h"
#include"Hero.h"
#include"Monster.h"



void BattleSet(Monster* monster, Hero* hero)
{
	while (true)
	{
		cout << monster->name << "�� ���� ü�� : " << monster->hp << endl;
		cout << hero->name << "�� ���� ü�� : " << hero->hp << endl;
		cout << "     ����  0" << endl;
		cout << "  �׸��α�  1" << endl;
		

		switch (selBattle)
		{
		case 0:
		{
			hero->Attack(monster);
			monster->monsterAttack(hero);
			if (monster->hp <= 0)
			{
				cout << "   " << monster->name << "�� ��� �߽��ϴ�." << endl;
				return;
			}

			else if (hero->hp <= 0)
			{
				cout << "   " << hero->name << "�� ��� �߽��ϴ�." << endl;
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