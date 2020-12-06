#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>
#include <map>
#include <math.h>

const int nb = 40, tb = 30; //  number of normal bear , number of throw bear
const int f = 30, fb = 40, it = 10; // number of fish , number of fishbone , number of item
const int ch = 2; // number of chest
double Speed = 1.25;
double startt, endt,startAttack,startB,startM,startEx,dif;
double startP,startF; // start Potion, start fishbonecase
bool potion = 0; // state of potion
bool fishbonecase = 0; // state of fishbonecase
int g = 0; // number of ground
int i,j;
int state = 0; // 1 = after recieve damage
int attack = 0; // 0 = ready to attack, 1 = attack state , 2 = after attack
int cItem = 0; // current item in bags 1.+HP 2.Potion 3.Fishbonecase
int attackDamage = 5;
int animation = 0,Ranimation = 0,Lanimation = 0;
std::string tHP, tScore , tFish , tFishbone; // String of HP , Score , Fish , Fishbone
int HP = 3; // Hit point
int score = 0;
int fish = 0; // Fish
int fishbone = 2; // Ammo
bool gr = 0; // is sprite on the ground?  
int RH = 1,BH,AH; // recent head of main character
int bullet = 0; // bullet status
int bx,endx,startx; // x of bullet,Highest x,Lowest of x 
int close = 0;
int moveView = 0;
sf::Text textHP,textScore,textFish,textFishbone;
sf::Text Exit[3];
sf::Text Menu[3];
sf::Text Leaderboard[7];
sf::Text Score[6];
sf::Font font;
sf::Vector2f spawn = { 30, 450 }; // spawn point
sf::Sprite shapeSprite; // main character
sf::Sprite attackSprite;
sf::Sprite heart;
sf::Sprite test;
sf::Sprite inventory1,inventory2,item2,item3;
sf::Sprite fishForShow,fishboneForShow;
sf::Sprite Bullet;
sf::Sprite menuBG, exitBG,gameBG,leaderBG;
sf::View view,startView;
sf::Texture playerTextureRight, playerTextureLeft, fishboneTexture, attackTexture,stickTexture,fishTexture,chestTexture,item1Texture, item2Texture, item3Texture;
sf::Texture heartTexture,fishForShowTexture, fishboneForShowTexture,normalBearTexture,throwBearTexture,fishboneDropTexture,inventoryTexture;
sf::Texture ground1Texture, underGround1Texture, bigstickTexture, boss1rightTexture, boss1leftTexture;
sf::Texture menuBGTexture, exitBGTexture,gameBG1Texture, leaderBGTexture;
double speed = 0; // use when jumping or falling
bool down = 0, up = 0; // state of jumping
FILE* fp;
std::map<int, std::string> data;

class GROUND
{
public:
	
	sf::Sprite ground;
	sf::Sprite underGround;
	GROUND(float sizex,float sizey,float posx,float posy,int n,int under)
	{
		if (n == 1)
		{
			ground.setTexture(ground1Texture);
		}
		ground.setPosition(posx,posy);
		ground.setTextureRect(sf::IntRect(0, 0, sizex, sizey));
		g++;
		if (under == 1)
		{
			underGround.setTexture(underGround1Texture);
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
		if (state == 0)
		{
			body.setTexture(fishboneDropTexture);
			body.setTextureRect(sf::IntRect(0, 0, width, height));
		}
		this->state = 1;
		body.setPosition(x, y);
	}
};
Fishbone FISHBONE[fb];
class normalBear 
{
public:

