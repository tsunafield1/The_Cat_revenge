#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <time.h>
#include <string>
#include <map>
#include <math.h>

const int nb = 30, tb = 20; //  number of normal bear , number of throw bear
const int f = 40, fb = 40, it = 7; // number of fish , number of fishbone , number of item
const int ch = 3; // number of chest
double Speed = 1.35;
double startt, endt, startAttack, startB, startM, startEx, dif;
double startP, startF; // start Potion, start fishbonecase
bool potion = 0; // state of potion
bool fishbonecase = 0; // state of fishbonecase
int g = 0; // number of ground
int i, j;
int stage;
int state = 0; // 1 = after recieve damage
int attack = 0; // 0 = ready to attack, 1 = attack state , 2 = after attack
int cItem = 0; // current item in bags 1.+HP 2.Potion 3.Fishbonecase
int attackDamage = 5;
int animation = 0, Ranimation = 0, Lanimation = 0;
std::string tHP, tScore, tFish, tFishbone; // String of HP , Score , Fish , Fishbone
int HP = 3; // Hit point
int score = 0;
int fish = 0; // Fish
int fishbone = 2; // Ammo
bool gr = 0; // is sprite on the ground?  
int RH = 1, BH, AH; // recent head of main character
int bullet = 0; // bullet status
int bx, endx, startx; // x of bullet,Highest x,Lowest of x 
int close = 0;
int moveView = 0;
int BTM = 0;
std::string name;
sf::Text textHP, textScore, textFish, textFishbone;
sf::Text Exit[3];
sf::Text Menu[3];
sf::Text Leaderboard[7];
sf::Text Score[6];
sf::Text SHOP[4];
sf::Text NAME;
sf::Text showName, showID, gameCreated;
sf::Text NAMETEXT;
sf::Font font;
sf::Vector2f spawn = { 30, 450 }; // spawn point
sf::Sprite shapeSprite; // main character
sf::Sprite attackSprite;
sf::Sprite heart;
sf::Sprite test;
sf::Sprite heartShop, rngboxShop, weaponShop, fishboneShop;
sf::Sprite fishShop1, fishShop2, fishShop3, fishShop4;
sf::Sprite inventory1, inventory2, item2, item3;
sf::Sprite fishForShow, fishboneForShow, clawForShow;
sf::Sprite Bullet;
sf::Sprite menuBG, exitBG, gameBG, leaderBG, pauseBG, gameoverBG, congratBG;
sf::RectangleShape Pillar[4];
sf::View view, startView;
sf::Texture playerTextureRight, playerTextureLeft, fishboneTexture, attackTexture, stickTexture, fishTexture, chestTexture, item1Texture, item2Texture, item3Texture;
sf::Texture heartTexture, fishForShowTexture, fishboneForShowTexture, normalBearTexture, throwBearTexture, fishboneDropTexture, inventoryTexture, rngboxTexture, weapon1Texture, weapon2Texture, weapon3Texture;
sf::Texture ground1Texture, underGround1Texture, bigstickTexture, boss1rightTexture, boss1leftTexture;
sf::Texture menuBGTexture, exitBGTexture, gameBG1Texture, leaderBGTexture, gameBGShopTexture, fishShopTexture;
sf::Texture groundShopTexture, underGroundShopTexture, gameBG2Texture, ground2Texture, underGround2Texture, gameBG3Texture, ground3Texture, underGround3Texture;
sf::Texture boss3rightTexture, boss3leftTexture, stoneTexture, pauseBGTexture, gameoverBGTexture, congratBGTexture;
sf::SoundBuffer damagedBF, throwfishBF, buyBF, gameoverBF, congratBF, TBearthrowBF, TBeardamagedBF, TBeardeadBF, NBeardamagedBF;
sf::SoundBuffer NBeardeadBF, bossthrowBF, bossroarBF, bossdamagedBF, bossdeadBF, useitemBF, clawBF, collectfishBF, collectitemBF;
sf::SoundBuffer pauseinBF, pauseoutBF, UIBF, jumpBF, chestBF;
sf::Sound damagedEF, throwfishEF, buyEF, gameoverEF, congratEF, TBeardamagedEF, TBeardeadEF, NBeardamagedEF;
sf::Sound NBeardeadEF, bossdamagedEF, bossdeadEF, useitemEF, clawEF, collectfishEF, collectitemEF;
sf::Sound pauseinEF, pauseoutEF, UIEF, jumpEF, chestEF;
sf::Music menuBGM, stage1BGM, boss1BGM, stage2BGM, boss2BGM, stage3BGM, shopBGM;
double speed = 0; // use when jumping or falling
bool down = 0, up = 0; // state of jumping
FILE* fp;
std::map<int, std::string> data;

class GROUND
{
public:

	sf::Sprite ground;
	sf::Sprite underGround;
	GROUND(float sizex, float sizey, float posx, float posy, int n, int under)
	{
		if (n == 1)
		{
			ground.setTexture(ground1Texture);
		}
		if (n == 2)
		{
			ground.setTexture(groundShopTexture);
		}
		if (n == 3)
		{
			ground.setTexture(ground2Texture);
		}
		if (n == 4)
		{
			ground.setTexture(ground3Texture);
		}
		ground.setPosition(posx, posy);
		ground.setTextureRect(sf::IntRect(0, 0, sizex, sizey));
		g++;
		if (under == 1)
		{
			underGround.setTexture(underGround1Texture);
		}
		if (under == 2)
		{
			underGround.setTexture(underGroundShopTexture);
		}
		if (under == 3)
		{
			underGround.setTexture(underGround2Texture);
		}
		if (under == 4)
		{
			underGround.setTexture(underGround3Texture);
		}
		if (under > 0)
		{
			underGround.setPosition(posx, posy + 32);
			underGround.setTextureRect(sf::IntRect(0, 0, sizex, 750 - (32 + posy)));
		}
	}
};
std::vector<GROUND> ground; //ground
class Fish
{
public:

	int state = 0;
	float width = 50, height = 24;
	sf::Sprite body;
	void re()
	{
		this->state = 0;
		body.setTextureRect(sf::IntRect(0, 0, 0, 0));
		body.setPosition(-100, -100);
	}
	void set(float x, float y)
	{
		body.setTexture(fishTexture);
		body.setTextureRect(sf::IntRect(0, 0, width, height));
		this->state = 1;
		body.setPosition(x, y);
	}
};
class Fishbone
{
public:

	int state = 0;
	float width = 32, height = 34;
	sf::Sprite body;
	void re()
	{
		this->state = 2;
		body.setTextureRect(sf::IntRect(0, 0, 0, 0));
		body.setPosition(-100, -100);
	}
	void set(float x, float y)
	{
		body.setTexture(fishboneDropTexture);
		body.setTextureRect(sf::IntRect(0, 0, width, height));
		this->state = 1;
		body.setPosition(x, y);
	}
};
Fishbone FISHBONE[fb];
class normalBear
{
public:

	int head = 2;  // 1 = Right , 2 = Left
	int HP = -50;
	int animation;
	float width = 24, height = 41;
	int on;  // which ground that body stay
	sf::Sprite body;
	void re()
	{
		int rng = rand() % 100;
		if (rng < 20)
		{
			for (int i = 0; i < fb; i++)
			{
				if (FISHBONE[i].state != 1)
				{
					FISHBONE[i].set(body.getPosition().x + ((this->width - FISHBONE[i].width) / 2), body.getPosition().y + this->height - FISHBONE[i].height - 6);
					break;
				}
			}
		}
		body.setPosition(-100, -100);
		this->HP = -50;
	}
	void set(float x, float y)
	{
		head = (rand() % 2) + 1;
		body.setTexture(normalBearTexture);
		body.setTextureRect(sf::IntRect(0, 0, 0, 0));
		body.setPosition(x, y - height + 0.0001);
		HP = 10;
		animation = 0;
	}
	void move() // walk left or right
	{
		animation++;
		if (head == 1)
		{
			body.move(0.075f * Speed, .0f);
			i = 0;
			for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
			{
				if (body.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
				{
					on = i;
					if (body.getPosition().y + 31 > ground[i].ground.getPosition().y)
					{
						body.move(-0.075f * Speed, 0.f);
						head = 2;
						break;
					}
				}
				if (i == g - 1)
				{
					body.move(width, 0);
					if (!body.getGlobalBounds().intersects(ground[on].ground.getGlobalBounds()))
					{
						body.move(-0.075f * Speed, 0.f);
						head = 2;
					}
					body.move(-width, 0.f);
				}
			}
			body.setTextureRect(sf::IntRect(16 + (61 * ((animation / 100) % 6)), 62, width, height));
		}
		else if (head == 2)
		{
			body.move(-0.075f * Speed, .0f);
			i = 0;
			for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
			{
				if (body.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
				{
					on = i;
					if (body.getPosition().y + 31 > ground[i].ground.getPosition().y)
					{
						body.move(0.075f * Speed, 0.f);
						head = 1;
						break;
					}
				}
				if (i == g - 1)
				{
					body.move(-width, 0.f);
					if (!body.getGlobalBounds().intersects(ground[on].ground.getGlobalBounds()))
					{
						body.move(0.075f * Speed, 0.f);
						head = 1;
					}
					body.move(width, 0.f);
				}
			}
			body.setTextureRect(sf::IntRect(15 + (61 * ((animation / 100) % 6)), 141, width, height));
		}
	}
};
normalBear NBear[nb];
class throwBear
{
public:

	clock_t start = 0;
	int sx;
	int head; // 1 = Right , 2 = Left
	int HP = -50;
	int th = 0;
	int animation = 0;
	float width = 27, height = 54;
	sf::Sprite body;
	sf::Sprite stick;
	sf::Sound throwEF;
	void re()
	{
		int rng = rand() % 100;
		if (rng < 20)
		{
			for (int i = 0; i < fb; i++)
			{
				if (FISHBONE[i].state != 1)
				{
					FISHBONE[i].set(body.getPosition().x + ((this->width - FISHBONE[i].width) / 2), body.getPosition().y + this->height - FISHBONE[i].height - 6);
					break;
				}
			}
		}
		body.setPosition(-100, -100);
		stick.setPosition(-100, -100);
		stick.setTextureRect({ 0,0,0,0 });
		this->HP = -50;
	}
	void set(float x, float y)
	{
		if (HP == -50) {
			stick.setTexture(stickTexture);
			body.setTexture(throwBearTexture);
		}
		throwEF.setBuffer(TBearthrowBF);
		throwEF.setVolume(40);
		stick.setTextureRect(sf::IntRect(0, 0, 0, 0));
		body.setTextureRect(sf::IntRect(0, 0, 0, 0));
		body.setPosition(x, y - height + 0.0001);
		HP = 20;
	}
	void move() // turn left or right
	{
		animation++;
		if (shapeSprite.getPosition().x > body.getPosition().x)
		{
			head = 1;
			body.setTextureRect(sf::IntRect(216 - 40 * ((animation / 250) % 3), 9, width, height));
			// turn right
		}
		else
		{
			head = 2;
			body.setTextureRect(sf::IntRect(15 + 40 * ((animation / 250) % 3), 73, width, height));
			// turn left
		}
		if (head == 1 && th == 0)
		{
			if (body.getPosition().x - shapeSprite.getPosition().x > -630)
			{
				animation = 0;
				stick.setTextureRect(sf::IntRect(0, 0, 30, 24));
				stick.setPosition(body.getPosition().x + width + 3, body.getPosition().y + 14);
				sx = stick.getPosition().x;
				th = -1;
				start = clock();
			}
		}
		else if (head == 2 && th == 0)
		{
			if (body.getPosition().x - shapeSprite.getPosition().x < 630)
			{
				animation = 0;
				stick.setTextureRect(sf::IntRect(0, 0, 30, 24));
				stick.setPosition(body.getPosition().x - 30 - 3, body.getPosition().y + 14);
				sx = stick.getPosition().x;
				th = -2;
				start = clock();
			}
		}
		if (th == -1)
		{
			dif = (endt - start) / CLOCKS_PER_SEC;
			if (dif <= 0.075) body.setTextureRect(sf::IntRect(95, 9, width, height));
			else if (dif <= 0.15) body.setTextureRect(sf::IntRect(55, 9, width, height));
			else if (dif <= 0.225) body.setTextureRect(sf::IntRect(15, 9, width + 3, height));
			else {
				th = 1;
				throwEF.play();
				start = clock();
			}
		}
		else if (th == -2)
		{
			dif = (endt - start) / CLOCKS_PER_SEC;
			if (dif <= 0.075) body.setTextureRect(sf::IntRect(136, 73, width, height));
			else if (dif <= 0.15) body.setTextureRect(sf::IntRect(176, 73, width, height));
			else if (dif <= 0.225) body.setTextureRect(sf::IntRect(216, 73, width + 3, height));
			else {
				th = 2;
				throwEF.play();
				start = clock();
			}
		}
	}
	void stickSet(int a)
	{
		if (a == 0)
		{
			stick.setTextureRect(sf::IntRect(0, 0, 30, 24));
		}
		else if (a == 1)
		{
			stick.setTextureRect(sf::IntRect(30, 0, 24, 30));
		}
		else if (a == 2)
		{
			stick.setTextureRect(sf::IntRect(54, 0, 30, 24));
		}
		else
		{
			stick.setTextureRect(sf::IntRect(84, 0, 24, 30));
		}
	}
	void shot()
	{
		dif = (endt - start) / CLOCKS_PER_SEC;
		int a = ((int)(dif / 0.075)) % 4;
		if (th == 1)
		{
			stickSet(a);
			stick.move(0.25 * Speed, 0);
			if (stick.getPosition().x - sx > 600)reStick();
		}
		else if (th == 2)
		{
			stickSet(3 - a);
			stick.move(-0.25 * Speed, 0);
			if (stick.getPosition().x - sx < -600)reStick();
		}
		i = 0;
		for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
		{
			if (stick.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
			{
				reStick();
			}
		}
		if (dif > 4 && th > 0)
		{
			th = 0;
		}
	}
	void reStick()
	{
		th = 3;
		stick.setPosition(-1, -1);
		stick.setTextureRect({ 0,0,0,0 });
	}
};
throwBear TBear[tb];
class boss1Bear
{
public:

	clock_t start = 0, skill;
	int spw;
	int sx;
	int head; // 1 = Right , 2 = Left
	int HP = -50;
	int th = 0;
	int roar = 0;
	int animation = 0;
	int random = 3;
	int RS = 0;
	float width = 89, height = 89;
	sf::Sprite body;
	sf::Sprite stick;
	sf::Sound throwEF, roarEF;
	void re()
	{
		body.setPosition(-100, -100);
		stick.setPosition(-100, -100);
		stick.setTextureRect({ 0,0,0,0 });
		this->HP = -50;
	}
	void set(float x, float y)
	{
		if (HP == -50) {
			stick.setTexture(bigstickTexture);
			stick.setPosition(-100, -100);
			stick.setTextureRect({ 0,0,0,0 });
			body.setTexture(boss1leftTexture);
			body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), 0, width, height));
		}
		throwEF.setBuffer(bossthrowBF);
		throwEF.setVolume(50);
		roarEF.setBuffer(bossroarBF);
		body.setPosition(x, y - height + 0.0001);
		this->HP = 200;
	}
	void move() // turn left or right
	{
		animation++;
		if (shapeSprite.getPosition().x > body.getPosition().x + 10)
		{
			head = 1;
			body.setTexture(boss1rightTexture);
			body.setTextureRect(sf::IntRect(711 - width * ((animation / 250) % 3), 0, width, height));
			// turn right
		}
		else
		{
			head = 2;
			body.setTexture(boss1leftTexture);
			body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), 0, width, height));
			// turn left
		}
		if (shapeSprite.getPosition().x > body.getPosition().x)
		{
			body.move(0.08, 0);
		}
		else
		{
			body.move(-0.08, 0);
		}
		if (double(endt - skill) / CLOCKS_PER_SEC >= 15)
		{
			random = rand();
			random %= 2;
			spw = 0;
			roar = 0;
			RS = 0;
			skill = clock();
			start = clock();
		}
		if (random == 0)
		{
			dif = (endt - start) / CLOCKS_PER_SEC;
			if (dif <= 7 && shapeSprite.getPosition().x > body.getPosition().x) body.move(-0.08, 0);
			else if (dif <= 7) body.move(0.08, 0);
			if (dif <= 2 && head == 1) body.setTextureRect(sf::IntRect(711 - width * ((animation / 250) % 3), 89 * 3, width, height));
			if (dif <= 2 && head == 2) body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), 89 * 3, width, height));
			else if (dif <= 4 && dif > 2)
			{
				if (head == 1 && th == 0)
				{
					if (body.getPosition().x - shapeSprite.getPosition().x > -1000)
					{
						animation = 0;
						stick.setTextureRect(sf::IntRect(0, 0, 60, 48));
						stick.setPosition(body.getPosition().x + width - 6, body.getPosition().y + 14);
						sx = stick.getPosition().x;
						th = -1;
						start = clock();
					}
				}
				else if (head == 2 && th == 0)
				{
					if (body.getPosition().x - shapeSprite.getPosition().x < 1000)
					{
						animation = 0;
						stick.setTextureRect(sf::IntRect(0, 0, 60, 48));
						stick.setPosition(body.getPosition().x - 54, body.getPosition().y + 14);
						sx = stick.getPosition().x;
						th = -2;
						start = clock();
					}
				}
				if (th == -1)
				{
					if (dif <= 2.1) body.setTextureRect(sf::IntRect(711, 89, width, height));
					else if (dif <= 2.2) body.setTextureRect(sf::IntRect(711 - width * 3, 89, width, height));
					else if (dif <= 2.3) body.setTextureRect(sf::IntRect(711 - width * 5, 89, width, height));
					else {
						th = 1;
						throwEF.play();
						start = clock();
					}
				}
				else if (th == -2)
				{
					if (dif <= 2.1) body.setTextureRect(sf::IntRect(0, 89, width, height));
					else if (dif <= 2.2) body.setTextureRect(sf::IntRect(width * 3, 89, width, height));
					else if (dif <= 2.3) body.setTextureRect(sf::IntRect(width * 5, 89, width, height));
					else {
						th = 2;
						throwEF.play();
						start = clock();
					}
				}
			}
		}
		else if (random == 1)
		{
			dif = (endt - start) / CLOCKS_PER_SEC;
			if (dif <= 7 && shapeSprite.getPosition().x > body.getPosition().x) body.move(-0.08, 0);
			else if (dif <= 7) body.move(0.08, 0);
			if (head == 1)
			{
				if (dif <= 2) body.setTextureRect(sf::IntRect(711 - width * ((animation / 250) % 3), 89 * 3, width, height));
				else if (dif <= 4)
				{
					if (RS == 0)
					{
						roarEF.play();
						RS = 1;
					}
					body.setTextureRect(sf::IntRect(711 - width * 3, 89 * 3 + 1, width, height));
					if (roar == 0)
					{
						view.move(20, 0);
						roar = 1;
					}
					else
					{
						view.move(-20, 0);
						roar = 0;
					}
				}
				else if (dif <= 5 && spw < 2)
				{
					if (roar == 1)
					{
						view.move(-20, 0);
						roar = 0;
					}
					for (int i = 0; i < nb; i++)
					{
						if (NBear[i].HP == -50)
						{
							NBear[i].set(4800, 600);
							spw++;
							break;
						}
					}
					for (int i = 0; i < nb; i++)
					{
						if (NBear[i].HP == -50)
						{
							NBear[i].set(3800, 600);
							spw++;
							break;
						}
					}
				}
			}
			else
			{
				if (dif <= 2) body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), 89 * 3, width, height));
				else if (dif <= 4)
				{
					if (RS == 0)
					{
						roarEF.play();
						RS = 1;
					}
					body.setTextureRect(sf::IntRect(width * 3, 89 * 3 + 1, width, height));
					if (roar == 0)
					{
						view.move(20, 0);
						roar = 1;
					}
					else
					{
						view.move(-20, 0);
						roar = 0;
					}
				}
				else if (dif <= 5 && spw < 2)
				{
					if (roar == 1)
					{
						view.move(-20, 0);
						roar = 0;
					}
					for (int i = 0; i < nb; i++)
					{
						if (NBear[i].HP == -50)
						{
							NBear[i].set(4800, 600);
							spw++;
							break;
						}
					}
					for (int i = 0; i < nb; i++)
					{
						if (NBear[i].HP == -50)
						{
							NBear[i].set(3800, 600);
							spw++;
							break;
						}
					}
				}
			}
		}
	}
	void stickSet(int a)
	{
		if (a == 0)
		{
			stick.setTextureRect(sf::IntRect(0, 0, 60, 48));
		}
		else if (a == 1)
		{
			stick.setTextureRect(sf::IntRect(60, 0, 48, 60));
		}
		else if (a == 2)
		{
			stick.setTextureRect(sf::IntRect(108, 0, 60, 48));
		}
		else
		{
			stick.setTextureRect(sf::IntRect(168, 0, 48, 60));
		}
	}
	void shot()
	{
		dif = (endt - start) / CLOCKS_PER_SEC;
		int a = ((int)(dif / 0.075)) % 4;
		if (th == 1)
		{
			stickSet(a);
			stick.move(0.25 * Speed, 0);
			if (stick.getPosition().x - sx > 600)reStick();
		}
		else if (th == 2)
		{
			stickSet(3 - a);
			stick.move(-0.25 * Speed, 0);
			if (stick.getPosition().x - sx < -600)reStick();
		}
		i = 0;
		for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
		{
			if (stick.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
			{
				reStick();
			}
		}
		if (dif > 6 && th > 0)
		{
			random = 3;
			th = 0;
		}
	}
	void reStick()
	{
		th = 3;
		stick.setPosition(-1, -1);
		stick.setTextureRect({ 0,0,0,0 });
	}
};
boss1Bear Boss1;
class boss2Bear
{
public:

