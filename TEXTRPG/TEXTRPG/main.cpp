#include "header.h"
#include "Monster.h"
#include "Hero.h"
#include "PotionStore.h"
#include "WeaponStore.h"
#include "Screen.h"
#include "Color.h"
using namespace std;

//���� �÷��� ��� �����ϱ� �ҷ�����.
enum GAME_MODE
{
	GM_NONE, //0
	GM_NEW,  //1
	GM_LOAD, //2
	GM_END   //3
};
//���� ����
Color color;
enum {
	BLACK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_SKYBLUE,
	DARK_RED,
	DARK_VOILET,
	DAKR_YELLOW,
	GRAY,
	DARK_GRAY,
	BLUE,
	GREEN,
	SKYBLUE,
	RED,
	VIOLET,
	YELLOW,
	WHITE,
};
//ȭ�� ����
Screen screen;

//�����ϱ� (bool �� �̿��ؼ� ������ true false ���� Ȯ��)
bool SavePlayer(Hero* hero)
{
	FILE* pFile = NULL;
	fopen_s(&pFile, "player.A", "wb");
	if (pFile)
	{
		fwrite(&hero->name, sizeof(hero->name), 1, pFile);
		//ü���� �о�´�
		fwrite(&hero->hp, 4, 1, pFile);
		//���ݷ� �о����
		fwrite(&hero->minDamage, 4, 1, pFile);
		fwrite(&hero->maxDamage, 4, 1, pFile);
		//�� �о����
		fwrite(&hero->money, 4, 1, pFile);

		fclose(pFile);
		return true;
	}
	return false;
};
//�ҷ����� �Լ��� ����ؼ� �����س��� �����͸� �ҷ��´�.
//(bool �� �̿��ؼ� ������ true false ���� Ȯ��)
bool LoadPlayer(Hero* hero)

{   //������ �ε��ϴ� �Լ�
	FILE* pFile = NULL;
	fopen_s(&pFile, "player.A", "rb");
	
	if(pFile)
	{
		fread(&hero->name, sizeof(hero->name), 1, pFile);
		//ü���� �о�´�
		fread(&hero->hp, 4, 1, pFile);
		//���ݷ� �о����
		fread(&hero->minDamage, 4, 1, pFile);
		fread(&hero->maxDamage, 4, 1, pFile);
		//�� �о����
		fread(&hero->money, 4, 1, pFile);
	
		fclose(pFile);
		return true;
	}


	return false;
}



