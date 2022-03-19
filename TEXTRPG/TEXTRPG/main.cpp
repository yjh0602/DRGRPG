#include "header.h"
#include "Monster.h"
#include "Hero.h"
#include "PotionStore.h"
#include "WeaponStore.h"
#include "Screen.h"
#include "Color.h"
using namespace std;

//게임 플레이 모드 시작하기 불러오기.
enum GAME_MODE
{
	GM_NONE, //0
	GM_NEW,  //1
	GM_LOAD, //2
	GM_END   //3
};
//색상 구현
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
//화면 구현
Screen screen;

//저장하기 (bool 을 이용해서 파일이 true false 인지 확인)
bool SavePlayer(Hero* hero)
{
	FILE* pFile = NULL;
	fopen_s(&pFile, "player.A", "wb");
	if (pFile)
	{
		fwrite(&hero->name, sizeof(hero->name), 1, pFile);
		//체력을 읽어온다
		fwrite(&hero->hp, 4, 1, pFile);
		//공격력 읽어오기
		fwrite(&hero->minDamage, 4, 1, pFile);
		fwrite(&hero->maxDamage, 4, 1, pFile);
		//돈 읽어오기
		fwrite(&hero->money, 4, 1, pFile);

		fclose(pFile);
		return true;
	}
	return false;
};
//불러오기 함수를 사용해서 저장해놨던 데이터를 불러온다.
//(bool 을 이용해서 파일이 true false 인지 확인)
bool LoadPlayer(Hero* hero)

{   //파일을 로드하는 함수
	FILE* pFile = NULL;
	fopen_s(&pFile, "player.A", "rb");
	
	if(pFile)
	{
		fread(&hero->name, sizeof(hero->name), 1, pFile);
		//체력을 읽어온다
		fread(&hero->hp, 4, 1, pFile);
		//공격력 읽어오기
		fread(&hero->minDamage, 4, 1, pFile);
		fread(&hero->maxDamage, 4, 1, pFile);
		//돈 읽어오기
		fread(&hero->money, 4, 1, pFile);
	
		fclose(pFile);
		return true;
	}


	return false;
}