	clock_t start = 0, skill;
	int sx;
	int head; // 1 = Right , 2 = Left
	int HP = -50;
	int th = 0;
	int mv = 0;
	int animation = 0;
	float width = 89, height = 89;
	sf::Sprite body;
	sf::Sprite stick;
	sf::Sound throwEF;
	void re()
	{
		body.setPosition(-100, -100);
		stick.setPosition(-100, -100);
		stick.setTextureRect({ 0,0,0,0 });
		this->HP = -50;
	}
	void set(float x, float y)
	{
		if (HP == -50) {
			stick.setTexture(bigstickTexture);
			stick.setPosition(-100, -100);
			stick.setTextureRect({ 0,0,0,0 });
			body.setTexture(boss1leftTexture);
			body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), 0, width, height));
		}
		throwEF.setBuffer(bossthrowBF);
		throwEF.setVolume(50);
		body.setPosition(x, y - height + 0.0001);
		this->HP = 300;
		this->head = 2;
	}
	void move() // turn left or right
	{
		animation++;
		dif = (endt - skill) / CLOCKS_PER_SEC;
		if (head == 1)
		{
			body.setTexture(boss1rightTexture);
			body.setTextureRect(sf::IntRect(711 - width * ((animation / 250) % 3), 0, width, height));
			// turn right
		}
		else if (head == 2)
		{
			body.setTexture(boss1leftTexture);
			body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), 0, width, height));
			// turn left
		}
		if (dif <= 3)
		{
			if (head == 1) body.setTextureRect(sf::IntRect(711 - width * ((animation / 250) % 3), 89 * 3, width, height));
			else if (head == 2) body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), 89 * 3, width, height));
		}
		else if (dif <= 10)
		{
			if (head == 1) body.setTextureRect(sf::IntRect(711 - width * ((animation / 250) % 3), 89 * 3, width, height));
			else if (head == 2) body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), 89 * 3, width, height));
			if (head == 1 && th == 0)
			{
				animation = 0;
				stick.setTextureRect(sf::IntRect(0, 0, 60, 48));
				stick.setPosition(body.getPosition().x + width - 6, body.getPosition().y + 14);
				sx = stick.getPosition().x;
				th = -1;
				start = clock();
			}
			else if (head == 2 && th == 0)
			{
				animation = 0;
				stick.setTextureRect(sf::IntRect(0, 0, 60, 48));
				stick.setPosition(body.getPosition().x - 54, body.getPosition().y + 14);
				sx = stick.getPosition().x;
				th = -2;
				start = clock();
			}
			if (th == -1)
			{
				if ((double)(endt - start) / CLOCKS_PER_SEC <= 0.1) body.setTextureRect(sf::IntRect(711, 89, width, height));
				else if ((double)(endt - start) / CLOCKS_PER_SEC <= 0.2) body.setTextureRect(sf::IntRect(711 - width * 3, 89, width, height));
				else if ((double)(endt - start) / CLOCKS_PER_SEC <= 0.3) body.setTextureRect(sf::IntRect(711 - width * 5, 89, width, height));
				else {
					th = 1;
					throwEF.play();
					start = clock();
				}
			}
			else if (th == -2)
			{
				if ((double)(endt - start) / CLOCKS_PER_SEC <= 0.1) body.setTextureRect(sf::IntRect(0, 89, width, height));
				else if ((double)(endt - start) / CLOCKS_PER_SEC <= 0.2) body.setTextureRect(sf::IntRect(width * 3, 89, width, height));
				else if ((double)(endt - start) / CLOCKS_PER_SEC <= 0.3) body.setTextureRect(sf::IntRect(width * 5, 89, width, height));
				else {
					th = 2;
					throwEF.play();
					start = clock();
				}
			}
		}
		else if (dif <= 14)
		{
			if (head == 1) body.setTextureRect(sf::IntRect(711 - width * ((animation / 250) % 3), 89 * 3, width, height));
			else if (head == 2) body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), 89 * 3, width, height));
		}
		else if (dif > 16 && mv == 0)
		{
			if (head == 1 && body.getPosition().x - shapeSprite.getPosition().x > -470)
			{
				mv = 1;
			}
			else if (head == 2 && body.getPosition().x - shapeSprite.getPosition().x < 470)
			{
				mv = 2;
			}
			else
			{
				skill = clock();
			}
		}
		if (mv == 1)
		{
			if (body.getPosition().x < 5470)
			{
				body.move(1, 0);
			}
			else
			{
				head = 2;
				mv = 0;
				skill = clock();
			}
		}
		else if (mv == 2)
		{
			if (body.getPosition().x > 4500)
			{
				body.move(-1, 0);
			}
			else
			{
				head = 1;
				mv = 0;
				skill = clock();
			}
		}
	}
	void stickSet(int a)
	{
		if (a == 0)
		{
			stick.setTextureRect(sf::IntRect(0, 0, 60, 48));
		}
		else if (a == 1)
		{
			stick.setTextureRect(sf::IntRect(60, 0, 48, 60));
		}
		else if (a == 2)
		{
			stick.setTextureRect(sf::IntRect(108, 0, 60, 48));
		}
		else
		{
			stick.setTextureRect(sf::IntRect(168, 0, 48, 60));
		}
	}
	void shot()
	{
		dif = (endt - start) / CLOCKS_PER_SEC;
		int a = ((int)(dif / 0.075)) % 4;
		if (th == 1)
		{
			stickSet(a);
			stick.move(0.8 * Speed, 0);
		}
		else if (th == 2)
		{
			stickSet(3 - a);
			stick.move(-0.8 * Speed, 0);
		}
		i = 0;
		for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
		{
			if (stick.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
			{
				reStick();
			}
		}
		if (dif > 1.25 && th != 0)
		{
			reStick();
			th = 0;
		}
	}
	void reStick()
	{
		th = 3;
		stick.setPosition(-1, -1);
		stick.setTextureRect({ 0,0,0,0 });
	}
};
boss2Bear Boss2;
class boss3Bear
{
public:

	clock_t start = 0, skill;
	int sx;
	int head; // 1 = Right , 2 = Left
	int HP = -50;
	int th = 0;
	int mv = 0;
	int animation = 0;
	int ran;
	int STATE;
	int roar;
	int spw;
	int RS = 0;
	float width = 178, height = 178;
	sf::Sprite body;
	sf::Sprite stick;
	sf::Sprite stone1;
	sf::Sprite stone2;
	sf::Sprite stone3;
	sf::Sound throwEF, roarEF;
	void re()
	{
		body.setPosition(-100, -100);
		stick.setPosition(-100, -100);
		stick.setTextureRect({ 0,0,0,0 });
		this->HP = -50;
	}
	void set(float x, float y)
	{
		if (HP == -50) {
			stick.setTexture(bigstickTexture);
			stick.setPosition(-100, -100);
			stick.setTextureRect({ 0,0,0,0 });
			body.setTexture(boss3leftTexture);
			body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), 0, width, height));
			stone1.setTexture(stoneTexture);
			stone2.setTexture(stoneTexture);
			stone3.setTexture(stoneTexture);
		}
		body.setPosition(x, y - height + 1.0001);
		throwEF.setBuffer(bossthrowBF);
		throwEF.setVolume(50);
		roarEF.setBuffer(bossroarBF);
		this->HP = 600;
		this->head = 2;
		ran = rand() % 3;
		roar = 0;
		STATE = 1;
		stone1.setPosition(-100, -100);
		stone2.setPosition(-100, -100);
		stone3.setPosition(-100, -100);
	}
	void move() // turn left or right
	{
		animation++;
		dif = (endt - skill) / CLOCKS_PER_SEC;
		if (head == 1)
		{
			body.setTexture(boss3rightTexture);
			body.setTextureRect(sf::IntRect(1422 - width * ((animation / 250) % 3), 2, width, height));
			// turn right
		}
		else if (head == 2)
		{
			body.setTexture(boss3leftTexture);
			body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), 2, width, height));
			// turn left
		}
		if (STATE == 1)
		{
			if (dif <= 2)
			{
				if (head == 1) body.setTextureRect(sf::IntRect(1422 - width * ((animation / 250) % 3), height * 3 + 2, width, height));
				else if (head == 2) body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), height * 3 + 2, width, height));
			}
			else if (dif <= 4)
			{
				if (RS == 0)
				{
					roarEF.play();
					RS = 1;
				}
				body.setTextureRect(sf::IntRect(1422 - width * 3, height * 3 + 3, width, height));
				if (roar == 0)
				{
					view.move(20, 0);
					roar = 1;
				}
				else
				{
					view.move(-20, 0);
					roar = 0;
				}
			}
			else if (dif <= 5)
			{
				if (roar == 1)
				{
					view.move(-20, 0);
					roar = 0;
				}
				if (head == 1) body.setTextureRect(sf::IntRect(1422 - width * ((animation / 250) % 3), height * 3 + 2, width, height));
				else if (head == 2) body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), height * 3 + 2, width, height));
			}
			else if (ran == 0)
			{
				if (dif <= 12)
				{
					if (head == 1) body.setTextureRect(sf::IntRect(1422 - width * ((animation / 250) % 3), height * 3 + 2, width, height));
					else if (head == 2) body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), height * 3 + 2, width, height));
					if (head == 1 && th == 0)
					{
						animation = 0;
						stick.setTextureRect(sf::IntRect(0, 0, 60, 48));
						stick.setPosition(body.getPosition().x + width - 6, body.getPosition().y + 90);
						sx = stick.getPosition().x;
						th = -1;
						start = clock();
					}
					else if (head == 2 && th == 0)
					{
						animation = 0;
						stick.setTextureRect(sf::IntRect(0, 0, 60, 48));
						stick.setPosition(body.getPosition().x - 54, body.getPosition().y + 90);
						sx = stick.getPosition().x;
						th = -2;
						start = clock();
					}
					if (th == -1)
					{
						if ((double)(endt - start) / CLOCKS_PER_SEC <= 0.1) body.setTextureRect(sf::IntRect(1422, height + 2, width, height));
						else if ((double)(endt - start) / CLOCKS_PER_SEC <= 0.2) body.setTextureRect(sf::IntRect(1422 - width * 3, height + 2, width, height));
						else if ((double)(endt - start) / CLOCKS_PER_SEC <= 0.3) body.setTextureRect(sf::IntRect(1422 - width * 5, height + 2, width, height));
						else {
							th = 1;
							throwEF.play();
							start = clock();
						}
					}
					else if (th == -2)
					{
						if ((double)(endt - start) / CLOCKS_PER_SEC <= 0.1) body.setTextureRect(sf::IntRect(0, height + 2, width, height));
						else if ((double)(endt - start) / CLOCKS_PER_SEC <= 0.2) body.setTextureRect(sf::IntRect(width * 3, height + 2, width, height));
						else if ((double)(endt - start) / CLOCKS_PER_SEC <= 0.3) body.setTextureRect(sf::IntRect(width * 5, height + 2, width, height));
						else {
							th = 2;
							throwEF.play();
							start = clock();
						}
					}
				}
				else if (dif <= 17)
				{
					if (head == 1) body.setTextureRect(sf::IntRect(1422 - width * ((animation / 250) % 3), height * 3 + 2, width, height));
					else if (head == 2) body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), height * 3 + 2, width, height));
				}
				else if (dif > 19)
				{
					RS = 0;
					skill = clock();
					ran = rand() % 3;
					if (HP <= 300)
					{
						ran = 2;
						STATE = 2;
					}
				}
			}
			else if (ran == 1)
			{
				if (dif <= 6)
				{
					if (head == 1) body.setTextureRect(sf::IntRect(1422 - width * ((animation / 250) % 3), height * 3 + 2, width, height));
					else if (head == 2) body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), height * 3 + 2, width, height));
					stone1.setPosition(600, -64);
					stone2.setPosition(900, -64);
					stone3.setPosition(1200, -64);
				}
				else if (dif <= 8)
				{
					if (head == 1) body.setTextureRect(sf::IntRect(1422 - width * ((animation / 250) % 3), height * 3 + 2, width, height));
					else if (head == 2) body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), height * 3 + 2, width, height));
					stone1.move(0, 0.9);
					stone2.move(0, 0.9);
					stone3.move(0, 0.9);
				}
				else if (dif > 12)
				{
					RS = 0;
					skill = clock();
					ran = rand() % 3;
					if (HP <= 300)
					{
						ran = 2;
						STATE = 2;
					}
				}
			}
			else if (ran == 2)
			{
				if (spw < 3)
				{
					for (int i = 0; i < nb; i++)
					{
						if (NBear[i].HP == -50)
						{
							NBear[i].set(1500, 568);
							spw++;
							break;
						}
					}
					for (int i = 0; i < nb; i++)
					{
						if (NBear[i].HP == -50)
						{
							NBear[i].set(550, 568);
							spw++;
							break;
						}
					}
					for (int i = 0; i < tb; i++)
					{
						if (TBear[i].HP == -50)
						{
							TBear[i].set(500, 568);
							spw++;
							break;
						}
					}
				}
				if (dif > 8)
				{
					spw = 0;
					RS = 0;
					skill = clock();
					ran = rand() % 3;
					if (HP <= 300)
					{
						ran = 2;
						STATE = 2;
					}
				}
			}
		}
		else if (STATE == 2)
		{
			if (dif <= 2)
			{
				if (head == 1) body.setTextureRect(sf::IntRect(1422 - width * ((animation / 250) % 3), height * 3 + 2, width, height));
				else if (head == 2) body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), height * 3 + 2, width, height));
			}
			else if (dif <= 4)
			{
				if (RS == 0)
				{
					roarEF.play();
					RS = 1;
				}
				body.setTextureRect(sf::IntRect(1422 - width * 3, height * 3 + 3, width, height));
				if (roar == 0)
				{
					view.move(20, 0);
					roar = 1;
				}
				else
				{
					view.move(-20, 0);
					roar = 0;
				}
			}
			else if (dif <= 5)
			{
				if (roar == 1)
				{
					view.move(-20, 0);
					roar = 0;
				}
				if (head == 1) body.setTextureRect(sf::IntRect(1422 - width * ((animation / 250) % 3), height * 3 + 2, width, height));
				else if (head == 2) body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), height * 3 + 2, width, height));
			}
			else if (ran == 0)
			{
				if (dif <= 12)
				{
					if (head == 1) body.setTextureRect(sf::IntRect(1422 - width * ((animation / 250) % 3), height * 3 + 2, width, height));
					else if (head == 2) body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), height * 3 + 2, width, height));
					if (head == 1 && th == 0)
					{
						animation = 0;
						stick.setTextureRect(sf::IntRect(0, 0, 60, 48));
						stick.setPosition(body.getPosition().x + width - 6, body.getPosition().y + 90);
						sx = stick.getPosition().x;
						th = -1;
						start = clock();
					}
					else if (head == 2 && th == 0)
					{
						animation = 0;
						stick.setTextureRect(sf::IntRect(0, 0, 60, 48));
						stick.setPosition(body.getPosition().x - 54, body.getPosition().y + 90);
						sx = stick.getPosition().x;
						th = -2;
						start = clock();
					}
					if (th == -1)
					{
						if ((double)(endt - start) / CLOCKS_PER_SEC <= 0.1) body.setTextureRect(sf::IntRect(1422, height + 2, width, height));
						else if ((double)(endt - start) / CLOCKS_PER_SEC <= 0.2) body.setTextureRect(sf::IntRect(1422 - width * 3, height + 2, width, height));
						else if ((double)(endt - start) / CLOCKS_PER_SEC <= 0.3) body.setTextureRect(sf::IntRect(1422 - width * 5, height + 2, width, height));
						else {
							th = 1;
							throwEF.play();
							start = clock();
						}
					}
					else if (th == -2)
					{
						if ((double)(endt - start) / CLOCKS_PER_SEC <= 0.1) body.setTextureRect(sf::IntRect(0, height + 2, width, height));
						else if ((double)(endt - start) / CLOCKS_PER_SEC <= 0.2) body.setTextureRect(sf::IntRect(width * 3, height + 2, width, height));
						else if ((double)(endt - start) / CLOCKS_PER_SEC <= 0.3) body.setTextureRect(sf::IntRect(width * 5, height + 2, width, height));
						else {
							th = 2;
							throwEF.play();
							start = clock();
						}
					}
				}
				else if (dif <= 16)
				{
					if (head == 1) body.setTextureRect(sf::IntRect(1422 - width * ((animation / 250) % 3), height * 3 + 2, width, height));
					else if (head == 2) body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), height * 3 + 2, width, height));
				}
				else if (dif > 18)
				{
					RS = 0;
					skill = clock();
					STATE = 3;
				}
			}
			else if (ran == 1)
			{
				if (dif <= 6)
				{
					if (head == 1) body.setTextureRect(sf::IntRect(1422 - width * ((animation / 250) % 3), height * 3 + 2, width, height));
					else if (head == 2) body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), height * 3 + 2, width, height));
					stone1.setPosition(600, -64);
					stone2.setPosition(900, -64);
					stone3.setPosition(1200, -64);
				}
				else if (dif <= 8)
				{
					if (head == 1) body.setTextureRect(sf::IntRect(1422 - width * ((animation / 250) % 3), height * 3 + 2, width, height));
					else if (head == 2) body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), height * 3 + 2, width, height));
					stone1.move(0, 0.9);
					stone2.move(0, 0.9);
					stone3.move(0, 0.9);
				}
				else if (dif > 10)
				{
					RS = 0;
					skill = clock();
					ran = 0;
				}
			}
			else if (ran == 2)
			{
				if (spw < 3)
				{
					for (int i = 0; i < nb; i++)
					{
						if (NBear[i].HP == -50)
						{
							NBear[i].set(1500, 568);
							spw++;
							break;
						}
					}
					for (int i = 0; i < nb; i++)
					{
						if (NBear[i].HP == -50)
						{
							NBear[i].set(550, 568);
							spw++;
							break;

						}
						for (int i = 0; i < tb; i++)
						{
							if (TBear[i].HP == -50)
							{
								TBear[i].set(500, 568);
								spw++;
								break;
							}
						}
					}
				}
				if (dif > 6)
				{
					RS = 0;
					spw = 0;
					skill = clock();
					ran = 1;
				}
			}
		}
		else
		{
			if (shapeSprite.getPosition().x > body.getPosition().x + 10)
			{
				head = 1;
				body.setTexture(boss3rightTexture);
				body.setTextureRect(sf::IntRect(1422 - width * ((animation / 250) % 3), 2, width, height));
				// turn right
			}
			else
			{
				head = 2;
				body.setTexture(boss3leftTexture);
				body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), 2, width, height));
				// turn left
			}
			if (shapeSprite.getPosition().x > body.getPosition().x)
			{
				body.move(0.075, 0);
			}
			else
			{
				body.move(-0.075, 0);
			}
		}
	}
	void stickSet(int a)
	{
		if (a == 0)
		{
			stick.setTextureRect(sf::IntRect(0, 0, 60, 48));
		}
		else if (a == 1)
		{
			stick.setTextureRect(sf::IntRect(60, 0, 48, 60));
		}
		else if (a == 2)
		{
			stick.setTextureRect(sf::IntRect(108, 0, 60, 48));
		}
		else
		{
			stick.setTextureRect(sf::IntRect(168, 0, 48, 60));
		}
	}
	void shot()
	{
		dif = (endt - start) / CLOCKS_PER_SEC;
		int a = ((int)(dif / 0.075)) % 4;
		if (th == 1)
		{
			stickSet(a);
			stick.move(0.8 * Speed, 0);
		}
		else if (th == 2)
		{
			stickSet(3 - a);
			stick.move(-0.8 * Speed, 0);
		}
		i = 0;
		for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
		{
			if (stick.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
			{
				reStick();
			}
		}
		if (dif > 1.25 && th != 0)
		{
			reStick();
			th = 0;
		}
	}
	void reStick()
	{
		th = 3;
		stick.setPosition(-1, -1);
		stick.setTextureRect({ 0,0,0,0 });
	}
};
boss3Bear Boss3;
class item
{
public:

