#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>

const int nb = 10, tb = 1; //  number of normal bear , number of throw bear
const int f = 20, fb = 20, it = 10; // number of fish , number of fishbone , number of item
const int ch = 2; // number of chest
double startt, endt,startAttack,startB,dif;
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
sf::Text textHP,textScore,textFish,textFishbone;
sf::Font font;
sf::Vector2f spawn = { 30, 450 }; // spawn point
sf::Sprite shapeSprite; // main character
sf::Sprite attackSprite;
sf::Sprite heart;
sf::Sprite test;
sf::Sprite inventory1,inventory2,item2,item3;
sf::Sprite fishForShow,fishboneForShow;
sf::Sprite Bullet;
sf::View view;
sf::Texture playerTextureRight, playerTextureLeft, fishboneTexture, attackTexture,stickTexture,fishTexture,chestTexture,item1Texture, item2Texture, item3Texture, ground1Texture;
sf::Texture heartTexture,fishForShowTexture, fishboneForShowTexture,normalBearTexture,throwBearTexture,fishboneDropTexture,inventoryTexture;
double speed = 0; // use when jumping or falling
bool down = 0, up = 0; // state of jumping

class GROUND
{
public:
	
	sf::Sprite ground;
	GROUND(float sizex,float sizey,float posx,float posy,int n)
	{
		if (n == 1)
		{
			ground.setTexture(ground1Texture);
		}
		ground.setPosition(posx,posy);
		ground.setTextureRect(sf::IntRect(0, 0, sizex, sizey));
		g++;
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
		this->state = 2;
		body.setTextureRect(sf::IntRect(0, 0, 0, 0));
		body.setPosition(-100, -100);
	}
	void set(float x, float y)
	{
		if (state == 0)
		{
			body.setTexture(fishTexture);
			body.setTextureRect(sf::IntRect(0, 0, width, height));
		}
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
			body.move(0.075f, .0f);
			i = 0;
			for (std::vector<GROUND>::iterator it = ground.begin(); it!=ground.end(); i++,it++)
			{
				if (body.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
				{
					on = i;
					if (body.getPosition().y + 31 > ground[i].ground.getPosition().y)
					{
						body.move(-0.075f, 0.f);
						head = 2;
						break;
					}
				}
				if (i == g - 1)
				{
					body.move(width, 0);
					if (!body.getGlobalBounds().intersects(ground[on].ground.getGlobalBounds()))
					{
						body.move(-0.075f, 0.f);
						head = 2;
					}
					body.move(-width, 0.f);
				}
			}
			body.setTextureRect(sf::IntRect(16 + (61 * ((animation / 100) % 6)), 62, width, height));
		}
		else if (head == 2)
		{
			body.move(-0.075f, .0f);
			i = 0;
			for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
			{
				if (body.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
				{
					on = i;
					if (body.getPosition().y + 31 > ground[i].ground.getPosition().y)
					{
						body.move(0.075f, 0.f);
						head = 1;
						break;
					}
				}
				if (i == g - 1)
				{
					body.move(-width, 0.f);
					if (!body.getGlobalBounds().intersects(ground[on].ground.getGlobalBounds()))
					{
						body.move(0.075f, 0.f);
						head = 1;
					}
					body.move(width, 0.f);
				}
			}
			body.setTextureRect(sf::IntRect(15 + (61 * ((animation / 100) % 6)), 141, width, height));
		}
	}
};
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
			// turn left
		}
		else
		{
			head = 2;
			body.setTextureRect(sf::IntRect(15 + 40 * ((animation / 250) % 3), 73, width, height));
			// turn right
		}
		if (head == 1 && th == 0)
		{
			if (body.getPosition().x - shapeSprite.getPosition().x < 1000)
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
			if (body.getPosition().x - shapeSprite.getPosition().x > -1000)
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
			stick.move(0.25, 0);
			if (stick.getPosition().x - sx > 600)reStick();
		}
		else if (th == 2)
		{
			stickSet(3-a);
			stick.move(-0.25, 0);
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
			std:: cout << a;
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

normalBear NBear[nb];
throwBear TBear[tb];
Fish FISH[f];
chest CHEST[ch];

int main()
{
	srand(time(NULL));
	startx = 0;
	endx = 5000;
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Test", sf::Style::Default);
	view = window.getView();

	shapeSprite.setPosition(spawn);
	loadTexture();
	setGround1();
	setSprite();
	firstTextSet();
	setMonster1();
	setFish1();
	setChest1();
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
		setHead();
		window.setView(view);
		for (int i = 0; i < ch; i++)
		{
			if (CHEST[i].state > 0)window.draw(CHEST[i].body);
		}
		if(state == 0||state == 2)window.draw(shapeSprite);
		window.draw(inventory1);
		window.draw(inventory2);
		window.draw(textScore);
		window.draw(textFish);
		window.draw(textFishbone);
		window.draw(textHP);
		window.draw(heart);
		window.draw(fishForShow);
		window.draw(fishboneForShow);
		if(cItem == 2){ window.draw(item2); }
		else if(cItem == 3){ window.draw(item3); }
		endt = clock();
		mainCharacter();
		for (int i = 0; i < nb; i++)
		{
			if (NBear[i].HP > 0)
			{
				window.draw(NBear[i].body);
				NBear[i].move();
			}
			else if (NBear[i].HP == -50){}
			else
			{
				NBear[i].re();
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
				TBear[i].move();
				TBear[i].shot();
			}
			else if (TBear[i].HP == -50) {}
			else if (TBear[i].HP <=0)
			{
				TBear[i].re();
			}
		}
		if (bullet > 0)
		{
			shoot();
			if (bullet < 3) window.draw(Bullet);
		}
		if (attack > 0)
		{
			scratch();
			if (attack < 4)window.draw(attackSprite);
		}
		for (int i = 0; i < it; i++)
		{
			if (ITEM[i].state > 0)
			{
				window.draw(ITEM[i].body);
				ITEM[i].move();
			}
		}
		for (int i = 0; i < f; i++)
		{
			if(FISH[i].state == 1)window.draw(FISH[i].body);
		}
		for (int i = 0; i < fb; i++)
		{
			if (FISHBONE[i].state == 1)window.draw(FISHBONE[i].body);
		}
		for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); it++)
		{
			window.draw(it->ground);
		}
		damageCal();
		collectFish();
		window.display();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
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
		window.clear();
	}
	return 0;
}