//전투 시스템 구축, 사망 시스템
void BattleSet(Monster* monster, Hero* hero)
{
	int selBattle;
	while (true)
	{
		system("cls");
		cout << "     ㅁ 캐릭터가 가진 데미지에서 랜덤하게 주사위가 굴러가서 데미지가 들어갑니다. " << endl << endl;
		cout << "     ㅁ " << monster->name << "의 남은 체력 :  ";
		color.setColor(GREEN);
		cout << monster->hp << endl;
		color.setColor(WHITE);
		cout << "     ㅁ " <<monster->name << "의 데미지 :  " << monster->minDamage << " ~ " << monster->maxDamage << endl << endl;
		cout << "     ㅁ " << hero->name << "의 남은 체력 :   ";
		color.setColor(GREEN);
		cout << hero->hp << endl;
		color.setColor(WHITE);
		cout << "     ㅁ " << hero->name << "의 데미지 :  " << hero->minDamage << " ~ " << hero->maxDamage << endl << endl;
		cout << "---------------------------------------------------------------------------------" << endl;
		cout << "                                공격  0" << endl;
		cout << "                              그만두기  1" << endl;
		cout << "---------------------------------------------------------------------------------" << endl;
		cin >> selBattle;
		switch (selBattle)
		{
		case 0:
			//히어로의 공격 스크린화
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
			// 랜덤 함수를 이용해서 데미지 값 입력
			cout << "=========================================" << endl;
			cout << "        ㅁ " << monster->name << " -";
			color.setColor(SKYBLUE);
			cout << hero->_randomDamege;
			color.setColor(WHITE);
			cout << " 만큼 피해를 입었습니다." << endl << endl;
			Sleep(1000);
			//체력이 0이 될시 공격을 안하고 사망을 띄운다.
			if (monster->hp >= 0)
			{
			monster->monsterAttack(hero, monster);
			cout << "        ㅁ " << hero->name << " -";
			color.setColor(SKYBLUE);
			cout << monster->_randomDamege;
			color.setColor(WHITE);
			cout << "  만큼 피해를 입었습니다." << endl;
			cout << "=========================================" << endl;
			}
			else if (monster->hp <= 0)
			{
				color.setColor(SKYBLUE);
				cout << monster->name;
				color.setColor(WHITE);
				cout << " 이 사망 했습니다." << endl;
			}
			Sleep(1000);
			
		
			system("cls");
					
			//몬스터 사망시 돈 획득
			if (monster->hp <= 0)
			{
				color.setColor(RED);
				cout << "====================================================" << endl;
				color.setColor(WHITE);
				cout << "   " << monster->name << "이 사망 했습니다." << endl;
				hero->money = monster->money + hero->money;
				cout << "   " << monster->money << "  원을 획득했습니다." << endl;
				color.setColor(RED);
				cout << "====================================================" << endl << endl;
				color.setColor(WHITE);
			
				return;
			}
			//히어로 사망시 돈을 내고 회복 돈이없을시 게임오버
			else if (hero->hp <= 0)
			{
				cout << "   " << hero->name << "이 사망 했습니다." << endl;
				if (hero->money >= 250)
				{
					hero->money = hero->money - 250;
					cout << "250$을 지불하고 체력을 회복 했습니다." << endl;
					hero->hp = (hero->hp * 0) + 500;
					return;
				}
				else
				{
					cout << "돈이 부족해서 회복 하지 못하고 사망 하였습니다." << endl << endl;
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
		   // 그만두고 나가기.
		case 1:
		{   
			system("cls");
			return;
		}
		}
		
	}
}

//포션상점
void Potion_(Hero* hero)
{   
	color.setColor(YELLOW);
	screen.ScreenPotion();
	color.setColor(WHITE);
	Sleep(500);
	cout << "---------------------------------------------------" << endl;
	cout << "           어서오세요 포션 상점 입니다." << endl;
	cout << "---------------------------------------------------" << endl;
	PotionStore potionStore;
	int v;
	cout << "                   포션 상점        " << endl;
	cout << "          -------------------------" << endl;
	cout << hero->name << "의 소지금 : " << hero->money << endl;
	cout << hero->name << "의 HP : " << hero->hp << endl;
	while (true)
	{
        cout << "포션 상점입니다." << endl;
        cout << "구매할 포션을 선택하세요" << endl;
		cout << "1.빨간포션 $50";
		color.setColor(RED);
		cout<< "    + 100 " << endl;
		color.setColor(WHITE);
		cout << "2.황금포션 $200";
		color.setColor(RED);
		cout << "   + 500 " << endl;
		color.setColor(WHITE);
		cout << "3.나가기" << endl << endl;
		cin >> v;
		if (v == 1)
		{
			if (hero->money >= 50)
			{
				potionStore.PotionInfo("빨간포션", 100, 50);
				potionStore.Potion(hero);
				cout << hero->name << "의 HP" << potionStore.hill << " 회복 되었습니다." << endl;
				hero->money = hero->money - potionStore.price;
				cout << hero->money << "원 남았습니다." << endl << endl;
				
				cout << "=============================================" << endl;
				system("pause");
				system("cls");
			}
			else
			{
				cout << "돈이 부족합니다" << endl;
				break;
			}
			break;
		}
		else if (v == 2)
		{
			if (hero->money >= 90)
			{
				potionStore.PotionInfo("황금포션", 500, 200);
				potionStore.Potion(hero);
				cout << hero->name << "의 HP" << potionStore.hill << " 회복 되었습니다." << endl;
				hero->money = hero->money - potionStore.price;
				cout << hero->money << "원 남았습니다." << endl << endl;

				cout << "=============================================" << endl;
				system("pause");
				system("cls");
			}
			else
			{
				cout << "돈이 부족합니다" << endl;
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

//무기 상점
void Waepon_(Hero* hero)
{
	color.setColor(SKYBLUE);
	screen.ScreenWaepon();
	
	WeaponStore weaponStore;
	int v;
	color.setColor(WHITE);
	Sleep(500);
	cout << "---------------------------------------------------" << endl;
	cout << "        어서 오시게 여기는 화살 상점일세  " << endl;
	cout << "---------------------------------------------------" << endl;
	Sleep(700);
	cout << "                   화살 상점        " << endl;
	cout << "          -------------------------" << endl;
	cout << hero->name << "의 소지금 : " << hero->money << endl << endl;
	while (true)
	{
		cout << "화살 상점입니다." << endl;
		cout << "구매할 화살을 선택하세요" << endl;
		color.setColor(BLUE);
		cout << "1.은빛 화살  $1000" << endl;
		cout << "minDmg : +10  maxDmg : +50" << endl;
		cout << " 은으로 만든 정교한 화살입니다." << endl;
		color.setColor(YELLOW);
		cout << "2.용의 화살 $5000" << endl;
		cout << "minDmg : +80, maxDmg : +200" << endl;
		cout << "  용의 비늘 조차 뚫는 강력한 화살 입니다." << endl;
		color.setColor(SKYBLUE);
		cout << "3.!!!!강화 하기!!!!" << endl;
		color.setColor(WHITE);
		cout << "4.나가기" << endl << endl;
		cin >> v;
		system("cls");
		//은빛 화살
		if (v == 1)
		{
			weaponStore.WaeponInfo("은빛 화살", 10 , 50 , 1000);
			if (hero->money >= 1000)
			{   
				cout << "구 매 완 료" << endl;
				weaponStore.Waepon(hero);
				cout << hero->name << "의 최소 공격력이 " << weaponStore.minDamage << " 상승 되었습니다." << endl;
				cout << hero->name << "의 최대 공격력이 " << weaponStore.maxDamage << " 상승 되었습니다." << endl;
				hero->money = hero->money - weaponStore.price;
				cout << hero->money << "원 남았습니다." << endl;
				break;
			}
			else
			{
				
				cout << "-------------------------------------- " << endl;
				color.setColor(GREEN);
				Sleep(700);
				cout << "어디보자";
				Sleep(700);
				cout << ".......하나.";
				Sleep(500);
				cout << ".......두울....." << endl;
				Sleep(1500);
				color.setColor(BLUE);
				cout << "은빛 화살 ";
				color.setColor(GREEN);
				cout <<	"을 구매할 돈이 부족하잖아" << endl;
				Sleep(700);
				cout << "                  구매할 돈을 가져오게" << endl;
				Sleep(300);
				color.setColor(WHITE);
				cout << "-------------------------------------- " << endl;
				Sleep(200);
				
				break;
			}
			break;
		}
	    //용의 화살
		else if (v == 2)
		{
			weaponStore.WaeponInfo("용의 화살", 50 , 270 , 5000);
			if (hero->money >= 5000)
			{
				
				cout << "구 매 완 료" << endl;
				weaponStore.Waepon(hero);
				cout << hero->name << "의 최소 공격력 :  " << weaponStore.minDamage << " 상승 되었습니다." << endl;
				cout << hero->name << "의 최대 공격력 :  " << weaponStore.maxDamage << " 상승 되었습니다." << endl;
				hero->money = hero->money - weaponStore.price;
				cout << hero->money << "원 남았습니다." << endl;
				break;
			}
			else
			{
				cout << "-------------------------------------- " << endl;
				color.setColor(GREEN);
				Sleep(700);
				cout << "어디보자";
				Sleep(700);
				cout << ".......하나.";
				Sleep(500);
				cout << ".......두울....." << endl;
				Sleep(1500);
				color.setColor(YELLOW);
				cout << "용의 화살 ";
				color.setColor(GREEN);
				cout << " 을 구매할 돈이 부족하잖아" << endl;
				Sleep(700);
				cout << "                구매할 돈을 가져오게" << endl;
				Sleep(300);
				color.setColor(WHITE);
				cout << "-------------------------------------- " << endl;
				Sleep(200);
				break;
			}
			break;
		}
		//강화시스템
		else if (v == 3)
		{   
			while(true)
			{
				color.setColor(SKYBLUE);
				cout << " =============== " << hero->name << "의 소지금 :" << hero->money << " ===============" << endl;
				cout << " ============== " << hero->name << " : " << hero->minDamage << " ~ " << hero->maxDamage << " DAMAGE " << " ============== " << endl << endl;
				color.setColor(GREEN);
				cout << " =========강화 시스템 입니다= $100 지불 하면 강화가 진행됩니다.  ==========" << endl;
				cout << " =========성공확률 50% 대성공 10% // 실패확률 35% 대실패확률 5%  ==========" << endl;
				color.setColor(WHITE);
				cout << "         최소 데미지 강화는 ㅁ 1" << endl;
				cout << "         최대 데미지 강화는 ㅁ 2" << endl;
				cout << "            강화 나가기  ㅁ 3" << endl;
				int input;
				cin >> input;
				
				//돈이 부족할시 브레이크
				if (hero->money < 100)
				{
					color.setColor(RED);
					cout << "      돈이 부족 합니다       " << endl << endl;
					color.setColor(WHITE);
					break;
				}
				//최소데미지는 최대데미지를 넘을수없습니다.
				if (hero->minDamage > hero->maxDamage)
				{
					color.setColor(RED);
					cout << "최소 데미지는 최대 데미지를 넘을수 없습니다." << endl;
					Sleep(1500);
					break;
				}
				//데미지는 -가 될수 없습니다.
				else if (hero->minDamage < 0 && hero->maxDamage < 0)
				{
					color.setColor(RED);
					cout << "데미지는 - 가 될수 없습니다." << endl;
					Sleep(1500);
					break;
				}
				//최소 데미지 업그레이드
				if (input == 1)
				{
					cout << "++++++++++++++++++++++강화 진행중+++++++++++++++++++" << endl << endl;
					Sleep(1000);
					random_device rd;
					mt19937 gen(rd());
					uniform_int_distribution<int> _weaponUp(1, 103);
					int weaponUp = _weaponUp(gen);
					//50프로
					if (weaponUp <= 50)// 50= 50 개
					{
						cout << "          50%성공!! +5 Damage" << endl;
						hero->minDamage += 5;
						hero->money -= 100;
						Sleep(500);
					}
					//10프로
					else if (51 <= weaponUp && weaponUp <= 61) // 51 61 =10 개
					{
						color.setColor(SKYBLUE);
						cout << "          10%대성공!! +20 Damage" << endl;
						hero->minDamage += 20;
						hero->money -= 100;
						color.setColor(WHITE);
						Sleep(500);
					}
					//35프로
					else if (62 <= weaponUp && weaponUp <= 97) // 62 72 82 87 97= 35 개 
					{

						cout << "          35%실패.. -3 Damage" << endl;
						hero->minDamage -= 3;
						hero->money -= 100;
						//0보다 작아질시 다시 1로 초기화.
						if (hero->minDamage <= 0)
						{
							hero->minDamage = 1;
							cout << "데미지가 -로 떨어져서 1로 초기화 되었습니다." << endl << endl;
						}
						Sleep(500);
					}
					//5프로
					else if (98 <= weaponUp && weaponUp <= 103) // 98 103 = 10개 
					{
						color.setColor(RED);
						cout << "           5%대실패.. -15 Damage " << endl;
						color.setColor(WHITE);
						hero->minDamage -= 15;
						hero->money -= 100;
						//0보다 작아질시 다시 1로 초기화.
						if (hero->minDamage <= 0)
						{
							hero->minDamage = 1;
							cout << "데미지가 -로 떨어져서 1로 초기화 되었습니다." << endl << endl;
						}
						Sleep(500);
					}
					Sleep(1500);
					system("cls");
				}
				//최대 데미지 업그레이드
				if (input == 2)
				{
					cout << "++++++++++++++++++++++강화 진행중+++++++++++++++++++" << endl << endl;
					Sleep(1000);
					random_device rd;
					mt19937 gen(rd());
					uniform_int_distribution<int> _weaponUp(1, 103);
					int weaponUp = _weaponUp(gen);
					//50프로
					if (weaponUp <= 50)
					{
						cout << "       50%  성공 ! +5 Damage" << endl;
						hero->maxDamage += 5;
						hero->money -= 100;
						Sleep(500);
					}
					//10프로
					else if (51 <= weaponUp && weaponUp <= 61)
					{
						color.setColor(SKYBLUE);
						cout << "       10%  대성공!! +20 Damage" << endl;
						hero->maxDamage += 20;
						hero->money -= 100;
						color.setColor(WHITE);
						Sleep(500);
					}
					//35프로
					else if (62 <= weaponUp && weaponUp <= 97)
					{
						cout << "        35% 실패.. -3 Damage" << endl;
						hero->maxDamage -= 3;
						hero->money -= 100;
						//0보다 작아질시 다시 1로 초기화.
						if (hero->minDamage <= 0)
						{
							hero->minDamage = 1;
							cout << "데미지가 -로 떨어져서 1로 초기화 되었습니다." << endl << endl;
						}
						Sleep(500);
					}
					//5프로
					else if (98 <= weaponUp && weaponUp <= 103)
					{
						color.setColor(RED);
						cout << "        5% 대실패.. -15 Damage" << endl;
						color.setColor(WHITE);
						hero->maxDamage -= 15;
						hero->money -= 100;
						//0보다 작아질시 다시 1로 초기화.
						if (hero->minDamage <= 0)
						{
							hero->minDamage = 1;
							cout << "데미지가 -로 떨어져서 1로 초기화 되었습니다." << endl << endl;
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
//처음 서사 를 함수화
void Synopsis(Hero* hero)
{
	
	color.setColor(BLUE);
	cout << "                                             Dragon  Archer" << endl;
	color.setColor(WHITE);
	cout << "======================================================================================================" << '\n';
	color.setColor(GREEN);
	Sleep(500);
	cout << "    한 평화롭고 작은 광산마을의 광산 깊은 곳 에는 전설의 궁수가 드래곤을 봉인했다는 전설이 전해 내려온다..." << endl << endl;
	Sleep(500);
	cout << "         전설의 말에 의하면 깊은곳 드래곤의 둥지에는 드래곤과 금은 보화와 함께 잠들어있다고....  " << endl << endl;
	Sleep(500);
	cout << "           금은보화 소식을 듣고 많은 마을의 용사들이 깊은 광산에서 그곳을 찾게 되지만.... " << endl << endl;
	Sleep(500);
	cout << "             용사들은 금은보화를 탐하다 결국 봉인된 드래곤 마저 봉인을 깨우게 된다 .... " << endl << endl;
	Sleep(500);
	cout << "    드래곤은 봉인되었던 자신을 다시 봉인을 깨워 금은 보화를 탐낸 용사들에게 분노해 모두 저주를 내리고 죽음을 안겨주었다....  " << endl << endl;
	Sleep(500);
	cout << "                 이제 마을의 남은 용사는 활을 쏘는 용사인 궁수: ";
	color.setColor(BLUE);
	cout << hero->name;
	color.setColor(GREEN);
	cout << " 뿐이다...  " << endl << endl;
	Sleep(1000);
	cout << "                              분노한 드래곤을 처치하고 평화를 되찾길 ...... " << endl;
	Sleep(500);
	color.setColor(WHITE);
	cout << "======================================================================================================" << '\n';
	
}

//메인
int main()
{
	// 변수 선언
	string name;
	Hero heroA;
	int selMenu = 0;
	int selCombatMenu;
	int selInfo;
	int iGameMode = 0;
	int countMonster = 1;

	vector<Monster*> monsters;
	monsters.push_back(new Monster("드래곤", "대형", 10000, 100, 400, 99999));
	monsters.push_back(new Monster("골렘", "중형", 500, 30, 100, 2000));
	monsters.push_back(new Monster("고블린", "소형", 200, 10, 40, 400));
	monsters.push_back(new Monster("슬라임", "소형", 100, 5, 20, 200));
	// 몬스터 초기화


	//게임시작 영웅 이름 초기화

	color.setColor(RED);
	screen.ScreenDragon();
	color.setColor(WHITE);
	Sleep(500);
	//게임시작 세이브 파일 불러오기 , 새로시작하기
	while (iGameMode <= GM_NONE || iGameMode > GM_END)
	{   
		cout << "ㅁㅁㅁㅁㅁ";
		color.setColor(SKYBLUE);
		cout << "MINE 드래곤 RPG";
		color.setColor(WHITE);
		cout << "ㅁㅁㅁㅁㅁ" << endl;
		cout << "====================================" << endl;
		cout << "         1.   새로하기" << endl;
		cout << "         2.   이어하기" << endl;
		cout << "         3.   종료하기" << endl;
		cout << "         게임모드 선택하세요" <<endl;	
		cout << "====================================" << endl;
		cin >> iGameMode;
		system("cls");
	}
	//종료
	if (iGameMode == GM_END)
		return 0;
	//새로운 플레이 시작
	if (iGameMode == GM_NEW)
	{
		
		cout << "============================================================================================================" << '\n';
		cout << "                                      당신의 이름을 입력하세요.       " << '\n';
		cout << "============================================================================================================" << '\n';
		cout << "                                              ";
		cin >> name;
		heroA.name = name;
		system("cls");

		//처음 이야기를 함수로.
		Synopsis(&heroA);
		//아무키나 입력 넘어가기
		cout << "                    ";
		system("pause");
		system("cls");

		// 영웅 정보 확인	
		color.setColor(BLUE);
		screen.ScreenHero();
		color.setColor(GREEN);
		cout << "=======================================" << '\n';
		cout << "        궁수의 이름 :" << heroA.name << '\n';
		cout << "           HP   : " << heroA.hp << '\n';
		cout << "       화살 Damage : " << heroA.minDamage << " ~ " << heroA.maxDamage << '\n';
		cout << "         Money  : " << heroA.money << '\n';
		cout << "=======================================" << '\n';
		color.setColor(WHITE);
		//아무키나 입력 넘어가기
		cout << "       ";
		system("pause");


		system("cls");
	}
	//이어하기를 선택시 바로 메인메뉴로.
	else if (iGameMode == GM_LOAD)
	{   
		//false에 ! 을 붙이면 true가 반환된다.
		if (!LoadPlayer(&heroA))
		{
			cout << "플레이어 파일 오류입니다." << endl;
		}
	
	cout << "=============로딩중=============" << endl;
	color.setColor(YELLOW);
	cout << "   ";
	for (int i = 0; i < 10; i++)
	{   
		cout << "■ ";
		Sleep(300);
	}
	system("cls");
	color.setColor(WHITE);
	
	}
	
	// 메인 메뉴
	while (true)
	{   //드래곤처치시 게임 종료
		if (monsters[0]->hp <= 0)
		{
			cout << "            드래곤을 처치하였습니다." << endl;
			cout << "                  감사 합니다." << endl;
			return 0;
		}
		if (heroA.hp <= 0)
		{
			cout << ".전투 불능 게임 오버." << endl;
			return 0;
		}
		cout << "-----------------------------------------" << '\n';
		cout << "            게임 정보 보기      *";
		color.setColor(GREEN);
		cout << " 0" << '\n';
		color.setColor(WHITE);
		cout << "-----------------------------------------" << '\n';
		cout << "    깊은 광산에서 전투하기      *";
		color.setColor(GREEN);
		cout << " 1" << '\n';
		color.setColor(WHITE);
		cout << "-----------------------------------------" << '\n';
		cout << "                 상점 가기      *";
		color.setColor(GREEN);
		cout << " 2" << '\n';
		color.setColor(WHITE);
		cout << "-----------------------------------------" << '\n';
		cout << "    가까운 광산에서 돈벌기      *";
		color.setColor(GREEN);
		cout << " 3" << '\n';
		color.setColor(WHITE);
		cout << "-----------------------------------------" << '\n';
		cout << "          저장후 게임 종료      *";
		color.setColor(GREEN);
		cout << " 9" << '\n';
		color.setColor(WHITE);
		cout << "-----------------------------------------" << '\n';
		cin >> selMenu;
		system("cls");
	     // 메뉴를 선택하기
		switch (selMenu)
		{
		case 0: // 도감 메뉴
		{
		    while(true)
			{
				 color.setColor(GREEN);
				 cout << "           ****게임 오버 조건 : 플레이어 사망****" << '\n';
				 cout << "           ****게임 승리 조건 : 드래곤   처치****" << '\n';
				 color.setColor(WHITE);
				 cout << "         ㅁ 체력이 0 이면 사망합니다. GAME OVER" << '\n';
				 cout << "         ㅁ 플레이어가 사망시 250$ 지불후 부활할수 있습니다." << '\n';
				 cout << "         ㅁ HP를 올리고 Damage를 업그레이드 해서 드래곤을 물리치세요." << '\n';

				 color.setColor(WHITE);
			     cout << "          ------------------------------" << '\n';
			     cout << "                 내정보 보기.        0 " << '\n';
			     cout << "                 몬스터 정보 보기.   1  " << '\n';
				 cout << "                 전투하러 나가기.    2  "  << '\n';
			     cout << "          ------------------------------" << '\n';
			     cin >> selInfo;	
				 system("cls");
				switch (selInfo)
				{
			        case 0:
			        {
			        	cout << "-----------------------------" <<'\n';
			        	cout << "           내정보            " << '\n';
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
			        	cout << "      몬스터 정보       " << '\n';
			        	cout << "-----------------------------" << '\n';
						color.setColor(WHITE);
						cout << "ㅁ. 골렘은 잡을때마다 체력이 100씩 증가하고 ";
						cout << " min,max공격력이 10씩 상승합니다." << '\n';
						cout << "ㅁ. 고블린은 잡을때마다 min,max공격력이 2씩 상승합니다." << '\n';
						cout << "ㅁ. 슬라임은 잡을때마다체력이 20씩 증가합니다." << '\n';
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
		case 1: // 전투 메뉴
		{
			while (true)
			{	
			
				cout << "-------------------------------------------" << '\n';
				cout << "                 전투메뉴                   " << '\n';
				cout << " 1.드래곤 2.골렘 3.고블린 4.슬라임 5.메인메뉴  " <<'\n';
				cout << "-------------------------------------------" << '\n';
				//몬스터가 죽었을시 hp 회복	
				//골렘이 사망시 카운트가 올라서 골렘에 체력이 100씩 증가하고 부활한다.
				

				if (monsters[1]->hp <= 0)
				{
					monsters[1]->hp = 500 + (100 * (monsters[1]->GolemCountMonster++));
					monsters[1]->minDamage = 30 + (10 * monsters[1]->GolemCountMonster++);
					monsters[1]->maxDamage = 100 + (10 * monsters[1]->GolemCountMonster++);
				
				}
				//고블린 사망시 데미지 2+ 씩 증가하고 부활한다.
				if (monsters[2]->hp <= 0)
				{
					monsters[2]->hp =+ 200;
					monsters[2]->minDamage = 10 + (2 * monsters[2]->GoblinCountMonster++);
					monsters[2]->maxDamage = 40 + (2 * monsters[2]->GoblinCountMonster++);
				}
				//슬라임 사망시 체력이 20씩 증가하고 부활한다.
				if (monsters[3]->hp <= 0)
				{
					monsters[3]->hp = 100 + (20 * monsters[1]->SlimeCountMonster++);
				}
				
				cin >> selCombatMenu;
				//선택시 배틀 메뉴로 들어가기
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
		case 2: // 상점 메뉴
		{
			while (true)
			{																				
				cout << "                   -------------------------------------------" << '\n';
				cout << "                                    상점 메뉴                  " << '\n';
				cout << "                   1. 포션 상점      2.화살 상점     3.메인메뉴  " <<'\n';
				cout << "                   -------------------------------------------" << '\n';
				int Store_Selection;
				cin >> Store_Selection;
				switch (Store_Selection)
				{ 
				 //포션 상점으로
			      case 1:
			      {
			      	Potion_(&heroA);
			      	break;
			      }
				  //화살 상점으로
			      case 2:
			      {
			      	Waepon_(&heroA);
			      	break;
			      }
				  //메인 메뉴로
			      case 3:
			      {
			      	break;
			      }
				}
				break;
			}
			break;
		}  
		case 3: // 광산 메뉴
		{  
			cout << "              ";
			color.setColor(YELLOW);
			cout << heroA.name;
			color.setColor(WHITE);
			cout << " 님이 광산에 진입 했습니다." << endl;
			cout << "                HP : " << heroA.hp << endl;
			cout << " =================================================================" << endl;
			cout << "               광산은 광석을 캐고 팔면 10원을 얻습니다. " << endl;
			cout << "                      체력은 -5 씩 감소합니다. " << endl << endl;
			cout << "               1.확률 20 프로로 보석(100$)을 발견한다" << endl;
			cout << "               2.확룔 10 프로로 신비의 보석(500$)을 발견한다" << endl;                     
			cout << " =================================================================" << endl;
			cout << "                          광산 캐기   1" << endl;
			cout << "                          광산 나가기 2" << endl;
			int dig = 0;
			cin >> dig;
			system("cls");
			while (true)
			{   
				//혹시나 체력이 0 일때도 광산을 들어온다면
				if (heroA.hp <= 5)
				{
					cout << "체력이 부족합니다.";
					return 0;
				}
				switch (dig)
				{
			    //광산 캐기
				case 1:
				{
					cout << "                광산 캐는중.." << endl;
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

					//랜덤 함수 사용으로 확룔
					Sleep(1000);
					random_device rd;
					mt19937 gen(rd());
					uniform_int_distribution<int> dis(1,10);
					//보석
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
						cout << "    보석을 발견 했습니다" << endl;
						Sleep(1000);
						cout << "================================" << endl;
						cout << "보석을 팔고" << "100 원 벌었습니다." << endl;
						cout << "================================" << endl;
						heroA.money += 100;
						heroA.hp -= 5;
						Sleep(500);
						break;
					}
					//신비의 보석
					else if (dis(gen) == 7)
					{
						color.setColor(YELLOW);
						cout << " ???????????????????" << endl << endl;
						Sleep(1200);
						screen.Diamond();
						color.setColor(WHITE);
						cout << "       ....신비의 보 석 이 다....." << endl << endl;
						Sleep(1000);
						cout << "======================================" << endl;
						cout << "신비의 보석의 힘으로 HP 100을 회복합니다." << endl;
						cout << "신비의 보석을 팔고 500 원을 획득합니다." << endl;
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
						cout << "광석을 팔고 " << "10 원 벌었습니다." << endl;	
						cout << "HP -5" << endl;			
						Sleep(500);
						break;
					}
					Sleep(1000);
					break;								
				}
				// 2입력시 나가지기
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
		//게임 종료 플레이어 정보 저장하기
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