	int num;
	int state = 0;
	int air = 0;
	float speed;
	float width[3] = { 32,30,36 }, height[3] = { 32,36,36 };
	sf::Sprite body;
	void re()
	{
		this->num = 0;
		this->state = 0;
		body.setTextureRect(sf::IntRect(0, 0, 0, 0));
		body.setPosition(-1, -1);
	}
	void set(float x, float y, int a)
	{
		this->num = a;
		if (a == 1)
		{
			body.setTexture(item1Texture);
		}
		else if (a == 2)
		{
			body.setTexture(item2Texture);
		}
		else if (a == 3)
		{
			body.setTexture(item3Texture);
		}
		body.setTextureRect(sf::IntRect(0, 0, width[a - 1], height[a - 1]));
		body.setPosition(x, y);
		this->state = 1;
		this->air = 1;
		this->speed = 0.3 * Speed;
	}
	void move()
	{
		if (air == 1)
		{
			speed -= 0.0005 * Speed * Speed;
			body.move(.0f, -speed);
			i = 0;
			for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
			{
				if (body.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
				{
					if (body.getPosition().y > ground[i].ground.getPosition().y)
					{
						body.move(.0f, speed);
					}
				}
			}
			if (speed <= 0)air = 2;
		}
		if (air == 2)
		{
			speed += 0.0005 * Speed * Speed;
			body.move(0.f, speed);
			i = 0;
			for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
			{
				if (body.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
				{
					if (body.getPosition().y > ground[i].ground.getPosition().y)
					{
						body.move(0.f, -(body.getPosition().y - ground[i].ground.getPosition().y));
					}
					air = 0;
				}
			}
		}
	}
};
item ITEM[it];
class chest
{
public:

	int state = 0;
	float width = 48, height = 42, difH = 6;
	sf::Sprite body;
	void re()
	{
		body.setPosition(-100, -100);
		this->state = 1;
	}
	void set(float x, float y)
	{
		body.setTexture(chestTexture);
		body.setTextureRect(sf::IntRect(0, 0, width, height));
		this->state = 1;
		body.setPosition(x, y - height);
	}
	void open()
	{
		if (state == 1)
		{
			int a = (rand() % 3) + 1;
			for (int i = 0; i < it; i++)
			{
				if (ITEM[i].state == 0)
				{
					ITEM[i].set(body.getPosition().x + ((width - ITEM[i].width[a - 1]) / 2), body.getPosition().y + 5, a);
					break;
				}
			}
			body.setTextureRect(sf::IntRect(0, height + difH, width, height));
			this->state = 2;
			fish += 20;
			score += 200;
		}
	}
};

void mainCharacter();
void damageCal();
void shoot();
void setText();
std::string changeNtoS(int, int);
std::string changeNtoS(int);
void scratch();
void loadTexture();
void setSprite();
void firstTextSet();
void setGround1();
void setMonster1();
void setFish1();
void collectFish();
void setChest1();
void use(int);
void setHead();
void stage1();
void setup();
void start();
void reset();
void leaderboard();
void MENU();
void exitFromMenu();
void gameDraw();
void gameCal();
void gamePause();
void startdata();
void gameover();
void stage1boss();
void shop();
void setGroundShop();
void buy(int);
void stage2();
void setGround2();
void setMonster2();
void setFish2();
void setChest2();
void stage2boss();
void stage3();
void setGround3();
void setMonster3();
void setChest3();
void stage3boss();
void saveData();
void loadSound();

Fish FISH[f];
chest CHEST[ch];
sf::RenderWindow window(sf::VideoMode(1080, 720), "The Cat's revenge", sf::Style::Default);

int main()
{
	srand(time(NULL));
	startView = window.getView();
	setup();
menu:
	start();
	MENU();
quit:
	if (close == 1)return 0;
	//goto s;
	stage1();
	while (window.isOpen())
	{
		sf::Event event;
		if (window.pollEvent(event)) {}
		gameCal();
		stage1boss();
		if (shapeSprite.getPosition().x > 5000)
		{
			break;
		}
		gameDraw();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			pauseinEF.play();
			gamePause();
			pauseoutEF.play();
		}
		if (HP < 0)
		{
			gameoverEF.play();
			gameover();
		}
		if (BTM == 1)goto menu;
		if (close == 1)goto quit;
	}
	reset();
	shop();
	while (window.isOpen())
	{
		sf::Event event;
		if (window.pollEvent(event)) {}
		gameCal();
		gameDraw();
		if (shapeSprite.getPosition().x > 1000)
		{
			break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			pauseinEF.play();
			gamePause();
			pauseoutEF.play();
		}
		if (HP < 0)
		{
			gameoverEF.play();
			gameover();
		}
		if (BTM == 1)goto menu;
		if (close == 1)goto quit;
	}
	reset();
	stage2();
	/*int mv = 3800;
	view.move(mv, 0);
	shapeSprite.move(mv+500,0);//*/
	while (window.isOpen())
	{
		sf::Event event;
		if (window.pollEvent(event)) {}
		gameCal();
		stage2boss();
		if (shapeSprite.getPosition().x > 5750)
		{
			break;
		}
		gameDraw();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			pauseinEF.play();
			gamePause();
			pauseoutEF.play();
		}
		if (HP < 0)
		{
			gameoverEF.play();
			gameover();
		}
		if (BTM == 1)goto menu;
		if (close == 1)goto quit;
	}
	reset();
	shop();
	while (window.isOpen())
	{
		sf::Event event;
		if (window.pollEvent(event)) {}
		gameCal();
		gameDraw();
		if (shapeSprite.getPosition().x > 1000)
		{
			break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			pauseinEF.play();
			gamePause();
			pauseoutEF.play();
		}
		if (HP < 0)
		{
			gameoverEF.play();
			gameover();
		}
		if (BTM == 1)goto menu;
		if (close == 1)goto quit;
	}
	reset();
	stage3();
	while (window.isOpen())
	{
		sf::Event event;
		if (window.pollEvent(event)) {}
		gameCal();
		stage3boss();
		if (shapeSprite.getPosition().x > 1740)
		{
			break;
		}
		gameDraw();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			pauseinEF.play();
			gamePause();
			pauseoutEF.play();
		}
		if (HP < 0)
		{
			gameoverEF.play();
			gameover();
		}
		if (BTM == 1)goto menu;
		if (close == 1)goto quit;
	}
	congratEF.play();
	gameover();
	goto menu;
	return 0;
}

void mainCharacter()
{
	if (RH == 1)
	{
		shapeSprite.setTexture(playerTextureRight);
		shapeSprite.setTextureRect(sf::IntRect(36 + (39 * ((animation / (150 / (int)Speed)) % 6)), 22, 40, 54));
	}
	else
	{
		shapeSprite.setTexture(playerTextureLeft);
		shapeSprite.setTextureRect(sf::IntRect(626 - 40 - (36 + 39 * ((animation / (150 / (int)Speed)) % 6)), 22, 40, 54));
	}
	gr = 0;
	animation++;
	Ranimation++;
	Lanimation++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && shapeSprite.getPosition().x > startx && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		RH = 2;
		shapeSprite.move(-0.18f * Speed, 0.f);
		if ((view.getCenter().x - shapeSprite.getPosition().x >= -16) && view.getCenter().x - 540 > startx && moveView == 0)view.move(-0.18 * Speed, 0);
		i = 0;
		for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
		{
			if (shapeSprite.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
			{
				if (shapeSprite.getPosition().y + shapeSprite.getTextureRect().height - 2 > ground[i].ground.getPosition().y && shapeSprite.getPosition().x > ground[i].ground.getPosition().x)
				{
					shapeSprite.move(0.18f * Speed, 0.f);
					if ((view.getCenter().x - shapeSprite.getPosition().x >= -16) && view.getCenter().x - 540 > startx && moveView == 0)view.move(0.18 * Speed, 0);
					break;
				}
			}
		}
		shapeSprite.setTextureRect(sf::IntRect(626 - 39 - (280 + 38 * ((Lanimation / (100 / (int)Speed)) % 6)), 22, 39, 54));
		Ranimation = animation = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && shapeSprite.getPosition().x + 32 < endx && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		RH = 1;
		shapeSprite.move(.18f * Speed, 0.f);
		if ((view.getCenter().x - shapeSprite.getPosition().x <= 16) && view.getCenter().x + 540 < endx && moveView == 0)view.move(.18 * Speed, 0);
		i = 0;
		for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
		{
			if (shapeSprite.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
			{
				if (shapeSprite.getPosition().y + shapeSprite.getTextureRect().height - 2 > ground[i].ground.getPosition().y && shapeSprite.getPosition().x < ground[i].ground.getPosition().x)
				{
					shapeSprite.move(-0.18f * Speed, 0.f);
					if ((view.getCenter().x - shapeSprite.getPosition().x <= 16) && view.getCenter().x + 540 < endx && moveView == 0)view.move(-.18 * Speed, 0);
					break;
				}
			}
		}
		shapeSprite.setTextureRect(sf::IntRect(280 + 38 * ((Ranimation / (100 / (int)Speed)) % 6), 22, 39, 54));
		Lanimation = animation = 0;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::K) && bullet == 0 && fishbone > 0) || (fishbonecase && sf::Keyboard::isKeyPressed(sf::Keyboard::K) && bullet == 0))
	{
		startB = clock();
		if (!fishbonecase)fishbone--;
		BH = RH;
		bullet = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && attack == 0)
	{
		clawEF.play();
		AH = RH;
		attack = 1;
		startAttack = clock();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		bool s = 0;
		while (1)
		{
			for (int i = 0; i < ch; i++)
			{
				if (shapeSprite.getGlobalBounds().intersects(CHEST[i].body.getGlobalBounds()) && CHEST[i].state == 1)
				{
					chestEF.play();
					CHEST[i].open();
					s = 1;
					break;
				}
			}
			if (s == 1)break;
			for (int i = 0; i < it; i++)
			{
				if (shapeSprite.getGlobalBounds().intersects(ITEM[i].body.getGlobalBounds()) && ITEM[i].air != 1)
				{
					collectitemEF.play();
					s = 1;
					if (ITEM[i].num == 1)
					{
						use(1);
					}
					else
					{
						if (cItem == 0)
						{
							cItem = ITEM[i].num;
						}
						else
						{
							use(ITEM[i].num);
						}
					}
					ITEM[i].re();
					break;
				}
			}
			if (s == 1)break;
			for (int i = 0; i < 4; i++)
			{
				if (shapeSprite.getGlobalBounds().intersects(Pillar[i].getGlobalBounds()))
				{
					buy(i);
					break;
				}
			}
			break;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		if (cItem != 0)
		{
			use(cItem);
			cItem = 0;
		}
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && !down && !up)
	{
		jumpEF.play();
		speed = 0.9 * Speed;
		up = 1;
	}
	if (up)
	{
		speed -= 0.0019125 * (Speed * Speed);
		shapeSprite.move(.0f, -speed);
		i = 0;
		for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
		{
			if (shapeSprite.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
			{
				if (shapeSprite.getPosition().y - 2 > ground[i].ground.getPosition().y)
				{
					shapeSprite.move(.0f, speed);
				}
			}
		}
		if (RH == 1)shapeSprite.setTextureRect(sf::IntRect(330, 234, 40, 56));
		else shapeSprite.setTextureRect(sf::IntRect(626 - 40 - 330, 234, 40, 56));
		if (speed <= 0)up = 0;
	}
	i = 0;
	for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
	{
		if (shapeSprite.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()) && !up && !down && !gr)
		{
			gr = 1;
		}
	}
	i = 0;
	for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
	{
		if (!shapeSprite.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()) && !up && !down && !gr)
		{
			down = 1;
			speed = 0;
		}
	}
	if (down)
	{
		speed += 0.0019125 * Speed * Speed;
		shapeSprite.move(0.f, speed);
		i = 0;
		for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
		{
			if (shapeSprite.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
			{
				if (shapeSprite.getPosition().y > ground[i].ground.getPosition().y)
				{
					shapeSprite.move(0.f, shapeSprite.getPosition().y - ground[i].ground.getPosition().y);
				}
				down = 0;
				break;
			}
		}
		if (RH == 1)shapeSprite.setTextureRect(sf::IntRect(372, 236, 42, 55));
		else shapeSprite.setTextureRect(sf::IntRect(626 - 42 - 372, 236, 42, 55));
	}
	if (bullet > 0)
	{
		dif = (endt - startB) / CLOCKS_PER_SEC;
		if (RH == 1)
		{
			if (dif <= 0.1) shapeSprite.setTextureRect(sf::IntRect(149, 94, 40, 54));
			else if (dif <= 0.2) shapeSprite.setTextureRect(sf::IntRect(185, 94, 40, 54));
			else if (dif <= 0.3) shapeSprite.setTextureRect(sf::IntRect(149, 94, 40, 54));
		}
		else
		{
			if (dif <= 0.1) shapeSprite.setTextureRect(sf::IntRect(626 - 40 - 149, 94, 40, 54));
			else if (dif <= 0.2) shapeSprite.setTextureRect(sf::IntRect(626 - 40 - 185, 94, 40, 54));
			else if (dif <= 0.3) shapeSprite.setTextureRect(sf::IntRect(626 - 40 - 149, 94, 40, 54));
		}
	}
	if (attack > 0)
	{
		dif = (endt - startAttack) / CLOCKS_PER_SEC;
		if (RH == 1)
		{
			if (dif <= 0.1) shapeSprite.setTextureRect(sf::IntRect(149, 94, 40, 54));
			else if (dif <= 0.2) shapeSprite.setTextureRect(sf::IntRect(185, 94, 40, 54));
			else if (dif <= 0.3) shapeSprite.setTextureRect(sf::IntRect(454, 250, 40, 54));
		}
		else
		{
			if (dif <= 0.1) shapeSprite.setTextureRect(sf::IntRect(626 - 40 - 149, 94, 40, 54));
			else if (dif <= 0.2) shapeSprite.setTextureRect(sf::IntRect(626 - 40 - 185, 94, 40, 54));
			else if (dif <= 0.3) shapeSprite.setTextureRect(sf::IntRect(626 - 40 - 454, 250, 40, 54));
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::End))
	{
		close = 1;
		window.close();
	}
	animation++;
}