	int head = 2;  // 1 = Right , 2 = Left
	int HP= -50;
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
					FISHBONE[i].set(body.getPosition().x+((this->width-FISHBONE[i].width)/2), body.getPosition().y+this->height-FISHBONE[i].height-6);
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
		body.setPosition(x, y - height +0.0001);
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
			for (std::vector<GROUND>::iterator it = ground.begin(); it!=ground.end(); i++,it++)
			{
				if (body.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
				{
					on = i;
					if (body.getPosition().y + 31 > ground[i].ground.getPosition().y)
					{
						body.move(-0.075f*Speed, 0.f);
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
		if (HP == -50) { stick.setTexture(stickTexture);
		body.setTexture(throwBearTexture);
		}
		body.setPosition(x, y - height + 0.0001);
		HP = 20;
	}
	void move() // turn left or right
	{
		animation++;
		if (shapeSprite.getPosition().x > body.getPosition().x)
		{
			head = 1;
			body.setTextureRect(sf::IntRect(216 - 40*((animation/250)%3), 9, width, height));
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
				stick.setPosition(body.getPosition().x+width+3,body.getPosition().y +14);
				sx = stick.getPosition().x;
				th = -1;
				start = clock();
			}
		}
		else if(head == 2 && th == 0)
		{
			if (body.getPosition().x - shapeSprite.getPosition().x < 630)
			{
				animation = 0;
				stick.setTextureRect(sf::IntRect(0, 0, 30, 24));
				stick.setPosition(body.getPosition().x-30-3, body.getPosition().y +14);
				sx = stick.getPosition().x;
				th = -2;
				start = clock();
			}
		}
		if (th == -1)
		{
			dif = (endt - start) / CLOCKS_PER_SEC;
			if (dif <= 0.075) body.setTextureRect(sf::IntRect(95 , 9, width, height));
			else if (dif <= 0.15) body.setTextureRect(sf::IntRect(55, 9, width, height));
			else if (dif <= 0.225) body.setTextureRect(sf::IntRect(15, 9, width+3, height));
			else {
				th = 1;
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
		int a = ((int)(dif / 0.075))%4;
		if (th == 1)
		{
			stickSet(a);
			stick.move(0.25 * Speed, 0);
			if (stick.getPosition().x - sx > 600)reStick();
		}
		else if (th == 2)
		{
			stickSet(3-a);
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

	clock_t start = 0,skill;
	int spw;
	int sx;
	int head; // 1 = Right , 2 = Left
	int HP = -50;
	int th = 0;
	int roar = 0;
	int animation = 0;
	int random = 3;
	float width = 89, height = 89;
	sf::Sprite body;
	sf::Sprite stick;
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
		if (shapeSprite.getPosition().x  > body.getPosition().x)
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
				if(dif <= 2) body.setTextureRect(sf::IntRect(711 - width * ((animation / 250) % 3), 89*3, width, height));
				else if (dif <= 4)
				{
					body.setTextureRect(sf::IntRect(711 - width * 3, 89*3+1, width, height));
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
				if (dif <= 2) body.setTextureRect(sf::IntRect(width * ((animation / 250) % 3), 89*3, width, height));
				else if (dif <= 4)
				{
					body.setTextureRect(sf::IntRect(width * 3 , 89*3 +1, width, height));
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
		body.setTextureRect(sf::IntRect(0,0,0,0));
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
		body.setPosition(x,y);
		this->state = 1;
		this->air = 1;
		this->speed = 0.3;
	}
	void move()
	{
		if (air == 1)
		{
			speed -= 0.0005;
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
			speed += 0.0005;
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

	int state;
	float width = 48, height = 42, difH = 6;
	sf::Sprite body;
	void re()
	{
		body.setPosition(-100,-100);
		this->state = 1;
	}
	void set(float x, float y)
	{
		body.setTexture(chestTexture);
		body.setTextureRect(sf::IntRect(0, 0, width, height));
		this->state = 1;
		body.setPosition(x, y-height);
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
					ITEM[i].set(body.getPosition().x + ((width - ITEM[i].width[a-1]) / 2), body.getPosition().y + 5, a);
					break;
				}
			}
			body.setTextureRect(sf::IntRect(0, height+difH, width, height));
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
void showText();
std::string changeNtoS(int ,int);
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

Fish FISH[f];
chest CHEST[ch];
sf::RenderWindow window(sf::VideoMode(1080, 720), "Test", sf::Style::Default);

int main()
{
	srand(time(NULL));
	startView = window.getView();
	start();
	MENU();
	if (close == 1)return 0;
	stage1();
	/*int mv = 3000;
	view.move(mv, 0);
	shapeSprite.move(mv+500,0);*/
	while (window.isOpen())
	{
		sf::Event event;
		if (window.pollEvent(event)) {}
		/*
			float w = 27, h = 54;
			sf::RectangleShape bg;
			bg.setSize({ w, h });
			bg.setPosition(spawn);
			bg.setFillColor(sf::Color::White);
			window.draw(bg);
			test.setTexture(throwBearTexture); 
			test.setTextureRect(sf::IntRect(95-80, 9, w+3, h));
			test.setPosition(spawn);
			window.draw(test);
		//*/
		gameCal();
		stage1boss();
		if (shapeSprite.getPosition().x > 5000)
		{
			break;
		}
		gameDraw();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			gamePause();
		}
	}
	reset();
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && shapeSprite.getPosition().x > startx&&!sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		RH = 2;
		shapeSprite.move(-0.18f * Speed, 0.f);
		if ((view.getCenter().x - shapeSprite.getPosition().x >= -16) && view.getCenter().x - 540 > startx && moveView == 0)view.move(-0.18* Speed, 0);
		i = 0;
		for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
		{
			if (shapeSprite.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
			{
				if (shapeSprite.getPosition().y + shapeSprite.getTextureRect().height - 2 > ground[i].ground.getPosition().y && shapeSprite.getPosition().x > ground[i].ground.getPosition().x )
				{
					shapeSprite.move(0.18f * Speed, 0.f);
					if ((view.getCenter().x - shapeSprite.getPosition().x >= -16) && view.getCenter().x - 540 > startx && moveView == 0)view.move(0.18 * Speed, 0);
					break;
				}
			}
		}
		shapeSprite.setTextureRect(sf::IntRect(626-39-(280 + 38 * ((Lanimation / (100/ (int)Speed)) % 6)), 22, 39, 54));
		Ranimation = animation = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)&&shapeSprite.getPosition().x+32<endx&& !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		RH = 1;
		shapeSprite.move(.18f * Speed, 0.f);
		if ((view.getCenter().x - shapeSprite.getPosition().x <= 16) && view.getCenter().x + 540 < endx && moveView == 0)view.move(.18 * Speed, 0);
		i = 0;
		for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
		{
			if (shapeSprite.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
			{
				if (shapeSprite.getPosition().y + shapeSprite.getTextureRect().height-2 > ground[i].ground.getPosition().y && shapeSprite.getPosition().x < ground[i].ground.getPosition().x)
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
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::K) && bullet == 0 && fishbone > 0)||(fishbonecase && sf::Keyboard::isKeyPressed(sf::Keyboard::K)&&bullet == 0))
	{
		startB = clock();
		if(!fishbonecase)fishbone--;
		BH = RH;
		bullet = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && attack == 0)
	{
		AH = RH;
		attack = 1;
		startAttack = clock();
	}
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		std::cout << view.getCenter().x << std::endl;
	}*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		bool s = 0;
		while (1)
		{
			for (int i = 0; i < ch; i++)
			{
				if (shapeSprite.getGlobalBounds().intersects(CHEST[i].body.getGlobalBounds()) && CHEST[i].state == 1)
				{
					CHEST[i].open();
					s = 1;
					break;
				}
			}
			if (s == 1)break;
			for (int i = 0; i < it; i++)
			{
				if (shapeSprite.getGlobalBounds().intersects(ITEM[i].body.getGlobalBounds())&&ITEM[i].air != 1)
				{
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
		speed = 0.9*Speed;
		up = 1;
	}
	if (up)
	{
		speed -= 0.0019125*(Speed*Speed);
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
		if(RH == 1)shapeSprite.setTextureRect(sf::IntRect(330, 234, 40, 56));
		else shapeSprite.setTextureRect(sf::IntRect(626-40-330, 234, 40, 56));
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
		speed += 0.0019125 *Speed*Speed;
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
				std::cout << i;
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
			if(dif <= 0.1) shapeSprite.setTextureRect(sf::IntRect(149, 94, 40, 54));
			else if(dif <= 0.2) shapeSprite.setTextureRect(sf::IntRect(185, 94, 40, 54));
			else if(dif <= 0.3) shapeSprite.setTextureRect(sf::IntRect(149, 94, 40, 54));
		}
		else
		{
			if (dif <= 0.1) shapeSprite.setTextureRect(sf::IntRect(626-40-149, 94, 40, 54));
			else if (dif <= 0.2) shapeSprite.setTextureRect(sf::IntRect(626-40-185, 94, 40, 54));
			else if (dif <= 0.3) shapeSprite.setTextureRect(sf::IntRect(626-40-149, 94, 40, 54));
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
					if (NBear[i].HP <= 0) score += 10;
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
						if (TBear[i].HP <= 0) score += 20;
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
					if (NBear[i].HP <= 0) score += 10;
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
						if (TBear[i].HP <= 0) score += 20;
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
	if(score<10000)tScore.insert(6, changeNtoS(score, 4));
	else tScore.insert(6, changeNtoS(score, 5));
	textScore.setString(tScore);
	textScore.setPosition(view.getCenter().x - 510, 0);

	tFish = "X ";
	if(fish<100)tFish.insert(2, changeNtoS(fish, 2));
	else tFish.insert(2, changeNtoS(fish, 3));
	textFish.setString(tFish);
	textFish.setPosition(view.getCenter().x - 110 , 0);

	tFishbone = "X ";
	if(fishbonecase == 0)tFishbone.insert(2, changeNtoS(fishbone, 2));
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
	if(potion == 0)tHP.insert(2, changeNtoS(HP,2));
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
	textHP.setPosition(view.getCenter().x+280,0);
}

std::string changeNtoS(int num,int zero)
{
	char b[10];
	b[zero] = '\0';
	int n = num;
	std::string a = "";
	for (int i = zero; i >= 1; i--)
	{
		b[i - 1] = (n % 10)+'0';
		n /= 10;
	}
	a.insert(0,b);
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
	b[max+1] = '\0';
	while (max>=0)
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
			attackSprite.setPosition(shapeSprite.getPosition().x + 35 , shapeSprite.getPosition().y-12);
		}
		else
		{
			attackSprite.setPosition(shapeSprite.getPosition().x - 38, shapeSprite.getPosition().y-12);
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
				if (NBear[i].HP <= 0) score += 10;
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
					if (TBear[i].HP <= 0) score += 20;
				}
			}
		}
		if (attack == 2)
		{
			if (attackSprite.getGlobalBounds().intersects(Boss1.body.getGlobalBounds()))
			{
				attack = 3;
				Boss1.HP -= attackDamage;
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
	if (!font.loadFromFile("fonts/ARCADECLASSIC.TTF"))//("fonts/#glidepath.ttf"))
	{
		std::cout << "fonts Load failed " << std::endl;
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
	if (!menuBGTexture.loadFromFile("assets/menuBG.png"))
	{
		std::cout << "menuBG Load failed " << std::endl;
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
}

void setSprite()
{
	shapeSprite.setTexture(playerTextureRight);
	shapeSprite.setPosition(spawn);

	Bullet.setTexture(fishboneTexture);
	Bullet.setTextureRect(sf::IntRect(0, 0, 12, 12));

	attackSprite.setTexture(attackTexture);

	heart.setTexture(heartTexture);
	heart.setTextureRect(sf::IntRect(0,0,48,48));

	fishForShow.setTexture(fishForShowTexture);
	fishForShow.setTextureRect(sf::IntRect(0, 0, 48, 51));

	fishboneForShow.setTexture(fishboneForShowTexture);
	fishboneForShow.setTextureRect(sf::IntRect(0,0,56,54));

	Bullet.setTexture(fishboneTexture);
	Bullet.setTextureRect(sf::IntRect(0,0,26,24));

	inventory1.setTexture(inventoryTexture);
	inventory1.setTextureRect(sf::IntRect(0, 0, 56, 53));

	inventory2.setTexture(inventoryTexture);
	inventory2.setTextureRect(sf::IntRect(0, 0, 56, 53));

	item2.setTexture(item2Texture);
	item2.setTextureRect(sf::IntRect(0, 0, 30, 36));

	item3.setTexture(item3Texture);
	item3.setTextureRect(sf::IntRect(0, 0, 36, 36));
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
}

void setGround1()
{// if intersect posx -= 9.5
//  ground.push_back(GROUND(sizex, sizey,	posx, posy,		g,	underground)); 
	ground.push_back(GROUND(1600.0, 32.0,	1210.0, 632.0,	1,	1)); // 0
	ground.push_back(GROUND(1216.0, 32.0,	0.0,	600.0,	1,	1)); // 1
	ground.push_back(GROUND(96.0,	32.0,	0.0,	568.0,	1,	1)); // 2
	ground.push_back(GROUND(288.0,	32.0,	200.0,	400.0,	1,	0)); // 3
	ground.push_back(GROUND(192.0,	32.0,	950.5,	568.0,	1,	1)); // 4
	ground.push_back(GROUND(32.0,	232.0,	2778.0,	433.0,	1,	0)); // 5 I
	ground.push_back(GROUND(1472.0, 32.0,	1306.0, 432.0,	1,	0)); // 6
	ground.push_back(GROUND(3000.0,	32.0,	3088.5, 632.0,	1,	1)); // 7
	ground.push_back(GROUND(32.0,	328.0,	3066.0,	432.0,	1,	0)); // 8 I
	ground.push_back(GROUND(320.0,	32.0,	2780.0, 368.0,	1,	1)); // 9
	ground.push_back(GROUND(1100.0, 32.0,	3748.0,	600.0,	1,	1)); // 10
	ground.push_back(GROUND(150.0,	32.0,	3850.0,	400.0,	1,	0)); // 11
	ground.push_back(GROUND(150.0,	32.0,	4100.0, 400.0,	1,	0)); // 12
	ground.push_back(GROUND(150.0,	32.0,	4350.0, 400.0,	1,	0)); // 13
	ground.push_back(GROUND(150.0,	32.0,	4600.0, 400.0,	1,	0)); // 14
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
	
	TBear[0].set(300, 400); // g1
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
		}
	}
	for (int i = 0; i < fb; i++)
	{
		if (shapeSprite.getGlobalBounds().intersects(FISHBONE[i].body.getGlobalBounds()))
		{
			FISHBONE[i].re();
			fishbone++;
		}
	}
}

void setChest1()
{
	CHEST[0].set(2700, 632);
}

void use(int n)
{
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
	fishboneForShow.setPosition(view.getCenter().x+30, 9);
	inventory1.setPosition(view.getCenter().x + 407, 9);
	inventory2.setPosition(view.getCenter().x + 463, 9);
	item2.setPosition(view.getCenter().x + 477, 16);
	item3.setPosition(view.getCenter().x + 474, 14);
	setText();
}

void stage1()
{

	startx = 0;
	endx = 5000;
	shapeSprite.setPosition(spawn);
	gameBG.setTexture(gameBG1Texture);
	gameBG.setTextureRect(sf::IntRect(0, 0, 5760, 720));
	setGround1();
	setMonster1();
	setFish1();
	setChest1();
}

void start()
{
	reset();
	setSprite();
	firstTextSet();
	loadTexture();
	startdata();
	fish = 0;
	fishbone = 2;
	HP = 3;
	score = 0;
	cItem = 0;
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
	fishbonecase = 0;
	animation = 0, Ranimation = 0, Lanimation = 0;
	RH = 1;
	window.clear();
	view = startView;
	moveView = 0;
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::E));
				window.clear();
				window.display();
				cos = 1;
			}
			break;
		}
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
	int menu = 3;
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::E))
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::E))
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::E))
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
		window.draw(menuBG);
		for (int i = 0; i < 3; i++)
		{
			window.draw(Menu[i]);
		}
		window.display();
		window.clear();
		if (close == 2)break;
	}
}