//���� �ý��� ����, ��� �ý���
void BattleSet(Monster* monster, Hero* hero)
{
	int selBattle;
	while (true)
	{
		system("cls");
		cout << "     �� ĳ���Ͱ� ���� ���������� �����ϰ� �ֻ����� �������� �������� ���ϴ�. " << endl << endl;
		cout << "     �� " << monster->name << "�� ���� ü�� :  ";
		color.setColor(GREEN);
		cout << monster->hp << endl;
		color.setColor(WHITE);
		cout << "     �� " <<monster->name << "�� ������ :  " << monster->minDamage << " ~ " << monster->maxDamage << endl << endl;
		cout << "     �� " << hero->name << "�� ���� ü�� :   ";
		color.setColor(GREEN);
		cout << hero->hp << endl;
		color.setColor(WHITE);
		cout << "     �� " << hero->name << "�� ������ :  " << hero->minDamage << " ~ " << hero->maxDamage << endl << endl;
		cout << "---------------------------------------------------------------------------------" << endl;
		cout << "                                ����  0" << endl;
		cout << "                              �׸��α�  1" << endl;
		cout << "---------------------------------------------------------------------------------" << endl;
		cin >> selBattle;
		switch (selBattle)
		{
		case 0:
			//������� ���� ��ũ��ȭ
		{   color.setColor(RED);
			screen.ScreenBow();
			Sleep(800);
			system("cls");
			screen.ScreenBowShot();
			Sleep(500);
			system("cls");
			color.setColor(YELLOW);
			screen.AttackEffect();	
			color.setColor(WHITE);
			Sleep(500);
			hero->Attack(monster, hero);
			// ���� �Լ��� �̿��ؼ� ������ �� �Է�
			cout << "=========================================" << endl;
			cout << "        �� " << monster->name << " -";
			color.setColor(SKYBLUE);
			cout << hero->_randomDamege;
			color.setColor(WHITE);
			cout << " ��ŭ ���ظ� �Ծ����ϴ�." << endl << endl;
			Sleep(1000);
			//ü���� 0�� �ɽ� ������ ���ϰ� ����� ����.
			if (monster->hp >= 0)
			{
			monster->monsterAttack(hero, monster);
			cout << "        �� " << hero->name << " -";
			color.setColor(SKYBLUE);
			cout << monster->_randomDamege;
			color.setColor(WHITE);
			cout << "  ��ŭ ���ظ� �Ծ����ϴ�." << endl;
			cout << "=========================================" << endl;
			}
			else if (monster->hp <= 0)
			{
				color.setColor(SKYBLUE);
				cout << monster->name;
				color.setColor(WHITE);
				cout << " �� ��� �߽��ϴ�." << endl;
			}
			Sleep(1000);
			
		
			system("cls");
					
			//���� ����� �� ȹ��
			if (monster->hp <= 0)
			{
				color.setColor(RED);
				cout << "====================================================" << endl;
				color.setColor(WHITE);
				cout << "   " << monster->name << "�� ��� �߽��ϴ�." << endl;
				hero->money = monster->money + hero->money;
				cout << "   " << monster->money << "  ���� ȹ���߽��ϴ�." << endl;
				color.setColor(RED);
				cout << "====================================================" << endl << endl;
				color.setColor(WHITE);
			
				return;
			}
			//����� ����� ���� ���� ȸ�� ���̾����� ���ӿ���
			else if (hero->hp <= 0)
			{
				cout << "   " << hero->name << "�� ��� �߽��ϴ�." << endl;
				if (hero->money >= 250)
				{
					hero->money = hero->money - 250;
					cout << "250$�� �����ϰ� ü���� ȸ�� �߽��ϴ�." << endl;
					hero->hp = (hero->hp * 0) + 500;
					return;
				}
				else
				{
					cout << "���� �����ؼ� ȸ�� ���� ���ϰ� ��� �Ͽ����ϴ�." << endl << endl;
					color.setColor(RED);
					cout << "  --------------GAME  OVER --------------  " << endl;
					color.setColor(BLUE);
					cout << "  --------------GAME  OVER --------------  " << endl;
					color.setColor(GREEN);
					cout << "  --------------GAME  OVER --------------  " << endl;
					color.setColor(WHITE);
					return;
				}
			}
			break;
		}
		   // �׸��ΰ� ������.
		case 1:
		{   
			system("cls");
			return;
		}
		}
		
	}
}

//���ǻ���
void Potion_(Hero* hero)
{   
	color.setColor(YELLOW);
	screen.ScreenPotion();
	color.setColor(WHITE);
	Sleep(500);
	cout << "---------------------------------------------------" << endl;
	cout << "           ������� ���� ���� �Դϴ�." << endl;
	cout << "---------------------------------------------------" << endl;
	PotionStore potionStore;
	int v;
	cout << "                   ���� ����        " << endl;
	cout << "          -------------------------" << endl;
	cout << hero->name << "�� ������ : " << hero->money << endl;
	cout << hero->name << "�� HP : " << hero->hp << endl;
	while (true)
	{
        cout << "���� �����Դϴ�." << endl;
        cout << "������ ������ �����ϼ���" << endl;
		cout << "1.�������� $50";
		color.setColor(RED);
		cout<< "    + 100 " << endl;
		color.setColor(WHITE);
		cout << "2.Ȳ������ $200";
		color.setColor(RED);
		cout << "   + 500 " << endl;
		color.setColor(WHITE);
		cout << "3.������" << endl << endl;
		cin >> v;
		if (v == 1)
		{
			if (hero->money >= 50)
			{
				potionStore.PotionInfo("��������", 100, 50);
				potionStore.Potion(hero);
				cout << hero->name << "�� HP" << potionStore.hill << " ȸ�� �Ǿ����ϴ�." << endl;
				hero->money = hero->money - potionStore.price;
				cout << hero->money << "�� ���ҽ��ϴ�." << endl << endl;
				
				cout << "=============================================" << endl;
				system("pause");
				system("cls");
			}
			else
			{
				cout << "���� �����մϴ�" << endl;
				break;
			}
			break;
		}
		else if (v == 2)
		{
			if (hero->money >= 90)
			{
				potionStore.PotionInfo("Ȳ������", 500, 200);
				potionStore.Potion(hero);
				cout << hero->name << "�� HP" << potionStore.hill << " ȸ�� �Ǿ����ϴ�." << endl;
				hero->money = hero->money - potionStore.price;
				cout << hero->money << "�� ���ҽ��ϴ�." << endl << endl;

				cout << "=============================================" << endl;
				system("pause");
				system("cls");
			}
			else
			{
				cout << "���� �����մϴ�" << endl;
				break;
			}
			break;
		}
		else
		{
			break;
		}
		
		cout << endl << endl;
		break;
	}
	return ;
}