void damageCal()
{
	if (potion == 0)
	{
		if (state == 0)
		{
			for (int i = 0; i < nb; i++)
			{
				if (shapeSprite.getGlobalBounds().intersects(NBear[i].body.getGlobalBounds()))
				{
					startt = clock();
					NBear[i].HP -= 5;
					HP--;
					state = 1;
					if (NBear[i].HP <= 0) score += 10;
					break;
				}
			}
			if (state == 0)
			{
				for (int i = 0; i < tb; i++)
				{
					if (shapeSprite.getGlobalBounds().intersects(TBear[i].body.getGlobalBounds()))
					{
						startt = clock();
						TBear[i].HP -= 5;
						HP--;
						state = 1;
						if (TBear[i].HP <= 0) score += 20;
						break;
					}
				}
			}
			if (state == 0)
			{
				for (int i = 0; i < tb; i++)
				{
					if (shapeSprite.getGlobalBounds().intersects(TBear[i].stick.getGlobalBounds()))
					{
						startt = clock();
						HP--;
						state = 1;
						TBear[i].reStick();
						break;
					}
				}
			}
			if (state == 0)
			{
				if (shapeSprite.getGlobalBounds().intersects(Boss1.body.getGlobalBounds()))
				{
					startt = clock();
					HP--;
					state = 1;
					Boss1.HP -= 5;
				}
			}
			if (state == 0)
			{
				if (shapeSprite.getGlobalBounds().intersects(Boss1.stick.getGlobalBounds()))
				{
					startt = clock();
					HP--;
					state = 1;
					Boss1.reStick();
				}
			}
			if (state == 0)
			{
				if (shapeSprite.getGlobalBounds().intersects(Boss2.body.getGlobalBounds()))
				{
					startt = clock();
					HP--;
					state = 1;
					Boss2.HP -= 5;
				}
			}
			if (state == 0)
			{
				if (shapeSprite.getGlobalBounds().intersects(Boss2.stick.getGlobalBounds()))
				{
					startt = clock();
					HP--;
					state = 1;
					Boss2.reStick();
				}
			}
			if (state == 0)
			{
				if (shapeSprite.getGlobalBounds().intersects(Boss3.body.getGlobalBounds()))
				{
					startt = clock();
					HP--;
					state = 1;
					Boss3.HP -= 5;
				}
			}
			if (state == 0)
			{
				if (shapeSprite.getGlobalBounds().intersects(Boss3.stick.getGlobalBounds()))
				{
					startt = clock();
					HP--;
					state = 1;
					Boss3.reStick();
				}
			}
			if (state == 0)
			{
				if (shapeSprite.getGlobalBounds().intersects(Boss3.stone1.getGlobalBounds()))
				{
					startt = clock();
					HP--;
					state = 1;
				}
			}
			if (state == 0)
			{
				if (shapeSprite.getGlobalBounds().intersects(Boss3.stone2.getGlobalBounds()))
				{
					startt = clock();
					HP--;
					state = 1;
				}
			}
			if (state == 0)
			{
				if (shapeSprite.getGlobalBounds().intersects(Boss3.stone3.getGlobalBounds()))
				{
					startt = clock();
					HP--;
					state = 1;
				}
			}
			if (state == 1)damagedEF.play();
		}
		else
		{
			dif = (endt - startt) / CLOCKS_PER_SEC;
			if (dif >= 2)
			{
				state = 0;
			}
			else if (dif >= 1.875)
			{
				state = 2;
			}
			else if (dif >= 1.75)
			{
				state = 1;
			}
			else if (dif >= 1.625)
			{
				state = 2;
			}
			else if (dif >= 1.5)
			{
				state = 1;
			}
			else if (dif >= 1.375)
			{
				state = 2;
			}
			else if (dif >= 1.25)
			{
				state = 1;
			}
			else if (dif >= 1.125)
			{
				state = 2;
			}
			else if (dif >= 1)
			{
				state = 1;
			}
			else if (dif >= 0.875)
			{
				state = 2;
			}
			else if (dif >= 0.75)
			{
				state = 1;
			}
			else if (dif >= 0.625)
			{
				state = 2;
			}
			else if (dif >= 0.5)
			{
				state = 1;
			}
			else if (dif >= 0.375)
			{
				state = 2;
			}
			else if (dif >= 0.25)
			{
				state = 1;
			}
			else if (dif >= 0.125)
			{
				state = 2;
			}
		}
	}
	else
	{
		if (state == 0)
		{
			for (int i = 0; i < nb; i++)
			{
				if (shapeSprite.getGlobalBounds().intersects(NBear[i].body.getGlobalBounds()))
				{
					startt = clock();
					NBear[i].HP -= 5;
					state = 1;
					if (NBear[i].HP <= 0) score += 10;
					break;
				}
			}
			if (state == 0)
			{
				for (int i = 0; i < tb; i++)
				{
					if (shapeSprite.getGlobalBounds().intersects(TBear[i].body.getGlobalBounds()))
					{
						startt = clock();
						TBear[i].HP -= 5;
						state = 1;
						if (TBear[i].HP <= 0) score += 20;
						break;
					}
				}
			}
			if (state == 0)
			{
				for (int i = 0; i < tb; i++)
				{
					if (shapeSprite.getGlobalBounds().intersects(TBear[i].stick.getGlobalBounds()))
					{
						startt = clock();
						TBear[i].reStick();
						break;
					}
				}
			}
			if (state == 0)
			{
				if (shapeSprite.getGlobalBounds().intersects(Boss1.body.getGlobalBounds()))
				{
					startt = clock();
					state = 1;
					Boss1.HP -= 5;
				}
			}
			if (state == 0)
			{
				if (shapeSprite.getGlobalBounds().intersects(Boss1.stick.getGlobalBounds()))
				{
					startt = clock();
					state = 1;
					Boss1.reStick();
				}
			}
			if (state == 0)
			{
				if (shapeSprite.getGlobalBounds().intersects(Boss2.body.getGlobalBounds()))
				{
					startt = clock();
					state = 1;
					Boss2.HP -= 5;
				}
			}
			if (state == 0)
			{
				if (shapeSprite.getGlobalBounds().intersects(Boss2.stick.getGlobalBounds()))
				{
					startt = clock();
					state = 1;
					Boss2.reStick();
				}
			}
			if (state == 0)
			{
				if (shapeSprite.getGlobalBounds().intersects(Boss3.body.getGlobalBounds()))
				{
					startt = clock();
					state = 1;
					Boss3.HP -= 5;
				}
			}
			if (state == 0)
			{
				if (shapeSprite.getGlobalBounds().intersects(Boss3.stick.getGlobalBounds()))
				{
					startt = clock();
					state = 1;
					Boss3.reStick();
				}
			}
			if (state == 0)
			{
				if (shapeSprite.getGlobalBounds().intersects(Boss3.stone1.getGlobalBounds()))
				{
					startt = clock();
					state = 1;
				}
			}
			if (state == 0)
			{
				if (shapeSprite.getGlobalBounds().intersects(Boss3.stone2.getGlobalBounds()))
				{
					startt = clock();;
					state = 1;
				}
			}
			if (state == 0)
			{
				if (shapeSprite.getGlobalBounds().intersects(Boss3.stone3.getGlobalBounds()))
				{
					startt = clock();
					state = 1;
				}
			}
			if (state == 1)damagedEF.play();
		}
		else
		{
			dif = (endt - startt) / CLOCKS_PER_SEC;
			if (dif >= 1.5)
			{
				state = 0;
			}
			else if (dif >= 1.375)
			{
				state = 2;
			}
			else if (dif >= 1.25)
			{
				state = 1;
			}
			else if (dif >= 1.125)
			{
				state = 2;
			}
			else if (dif >= 1)
			{
				state = 1;
			}
			else if (dif >= 0.875)
			{
				state = 2;
			}
			else if (dif >= 0.75)
			{
				state = 1;
			}
			else if (dif >= 0.625)
			{
				state = 2;
			}
			else if (dif >= 0.5)
			{
				state = 1;
			}
			else if (dif >= 0.375)
			{
				state = 2;
			}
			else if (dif >= 0.25)
			{
				state = 1;
			}
			else if (dif >= 0.125)
			{
				state = 2;
			}
		}
		dif = (endt - startP) / CLOCKS_PER_SEC;
		if (dif >= 9)
		{
			potion = 0;
			startt = clock();
			state = 1;
			startt -= CLOCKS_PER_SEC;
		}
	}
}

void shoot()
{
	if (fishbonecase == 0)
	{
		if (bullet == 1)
		{
			throwfishEF.play();
			bullet = 2;
			if (BH == 1)
			{
				Bullet.setPosition(shapeSprite.getPosition().x + 35, shapeSprite.getPosition().y + 20);
				bx = shapeSprite.getPosition().x + 35;
			}
			else
			{
				Bullet.setPosition(shapeSprite.getPosition().x - 15, shapeSprite.getPosition().y + 20);
				bx = shapeSprite.getPosition().x - 15;
			}
		}
		if (BH == 1)
		{
			Bullet.move(0.25 * Speed, 0);
		}
		else
		{
			Bullet.move(-0.25 * Speed, 0);
		}
		if (bullet == 2)
		{
			for (int i = 0; i < nb; i++)
			{
				if (Bullet.getGlobalBounds().intersects(NBear[i].body.getGlobalBounds()))
				{
					bullet = 3;
					NBear[i].HP -= 10;
					if (NBear[i].HP <= 0)
					{
						NBeardeadEF.play();
						score += 10;
					}
					else NBeardamagedEF.play();
					break;
				}
			}
			if (bullet == 2)
			{
				for (int i = 0; i < tb; i++)
				{
					if (Bullet.getGlobalBounds().intersects(TBear[i].body.getGlobalBounds()))
					{
						bullet = 3;
						TBear[i].HP -= 10;
						if (TBear[i].HP <= 0)
						{
							TBeardeadEF.play();
							score += 20;
						}
						else TBeardamagedEF.play();
						break;
					}
				}
			}
			if (bullet == 2)
			{
				if (Bullet.getGlobalBounds().intersects(Boss1.body.getGlobalBounds()))
				{
					bullet = 3;
					Boss1.HP -= 10;
					bossdamagedEF.play();
				}
			}
			if (bullet == 2)
			{
				if (Bullet.getGlobalBounds().intersects(Boss2.body.getGlobalBounds()))
				{
					bullet = 3;
					Boss2.HP -= 10;
					bossdamagedEF.play();
				}
			}
			if (bullet == 2)
			{
				if (Bullet.getGlobalBounds().intersects(Boss3.body.getGlobalBounds()))
				{
					bullet = 3;
					Boss3.HP -= 10;
					bossdamagedEF.play();
				}
			}
			if (bullet == 2)
			{
				i = 0;
				for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
				{
					if (Bullet.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
					{
						bullet = 3;
						break;
					}
				}
			}
		}
		if (Bullet.getPosition().x - bx > 600 || Bullet.getPosition().x - bx < -600)
		{
			bullet = 0;
			Bullet.setPosition(-1, -1);
		}
	}
	else
	{
		dif = (endt - startF) / CLOCKS_PER_SEC;
		if (dif >= 10) fishbonecase = 0;
		if (bullet == 1)
		{
			throwfishEF.play();
			bullet = 2;
			if (BH == 1)
			{
				Bullet.setPosition(shapeSprite.getPosition().x + 35, shapeSprite.getPosition().y + 20);
				bx = shapeSprite.getPosition().x + 35;
			}
			else
			{
				Bullet.setPosition(shapeSprite.getPosition().x - 15, shapeSprite.getPosition().y + 20);
				bx = shapeSprite.getPosition().x - 15;
			}
		}
		if (BH == 1)
		{
			Bullet.move(0.25, 0);
		}
		else
		{
			Bullet.move(-0.25, 0);
		}
		if (bullet == 2)
		{
			for (int i = 0; i < nb; i++)
			{
				if (Bullet.getGlobalBounds().intersects(NBear[i].body.getGlobalBounds()))
				{
					bullet = 3;
					NBear[i].HP -= 10;
					if (NBear[i].HP <= 0)
					{
						NBeardeadEF.play();
						score += 10;
					}
					else NBeardamagedEF.play();
					break;
				}
			}
			if (bullet == 2)
			{
				for (int i = 0; i < tb; i++)
				{
					if (Bullet.getGlobalBounds().intersects(TBear[i].body.getGlobalBounds()))
					{
						bullet = 3;
						TBear[i].HP -= 10;
						if (TBear[i].HP <= 0)
						{
							TBeardeadEF.play();
							score += 20;
						}
						else TBeardamagedEF.play();
						break;
					}
				}
			}
			if (bullet == 2)
			{
				if (Bullet.getGlobalBounds().intersects(Boss1.body.getGlobalBounds()))
				{
					bullet = 3;
					Boss1.HP -= 10;
					bossdamagedEF.play();
				}
			}
			if (bullet == 2)
			{
				if (Bullet.getGlobalBounds().intersects(Boss2.body.getGlobalBounds()))
				{
					bullet = 3;
					Boss2.HP -= 10;
					bossdamagedEF.play();
				}
			}
			if (bullet == 2)
			{
				if (Bullet.getGlobalBounds().intersects(Boss3.body.getGlobalBounds()))
				{
					bullet = 3;
					Boss3.HP -= 10;
					bossdamagedEF.play();
				}
			}
			if (bullet == 2)
			{
				i = 0;
				for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
				{
					if (Bullet.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
					{
						bullet = 3;
						break;
					}
				}
			}
		}
		if (Bullet.getPosition().x - bx > 600 || Bullet.getPosition().x - bx < -600)
		{
			bullet = 0;
			Bullet.setPosition(-1, -1);
		}
	}
}

void setText()
{
	tScore = "SCORE ";
	if (score < 10000)tScore.insert(6, changeNtoS(score, 4));
	else tScore.insert(6, changeNtoS(score, 5));
	textScore.setString(tScore);
	textScore.setPosition(view.getCenter().x - 510, 0);

	tFish = "X ";
	if (fish < 100)tFish.insert(2, changeNtoS(fish, 2));
	else tFish.insert(2, changeNtoS(fish, 3));
	textFish.setString(tFish);
	textFish.setPosition(view.getCenter().x - 110, 0);

	tFishbone = "X ";
	if (fishbonecase == 0)tFishbone.insert(2, changeNtoS(fishbone, 2));
	else
	{
		dif = (endt - startF) / CLOCKS_PER_SEC;
		if (dif >= 9.9) { tFishbone.insert(2, changeNtoS(fishbone, 2)); }
		else if (dif >= 9.625) {}
		else if (dif >= 9.5) { tFishbone.insert(2, changeNtoS(99, 2)); }
		else if (dif >= 9.375) {}
		else if (dif >= 9.25) { tFishbone.insert(2, changeNtoS(99, 2)); }
		else if (dif >= 9.125) {}
		else if (dif >= 9) { tFishbone.insert(2, changeNtoS(99, 2)); }
		else if (dif >= 8.75) {}
		else if (dif >= 8.5) { tFishbone.insert(2, changeNtoS(99, 2)); }
		else if (dif >= 8.25) {}
		else if (dif >= 8) { tFishbone.insert(2, changeNtoS(99, 2)); }
		else if (dif >= 7.5) {}
		else if (dif >= 7) { tFishbone.insert(2, changeNtoS(99, 2)); }
		else if (dif >= 6) {}
		else
		{
			tFishbone.insert(2, changeNtoS(99, 2));
		}
	}
	textFishbone.setString(tFishbone);
	textFishbone.setPosition(view.getCenter().x + 90, 0);

	tHP = "X ";
	if (potion == 0)tHP.insert(2, changeNtoS(HP, 2));
	else
	{
		dif = (endt - startP) / CLOCKS_PER_SEC;
		if (dif >= 8.625) {}
		else if (dif >= 8.5) { tHP.insert(2, changeNtoS(99, 2)); }
		else if (dif >= 8.375) {}
		else if (dif >= 8.25) { tHP.insert(2, changeNtoS(99, 2)); }
		else if (dif >= 8.125) {}
		else if (dif >= 8) { tHP.insert(2, changeNtoS(99, 2)); }
		else if (dif >= 7.75) {}
		else if (dif >= 7.5) { tHP.insert(2, changeNtoS(99, 2)); }
		else if (dif >= 7.25) {}
		else if (dif >= 7) { tHP.insert(2, changeNtoS(99, 2)); }
		else if (dif >= 6.5) {}
		else if (dif >= 6) { tHP.insert(2, changeNtoS(99, 2)); }
		else if (dif >= 5) {}
		else
		{
			tHP.insert(2, changeNtoS(99, 2));
		}
	}
	textHP.setString(tHP);
	textHP.setPosition(view.getCenter().x + 280, 0);

	SHOP[0].setString("30x");

	SHOP[1].setString("40x");

	if (attackDamage == 5)
	{
		SHOP[2].setString("20x");
	}
	else if (attackDamage == 10)
	{
		SHOP[2].setString("50x");
	}
	else SHOP[2].setString("");

	SHOP[3].setString("05x");
}

std::string changeNtoS(int num, int zero)
{
	char b[10];
	b[zero] = '\0';
	int n = num;
	std::string a = "";
	for (int i = zero; i >= 1; i--)
	{
		b[i - 1] = (n % 10) + '0';
		n /= 10;
	}
	a.insert(0, b);
	return a;
}

std::string changeNtoS(int num)
{
	char b[10];
	int n = num;
	int index = 0;
	int max = -1;
	std::string a = "";
	while (n > 0)
	{
		max++;
		n /= 10;
	}
	n = num;
	b[max + 1] = '\0';
	while (max >= 0)
	{
		b[index] = (int)(n / pow(10, max)) + '0';
		if (max > 0)n %= (int)pow(10, max);
		else n %= 10;
		max--;
		index++;
	}
	a.insert(0, b);
	return a;
}

void scratch()
{
	dif = (endt - startAttack) / CLOCKS_PER_SEC;
	if (attack == 1)
	{
		attack = 2;
		if (AH == 1)
		{
			attackSprite.setPosition(shapeSprite.getPosition().x + 35, shapeSprite.getPosition().y - 12);
		}
		else
		{
			attackSprite.setPosition(shapeSprite.getPosition().x - 38, shapeSprite.getPosition().y - 12);
		}
		attackSprite.setTextureRect(sf::IntRect(78, 24, 48, 0));
	}
	if (attack == 2)
	{
		for (int i = 0; i < nb; i++)
		{
			if (attackSprite.getGlobalBounds().intersects(NBear[i].body.getGlobalBounds()))
			{
				int onG;
				attack = 3;
				NBear[i].HP -= attackDamage;
				if (AH == 1)
				{
					NBear[i].head = 2;
					j = 0;
					for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); j++, it++)
					{
						if (NBear[i].body.getGlobalBounds().intersects(ground[j].ground.getGlobalBounds()))
						{
							onG = j;
							break;
						}
					}
					NBear[i].body.move(5, 0);
					j = 0;
					for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); j++, it++)
					{
						if (NBear[i].body.getGlobalBounds().intersects(ground[j].ground.getGlobalBounds()))
						{
							if (j != onG)
							{
								NBear[i].body.move(-5, 0);
								break;
							}
						}
					}
				}
				else
				{
					NBear[i].head = 1;
					j = 0;
					for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); j++, it++)
					{
						if (NBear[i].body.getGlobalBounds().intersects(ground[j].ground.getGlobalBounds()))
						{
							onG = j;
							break;
						}
					}
					NBear[i].body.move(-5, 0);
					j = 0;
					for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); j++, it++)
					{
						if (NBear[i].body.getGlobalBounds().intersects(ground[j].ground.getGlobalBounds()))
						{
							if (j != onG)
							{
								NBear[i].body.move(5, 0);
								break;
							}
						}
					}
				}
				if (NBear[i].HP <= 0)
				{
					NBeardeadEF.play();
					score += 10;
				}
				else NBeardamagedEF.play();
				break;
			}
		}
		if (attack == 2)
		{
			for (int i = 0; i < tb; i++)
			{
				if (attackSprite.getGlobalBounds().intersects(TBear[i].body.getGlobalBounds()))
				{
					attack = 3;
					TBear[i].HP -= attackDamage;
					if (TBear[i].HP <= 0)
					{
						TBeardeadEF.play();
						score += 20;
					}
					else TBeardamagedEF.play();
					break;
				}
			}
		}
		if (attack == 2)
		{
			if (attackSprite.getGlobalBounds().intersects(Boss1.body.getGlobalBounds()))
			{
				bossdamagedEF.play();
				attack = 3;
				Boss1.HP -= attackDamage;
			}
		}
		if (attack == 2)
		{
			if (attackSprite.getGlobalBounds().intersects(Boss2.body.getGlobalBounds()))
			{
				bossdamagedEF.play();
				attack = 3;
				Boss2.HP -= attackDamage;
			}
		}
		if (attack == 2)
		{
			if (attackSprite.getGlobalBounds().intersects(Boss3.body.getGlobalBounds()))
			{
				bossdamagedEF.play();
				attack = 3;
				Boss3.HP -= attackDamage;
			}
		}
	}
	if (dif > 1)
	{
		attack = 0;
	}
	else if (dif > 0.25)
	{
		attackSprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
		attack = 4;
	}
	else if (dif > 0.2)
	{
		attackSprite.setTextureRect(sf::IntRect(78, 24, 48, 80));
	}
	else if (dif > 0.175)
	{
		attackSprite.setTextureRect(sf::IntRect(78, 24, 48, 70));
	}
	else if (dif > 0.15)
	{
		attackSprite.setTextureRect(sf::IntRect(78, 24, 48, 60));
	}
	else if (dif > 0.125)
	{
		attackSprite.setTextureRect(sf::IntRect(78, 24, 48, 50));
	}
	else if (dif > 0.1)
	{
		attackSprite.setTextureRect(sf::IntRect(78, 24, 48, 40));
	}
	else if (dif > 0.075)
	{
		attackSprite.setTextureRect(sf::IntRect(78, 24, 48, 30));
	}
	else if (dif > 0.05)
	{
		attackSprite.setTextureRect(sf::IntRect(78, 24, 48, 20));
	}
	else if (dif > 0.025)
	{
		attackSprite.setTextureRect(sf::IntRect(78, 24, 48, 10));
	}
}