void exitFromMenu()
{
	while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::E));
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::E))
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				{
					closeEx = 1;
					while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::E));
				}
				break;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			closeEx = 1;
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
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
		else if (Boss1.HP <= 0 && Boss1.HP > -50)
		{
			Boss1.re();
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
	while (1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
			window.close();
			break;
		}
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
		data.insert(std::pair<int, std::string>(5000, "A"));
		data.insert(std::pair<int, std::string>(4000, "B"));
		data.insert(std::pair<int, std::string>(3000, "C"));
		data.insert(std::pair<int, std::string>(2000, "D"));
		data.insert(std::pair<int, std::string>(1000, "E"));
		int i = 0;
		for (std::map<int, std::string>::iterator it = data.begin();i<5; it++,i++)
		{
			for (int j = 0; it->second[j] != '\0'; j++)
			{
				fprintf(fp, "%c", it->second[j]);
			}
			fprintf(fp, " %d\n",it->first);
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

}

void stage1boss()
{
	while (view.getCenter().x > 3900 && view.getCenter().x < 4300)
	{
		startx = 3760;
		endx = 4840;
		moveView = 1;
		view.move(0.5, 0);
		window.setView(view);
		setHead();
		gameDraw();
		Boss1.skill = clock();
		for (int i = 0; i < nb; i++) NBear[i].re();
	}
	if (Boss1.HP <= 0 && Boss1.HP > -50)
	{
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