//���� ����
void Waepon_(Hero* hero)
{
	color.setColor(SKYBLUE);
	screen.ScreenWaepon();
	
	WeaponStore weaponStore;
	int v;
	color.setColor(WHITE);
	Sleep(500);
	cout << "---------------------------------------------------" << endl;
	cout << "        � ���ð� ����� ȭ�� �����ϼ�  " << endl;
	cout << "---------------------------------------------------" << endl;
	Sleep(700);
	cout << "                   ȭ�� ����        " << endl;
	cout << "          -------------------------" << endl;
	cout << hero->name << "�� ������ : " << hero->money << endl << endl;
	while (true)
	{
		cout << "ȭ�� �����Դϴ�." << endl;
		cout << "������ ȭ���� �����ϼ���" << endl;
		color.setColor(BLUE);
		cout << "1.���� ȭ��  $1000" << endl;
		cout << "minDmg : +10  maxDmg : +50" << endl;
		cout << " ������ ���� ������ ȭ���Դϴ�." << endl;
		color.setColor(YELLOW);
		cout << "2.���� ȭ�� $5000" << endl;
		cout << "minDmg : +80, maxDmg : +200" << endl;
		cout << "  ���� ��� ���� �մ� ������ ȭ�� �Դϴ�." << endl;
		color.setColor(SKYBLUE);
		cout << "3.!!!!��ȭ �ϱ�!!!!" << endl;
		color.setColor(WHITE);
		cout << "4.������" << endl << endl;
		cin >> v;
		system("cls");
		//���� ȭ��
		if (v == 1)
		{
			weaponStore.WaeponInfo("���� ȭ��", 10 , 50 , 1000);
			if (hero->money >= 1000)
			{   
				cout << "�� �� �� ��" << endl;
				weaponStore.Waepon(hero);
				cout << hero->name << "�� �ּ� ���ݷ��� " << weaponStore.minDamage << " ��� �Ǿ����ϴ�." << endl;
				cout << hero->name << "�� �ִ� ���ݷ��� " << weaponStore.maxDamage << " ��� �Ǿ����ϴ�." << endl;
				hero->money = hero->money - weaponStore.price;
				cout << hero->money << "�� ���ҽ��ϴ�." << endl;
				break;
			}
			else
			{
				
				cout << "-------------------------------------- " << endl;
				color.setColor(GREEN);
				Sleep(700);
				cout << "�����";
				Sleep(700);
				cout << ".......�ϳ�.";
				Sleep(500);
				cout << ".......�ο�....." << endl;
				Sleep(1500);
				color.setColor(BLUE);
				cout << "���� ȭ�� ";
				color.setColor(GREEN);
				cout <<	"�� ������ ���� �������ݾ�" << endl;
				Sleep(700);
				cout << "                  ������ ���� ��������" << endl;
				Sleep(300);
				color.setColor(WHITE);
				cout << "-------------------------------------- " << endl;
				Sleep(200);
				
				break;
			}
			break;
		}
	    //���� ȭ��
		else if (v == 2)
		{
			weaponStore.WaeponInfo("���� ȭ��", 50 , 270 , 5000);
			if (hero->money >= 5000)
			{
				
				cout << "�� �� �� ��" << endl;
				weaponStore.Waepon(hero);
				cout << hero->name << "�� �ּ� ���ݷ� :  " << weaponStore.minDamage << " ��� �Ǿ����ϴ�." << endl;
				cout << hero->name << "�� �ִ� ���ݷ� :  " << weaponStore.maxDamage << " ��� �Ǿ����ϴ�." << endl;
				hero->money = hero->money - weaponStore.price;
				cout << hero->money << "�� ���ҽ��ϴ�." << endl;
				break;
			}
			else
			{
				cout << "-------------------------------------- " << endl;
				color.setColor(GREEN);
				Sleep(700);
				cout << "�����";
				Sleep(700);
				cout << ".......�ϳ�.";
				Sleep(500);
				cout << ".......�ο�....." << endl;
				Sleep(1500);
				color.setColor(YELLOW);
				cout << "���� ȭ�� ";
				color.setColor(GREEN);
				cout << " �� ������ ���� �������ݾ�" << endl;
				Sleep(700);
				cout << "                ������ ���� ��������" << endl;
				Sleep(300);
				color.setColor(WHITE);
				cout << "-------------------------------------- " << endl;
				Sleep(200);
				break;
			}
			break;
		}
		//��ȭ�ý���
		else if (v == 3)
		{   
			while(true)
			{
				color.setColor(SKYBLUE);
				cout << " =============== " << hero->name << "�� ������ :" << hero->money << " ===============" << endl;
				cout << " ============== " << hero->name << " : " << hero->minDamage << " ~ " << hero->maxDamage << " DAMAGE " << " ============== " << endl << endl;
				color.setColor(GREEN);
				cout << " =========��ȭ �ý��� �Դϴ�= $100 ���� �ϸ� ��ȭ�� ����˴ϴ�.  ==========" << endl;
				cout << " =========����Ȯ�� 50% �뼺�� 10% // ����Ȯ�� 35% �����Ȯ�� 5%  ==========" << endl;
				color.setColor(WHITE);
				cout << "         �ּ� ������ ��ȭ�� �� 1" << endl;
				cout << "         �ִ� ������ ��ȭ�� �� 2" << endl;
				cout << "            ��ȭ ������  �� 3" << endl;
				int input;
				cin >> input;
				
				//���� �����ҽ� �극��ũ
				if (hero->money < 100)
				{
					color.setColor(RED);
					cout << "      ���� ���� �մϴ�       " << endl << endl;
					color.setColor(WHITE);
					break;
				}
				//�ּҵ������� �ִ뵥������ �����������ϴ�.
				if (hero->minDamage > hero->maxDamage)
				{
					color.setColor(RED);
					cout << "�ּ� �������� �ִ� �������� ������ �����ϴ�." << endl;
					Sleep(1500);
					break;
				}
				//�������� -�� �ɼ� �����ϴ�.
				else if (hero->minDamage < 0 && hero->maxDamage < 0)
				{
					color.setColor(RED);
					cout << "�������� - �� �ɼ� �����ϴ�." << endl;
					Sleep(1500);
					break;
				}
				//�ּ� ������ ���׷��̵�
				if (input == 1)
				{
					cout << "++++++++++++++++++++++��ȭ ������+++++++++++++++++++" << endl << endl;
					Sleep(1000);
					random_device rd;
					mt19937 gen(rd());
					uniform_int_distribution<int> _weaponUp(1, 103);
					int weaponUp = _weaponUp(gen);
					//50����
					if (weaponUp <= 50)// 50= 50 ��
					{
						cout << "          50%����!! +5 Damage" << endl;
						hero->minDamage += 5;
						hero->money -= 100;
						Sleep(500);
					}
					//10����
					else if (51 <= weaponUp && weaponUp <= 61) // 51 61 =10 ��
					{
						color.setColor(SKYBLUE);
						cout << "          10%�뼺��!! +20 Damage" << endl;
						hero->minDamage += 20;
						hero->money -= 100;
						color.setColor(WHITE);
						Sleep(500);
					}
					//35����
					else if (62 <= weaponUp && weaponUp <= 97) // 62 72 82 87 97= 35 �� 
					{

						cout << "          35%����.. -3 Damage" << endl;
						hero->minDamage -= 3;
						hero->money -= 100;
						//0���� �۾����� �ٽ� 1�� �ʱ�ȭ.
						if (hero->minDamage <= 0)
						{
							hero->minDamage = 1;
							cout << "�������� -�� �������� 1�� �ʱ�ȭ �Ǿ����ϴ�." << endl << endl;
						}
						Sleep(500);
					}
					//5����
					else if (98 <= weaponUp && weaponUp <= 103) // 98 103 = 10�� 
					{
						color.setColor(RED);
						cout << "           5%�����.. -15 Damage " << endl;
						color.setColor(WHITE);
						hero->minDamage -= 15;
						hero->money -= 100;
						//0���� �۾����� �ٽ� 1�� �ʱ�ȭ.
						if (hero->minDamage <= 0)
						{
							hero->minDamage = 1;
							cout << "�������� -�� �������� 1�� �ʱ�ȭ �Ǿ����ϴ�." << endl << endl;
						}
						Sleep(500);
					}
					Sleep(1500);
					system("cls");
				}
				//�ִ� ������ ���׷��̵�
				if (input == 2)
				{
					cout << "++++++++++++++++++++++��ȭ ������+++++++++++++++++++" << endl << endl;
					Sleep(1000);
					random_device rd;
					mt19937 gen(rd());
					uniform_int_distribution<int> _weaponUp(1, 103);
					int weaponUp = _weaponUp(gen);
					//50����
					if (weaponUp <= 50)
					{
						cout << "       50%  ���� ! +5 Damage" << endl;
						hero->maxDamage += 5;
						hero->money -= 100;
						Sleep(500);
					}
					//10����
					else if (51 <= weaponUp && weaponUp <= 61)
					{
						color.setColor(SKYBLUE);
						cout << "       10%  �뼺��!! +20 Damage" << endl;
						hero->maxDamage += 20;
						hero->money -= 100;
						color.setColor(WHITE);
						Sleep(500);
					}
					//35����
					else if (62 <= weaponUp && weaponUp <= 97)
					{
						cout << "        35% ����.. -3 Damage" << endl;
						hero->maxDamage -= 3;
						hero->money -= 100;
						//0���� �۾����� �ٽ� 1�� �ʱ�ȭ.
						if (hero->minDamage <= 0)
						{
							hero->minDamage = 1;
							cout << "�������� -�� �������� 1�� �ʱ�ȭ �Ǿ����ϴ�." << endl << endl;
						}
						Sleep(500);
					}
					//5����
					else if (98 <= weaponUp && weaponUp <= 103)
					{
						color.setColor(RED);
						cout << "        5% �����.. -15 Damage" << endl;
						color.setColor(WHITE);
						hero->maxDamage -= 15;
						hero->money -= 100;
						//0���� �۾����� �ٽ� 1�� �ʱ�ȭ.
						if (hero->minDamage <= 0)
						{
							hero->minDamage = 1;
							cout << "�������� -�� �������� 1�� �ʱ�ȭ �Ǿ����ϴ�." << endl << endl;
						}
						Sleep(500);
					}
					Sleep(1500);
					system("cls");
				}
				else if (input == 3)
				{
					break;
				}
			}
		}

		else
		{
			return;
		}
		break;
		cout << endl;
	}
	return;
}
//ó�� ���� �� �Լ�ȭ
void Synopsis(Hero* hero)
{
	
	color.setColor(BLUE);
	cout << "                                             Dragon  Archer" << endl;
	color.setColor(WHITE);
	cout << "======================================================================================================" << '\n';
	color.setColor(GREEN);
	Sleep(500);
	cout << "    �� ��ȭ�Ӱ� ���� ���긶���� ���� ���� �� ���� ������ �ü��� �巡���� �����ߴٴ� ������ ���� �����´�..." << endl << endl;
	Sleep(500);
	cout << "         ������ ���� ���ϸ� ������ �巡���� �������� �巡��� ���� ��ȭ�� �Բ� �����ִٰ�....  " << endl << endl;
	Sleep(500);
	cout << "           ������ȭ �ҽ��� ��� ���� ������ ������ ���� ���꿡�� �װ��� ã�� ������.... " << endl << endl;
	Sleep(500);
	cout << "             ������ ������ȭ�� Ž�ϴ� �ᱹ ���ε� �巡�� ���� ������ ����� �ȴ� .... " << endl << endl;
	Sleep(500);
	cout << "    �巡���� ���εǾ��� �ڽ��� �ٽ� ������ ���� ���� ��ȭ�� Ž�� ���鿡�� �г��� ��� ���ָ� ������ ������ �Ȱ��־���....  " << endl << endl;
	Sleep(500);
	cout << "                 ���� ������ ���� ���� Ȱ�� ��� ����� �ü�: ";
	color.setColor(BLUE);
	cout << hero->name;
	color.setColor(GREEN);
	cout << " ���̴�...  " << endl << endl;
	Sleep(1000);
	cout << "                              �г��� �巡���� óġ�ϰ� ��ȭ�� ��ã�� ...... " << endl;
	Sleep(500);
	color.setColor(WHITE);
	cout << "======================================================================================================" << '\n';
	
}