void loadTexture()
{
	if (!playerTextureRight.loadFromFile("sprites/catRight.png"))
	{
		std::cout << "Right Load failed " << std::endl;
	}
	if (!playerTextureLeft.loadFromFile("sprites/catLeft.png"))
	{
		std::cout << "Left Load failed " << std::endl;
	}
	if (!fishTexture.loadFromFile("assets/fish24.png"))
	{
		std::cout << "fish Load failed " << std::endl;
	}
	if (!fishboneTexture.loadFromFile("assets/fishbone.png"))
	{
		std::cout << "fishbone Load failed " << std::endl;
	}
	if (!attackTexture.loadFromFile("effects/claw.png"))
	{
		std::cout << "claw Load failed " << std::endl;
	}
	if (!stickTexture.loadFromFile("assets/stick.png"))
	{
		std::cout << "stick Load failed " << std::endl;
	}
	if (!item1Texture.loadFromFile("assets/item1.png"))
	{
		std::cout << "item1 Load failed " << std::endl;
	}
	if (!item2Texture.loadFromFile("assets/item2.png"))
	{
		std::cout << "item2 Load failed " << std::endl;
	}
	if (!item3Texture.loadFromFile("assets/item3.png"))
	{
		std::cout << "item3 Load failed " << std::endl;
	}
	if (!chestTexture.loadFromFile("assets/chest.png"))
	{
		std::cout << "chest Load failed " << std::endl;
	}
	if (!heartTexture.loadFromFile("assets/heart48.png"))
	{
		std::cout << "heart Load failed " << std::endl;
	}
	if (!fishForShowTexture.loadFromFile("assets/fishforshow.png"))
	{
		std::cout << "FFF Load failed " << std::endl;
	}
	if (!normalBearTexture.loadFromFile("sprites/normalBear.png"))
	{
		std::cout << "normalBear Load failed " << std::endl;
	}
	if (!throwBearTexture.loadFromFile("sprites/throwBear.png"))
	{
		std::cout << "throwBear Load failed " << std::endl;
	}
	if (!fishboneForShowTexture.loadFromFile("assets/fishboneforshow.png"))
	{
		std::cout << "fishboneforshow Load failed " << std::endl;
	}
	if (!fishboneDropTexture.loadFromFile("assets/fishbonedrop.png"))
	{
		std::cout << "fishbonedrop Load failed " << std::endl;
	}
	if (!inventoryTexture.loadFromFile("assets/inventory.png"))
	{
		std::cout << "inventory Load failed " << std::endl;
	}
	if (!ground1Texture.loadFromFile("maps/block1.png"))
	{
		std::cout << "block1 Load failed " << std::endl;
	}
	if (!underGround1Texture.loadFromFile("maps/under1.png"))
	{
		std::cout << "under1 Load failed " << std::endl;
	}
	if (!exitBGTexture.loadFromFile("assets/exitBG.png"))
	{
		std::cout << "exitBG Load failed " << std::endl;
	}
	if (!gameBG1Texture.loadFromFile("maps/gameBG.png"))
	{
		std::cout << "gameBG Load failed " << std::endl;
	}
	if (!leaderBGTexture.loadFromFile("assets/leaderBG.png"))
	{
		std::cout << "leaderBG Load failed " << std::endl;
	}
	if (!boss1rightTexture.loadFromFile("sprites/boss1right.jpg"))
	{
		std::cout << "boss1right Load failed " << std::endl;
	}
	if (!boss1leftTexture.loadFromFile("sprites/boss1left.jpg"))
	{
		std::cout << "boss1left Load failed " << std::endl;
	}
	if (!bigstickTexture.loadFromFile("assets/bigstick.png"))
	{
		std::cout << "bigstick Load failed " << std::endl;
	}
	if (!gameBGShopTexture.loadFromFile("maps/shopBG.png"))
	{
		std::cout << "BGShop Load failed " << std::endl;
	}
	if (!groundShopTexture.loadFromFile("maps/blockShop.png"))
	{
		std::cout << "blockShop Load failed " << std::endl;
	}
	if (!underGroundShopTexture.loadFromFile("maps/underShop.png"))
	{
		std::cout << "undershop Load failed " << std::endl;
	}
	if (!weapon1Texture.loadFromFile("assets/claw148.png"))
	{
		std::cout << "claw1 Load failed " << std::endl;
	}
	if (!weapon2Texture.loadFromFile("assets/claw248.png"))
	{
		std::cout << "claw2 Load failed " << std::endl;
	}
	if (!weapon3Texture.loadFromFile("assets/claw348.png"))
	{
		std::cout << "claw3 Load failed " << std::endl;
	}
	if (!rngboxTexture.loadFromFile("assets/rngbox.png"))
	{
		std::cout << "rngbox Load failed " << std::endl;
	}
	if (!fishShopTexture.loadFromFile("assets/fishShop.png"))
	{
		std::cout << "fishShop Load failed " << std::endl;
	}
	if (!gameBG2Texture.loadFromFile("maps/gameBG2.png"))
	{
		std::cout << "gameBG2 Load failed " << std::endl;
	}
	if (!ground2Texture.loadFromFile("maps/block2.png"))
	{
		std::cout << "block2 Load failed " << std::endl;
	}
	if (!underGround2Texture.loadFromFile("maps/under2.png"))
	{
		std::cout << "under2 Load failed " << std::endl;
	}
	if (!gameBG3Texture.loadFromFile("maps/gameBG3.png"))
	{
		std::cout << "gameBG3 Load failed " << std::endl;
	}
	if (!ground3Texture.loadFromFile("maps/block3.png"))
	{
		std::cout << "block3 Load failed " << std::endl;
	}
	if (!underGround3Texture.loadFromFile("maps/under3.png"))
	{
		std::cout << "under3 Load failed " << std::endl;
	}
	if (!boss3rightTexture.loadFromFile("sprites/boss3right.png"))
	{
		std::cout << "boss3right Load failed " << std::endl;
	}
	if (!boss3leftTexture.loadFromFile("sprites/boss3left.png"))
	{
		std::cout << "boss3left Load failed " << std::endl;
	}
	if (!stoneTexture.loadFromFile("assets/Stone.png"))
	{
		std::cout << "stone Load failed " << std::endl;
	}
	if (!pauseBGTexture.loadFromFile("assets/pauseBG.png"))
	{
		std::cout << "pauseBG Load failed " << std::endl;
	}
	if (!gameoverBGTexture.loadFromFile("assets/gameoverBG.png"))
	{
		std::cout << "gameoverBG Load failed " << std::endl;
	}
	if (!congratBGTexture.loadFromFile("assets/congratBG.png"))
	{
		std::cout << "congratBG Load failed " << std::endl;
	}
}

void setSprite()
{
	shapeSprite.setTexture(playerTextureRight);
	shapeSprite.setPosition(spawn);

	Bullet.setTexture(fishboneTexture);
	Bullet.setTextureRect(sf::IntRect(0, 0, 12, 12));

	attackSprite.setTexture(attackTexture);

	heart.setTexture(heartTexture);
	heart.setTextureRect(sf::IntRect(0, 0, 48, 48));

	fishForShow.setTexture(fishForShowTexture);
	fishForShow.setTextureRect(sf::IntRect(0, 0, 48, 51));

	fishboneForShow.setTexture(fishboneForShowTexture);
	fishboneForShow.setTextureRect(sf::IntRect(0, 0, 56, 54));

	Bullet.setTexture(fishboneTexture);
	Bullet.setTextureRect(sf::IntRect(0, 0, 26, 24));

	inventory1.setTexture(inventoryTexture);
	inventory1.setTextureRect(sf::IntRect(0, 0, 56, 53));

	inventory2.setTexture(inventoryTexture);
	inventory2.setTextureRect(sf::IntRect(0, 0, 56, 53));

	item2.setTexture(item2Texture);
	item2.setTextureRect(sf::IntRect(0, 0, 30, 36));

	item3.setTexture(item3Texture);
	item3.setTextureRect(sf::IntRect(0, 0, 36, 36));

	heartShop.setTexture(heartTexture);
	heartShop.setPosition(240, 490);

	rngboxShop.setTexture(rngboxTexture);
	rngboxShop.setPosition(405, 485);

	weaponShop.setPosition(577, 495);

	fishboneShop.setTexture(fishboneForShowTexture);
	fishboneShop.setPosition(740, 485);

	fishShop1.setTexture(fishShopTexture);
	fishShop2.setTexture(fishShopTexture);
	fishShop3.setTexture(fishShopTexture);
	fishShop4.setTexture(fishShopTexture);

	fishShop1.setPosition(285, 450);
	fishShop2.setPosition(450, 450);
	fishShop3.setPosition(620, 450);
	fishShop4.setPosition(790, 450);

	pauseBG.setTexture(pauseBGTexture);
	gameoverBG.setTexture(gameoverBGTexture);
	congratBG.setTexture(congratBGTexture);
}

void firstTextSet()
{
	textScore.setFont(font);
	textScore.setFillColor(sf::Color::White);
	textScore.setOutlineColor(sf::Color::Black);
	textScore.setCharacterSize(50);
	textScore.setStyle(sf::Text::Bold);

	textFish.setFont(font);
	textFish.setFillColor(sf::Color::White);
	textFish.setOutlineColor(sf::Color::Black);
	textFish.setCharacterSize(50);
	textFish.setStyle(sf::Text::Bold);

	textFishbone.setFont(font);
	textFishbone.setFillColor(sf::Color::White);
	textFishbone.setOutlineColor(sf::Color::Black);
	textFishbone.setCharacterSize(50);
	textFishbone.setStyle(sf::Text::Bold);

	textHP.setFont(font);
	textHP.setFillColor(sf::Color::White);
	textHP.setOutlineColor(sf::Color::Black);
	textHP.setCharacterSize(50);
	textHP.setStyle(sf::Text::Bold);

	for (int i = 0; i < 4; i++)
	{
		SHOP[i].setFont(font);
		SHOP[i].setFillColor(sf::Color::White);
		SHOP[i].setOutlineColor(sf::Color::Black);
		SHOP[i].setCharacterSize(30);
		SHOP[i].setStyle(sf::Text::Bold);
	}
	SHOP[0].setPosition(225, 440);
	SHOP[1].setPosition(390, 440);
	SHOP[2].setPosition(560, 440);
	SHOP[3].setPosition(730, 440);
}

void setGround1()
{// if intersect posx -= 9.5
//  ground.push_back(GROUND(sizex, sizey,	posx, posy,		g,	underground)); 
	ground.push_back(GROUND(1600.0, 32.0, 1210.0, 632.0, 1, 1)); // 0
	ground.push_back(GROUND(1216.0, 32.0, 0.0, 600.0, 1, 1)); // 1
	ground.push_back(GROUND(96.0, 32.0, 0.0, 568.0, 1, 1)); // 2
	ground.push_back(GROUND(288.0, 32.0, 200.0, 400.0, 1, 0)); // 3
	ground.push_back(GROUND(192.0, 32.0, 950.5, 568.0, 1, 1)); // 4
	ground.push_back(GROUND(32.0, 232.0, 2778.0, 433.0, 1, 0)); // 5 I
	ground.push_back(GROUND(1472.0, 32.0, 1306.0, 432.0, 1, 0)); // 6
	ground.push_back(GROUND(3000.0, 32.0, 3088.5, 632.0, 1, 1)); // 7
	ground.push_back(GROUND(32.0, 328.0, 3066.0, 432.0, 1, 0)); // 8 I
	ground.push_back(GROUND(320.0, 32.0, 2780.0, 368.0, 1, 1)); // 9
	ground.push_back(GROUND(1100.0, 32.0, 3748.0, 600.0, 1, 1)); // 10
	ground.push_back(GROUND(150.0, 32.0, 3850.0, 400.0, 1, 0)); // 11
	ground.push_back(GROUND(150.0, 32.0, 4100.0, 400.0, 1, 0)); // 12
	ground.push_back(GROUND(150.0, 32.0, 4350.0, 400.0, 1, 0)); // 13
	ground.push_back(GROUND(150.0, 32.0, 4600.0, 400.0, 1, 0)); // 14
}

void setMonster1()
{
	NBear[0].set(300, 400); // g3
	NBear[1].set(200, 600); // g1
	NBear[2].set(1000, 568); // g4
	NBear[3].set(1400, 632); // g0
	NBear[4].set(1700, 632); // g0
	NBear[5].set(2000, 632); // g0 
	NBear[6].set(2250, 632); // g0
	NBear[7].set(2500, 632); // g0
	NBear[8].set(1750, 432); // g6
	NBear[9].set(1875, 432); // g6
	NBear[10].set(2000, 432); // g6
	NBear[11].set(2125, 432); // g6
	NBear[12].set(2250, 432); // g6
	NBear[13].set(2500, 432); // g6

	TBear[0].set(340, 400); // g1
	TBear[1].set(2852, 368); // g9
	TBear[2].set(3026, 368); // g9

	Boss1.set(4700, 600);
}

void setFish1()
{
	FISH[0].set(75, 400);
	FISH[1].set(250, 250);
	FISH[2].set(400, 250);
	FISH[3].set(325, 475);
	FISH[4].set(550, 425);
	FISH[5].set(650, 425);
	FISH[6].set(750, 425);
	FISH[7].set(950, 400);
	FISH[8].set(1018.75, 350);
	FISH[9].set(1087.5, 400);
	FISH[10].set(1400, 250);
	FISH[11].set(1550, 250);
	FISH[12].set(1700, 250);
	FISH[13].set(1850, 250);
	FISH[14].set(2000, 250);
	FISH[15].set(2150, 250);
	FISH[16].set(2300, 250);
	FISH[17].set(2450, 250);
	FISH[18].set(2600, 250);
	FISH[19].set(1250, 350);
	FISH[20].set(2925, 150);
	FISH[21].set(3150, 450);
	FISH[22].set(3400, 450);
	FISH[23].set(3650, 450);
	FISH[24].set(325, 150);
}

void collectFish()
{
	for (int i = 0; i < f; i++)
	{
		if (shapeSprite.getGlobalBounds().intersects(FISH[i].body.getGlobalBounds()))
		{
			score += 10;
			FISH[i].re();
			fish++;
			collectfishEF.play();
		}
	}
	for (int i = 0; i < fb; i++)
	{
		if (shapeSprite.getGlobalBounds().intersects(FISHBONE[i].body.getGlobalBounds()))
		{
			FISHBONE[i].re();
			fishbone++;
			collectfishEF.play();
		}
	}
}

void setChest1()
{
	CHEST[0].set(2700, 632);
}

void use(int n)
{
	useitemEF.play();
	if (n == 1)
	{
		HP += 1;
	}
	else if (n == 2)
	{
		potion = 1;
		startP = clock();
	}
	else if (n == 3)
	{
		fishbonecase = 1;
		startF = clock();
	}
}

void setHead()
{
	heart.setPosition(view.getCenter().x + 225, 8);
	fishForShow.setPosition(view.getCenter().x - 165, 9);
	fishboneForShow.setPosition(view.getCenter().x + 30, 9);
	inventory1.setPosition(view.getCenter().x + 407, 9);
	inventory2.setPosition(view.getCenter().x + 463, 9);
	item2.setPosition(view.getCenter().x + 477, 16);
	item3.setPosition(view.getCenter().x + 474, 14);
	if (attackDamage == 5)
	{
		clawForShow.setTexture(weapon1Texture);
	}
	else if (attackDamage == 10)
	{
		clawForShow.setTexture(weapon2Texture);
	}
	else clawForShow.setTexture(weapon3Texture);
	clawForShow.setPosition(view.getCenter().x + 410, 14);
	if (attackDamage == 20)fishShop3.setTextureRect(sf::IntRect(0, 0, 0, 0));
	setText();
}

void stage1()
{
	menuBGM.stop();
	startx = 0;
	endx = 5000;
	shapeSprite.setPosition(spawn);
	gameBG.setTexture(gameBG1Texture);
	gameBG.setTextureRect(sf::IntRect(0, 0, 5760, 720));
	setGround1();
	setMonster1();
	setFish1();
	setChest1();
	stage1BGM.play();
}

void setup()
{
	if (!font.loadFromFile("fonts/ARCADECLASSIC.TTF"))//("fonts/#glidepath.ttf"))
	{
		std::cout << "fonts Load failed " << std::endl;
	}
	if (!menuBGTexture.loadFromFile("assets/menuBG.png"))
	{
		std::cout << "menuBG Load failed " << std::endl;
	}
	menuBG.setTexture(menuBGTexture);

	gameCreated.setFont(font);
	gameCreated.setFillColor(sf::Color::White);
	gameCreated.setOutlineColor(sf::Color::Black);
	gameCreated.setCharacterSize(100);
	gameCreated.setStyle(sf::Text::Bold);
	gameCreated.setString("GAME CREATED BY");
	gameCreated.setPosition(window.getView().getCenter().x - 383.75, 80);

	showName.setFont(font);
	showName.setFillColor(sf::Color::White);
	showName.setOutlineColor(sf::Color::Black);
	showName.setCharacterSize(100);
	showName.setStyle(sf::Text::Bold);
	showName.setString("GLIT RUNGROJKIJKUL");
	showName.setPosition(window.getView().getCenter().x - 480, 280);

	showID.setFont(font);
	showID.setFillColor(sf::Color::White);
	showID.setOutlineColor(sf::Color::Black);
	showID.setCharacterSize(100);
	showID.setStyle(sf::Text::Bold);
	showID.setString("STUDENT ID 63010022");
	showID.setPosition(window.getView().getCenter().x - 490, 480);

	window.draw(menuBG);
	window.draw(gameCreated);
	window.draw(showName);
	window.draw(showID);
	window.display();
	window.clear();
	loadSound();
	loadTexture();
	setSprite();
	firstTextSet();
	startt = clock();
	endt = clock();
	while ((endt - startt) / CLOCKS_PER_SEC <= 2)
	{
		sf::Event event;
		if (window.pollEvent(event)) {}
		window.draw(menuBG);
		window.draw(gameCreated);
		window.draw(showName);
		window.draw(showID);
		window.display();
		window.clear();
		endt = clock();
	}
}