void mainCharacter()
{
	if (RH == 1) 
	{
		shapeSprite.setTexture(playerTextureRight);
		shapeSprite.setTextureRect(sf::IntRect(36 + 39 * ((animation / 150) % 6), 22, 40, 54));
	}
	else
	{
		shapeSprite.setTexture(playerTextureLeft);
		shapeSprite.setTextureRect(sf::IntRect(626 - 40 - (36 + 39 * ((animation / 150) % 6)), 22, 40, 54));
	}
	gr = 0;
	animation++;
	Ranimation++;
	Lanimation++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && shapeSprite.getPosition().x > startx&&!sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		RH = 2;
		shapeSprite.move(-0.18f, 0.f);
		if ((view.getCenter().x - shapeSprite.getPosition().x >= -16) && view.getCenter().x - 540 > startx)view.move(-0.18, 0);
		i = 0;
		for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
		{
			if (shapeSprite.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
			{
				if (shapeSprite.getPosition().y + shapeSprite.getTextureRect().height - 1 > ground[i].ground.getPosition().y)
				{
					shapeSprite.move(0.18f, 0.f);
					if ((view.getCenter().x - shapeSprite.getPosition().x >= -16) && view.getCenter().x - 540 > startx)view.move(0.18, 0);
					break;
				}
			}
		}
		shapeSprite.setTextureRect(sf::IntRect(626-39-(280 + 38 * ((Lanimation / 100) % 6)), 22, 39, 54));
		Ranimation = animation = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)&&shapeSprite.getPosition().x+32<endx&& !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		RH = 1;
		shapeSprite.move(.18f, 0.f);
		if ((view.getCenter().x - shapeSprite.getPosition().x <= 16) && view.getCenter().x + 540 < endx)view.move(.18, 0);
		i = 0;
		for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
		{
			if (shapeSprite.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
			{
				if (shapeSprite.getPosition().y + shapeSprite.getTextureRect().height-1 > ground[i].ground.getPosition().y)
				{
					shapeSprite.move(-0.18f, 0.f);
					if ((view.getCenter().x - shapeSprite.getPosition().x <= 16) && view.getCenter().x + 540 < endx)view.move(-18, 0);
					break;
				}
			}
		}
		shapeSprite.setTextureRect(sf::IntRect(280 + 38 * ((Ranimation / 100) % 6), 22, 39, 54));
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
		speed = 0.6;
		up = 1;
	}
	if (up)
	{
		speed -= 0.00085;
		shapeSprite.move(.0f, -speed);
		i = 0;
		for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
		{
			if (shapeSprite.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
			{
				if (shapeSprite.getPosition().y > ground[i].ground.getPosition().y)
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
		speed += 0.00085;
		shapeSprite.move(0.f, speed);
		i = 0;
		for (std::vector<GROUND>::iterator it = ground.begin(); it != ground.end(); i++, it++)
		{
			if (shapeSprite.getGlobalBounds().intersects(ground[i].ground.getGlobalBounds()))
			{
				if (shapeSprite.getPosition().y > ground[i].ground.getPosition().y)
				{
					shapeSprite.move(0.f, -(shapeSprite.getPosition().y - ground[i].ground.getPosition().y));
				}
				down = 0;
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
	tScore.insert(6, changeNtoS(score, 4));
	textScore.setString(tScore);
	textScore.setPosition(view.getCenter().x - 510, 5);

	tFish = "X ";
	tFish.insert(2, changeNtoS(fish, 2));
	textFish.setString(tFish);
	textFish.setPosition(view.getCenter().x - 110 , 5);

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
	textFishbone.setPosition(view.getCenter().x + 90, 5);

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
	textHP.setPosition(view.getCenter().x+280,5);
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
	if (!font.loadFromFile("fonts/#glidepath.ttf"))
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
	if (!ground1Texture.loadFromFile("a.png"))
	{
		std::cout << "ground1 Load failed " << std::endl;
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
	textScore.setCharacterSize(40);
	textScore.setStyle(sf::Text::Bold);

	textFish.setFont(font);
	textFish.setFillColor(sf::Color::White);
	textFish.setOutlineColor(sf::Color::Black);
	textFish.setCharacterSize(40);
	textFish.setStyle(sf::Text::Bold);

	textFishbone.setFont(font);
	textFishbone.setFillColor(sf::Color::White);
	textFishbone.setOutlineColor(sf::Color::Black);
	textFishbone.setCharacterSize(40);
	textFishbone.setStyle(sf::Text::Bold);

	textHP.setFont(font);
	textHP.setFillColor(sf::Color::White);
	textHP.setOutlineColor(sf::Color::Black);
	textHP.setCharacterSize(40);
	textHP.setStyle(sf::Text::Bold);
}

void setGround1()
{
	ground.push_back(GROUND(1200.0, 32.0, 0.0, 600.0,1)); // 0
	ground.push_back(GROUND(300.0, 32.0, 200.0, 400.0, 1)); // 1
	ground.push_back(GROUND(200.0, 32.0, 900.0, 568.0, 1)); // 2
	ground.push_back(GROUND(1600.0, 32.0, 1200.0, 632.0, 1)); // 3
	ground.push_back(GROUND(32.0, 232.0, 2800.0, 432.0, 1)); // 4
	ground.push_back(GROUND(2000.0, 32.0, 1500.0, 432.0, 1)); // 5
	ground.push_back(GROUND(100.0, 32.0, 0.0, 568.0, 1)); // 6
}

void setMonster1()
{
	NBear[0].set(300, 400); // g1
	NBear[1].set(200, 600); // g0
	NBear[2].set(1000, 568); // g2
	NBear[3].set(1400, 632); // g3
	NBear[4].set(2500, 632); // g3
	NBear[5].set(2000, 632); // g3
	NBear[6].set(2250, 632); // g3
	NBear[7].set(1750, 432); // g5
	NBear[8].set(2000, 432); // g5
	NBear[9].set(2500, 432); // g5
	
	TBear[0].set(300, 400); // g1
}

void setFish1()
{
	FISH[0].set(75, 400);
	FISH[1].set(250, 250);
	FISH[2].set(350, 250);
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