//����
int main()
{
	// ���� ����
	string name;
	Hero heroA;
	int selMenu = 0;
	int selCombatMenu;
	int selInfo;
	int iGameMode = 0;
	int countMonster = 1;

	vector<Monster*> monsters;
	monsters.push_back(new Monster("�巡��", "����", 10000, 100, 400, 99999));
	monsters.push_back(new Monster("��", "����", 500, 30, 100, 2000));
	monsters.push_back(new Monster("���", "����", 200, 10, 40, 400));
	monsters.push_back(new Monster("������", "����", 100, 5, 20, 200));
	// ���� �ʱ�ȭ


	//���ӽ��� ���� �̸� �ʱ�ȭ

	color.setColor(RED);
	screen.ScreenDragon();
	color.setColor(WHITE);
	Sleep(500);
	//���ӽ��� ���̺� ���� �ҷ����� , ���ν����ϱ�
	while (iGameMode <= GM_NONE || iGameMode > GM_END)
	{   
		cout << "����������";
		color.setColor(SKYBLUE);
		cout << "MINE �巡�� RPG";
		color.setColor(WHITE);
		cout << "����������" << endl;
		cout << "====================================" << endl;
		cout << "         1.   �����ϱ�" << endl;
		cout << "         2.   �̾��ϱ�" << endl;
		cout << "         3.   �����ϱ�" << endl;
		cout << "         ���Ӹ�� �����ϼ���" <<endl;	
		cout << "====================================" << endl;
		cin >> iGameMode;
		system("cls");
	}
	//����
	if (iGameMode == GM_END)
		return 0;
	//���ο� �÷��� ����
	if (iGameMode == GM_NEW)
	{
		
		cout << "============================================================================================================" << '\n';
		cout << "                                      ����� �̸��� �Է��ϼ���.       " << '\n';
		cout << "============================================================================================================" << '\n';
		cout << "                                              ";
		cin >> name;
		heroA.name = name;
		system("cls");

		//ó�� �̾߱⸦ �Լ���.
		Synopsis(&heroA);
		//�ƹ�Ű�� �Է� �Ѿ��
		cout << "                    ";
		system("pause");
		system("cls");

		// ���� ���� Ȯ��	
		color.setColor(BLUE);
		screen.ScreenHero();
		color.setColor(GREEN);
		cout << "=======================================" << '\n';
		cout << "        �ü��� �̸� :" << heroA.name << '\n';
		cout << "           HP   : " << heroA.hp << '\n';
		cout << "       ȭ�� Damage : " << heroA.minDamage << " ~ " << heroA.maxDamage << '\n';
		cout << "         Money  : " << heroA.money << '\n';
		cout << "=======================================" << '\n';
		color.setColor(WHITE);
		//�ƹ�Ű�� �Է� �Ѿ��
		cout << "       ";
		system("pause");


		system("cls");
	}
	//�̾��ϱ⸦ ���ý� �ٷ� ���θ޴���.
	else if (iGameMode == GM_LOAD)
	{   
		//false�� ! �� ���̸� true�� ��ȯ�ȴ�.
		if (!LoadPlayer(&heroA))
		{
			cout << "�÷��̾� ���� �����Դϴ�." << endl;
		}
	
	cout << "=============�ε���=============" << endl;
	color.setColor(YELLOW);
	cout << "   ";
	for (int i = 0; i < 10; i++)
	{   
		cout << "�� ";
		Sleep(300);
	}
	system("cls");
	color.setColor(WHITE);
	
	}
	
	// ���� �޴�
	while (true)
	{   //�巡��óġ�� ���� ����
		if (monsters[0]->hp <= 0)
		{
			cout << "            �巡���� óġ�Ͽ����ϴ�." << endl;
			cout << "                  ���� �մϴ�." << endl;
			return 0;
		}
		if (heroA.hp <= 0)
		{
			cout << ".���� �Ҵ� ���� ����." << endl;
			return 0;
		}
		cout << "-----------------------------------------" << '\n';
		cout << "            ���� ���� ����      *";
		color.setColor(GREEN);
		cout << " 0" << '\n';
		color.setColor(WHITE);
		cout << "-----------------------------------------" << '\n';
		cout << "    ���� ���꿡�� �����ϱ�      *";
		color.setColor(GREEN);
		cout << " 1" << '\n';
		color.setColor(WHITE);
		cout << "-----------------------------------------" << '\n';
		cout << "                 ���� ����      *";
		color.setColor(GREEN);
		cout << " 2" << '\n';
		color.setColor(WHITE);
		cout << "-----------------------------------------" << '\n';
		cout << "    ����� ���꿡�� ������      *";
		color.setColor(GREEN);
		cout << " 3" << '\n';
		color.setColor(WHITE);
		cout << "-----------------------------------------" << '\n';
		cout << "          ������ ���� ����      *";
		color.setColor(GREEN);
		cout << " 9" << '\n';
		color.setColor(WHITE);
		cout << "-----------------------------------------" << '\n';
		cin >> selMenu;
		system("cls");
	     // �޴��� �����ϱ�
		switch (selMenu)
		{
		case 0: // ���� �޴�
		{
		    while(true)
			{
				 color.setColor(GREEN);
				 cout << "           ****���� ���� ���� : �÷��̾� ���****" << '\n';
				 cout << "           ****���� �¸� ���� : �巡��   óġ****" << '\n';
				 color.setColor(WHITE);
				 cout << "         �� ü���� 0 �̸� ����մϴ�. GAME OVER" << '\n';
				 cout << "         �� �÷��̾ ����� 250$ ������ ��Ȱ�Ҽ� �ֽ��ϴ�." << '\n';
				 cout << "         �� HP�� �ø��� Damage�� ���׷��̵� �ؼ� �巡���� ����ġ����." << '\n';

				 color.setColor(WHITE);
			     cout << "          ------------------------------" << '\n';
			     cout << "                 ������ ����.        0 " << '\n';
			     cout << "                 ���� ���� ����.   1  " << '\n';
				 cout << "                 �����Ϸ� ������.    2  "  << '\n';
			     cout << "          ------------------------------" << '\n';
			     cin >> selInfo;	
				 system("cls");
				switch (selInfo)
				{
			        case 0:
			        {
			        	cout << "-----------------------------" <<'\n';
			        	cout << "           ������            " << '\n';
			        	cout << "-----------------------------" <<'\n';
						color.setColor(BLUE);
						screen.ScreenHero();
						color.setColor(GREEN);
			        	heroA.HeroInfo();	
						color.setColor(WHITE);
						
			        	break;
			        }					
			        case 1:
			        {
						cout << "-----------------------------" << '\n';
			        	cout << "      ���� ����       " << '\n';
			        	cout << "-----------------------------" << '\n';
						color.setColor(WHITE);
						cout << "��. ���� ���������� ü���� 100�� �����ϰ� ";
						cout << " min,max���ݷ��� 10�� ����մϴ�." << '\n';
						cout << "��. ����� ���������� min,max���ݷ��� 2�� ����մϴ�." << '\n';
						cout << "��. �������� ����������ü���� 20�� �����մϴ�." << '\n';
						cout << "-----------------------------" << '\n';
						color.setColor(GREEN);
						for (int i = 0; i < monsters.size(); i++)
						{
							monsters[i]->ShowMonsterInfo();
						}
						color.setColor(WHITE);
						system("pause");
						system("cls");
			        	break;					
			        }
					system("cls");
					case 2:
					{
						break;
					}
					break;
				}
				break;
			}
			break;
		}
		case 1: // ���� �޴�
		{
			while (true)
			{	
			
				cout << "-------------------------------------------" << '\n';
				cout << "                 �����޴�                   " << '\n';
				cout << " 1.�巡�� 2.�� 3.��� 4.������ 5.���θ޴�  " <<'\n';
				cout << "-------------------------------------------" << '\n';
				//���Ͱ� �׾����� hp ȸ��	
				//���� ����� ī��Ʈ�� �ö� �񷽿� ü���� 100�� �����ϰ� ��Ȱ�Ѵ�.
				

				if (monsters[1]->hp <= 0)
				{
					monsters[1]->hp = 500 + (100 * (monsters[1]->GolemCountMonster++));
					monsters[1]->minDamage = 30 + (10 * monsters[1]->GolemCountMonster++);
					monsters[1]->maxDamage = 100 + (10 * monsters[1]->GolemCountMonster++);
				
				}
				//��� ����� ������ 2+ �� �����ϰ� ��Ȱ�Ѵ�.
				if (monsters[2]->hp <= 0)
				{
					monsters[2]->hp =+ 200;
					monsters[2]->minDamage = 10 + (2 * monsters[2]->GoblinCountMonster++);
					monsters[2]->maxDamage = 40 + (2 * monsters[2]->GoblinCountMonster++);
				}
				//������ ����� ü���� 20�� �����ϰ� ��Ȱ�Ѵ�.
				if (monsters[3]->hp <= 0)
				{
					monsters[3]->hp = 100 + (20 * monsters[1]->SlimeCountMonster++);
				}
				
				cin >> selCombatMenu;
				//���ý� ��Ʋ �޴��� ����
				switch (selCombatMenu)
				{
				case 1:
				{   color.setColor(VIOLET);
				   screen.ScreenDragon();
				   color.setColor(WHITE);

				    Sleep(2000);
					BattleSet(monsters[0], &heroA);
					break; 
					return 0;
				}
				case 2:
				{
					BattleSet(monsters[1], &heroA);
					break;
				}
				case 3:
				{
					BattleSet(monsters[2], &heroA);
					break;
				}
				case 4:
				{
					BattleSet(monsters[3], &heroA);
					break;
				}
				case 5:
				{
					break;
				}
				break;
				}
				break;
			}
			break;
		}
		case 2: // ���� �޴�
		{
			while (true)
			{																				
				cout << "                   -------------------------------------------" << '\n';
				cout << "                                    ���� �޴�                  " << '\n';
				cout << "                   1. ���� ����      2.ȭ�� ����     3.���θ޴�  " <<'\n';
				cout << "                   -------------------------------------------" << '\n';
				int Store_Selection;
				cin >> Store_Selection;
				switch (Store_Selection)
				{ 
				 //���� ��������
			      case 1:
			      {
			      	Potion_(&heroA);
			      	break;
			      }
				  //ȭ�� ��������
			      case 2:
			      {
			      	Waepon_(&heroA);
			      	break;
			      }
				  //���� �޴���
			      case 3:
			      {
			      	break;
			      }
				}
				break;
			}
			break;
		}  
		case 3: // ���� �޴�
		{  
			cout << "              ";
			color.setColor(YELLOW);
			cout << heroA.name;
			color.setColor(WHITE);
			cout << " ���� ���꿡 ���� �߽��ϴ�." << endl;
			cout << "                HP : " << heroA.hp << endl;
			cout << " =================================================================" << endl;
			cout << "               ������ ������ ĳ�� �ȸ� 10���� ����ϴ�. " << endl;
			cout << "                      ü���� -5 �� �����մϴ�. " << endl << endl;
			cout << "               1.Ȯ�� 20 ���η� ����(100$)�� �߰��Ѵ�" << endl;
			cout << "               2.Ȯ�� 10 ���η� �ź��� ����(500$)�� �߰��Ѵ�" << endl;                     
			cout << " =================================================================" << endl;
			cout << "                          ���� ĳ��   1" << endl;
			cout << "                          ���� ������ 2" << endl;
			int dig = 0;
			cin >> dig;
			system("cls");
			while (true)
			{   
				//Ȥ�ó� ü���� 0 �϶��� ������ ���´ٸ�
				if (heroA.hp <= 5)
				{
					cout << "ü���� �����մϴ�.";
					return 0;
				}
				switch (dig)
				{
			    //���� ĳ��
				case 1:
				{
					cout << "                ���� ĳ����.." << endl;
					Sleep(1000);
					cout << "++~~~~~~" << endl;
					Sleep(900);
					cout << "                       ++~~~~~~" << endl;
					Sleep(800);
					cout << "                                      ++~~~~~~" << endl;
					Sleep(700);
					cout << "         ++~~~~~~" << endl;
					Sleep(600);
					cout << "                                    ++~~~~~~" << endl;
					Sleep(500);
					cout << "                  ++~~~~~~" << endl << endl;

					//���� �Լ� ������� Ȯ��
					Sleep(1000);
					random_device rd;
					mt19937 gen(rd());
					uniform_int_distribution<int> dis(1,10);
					//����
					if (dis(gen) == 3 || dis(gen) == 8)
					{
						color.setColor(YELLOW);
						cout << " ???" << endl << endl;
						Sleep(1200);
						cout << "            $  " << endl;
						cout << "           $$$ " << endl;
						cout << "          $$$$$" << endl;
						cout << "           $$$ " << endl;
						cout << "            $  " << endl<<endl;
						color.setColor(WHITE);
						cout << "    ������ �߰� �߽��ϴ�" << endl;
						Sleep(1000);
						cout << "================================" << endl;
						cout << "������ �Ȱ�" << "100 �� �������ϴ�." << endl;
						cout << "================================" << endl;
						heroA.money += 100;
						heroA.hp -= 5;
						Sleep(500);
						break;
					}
					//�ź��� ����
					else if (dis(gen) == 7)
					{
						color.setColor(YELLOW);
						cout << " ???????????????????" << endl << endl;
						Sleep(1200);
						screen.Diamond();
						color.setColor(WHITE);
						cout << "       ....�ź��� �� �� �� ��....." << endl << endl;
						Sleep(1000);
						cout << "======================================" << endl;
						cout << "�ź��� ������ ������ HP 100�� ȸ���մϴ�." << endl;
						cout << "�ź��� ������ �Ȱ� 500 ���� ȹ���մϴ�." << endl;
						cout << "======================================" << endl;
						heroA.money += 500;
						heroA.hp += 100;
						Sleep(500);
						break;															
					}
					else
					{
						heroA.money += 10;
						heroA.hp -= 5;
						cout << "������ �Ȱ� " << "10 �� �������ϴ�." << endl;	
						cout << "HP -5" << endl;			
						Sleep(500);
						break;
					}
					Sleep(1000);
					break;								
				}
				// 2�Է½� ��������
				case 2:
				{
					break;
				}	
				break;
				}
				break;
			}
			break;
			
			
		}
		//���� ���� �÷��̾� ���� �����ϱ�
		case 9:
		{
			SavePlayer(&heroA);
			return 0;
			
		}
		break;		
		}		
	}

	return 0;
}