void start()
{
	startdata();
	reset();
	view = startView;
	window.setView(view);
	name.clear();
	fish = 0;
	fishbone = 2;
	HP = 3;
	score = 0;
	cItem = 0;
	attackDamage = 5;
	exitBG.setTexture(exitBGTexture);
	exitBG.setTextureRect(sf::IntRect(0, 0, 1050, 686));
	leaderBG.setTexture(leaderBGTexture);
	leaderBG.setTextureRect(sf::IntRect(0, 0, 1050, 686));
}

void reset()
{
	for (int i = 0; i < nb; i++)
	{
		NBear[i].re();
	}
	for (int i = 0; i < tb; i++)
	{
		TBear[i].re();
	}
	for (int i = 0; i < fb; i++)
	{
		FISHBONE[i].re();
	}
	for (int i = 0; i < f; i++)
	{
		FISH[i].re();
	}
	for (int i = 0; i < ch; i++)
	{
		CHEST[i].re();
	}
	Boss1.re();
	Boss2.re();
	g = 0;
	while (!ground.empty())
	{
		ground.erase(ground.begin());
	}
	for (int i = 0; i < it; i++)
	{
		ITEM[i].re();
	}
	attack = 0;
	bullet = 0;
	potion = 0;
	state = 0;
	fishbonecase = 0;
	animation = 0, Ranimation = 0, Lanimation = 0;
	RH = 1;
	window.clear();
	view = startView;
	moveView = 0;
	stage = 1;
	down = 1;
	Speed = 1.35;
	BTM = 0;
	speed = 0;
	for (int i = 0; i < 4; i++)
	{
		Pillar[i].setSize(sf::Vector2f(0, 0));
		Pillar[i].setPosition(-100, -100);
	}
	stage1BGM.stop();
	boss1BGM.stop();
	stage2BGM.stop();
	boss2BGM.stop();
	stage3BGM.stop();
	shopBGM.stop();
	menuBGM.stop();
}

void leaderboard()
{
	int leader = 2;
	int cos = 0;
	startM = clock();
	leaderBG.setPosition(window.getView().getCenter().x - 525, 20);
	Leaderboard[0].setFont(font);
	Leaderboard[0].setFillColor(sf::Color::White);
	Leaderboard[0].setOutlineColor(sf::Color::Black);
	Leaderboard[0].setCharacterSize(100);
	Leaderboard[0].setStyle(sf::Text::Bold);
	for (int i = 1; i < 6; i++)
	{
		Leaderboard[i].setFont(font);
		Leaderboard[i].setFillColor(sf::Color::White);
		Leaderboard[i].setOutlineColor(sf::Color::Black);
		Leaderboard[i].setCharacterSize(70);
		Leaderboard[i].setStyle(sf::Text::Bold);

		Score[i].setFont(font);
		Score[i].setFillColor(sf::Color::White);
		Score[i].setOutlineColor(sf::Color::Black);
		Score[i].setCharacterSize(70);
		Score[i].setStyle(sf::Text::Bold);
	}
	Leaderboard[6].setFont(font);
	Leaderboard[6].setFillColor(sf::Color::White);
	Leaderboard[6].setOutlineColor(sf::Color::Black);
	Leaderboard[6].setCharacterSize(110);
	Leaderboard[6].setStyle(sf::Text::Bold);

	Leaderboard[0].setString("LEADERBOARD");
	Leaderboard[0].setPosition(sf::Vector2f(230, 20));
	int i = 5;
	for (std::map<int, std::string>::iterator it = data.begin(); it != data.end(); it++, i--)
	{
		std::string ch;
		ch.append(it->second);
		Leaderboard[i].setString(ch);

		ch = "";
		ch.append(changeNtoS(it->first));
		Score[i].setString(ch);
	}
	Leaderboard[1].setPosition(sf::Vector2f(237.5, 150));
	Score[1].setPosition(sf::Vector2f(637.5, 150));

	Leaderboard[2].setPosition(sf::Vector2f(237.5, 225));
	Score[2].setPosition(sf::Vector2f(637.5, 225));

	Leaderboard[3].setPosition(sf::Vector2f(237.5, 300));
	Score[3].setPosition(sf::Vector2f(637.5, 300));

	Leaderboard[4].setPosition(sf::Vector2f(237.5, 375));
	Score[4].setPosition(sf::Vector2f(637.5, 375));

	Leaderboard[5].setPosition(sf::Vector2f(237.5, 450));
	Score[5].setPosition(sf::Vector2f(637.5, 450));

	Leaderboard[6].setString("BACK");
	Leaderboard[6].setPosition(sf::Vector2f(400, 550));
	while (window.isOpen())
	{
		sf::Event event;
		if (window.pollEvent(event)) {}
		endt = clock();
		switch (leader)
		{
		case 1:
		{
			Leaderboard[6].setFillColor(sf::Color::Red);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter));
				window.clear();
				window.display();
				cos = 1;
			}
			break;
		}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::End) || close == 1)
		{
			close = 1;
			break;
		}
		if ((double)(endt - startM) / CLOCKS_PER_SEC > 0.2)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				leader--;
				if (leader < 1)leader = 1;
				startM = clock();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				leader++;
				if (leader > 1)leader = 1;
				startM = clock();
			}
		}
		window.draw(leaderBG);
		for (int i = 0; i < 7; i++)
		{
			window.draw(Leaderboard[i]);
		}
		for (int i = 1; i < 6; i++)
		{
			window.draw(Score[i]);
		}
		if (cos == 1)break;
		window.display();
		window.clear();
	}
}

void MENU()
{
	menuBGM.play();
	while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter));
	showName.setCharacterSize(25);
	showName.setPosition(window.getView().getCenter().x + 260, 650);
	showID.setCharacterSize(25);
	showID.setPosition(window.getView().getCenter().x + 256.25, 675);
	int menu = 3;
	close = 0;
	startM = clock();
	for (int i = 0; i < 3; i++)
	{
		Menu[i].setFont(font);
		Menu[i].setFillColor(sf::Color::White);
		Menu[i].setOutlineColor(sf::Color::Black);
		Menu[i].setCharacterSize(110);
		Menu[i].setStyle(sf::Text::Bold);
	}
	Menu[0].setString("PLAY");
	Menu[0].setPosition(sf::Vector2f(430, 80));

	Menu[1].setString("LEADERBOARD");
	Menu[1].setPosition(sf::Vector2f(210, 280));

	Menu[2].setString("EXIT");
	Menu[2].setPosition(sf::Vector2f(430, 480));
	while (window.isOpen()) // Menu
	{
		sf::Event event;
		if (window.pollEvent(event)) {}
		endt = clock();
		switch (menu)
		{
		case 0:
		{
			Menu[0].setFillColor(sf::Color::Red);
			Menu[1].setFillColor(sf::Color::White);
			Menu[2].setFillColor(sf::Color::White);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				close = 2;
			}
			break;
		}

		case 1:
		{
			Menu[0].setFillColor(sf::Color::White);
			Menu[1].setFillColor(sf::Color::Red);
			Menu[2].setFillColor(sf::Color::White);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				leaderboard();
			}
			break;
		}

		case 2:
		{
			Menu[0].setFillColor(sf::Color::White);
			Menu[1].setFillColor(sf::Color::White);
			Menu[2].setFillColor(sf::Color::Red);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				exitFromMenu();
			}
			break;
		}
		}
		if ((double)(endt - startM) / CLOCKS_PER_SEC > 0.2)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				UIEF.play();
				if (menu == 3)menu = 0;
				else
				{
					menu--;
					if (menu < 0)menu = 2;
				}
				startM = clock();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				UIEF.play();
				if (menu == 3)menu = 2;
				else
				{
					menu++;
					if (menu > 2)menu = 0;
				}
				startM = clock();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			exitFromMenu();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::End) || close == 1)
		{
			close = 1;
			break;
		}
		window.draw(menuBG);
		for (int i = 0; i < 3; i++)
		{
			window.draw(Menu[i]);
		}
		window.draw(showName);
		window.draw(showID);
		window.display();
		window.clear();
		if (close == 2)break;
	}
}

void exitFromMenu()
{
	while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
	int exit = 2;
	exitBG.setPosition(window.getView().getCenter().x - 525, 20);
	startEx = clock();
	for (int i = 0; i < 3; i++)
	{
		Exit[i].setFont(font);
		Exit[i].setFillColor(sf::Color::White);
		Exit[i].setOutlineColor(sf::Color::Black);
		Exit[i].setCharacterSize(125);
		Exit[i].setStyle(sf::Text::Bold);
	}
	Exit[0].setCharacterSize(145);
	Exit[0].setString("ARE YOU SURE !");
	Exit[0].setPosition(sf::Vector2f(window.getView().getCenter().x - 462.5, 130));

	Exit[1].setString("YES");
	Exit[1].setPosition(sf::Vector2f(window.getView().getCenter().x - 325, 330));

	Exit[2].setString("NO");
	Exit[2].setPosition(sf::Vector2f(window.getView().getCenter().x + 175, 330));
	while (window.isOpen())
	{
		int closeEx = 0;
		sf::Event event;
		if (window.pollEvent(event)) {}
		endt = clock();
		switch (exit)
		{
		case 1:
		{
			Exit[1].setFillColor(sf::Color::Red);
			Exit[2].setFillColor(sf::Color::White);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				window.close();
				close = 1;
			}
			break;
		}

		case 2:
		{
			Exit[1].setFillColor(sf::Color::White);
			Exit[2].setFillColor(sf::Color::Red);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				closeEx = 1;
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter));
			}
			break;
		}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			closeEx = 1;
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::End) || close == 1)
		{
			close = 1;
			break;
		}
		if ((double)(endt - startEx) / CLOCKS_PER_SEC > 0.2)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				UIEF.play();
				exit--;
				if (exit < 1)exit = 2;
				startEx = clock();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				UIEF.play();
				exit++;
				if (exit > 2)exit = 1;
				startEx = clock();
			}
		}
		window.draw(menuBG);
		for (int i = 0; i < 3; i++)
		{
			window.draw(Menu[i]);
		}
		window.draw(exitBG);
		for (int i = 0; i < 3; i++)
		{
			window.draw(Exit[i]);
		}
		window.display();
		window.clear();
		if (closeEx == 1)break;
	}
}

void gameDraw()
{
	window.draw(gameBG);
	for (int i = 0; i < ch; i++)
	{
		if (CHEST[i].state > 0)window.draw(CHEST[i].body);
	}
	if (stage == 2)
	{
		for (i = 0; i < 4; i++)
		{
			window.draw(SHOP[i]);
		}
		if (attackDamage == 5) weaponShop.setTexture(weapon2Texture);
		else if (attackDamage == 10) weaponShop.setTexture(weapon3Texture);
		else weaponShop.setTextureRect(sf::IntRect(0, 0, 0, 0));
		window.draw(heartShop);
		window.draw(rngboxShop);
		window.draw(weaponShop);
		window.draw(fishboneShop);
		window.draw(fishShop1);
		window.draw(fishShop2);
		window.draw(fishShop3);
		window.draw(fishShop4);
	}
	if (state == 0 || state == 2)window.draw(shapeSprite);
	window.draw(inventory1);
	window.draw(inventory2);
	window.draw(textScore);
	window.draw(textFish);
	window.draw(textFishbone);
	window.draw(textHP);
	window.draw(heart);
	window.draw(fishForShow);
	window.draw(fishboneForShow);
	window.draw(Boss3.stone1);
	window.draw(Boss3.stone2);
	window.draw(Boss3.stone3);
	if (cItem == 2) { window.draw(item2); }
	else if (cItem == 3) { window.draw(item3); }
	window.draw(clawForShow);
	for (int i = 0; i < nb; i++)
	{
		if (NBear[i].HP > 0)
		{
			window.draw(NBear[i].body);
		}
	}
	for (int i = 0; i < tb; i++)
	{
		if (TBear[i].HP == -50) {}
		else if (TBear[i].th < 3 && TBear[i].th > 0)
		{
			window.draw(TBear[i].stick);
		}
	}
	for (int i = 0; i < tb; i++)
	{
		if (TBear[i].HP > 0)
		{
			window.draw(TBear[i].body);
		}
	}
	if (Boss1.HP > 0)
	{
		window.draw(Boss1.body);
		window.draw(Boss1.stick);
	}
	if (Boss2.HP > 0)
	{
		window.draw(Boss2.body);
		window.draw(Boss2.stick);
	}
	if (Boss3.HP > 0)
	{
		window.draw(Boss3.body);
		window.draw(Boss3.stick);
	}
	if (bullet < 3 && bullet > 0) window.draw(Bullet);
	if (attack < 4 && attack > 0)window.draw(attackSprite);
	for (int i = 0; i < it; i++)
	{
		if (ITEM[i].state > 0)
		{
			window.draw(ITEM[i].body);
		}
	}
	for (int i = 0; i < f; i++)
	{
		if (FISH[i].state == 1)window.draw(FISH[i].body);
	}
	for (int i = 0; i < fb; i++)
	{
		if (FISHBONE[i].state == 1)window.draw(FISHBONE[i].body);
	}
	for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); it++)
	{
		window.draw(it->ground);
		window.draw(it->underGround);
	}
	window.display();
	window.clear();
}

void gameCal()
{
	setHead();
	window.setView(view);
	endt = clock();
	mainCharacter();
	for (int i = 0; i < nb; i++)
	{
		if (NBear[i].HP > 0)
		{
			NBear[i].move();
		}
		else if (NBear[i].HP == -50) {}
		else
		{
			NBear[i].re();
		}
	}
	for (int i = 0; i < tb; i++)
	{
		if (TBear[i].HP > 0)
		{
			TBear[i].move();
			TBear[i].shot();
		}
		else if (TBear[i].HP == -50) {}
		else if (TBear[i].HP <= 0)
		{
			TBear[i].re();
		}
	}
	if (moveView == 1)
	{
		if (Boss1.HP > 0)
		{
			Boss1.move();
			Boss1.shot();
		}
		if (Boss2.HP > 0)
		{
			Boss2.move();
			Boss2.shot();
		}
		if (Boss3.HP > 0)
		{
			Boss3.move();
			Boss3.shot();
		}
	}
	if (bullet > 0)
	{
		shoot();
	}
	if (attack > 0)
	{
		scratch();
	}
	for (int i = 0; i < it; i++)
	{
		if (ITEM[i].state > 0)
		{
			ITEM[i].move();
		}
	}
	damageCal();
	collectFish();
}

void gamePause()
{
	while (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
	int exit = 2;
	pauseBG.setPosition(window.getView().getCenter().x - 525, 20);
	startEx = clock();
	for (int i = 0; i < 3; i++)
	{
		Exit[i].setFont(font);
		Exit[i].setFillColor(sf::Color::White);
		Exit[i].setOutlineColor(sf::Color::Black);
		Exit[i].setCharacterSize(80);
		Exit[i].setStyle(sf::Text::Bold);
	}
	Exit[0].setCharacterSize(145);
	Exit[0].setString("Pause");
	Exit[0].setPosition(sf::Vector2f(window.getView().getCenter().x - 200, 130));

	Exit[1].setString("Back to menu");
	Exit[1].setPosition(sf::Vector2f(window.getView().getCenter().x - 450, 330));

	Exit[2].setString("Resume");
	Exit[2].setPosition(sf::Vector2f(window.getView().getCenter().x + 175, 330));
	while (window.isOpen())
	{
		int closeEx = 0;
		sf::Event event;
		if (window.pollEvent(event)) {}
		endt = clock();
		switch (exit)
		{
		case 1:
		{
			Exit[1].setFillColor(sf::Color::Red);
			Exit[2].setFillColor(sf::Color::White);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				closeEx = 1;
				BTM = 1;
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter));
			}
			break;
		}
		case 2:
		{
			Exit[1].setFillColor(sf::Color::White);
			Exit[2].setFillColor(sf::Color::Red);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				closeEx = 1;
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter));
			}
			break;
		}
		}
		if ((double)(endt - startEx) / CLOCKS_PER_SEC > 0.2)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				UIEF.play();
				exit--;
				if (exit < 1)exit = 2;
				startEx = clock();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				UIEF.play();
				exit++;
				if (exit > 2)exit = 1;
				startEx = clock();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			closeEx = 1;
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::End) || close == 1)
		{
			close = 1;
			break;
		}
		window.draw(gameBG);
		for (int i = 0; i < ch; i++)
		{
			if (CHEST[i].state > 0)window.draw(CHEST[i].body);
		}
		if (stage == 2)
		{
			for (i = 0; i < 4; i++)
			{
				window.draw(SHOP[i]);
			}
			if (attackDamage == 5) weaponShop.setTexture(weapon2Texture);
			else if (attackDamage == 10) weaponShop.setTexture(weapon3Texture);
			else weaponShop.setTextureRect(sf::IntRect(0, 0, 0, 0));
			window.draw(heartShop);
			window.draw(rngboxShop);
			window.draw(weaponShop);
			window.draw(fishboneShop);
			window.draw(fishShop1);
			window.draw(fishShop2);
			window.draw(fishShop3);
			window.draw(fishShop4);
		}
		if (state == 0 || state == 2)window.draw(shapeSprite);
		window.draw(inventory1);
		window.draw(inventory2);
		window.draw(textScore);
		window.draw(textFish);
		window.draw(textFishbone);
		window.draw(textHP);
		window.draw(heart);
		window.draw(fishForShow);
		window.draw(fishboneForShow);
		window.draw(Boss3.stone1);
		window.draw(Boss3.stone2);
		window.draw(Boss3.stone3);
		if (cItem == 2) { window.draw(item2); }
		else if (cItem == 3) { window.draw(item3); }
		window.draw(clawForShow);
		for (int i = 0; i < nb; i++)
		{
			if (NBear[i].HP > 0)
			{
				window.draw(NBear[i].body);
			}
		}
		for (int i = 0; i < tb; i++)
		{
			if (TBear[i].HP == -50) {}
			else if (TBear[i].th < 3 && TBear[i].th > 0)
			{
				window.draw(TBear[i].stick);
			}
		}
		for (int i = 0; i < tb; i++)
		{
			if (TBear[i].HP > 0)
			{
				window.draw(TBear[i].body);
			}
		}
		if (Boss1.HP > 0)
		{
			window.draw(Boss1.body);
			window.draw(Boss1.stick);
		}
		if (Boss2.HP > 0)
		{
			window.draw(Boss2.body);
			window.draw(Boss2.stick);
		}
		if (Boss3.HP > 0)
		{
			window.draw(Boss3.body);
			window.draw(Boss3.stick);
		}
		if (bullet < 3 && bullet > 0) window.draw(Bullet);
		if (attack < 4 && attack > 0)window.draw(attackSprite);
		for (int i = 0; i < it; i++)
		{
			if (ITEM[i].state > 0)
			{
				window.draw(ITEM[i].body);
			}
		}
		for (int i = 0; i < f; i++)
		{
			if (FISH[i].state == 1)window.draw(FISH[i].body);
		}
		for (int i = 0; i < fb; i++)
		{
			if (FISHBONE[i].state == 1)window.draw(FISHBONE[i].body);
		}
		for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); it++)
		{
			window.draw(it->ground);
			window.draw(it->underGround);
		}
		window.draw(pauseBG);
		for (int i = 0; i < 3; i++)
		{
			window.draw(Exit[i]);
		}
		window.display();
		window.clear();
		if (closeEx == 1)break;
	}
}

void startdata()
{
	char a[40];
	char ch;
	int b;
	fp = fopen("highscore/data.txt", "a+");
	ch = fscanf(fp, "%s", a);
	fscanf(fp, "%d", &b);
	while (!data.empty()) data.erase(data.begin());
	if (ch == EOF)
	{
		fclose(fp);
		fp = fopen("highscore/data.txt", "w");
		data.insert(std::pair<int, std::string>(2500, "a"));
		data.insert(std::pair<int, std::string>(2000, "b"));
		data.insert(std::pair<int, std::string>(1000, "c"));
		data.insert(std::pair<int, std::string>(500, "d"));
		data.insert(std::pair<int, std::string>(300, "e"));
		int i = 0;
		for (std::map<int, std::string>::iterator it = data.begin(); i < 5; it++, i++)
		{
			for (int j = 0; it->second[j] != '\0'; j++)
			{
				fprintf(fp, "%c", it->second[j]);
			}
			fprintf(fp, " %d\n", it->first);
		}
	}
	else
	{
		while (ch != EOF)
		{
			data.insert(std::pair<int, std::string>(b, a));
			//std::cout << b << ' ' << a << std::endl;
			fscanf(fp, "%s", a);
			ch = fscanf(fp, "%d", &b);
		}
	}
	fclose(fp);
}

void gameover()
{
	int exit = 1;
	gameoverBG.setPosition(window.getView().getCenter().x - 525, 20);
	congratBG.setPosition(window.getView().getCenter().x - 525, 20);
	startEx = clock();
	for (int i = 0; i < 3; i++)
	{
		Exit[i].setFont(font);
		Exit[i].setFillColor(sf::Color::White);
		Exit[i].setOutlineColor(sf::Color::Black);
		Exit[i].setCharacterSize(100);
		Exit[i].setStyle(sf::Text::Bold);
	}
	if (HP < 0)
	{
		Exit[0].setCharacterSize(145);
		Exit[0].setString("Gameover!");
		Exit[0].setPosition(sf::Vector2f(window.getView().getCenter().x - 350, 130));
	}
	else
	{
		Exit[0].setCharacterSize(110);
		Exit[0].setString("Congratulation!");
		Exit[0].setPosition(sf::Vector2f(window.getView().getCenter().x - 462.5, 130));
	}

	Exit[1].setString("Back to menu");
	Exit[1].setPosition(sf::Vector2f(window.getView().getCenter().x - 300, 350));
	Exit[1].setFillColor(sf::Color::White);

	NAME.setPosition(sf::Vector2f(-200, -200));
	NAMETEXT.setPosition(sf::Vector2f(-200, -200));
	saveData();
	while (window.isOpen())
	{
		int closeEx = 0;
		sf::Event event;
		if (window.pollEvent(event)) {}
		endt = clock();
		switch (exit)
		{
		case 1:
		{
			Exit[1].setFillColor(sf::Color::Red);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				closeEx = 1;
				BTM = 1;
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter));
			}
			break;
		}
		}
		if ((double)(endt - startEx) / CLOCKS_PER_SEC > 0.2)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				exit--;
				if (exit < 1)exit = 2;
				startEx = clock();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				exit++;
				if (exit > 1)exit = 1;
				startEx = clock();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			closeEx = 1;
			BTM = 1;
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::End) || close == 1)
		{
			close = 1;
			break;
		}
		window.draw(gameBG);
		for (int i = 0; i < ch; i++)
		{
			if (CHEST[i].state > 0)window.draw(CHEST[i].body);
		}
		if (stage == 2)
		{
			for (i = 0; i < 4; i++)
			{
				window.draw(SHOP[i]);
			}
			if (attackDamage == 5) weaponShop.setTexture(weapon2Texture);
			else if (attackDamage == 10) weaponShop.setTexture(weapon3Texture);
			else weaponShop.setTextureRect(sf::IntRect(0, 0, 0, 0));
			window.draw(heartShop);
			window.draw(rngboxShop);
			window.draw(weaponShop);
			window.draw(fishboneShop);
			window.draw(fishShop1);
			window.draw(fishShop2);
			window.draw(fishShop3);
			window.draw(fishShop4);
		}
		if (state == 0 || state == 2)window.draw(shapeSprite);
		window.draw(inventory1);
		window.draw(inventory2);
		window.draw(textScore);
		window.draw(textFish);
		window.draw(textFishbone);
		window.draw(textHP);
		window.draw(heart);
		window.draw(fishForShow);
		window.draw(fishboneForShow);
		window.draw(Boss3.stone1);
		window.draw(Boss3.stone2);
		window.draw(Boss3.stone3);
		if (cItem == 2) { window.draw(item2); }
		else if (cItem == 3) { window.draw(item3); }
		window.draw(clawForShow);
		for (int i = 0; i < nb; i++)
		{
			if (NBear[i].HP > 0)
			{
				window.draw(NBear[i].body);
			}
		}
		for (int i = 0; i < tb; i++)
		{
			if (TBear[i].HP == -50) {}
			else if (TBear[i].th < 3 && TBear[i].th > 0)
			{
				window.draw(TBear[i].stick);
			}
		}
		for (int i = 0; i < tb; i++)
		{
			if (TBear[i].HP > 0)
			{
				window.draw(TBear[i].body);
			}
		}
		if (Boss1.HP > 0)
		{
			window.draw(Boss1.body);
			window.draw(Boss1.stick);
		}
		if (Boss2.HP > 0)
		{
			window.draw(Boss2.body);
			window.draw(Boss2.stick);
		}
		if (Boss3.HP > 0)
		{
			window.draw(Boss3.body);
			window.draw(Boss3.stick);
		}
		if (bullet < 3 && bullet > 0) window.draw(Bullet);
		if (attack < 4 && attack > 0)window.draw(attackSprite);
		for (int i = 0; i < it; i++)
		{
			if (ITEM[i].state > 0)
			{
				window.draw(ITEM[i].body);
			}
		}
		for (int i = 0; i < f; i++)
		{
			if (FISH[i].state == 1)window.draw(FISH[i].body);
		}
		for (int i = 0; i < fb; i++)
		{
			if (FISHBONE[i].state == 1)window.draw(FISHBONE[i].body);
		}
		for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); it++)
		{
			window.draw(it->ground);
			window.draw(it->underGround);
		}
		if (HP < 0)window.draw(gameoverBG);
		else window.draw(congratBG);
		for (int i = 0; i < 2; i++)
		{
			window.draw(Exit[i]);
		}
		window.draw(NAME);
		window.draw(NAMETEXT);
		window.display();
		window.clear();
		if (closeEx == 1)
		{
			gameoverEF.stop();
			congratEF.stop();
			break;
		}
	}
}

void stage1boss()
{
	if (view.getCenter().x > 3900 && view.getCenter().x < 4300 && Boss1.HP > 0)
	{
		stage1BGM.stop();
		while (view.getCenter().x > 3900 && view.getCenter().x < 4300 && Boss1.HP > 0)
		{
			view.move(0.5, 0);
			window.setView(view);
			setHead();
			gameDraw();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::End) || close == 1)
			{
				close = 1;
				break;
			}
		}
		for (int i = 0; i < nb; i++) NBear[i].re();
		for (int i = 0; i < fb; i++)FISHBONE[i].re();
		for (int i = 0; i < tb; i++) TBear[i].re();
		startx = 3760;
		endx = 4840;
		moveView = 1;
		boss1BGM.play();
		Boss1.skill = clock();
	}
	if (Boss1.HP <= 0 && Boss1.HP > -50)
	{
		bossdamagedEF.stop();
		bossdeadEF.play();
		Boss1.re();
		fish += 20;
		score += 300;
		endx = 5075;
		moveView = 0;
		while ((view.getCenter().x - shapeSprite.getPosition().x >= -16) && view.getCenter().x - 540 > startx)
		{
			view.move(-0.18 * Speed, 0);
		}
		while ((view.getCenter().x - shapeSprite.getPosition().x <= 16) && view.getCenter().x + 540 < endx)
		{
			view.move(.18 * Speed, 0);
		}
	}
}

void shop()
{
	stage = 2;
	startx = 0;
	endx = 1080;
	shapeSprite.setPosition(spawn);
	gameBG.setTexture(gameBGShopTexture);
	gameBG.setTextureRect(sf::IntRect(0, 0, 1080, 720));
	Pillar[0].setSize(sf::Vector2f(50, 60));
	Pillar[0].setPosition(240, 540);

	Pillar[1].setSize(sf::Vector2f(50, 60));
	Pillar[1].setPosition(408, 540);

	Pillar[2].setSize(sf::Vector2f(50, 60));
	Pillar[2].setPosition(576, 540);

	Pillar[3].setSize(sf::Vector2f(50, 60));
	Pillar[3].setPosition(744, 540);
	setGroundShop();
	shopBGM.play();
}

void setGroundShop()
{
	//  ground.push_back(GROUND(sizex, sizey,	posx,	posy,	g,	underground)); 
	ground.push_back(GROUND(2000.0, 32.0, 0.0, 600, 2, 2)); // 0
}

void buy(int a)
{
	sf::Sprite cost, pic;
	int exit = 2;
	int price;
	sf::Text t1, t2, t3;

	cost.setTexture(fishForShowTexture);
	cost.setPosition(sf::Vector2f(window.getView().getCenter().x + 285, 245));

	pic.setPosition(sf::Vector2f(window.getView().getCenter().x - 220, 245));

	t1.setFont(font);
	t1.setFillColor(sf::Color::White);
	t1.setOutlineColor(sf::Color::Black);
	t1.setCharacterSize(100);
	t1.setStyle(sf::Text::Bold);
	t1.setPosition(sf::Vector2f(window.getView().getCenter().x - 400, 200));

	t2.setFont(font);
	t2.setFillColor(sf::Color::White);
	t2.setOutlineColor(sf::Color::Black);
	t2.setCharacterSize(100);
	t2.setStyle(sf::Text::Bold);
	t2.setPosition(sf::Vector2f(window.getView().getCenter().x - 150, 200));

	t3.setFont(font);
	t3.setFillColor(sf::Color::White);
	t3.setOutlineColor(sf::Color::Black);
	t3.setCharacterSize(100);
	t3.setStyle(sf::Text::Bold);
	t3.setPosition(sf::Vector2f(window.getView().getCenter().x + 350, 200));

	t1.setString("Buy ");
	t3.setString("!");
	switch (a)
	{
	case 0:
	{
		price = 30;
		t2.setString("with 30 x");
		pic.setTexture(heartTexture);
		break;
	}
	case 1:
	{
		price = 40;
		t2.setString("with 40 x");
		pic.setTexture(rngboxTexture);
		pic.move(-5, 0);
		break;
	}
	case 2:
	{
		if (attackDamage == 5)
		{
			price = 20;
			t2.setString("with 20 x");
			pic.setTexture(weapon2Texture);
		}
		else if (attackDamage == 10)
		{
			price = 50;
			t2.setString("with 50 x");
			pic.setTexture(weapon3Texture);
		}
		else goto end;
		break;
	}
	case 3:
	{
		price = 5;
		t2.setString("with 05 x");
		pic.setTexture(fishboneForShowTexture);
		pic.move(-10, 0);
		break;
	}
	}
	for (int i = 0; i < 3; i++)
	{
		Exit[i].setFont(font);
		Exit[i].setFillColor(sf::Color::White);
		Exit[i].setOutlineColor(sf::Color::Black);
		Exit[i].setCharacterSize(100);
		Exit[i].setStyle(sf::Text::Bold);
	}

	Exit[1].setString("YES");
	Exit[1].setPosition(sf::Vector2f(window.getView().getCenter().x - 325, 450));

	Exit[2].setString("NO");
	Exit[2].setPosition(sf::Vector2f(window.getView().getCenter().x + 175, 450));
	while (window.isOpen())
	{
		int closeEx = 0;
		sf::Event event;
		if (window.pollEvent(event)) {}
		endt = clock();
		switch (exit)
		{
		case 1:
		{
			Exit[1].setFillColor(sf::Color::Red);
			Exit[2].setFillColor(sf::Color::White);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				if (fish >= price)
				{
					fish -= price;
					buyEF.play();
					switch (a)
					{
					case 0: {HP++; break; }
					case 1:
					{
						int r = (rand() % 2) + 2;
						for (int i = 0; i < it; i++)
						{
							if (ITEM[i].state == 0)
							{
								ITEM[i].set(417, 500, r);
								break;
							}
						}
						break;
					}
					case 2: {attackDamage *= 2; break; }
					case 3: {fishbone++; break; }
					}
					closeEx = 1;
				}
			}
			break;
		}

		case 2:
		{
			Exit[1].setFillColor(sf::Color::White);
			Exit[2].setFillColor(sf::Color::Red);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				closeEx = 1;
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter));
			}
			break;
		}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			closeEx = 1;
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::End) || close == 1)
		{
			close = 1;
			break;
		}
		if ((double)(endt - startEx) / CLOCKS_PER_SEC > 0.2)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				UIEF.play();
				exit--;
				if (exit < 1)exit = 2;
				startEx = clock();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				UIEF.play();
				exit++;
				if (exit > 2)exit = 1;
				startEx = clock();
			}
		}

		window.draw(gameBG);
		for (int i = 0; i < ch; i++)
		{
			if (CHEST[i].state > 0)window.draw(CHEST[i].body);
		}
		if (stage == 2)
		{
			for (i = 0; i < 4; i++)
			{
				window.draw(SHOP[i]);
			}
			if (attackDamage == 5) weaponShop.setTexture(weapon2Texture);
			else if (attackDamage == 10) weaponShop.setTexture(weapon3Texture);
			else weaponShop.setTextureRect(sf::IntRect(0, 0, 0, 0));
			window.draw(heartShop);
			window.draw(rngboxShop);
			window.draw(weaponShop);
			window.draw(fishboneShop);
			window.draw(fishShop1);
			window.draw(fishShop2);
			window.draw(fishShop3);
			window.draw(fishShop4);
		}
		if (state == 0 || state == 2)window.draw(shapeSprite);
		window.draw(inventory1);
		window.draw(inventory2);
		window.draw(textScore);
		window.draw(textFish);
		window.draw(textFishbone);
		window.draw(textHP);
		window.draw(heart);
		window.draw(fishForShow);
		window.draw(fishboneForShow);
		if (cItem == 2) { window.draw(item2); }
		else if (cItem == 3) { window.draw(item3); }
		window.draw(clawForShow);
		for (int i = 0; i < nb; i++)
		{
			if (NBear[i].HP > 0)
			{
				window.draw(NBear[i].body);
			}
		}
		for (int i = 0; i < tb; i++)
		{
			if (TBear[i].HP == -50) {}
			else if (TBear[i].th < 3 && TBear[i].th > 0)
			{
				window.draw(TBear[i].stick);
			}
		}
		for (int i = 0; i < tb; i++)
		{
			if (TBear[i].HP > 0)
			{
				window.draw(TBear[i].body);
			}
		}
		window.draw(Boss1.body);
		window.draw(Boss1.stick);
		if (bullet < 3 && bullet > 0) window.draw(Bullet);
		if (attack < 4 && attack > 0)window.draw(attackSprite);
		for (int i = 0; i < it; i++)
		{
			if (ITEM[i].state > 0)
			{
				window.draw(ITEM[i].body);
			}
		}
		for (int i = 0; i < f; i++)
		{
			if (FISH[i].state == 1)window.draw(FISH[i].body);
		}
		for (int i = 0; i < fb; i++)
		{
			if (FISHBONE[i].state == 1)window.draw(FISHBONE[i].body);
		}
		for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); it++)
		{
			window.draw(it->ground);
			window.draw(it->underGround);
		}
		for (int i = 1; i < 3; i++)
		{
			window.draw(Exit[i]);
		}
		window.draw(t1);
		window.draw(t2);
		window.draw(t3);
		window.draw(cost);
		window.draw(pic);
		window.display();
		window.clear();
		if (closeEx == 1)break;
	}
end: {}
}

void stage2()
{
	startx = 0;
	endx = 5800;
	Speed = 1.5;
	shapeSprite.setPosition(spawn);
	gameBG.setTexture(gameBG2Texture);
	gameBG.setTextureRect(sf::IntRect(0, 0, 6200, 720));
	setGround2();
	setMonster2();
	setFish2();
	setChest2();
	stage2BGM.play();
}

void setGround2()
{
	//  ground.push_back(GROUND(sizex,	sizey,	posx,	posy,	g,	underground)); 
	ground.push_back(GROUND(480.0, 32.0, 0.0, 600.0, 3, 3)); // 0
	ground.push_back(GROUND(320.0, 32.0, 480.0, 536.0, 3, 3)); // 1
	ground.push_back(GROUND(320.0, 32.0, 800.0, 472.0, 3, 3)); // 2
	ground.push_back(GROUND(320.0, 32.0, 1120.0, 408.0, 3, 3)); // 3
	ground.push_back(GROUND(320.0, 32.0, 1440.0, 344.0, 3, 3)); // 4
	ground.push_back(GROUND(320.0, 32.0, 1760.0, 280.0, 3, 3)); // 5
	ground.push_back(GROUND(32.0, 640.0, 2048.0, 280.0, 3, 3)); // 6 I
	ground.push_back(GROUND(240.0, 32.0, 2256.0, 280.0, 3, 0)); // 7
	ground.push_back(GROUND(240.0, 32.0, 2672.0, 280.0, 3, 0)); // 8
	ground.push_back(GROUND(240.0, 32.0, 3088.0, 280.0, 3, 0)); // 9
	ground.push_back(GROUND(240.0, 32.0, 3504.0, 280.0, 3, 0)); // 10
	ground.push_back(GROUND(1760.0, 32.0, 2080.0, 568.0, 3, 3)); // 11
	ground.push_back(GROUND(160.0, 32.0, 3840.0, 536.0, 3, 3)); // 12
	ground.push_back(GROUND(480.0, 32.0, 4000.0, 568.0, 3, 3)); // 13
	ground.push_back(GROUND(1100.0, 32.0, 4480.0, 504.0, 3, 3)); // 14
	ground.push_back(GROUND(360.0, 32.0, 5580.0, 536.0, 3, 3)); // 15
}

void setMonster2()
{
	NBear[0].set(560, 536);  // 1
	NBear[1].set(720, 536);  // 1
	NBear[2].set(870, 472);  // 2
	NBear[3].set(930, 472);  // 2
	NBear[4].set(1050, 472); // 2 
	NBear[5].set(1200, 408); // 3
	NBear[6].set(1360, 408); // 3
	NBear[7].set(1510, 344); // 4
	NBear[8].set(1570, 344); // 4
	NBear[9].set(1690, 344);// 4
	NBear[10].set(2316, 280);// 7
	NBear[11].set(2436, 280);// 7
	NBear[12].set(2732, 280);// 8
	NBear[13].set(2852, 280);// 8
	NBear[14].set(3148, 280);// 9
	NBear[15].set(3268, 280);// 9 
	NBear[16].set(3564, 280);// 10
	NBear[17].set(3684, 280);// 10
	NBear[18].set(2316, 568);// 11
	NBear[19].set(2732, 568);// 11
	NBear[20].set(3148, 568);// 11
	NBear[21].set(3564, 568);// 11
	NBear[22].set(4120, 568);// 13
	NBear[23].set(4360, 568);// 13

	TBear[0].set(625, 536);  // 1
	TBear[1].set(1265, 408); // 3
	TBear[2].set(1905, 280); // 5
	TBear[3].set(4235, 568); // 13

	Boss2.set(5470, 504);
}

void setFish2()
{
	FISH[0].set(560, 380); // 1
	FISH[1].set(620, 330); // 1
	FISH[2].set(680, 380); // 1
	FISH[3].set(880, 316); // 2
	FISH[4].set(940, 256); // 2
	FISH[5].set(1010, 316); // 2
	FISH[6].set(1200, 252); // 3
	FISH[7].set(1260, 192); // 3
	FISH[8].set(1320, 252); // 3
	FISH[9].set(1520, 188); // 4
	FISH[10].set(1580, 128); // 4
	FISH[11].set(1640, 188); // 4
	FISH[12].set(1840, 134); // 5
	FISH[13].set(1900, 74); // 5
	FISH[14].set(1960, 134); // 5
	FISH[15].set(2301, 166); // 7
	FISH[16].set(2401, 166); // 7
	FISH[17].set(2717, 166); // 8
	FISH[18].set(2817, 166); // 8
	FISH[19].set(3133, 166); // 9
	FISH[20].set(3233, 166); // 9
	FISH[21].set(3549, 166); // 10
	FISH[22].set(3649, 166); // 10
	FISH[23].set(2301, 420); // 11
	FISH[24].set(2401, 420); // 11
	FISH[25].set(2717, 420); // 11
	FISH[26].set(2817, 420); // 11
	FISH[27].set(3133, 420); // 11
	FISH[28].set(3233, 420); // 11
	FISH[29].set(3549, 420); // 11
	FISH[30].set(3649, 420); // 11
	FISH[31].set(3895, 388); // 12
	FISH[32].set(4030, 420); // 13
	FISH[33].set(4220, 420); // 13
	FISH[34].set(4410, 420); // 13
}

void setChest2()
{
	CHEST[0].set(360, 600);  // 0
	CHEST[1].set(3675, 280); // 10
}

void stage2boss()
{
	if (view.getCenter().x > 4630 && view.getCenter().x < 5030 && Boss2.HP > 0)
	{
		stage2BGM.stop();
		while (view.getCenter().x > 4630 && view.getCenter().x < 5030 && Boss2.HP > 0)
		{
			view.move(0.5, 0);
			window.setView(view);
			setHead();
			gameDraw();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::End) || close == 1)
			{
				close = 1;
				break;
			}
		}
		for (int i = 0; i < nb; i++) NBear[i].re();
		for (int i = 0; i < fb; i++) FISHBONE[i].re();
		for (int i = 0; i < tb; i++) TBear[i].re();
		startx = 4490;
		endx = 5565;
		moveView = 1;
		Speed = 1.35;
		boss2BGM.play();
		Boss2.skill = clock();
	}
	if (Boss2.HP <= 0 && Boss2.HP > -50)
	{
		bossdamagedEF.stop();
		bossdeadEF.play();
		Boss2.re();
		fish += 40;
		score += 500;
		endx = 5800;
		moveView = 0;
		while ((view.getCenter().x - shapeSprite.getPosition().x >= -16) && view.getCenter().x - 540 > startx)
		{
			view.move(-0.18 * Speed, 0);
		}
		while ((view.getCenter().x - shapeSprite.getPosition().x <= 16) && view.getCenter().x + 540 < endx)
		{
			view.move(.18 * Speed, 0);
		}
	}
}

void stage3()
{
	startx = 0;
	endx = 1810;
	shapeSprite.setPosition(spawn);
	gameBG.setTexture(gameBG3Texture);
	gameBG.setTextureRect(sf::IntRect(0, 0, 2880, 720));
	setGround3();
	setMonster3();
	setChest3();
	stage3BGM.play();
}

void setGround3()
{
	//  ground.push_back(GROUND(sizex,	sizey,	posx,	posy,	g,	underground)); 
	ground.push_back(GROUND(480.0, 32.0, 0.0, 600.0, 4, 4)); // 0
	ground.push_back(GROUND(1090.0, 32.0, 480.0, 568.0, 4, 4)); // 1
	ground.push_back(GROUND(240.0, 32.0, 1570.0, 600.0, 4, 4)); // 2
}

void setMonster3()
{
	Boss3.set(1400, 568);
}

void setChest3()
{
	CHEST[0].set(360, 600);  // 0
}

void stage3boss()
{
	if (view.getCenter().x > 600 && view.getCenter().x < 1030 && Boss3.HP > 0)
	{
		while (view.getCenter().x > 600 && view.getCenter().x < 1030 && Boss3.HP > 0)
		{
			view.move(0.5, 0);
			window.setView(view);
			setHead();
			gameDraw();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::End) || close == 1)
			{
				close = 1;
				break;
			}
		}
		for (int i = 0; i < nb; i++) NBear[i].re();
		for (int i = 0; i < fb; i++) FISHBONE[i].re();
		for (int i = 0; i < tb; i++) TBear[i].re();
		startx = 485;
		endx = 1565;
		moveView = 1;
		Speed = 1.35;
		Boss3.skill = clock();
	}
	if (Boss3.HP <= 0 && Boss3.HP > -50)
	{
		bossdamagedEF.stop();
		bossdeadEF.play();
		Boss3.re();
		score += 1000;
		endx = 1810;
		moveView = 0;
		while ((view.getCenter().x - shapeSprite.getPosition().x >= -16) && view.getCenter().x - 540 > startx)
		{
			view.move(-0.18 * Speed, 0);
		}
		while ((view.getCenter().x - shapeSprite.getPosition().x <= 16) && view.getCenter().x + 540 < endx)
		{
			view.move(.18 * Speed, 0);
		}
	}
}

void saveData()
{
	if (score > data.begin()->first)
	{
		startt = clock();
		startB = clock();
		NAMETEXT.setFont(font);
		NAMETEXT.setFillColor(sf::Color::White);
		NAMETEXT.setOutlineColor(sf::Color::Black);
		NAMETEXT.setCharacterSize(50);
		NAMETEXT.setStyle(sf::Text::Bold);
		NAMETEXT.setPosition(sf::Vector2f(window.getView().getCenter().x - 200, 300));
		NAMETEXT.setString("NAME");

		NAME.setFont(font);
		NAME.setFillColor(sf::Color::White);
		NAME.setOutlineColor(sf::Color::Black);
		NAME.setCharacterSize(50);
		NAME.setStyle(sf::Text::Bold);
		NAME.setPosition(sf::Vector2f(window.getView().getCenter().x - 50, 300));
		while (window.isOpen())
		{
			sf::Event event;
			if (window.pollEvent(event)) {}
			NAME.setString(name);
			endt = clock();
			char ch = ' ';
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && name.length() > 0)
			{
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter));
				break;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) && name.length() > 0 && (endt - startB) / CLOCKS_PER_SEC > 0.2)
			{
				std::string::iterator it = name.begin();
				while (it != name.end())it++;
				it--;
				name.erase(it);
				startB = clock();
			}
			else if ((endt - startt) / CLOCKS_PER_SEC > 0.15)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					ch = 'a';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
				{
					ch = 'b';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
				{
					ch = 'c';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					ch = 'd';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				{
					ch = 'e';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
				{
					ch = 'f';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::End))
				{
					ch = 'g';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
				{
					ch = 'h';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
				{
					ch = 'i';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
				{
					ch = 'j';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
				{
					ch = 'k';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
				{
					ch = 'l';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
				{
					ch = 'm';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
				{
					ch = 'n';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
				{
					ch = 'o';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				{
					ch = 'p';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				{
					ch = 'q';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{
					ch = 'r';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					ch = 's';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
				{
					ch = 't';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
				{
					ch = 'u';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
				{
					ch = 'v';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					ch = 'w';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
				{
					ch = 'x';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
				{
					ch = 'y';
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				{
					ch = 'z';
				}
				if (name.length() < 8 && ch != ' ')
				{
					name.push_back(ch);
					startt = clock();
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::End) || close == 1)
			{
				close = 1;
				break;
			}
			window.draw(gameBG);
			if (stage == 2)
			{
				for (i = 0; i < 4; i++)
				{
					window.draw(SHOP[i]);
				}
				if (attackDamage == 5) weaponShop.setTexture(weapon2Texture);
				else if (attackDamage == 10) weaponShop.setTexture(weapon3Texture);
				else weaponShop.setTextureRect(sf::IntRect(0, 0, 0, 0));
				window.draw(heartShop);
				window.draw(rngboxShop);
				window.draw(weaponShop);
				window.draw(fishboneShop);
				window.draw(fishShop1);
				window.draw(fishShop2);
				window.draw(fishShop3);
				window.draw(fishShop4);
			}
			if (state == 0 || state == 2)window.draw(shapeSprite);
			window.draw(inventory1);
			window.draw(inventory2);
			window.draw(textScore);
			window.draw(textFish);
			window.draw(textFishbone);
			window.draw(textHP);
			window.draw(heart);
			window.draw(fishForShow);
			window.draw(fishboneForShow);
			window.draw(Boss3.stone1);
			window.draw(Boss3.stone2);
			window.draw(Boss3.stone3);
			if (cItem == 2) { window.draw(item2); }
			else if (cItem == 3) { window.draw(item3); }
			window.draw(clawForShow);
			for (int i = 0; i < nb; i++)
			{
				if (NBear[i].HP > 0)
				{
					window.draw(NBear[i].body);
				}
			}
			for (int i = 0; i < tb; i++)
			{
				if (TBear[i].HP == -50) {}
				else if (TBear[i].th < 3 && TBear[i].th > 0)
				{
					window.draw(TBear[i].stick);
				}
			}
			for (int i = 0; i < tb; i++)
			{
				if (TBear[i].HP > 0)
				{
					window.draw(TBear[i].body);
				}
			}
			if (Boss1.HP > 0)
			{
				window.draw(Boss1.body);
				window.draw(Boss1.stick);
			}
			if (Boss2.HP > 0)
			{
				window.draw(Boss2.body);
				window.draw(Boss2.stick);
			}
			if (Boss3.HP > 0)
			{
				window.draw(Boss3.body);
				window.draw(Boss3.stick);
			}
			if (bullet < 3 && bullet > 0) window.draw(Bullet);
			if (attack < 4 && attack > 0)window.draw(attackSprite);
			for (int i = 0; i < it; i++)
			{
				if (ITEM[i].state > 0)
				{
					window.draw(ITEM[i].body);
				}
			}
			for (int i = 0; i < f; i++)
			{
				if (FISH[i].state == 1)window.draw(FISH[i].body);
			}
			for (int i = 0; i < fb; i++)
			{
				if (FISHBONE[i].state == 1)window.draw(FISHBONE[i].body);
			}
			for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); it++)
			{
				window.draw(it->ground);
				window.draw(it->underGround);
			}
			if (HP < 0)window.draw(gameoverBG);
			else window.draw(congratBG);
			for (int i = 0; i < 2; i++)
			{
				window.draw(Exit[i]);
			}
			window.draw(NAME);
			window.draw(NAMETEXT);
			window.display();
			window.clear();
		}
		window.clear();
		window.display();
		if (close != 1)
		{
			data.erase(data.begin());
			data.insert(std::pair<int, std::string>(score, name));
			fp = fopen("highscore/data.txt", "w");
			int i = 0;
			for (std::map<int, std::string>::iterator it = data.begin(); i < 5; it++, i++)
			{
				for (int j = 0; it->second[j] != '\0'; j++)
				{
					fprintf(fp, "%c", it->second[j]);
				}
				fprintf(fp, " %d\n", it->first);
			}
			fclose(fp);
		}
	}
}

void loadSound()
{
	if (!damagedBF.loadFromFile("sounds/effects/damaged.ogg"))
	{
		std::cout << "damage" << std::endl;
	}
	damagedEF.setBuffer(damagedBF);
	damagedEF.setVolume(40);
	if (!throwfishBF.loadFromFile("sounds/effects/throwfish.ogg"))
	{
		std::cout << "throwfish" << std::endl;
	}
	throwfishEF.setBuffer(throwfishBF);
	throwfishEF.setVolume(100);
	if (!buyBF.loadFromFile("sounds/effects/buy.ogg"))
	{
		std::cout << "buy" << std::endl;
	}
	buyEF.setBuffer(buyBF);
	buyEF.setVolume(60);
	if (!gameoverBF.loadFromFile("sounds/effects/gameover.ogg"))
	{
		std::cout << "gameover" << std::endl;
	}
	gameoverEF.setBuffer(gameoverBF);
	gameoverEF.setVolume(25);
	if (!congratBF.loadFromFile("sounds/effects/congrat.ogg"))
	{
		std::cout << "congrat" << std::endl;
	}
	congratEF.setBuffer(congratBF);
	congratEF.setVolume(30);
	if (!TBearthrowBF.loadFromFile("sounds/effects/TBear throw.ogg"))
	{
		std::cout << "TBear throw" << std::endl;
	}
	if (!TBeardamagedBF.loadFromFile("sounds/effects/TBear damaged.ogg"))
	{
		std::cout << "TBear damaged" << std::endl;
	}
	TBeardamagedEF.setBuffer(TBeardamagedBF);
	if (!TBeardeadBF.loadFromFile("sounds/effects/TBear dead.ogg"))
	{
		std::cout << "TBear dead" << std::endl;
	}
	TBeardeadEF.setBuffer(TBeardeadBF);
	if (!NBeardamagedBF.loadFromFile("sounds/effects/NBear damaged.ogg"))
	{
		std::cout << "NBear damaged" << std::endl;
	}
	NBeardamagedEF.setBuffer(NBeardamagedBF);
	NBeardamagedEF.setVolume(40);
	if (!NBeardeadBF.loadFromFile("sounds/effects/NBear dead.ogg"))
	{
		std::cout << "NBear dead" << std::endl;
	}
	NBeardeadEF.setBuffer(NBeardeadBF);
	NBeardeadEF.setVolume(40);
	if (!bossthrowBF.loadFromFile("sounds/effects/boss throw.ogg"))
	{
		std::cout << "boss throw" << std::endl;
	}
	if (!bossroarBF.loadFromFile("sounds/effects/boss roar.ogg"))
	{
		std::cout << "boss roar" << std::endl;
	}
	if (!bossdamagedBF.loadFromFile("sounds/effects/boss damaged.ogg"))
	{
		std::cout << "boss damaged" << std::endl;
	}
	bossdamagedEF.setBuffer(bossdamagedBF);
	bossdamagedEF.setVolume(40);
	if (!bossdeadBF.loadFromFile("sounds/effects/boss dead.ogg"))
	{
		std::cout << "boss dead" << std::endl;
	}
	bossdeadEF.setBuffer(bossdeadBF);
	bossdeadEF.setVolume(50);
	if (!useitemBF.loadFromFile("sounds/effects/use item.ogg"))
	{
		std::cout << "use item" << std::endl;
	}
	useitemEF.setBuffer(useitemBF);
	useitemEF.setVolume(25);
	if (!clawBF.loadFromFile("sounds/effects/claw.ogg"))
	{
		std::cout << "claw" << std::endl;
	}
	clawEF.setBuffer(clawBF);
	clawEF.setVolume(30);
	if (!collectfishBF.loadFromFile("sounds/effects/collect fish.ogg"))
	{
		std::cout << "collect fish" << std::endl;
	}
	collectfishEF.setBuffer(collectfishBF);
	collectfishEF.setVolume(45);
	if (!collectitemBF.loadFromFile("sounds/effects/collect item.ogg"))
	{
		std::cout << "collect item" << std::endl;
	}
	collectitemEF.setBuffer(collectitemBF);
	collectitemEF.setVolume(60);
	if (!pauseinBF.loadFromFile("sounds/effects/pause in.ogg"))
	{
		std::cout << "pause in" << std::endl;
	}
	pauseinEF.setBuffer(pauseinBF);
	pauseinEF.setVolume(30);
	if (!pauseoutBF.loadFromFile("sounds/effects/pause out.ogg"))
	{
		std::cout << "pause out" << std::endl;
	}
	pauseoutEF.setBuffer(pauseoutBF);
	pauseoutEF.setVolume(30);
	if (!UIBF.loadFromFile("sounds/effects/UI.ogg"))
	{
		std::cout << "ui" << std::endl;
	}
	UIEF.setBuffer(UIBF);
	UIEF.setVolume(60);
	if (!jumpBF.loadFromFile("sounds/effects/jump.ogg"))
	{
		std::cout << "jump" << std::endl;
	}
	jumpEF.setBuffer(jumpBF);
	jumpEF.setVolume(30);
	if (!chestBF.loadFromFile("sounds/effects/chest.ogg"))
	{
		std::cout << "chest" << std::endl;
	}
	chestEF.setBuffer(chestBF);
	chestEF.setVolume(100);

	menuBGM.setLoop(1);
	if (!menuBGM.openFromFile("sounds/musics/menu.ogg"))
	{
		std::cout << "menu" << std::endl;
	}
	menuBGM.setVolume(35);
	stage1BGM.setLoop(1);
	if (!stage1BGM.openFromFile("sounds/musics/stage1.ogg"))
	{
		std::cout << "stage1" << std::endl;
	}
	stage1BGM.setVolume(60);
	boss1BGM.setLoop(1);
	if (!boss1BGM.openFromFile("sounds/musics/boss1.ogg"))
	{
		std::cout << "boss1" << std::endl;
	}
	boss1BGM.setVolume(60);
	stage2BGM.setLoop(1);
	if (!stage2BGM.openFromFile("sounds/musics/stage2.ogg"))
	{
		std::cout << "stage2" << std::endl;
	}
	stage2BGM.setVolume(30);
	boss2BGM.setLoop(1);
	if (!boss2BGM.openFromFile("sounds/musics/boss2.ogg"))
	{
		std::cout << "boss2" << std::endl;
	}
	boss2BGM.setVolume(30);
	stage3BGM.setLoop(1);
	if (!stage3BGM.openFromFile("sounds/musics/stage3.ogg"))
	{
		std::cout << "stage3" << std::endl;
	}
	stage3BGM.setVolume(30);
	shopBGM.setLoop(1);
	if (!shopBGM.openFromFile("sounds/musics/shop.ogg"))
	{
		std::cout << "shop" << std::endl;
	}
	shopBGM.setVolume(30);
}