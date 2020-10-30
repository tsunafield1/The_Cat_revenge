#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>

const int g = 7, nb = 10, tb = 1; // number of ground , number of normal bear , number of throw bear
const int f = 20, fb = 20; // number of fish , number of fishbone
clock_t startt, endt,startAttack;
int state = 0; // 1 = after recieve damage
int attack = 0; // 0 = ready to attack, 1 = attack state , 2 = after attack
int attackDamage = 5;
std::string tHP, tScore , tFish , tFishbone; // String of HP , Score , Fish , Fishbone
int HP = 3; // Hit point
int score = 0; 
int fish = 0; // Fish
int fishbone = 3; // Ammo
bool gr = 0; // is sprite on the ground?  
int RH = 1,BH,AH; // recent head of main character
int bullet = 0; // bullet status
int bx,endx,startx; // x of bullet,Highest x,Lowest of x 
sf::Text textHP,textScore,textFish,textFishbone;
sf::Font font;
sf::Vector2f spawn = { 30, 450 }; // spawn point
sf::Sprite shapeSprite; // main character
sf::Sprite attackSprite;
sf::RectangleShape ground[g]; // ground
sf::Sprite Bullet;
sf::View view;
sf::Texture playerTexture, fishboneTexture, attackTexture,stickTexture,fishTexture;
float speed = 0; // use when jumping or falling
bool down = 0, up = 0; // state of jumping

class Fish
{
public:

	int state = 0;
	float width = 24, height = 24;
	sf::Sprite body;
	void re()
	{
		this->state = 2;
		body.setTextureRect(sf::IntRect(0, 0, 0, 0));
		body.setPosition(0, 0);
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
	float width = 24, height = 24;
	sf::Sprite body;
	void re()
	{
		this->state = 2;
		body.setTextureRect(sf::IntRect(0, 0, 0, 0));
		body.setPosition(0, 0);
	}
	void set(float x, float y)
	{
		if (state == 0)
		{
			body.setTexture(fishboneTexture);
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
	int HP;
	float width = 32, height = 32;
	int on;  // which ground that body stay
	sf::RectangleShape body;
	void re()
	{
		int rng = rand() % 100;
		if (rng < 20)
		{
			for (int i = 0; i < fb; i++)
			{
				if (FISHBONE[i].state != 1)
				{
					FISHBONE[i].set(body.getPosition().x+((this->width-FISHBONE[i].width)/2), body.getPosition().y+3);
					break;
				}
			}
		}
		body.setSize({ 0,0 });
		body.setPosition(-1, -1);
		this->HP = -50;
	}
	void set(float x, float y)
	{
		body.setSize({ width,height });
		body.setFillColor(sf::Color::Red);
		body.setPosition(x, y+0.0001);
		HP = 10;
	}
	void move() // walk left or right
	{
		if (head == 1)
		{
			body.move(0.075f, .0f);
			for (int i = 0; i < g; i++)
			{
				if (body.getGlobalBounds().intersects(ground[i].getGlobalBounds()))
				{
					on = i;
					if (body.getPosition().y + 31 > ground[i].getPosition().y)
					{
						body.move(-0.075f, 0.f);
						head = 2;
						break;
					}
				}
				if (i == g - 1)
				{
					body.move(width, 0);
					if (!body.getGlobalBounds().intersects(ground[on].getGlobalBounds()))
					{
						body.move(-0.075f, 0.f);
						head = 2;
					}
					body.move(-width, 0.f);
				}
			}
		}
		else if (head == 2)
		{
			body.move(-0.075f, .0f);
			for (int i = 0; i < g; i++)
			{
				if (body.getGlobalBounds().intersects(ground[i].getGlobalBounds()))
				{
					on = i;
					if (body.getPosition().y + 31 > ground[i].getPosition().y)
					{
						body.move(0.075f, 0.f);
						head = 1;
						break;
					}
				}
				if (i == g - 1)
				{
					body.move(-width, 0.f);
					if (!body.getGlobalBounds().intersects(ground[on].getGlobalBounds()))
					{
						body.move(0.075f, 0.f);
						head = 1;
					}
					body.move(width, 0.f);
				}
			}
		}
	}
};
class throwBear
{
public:

	clock_t start = 0;
	int sx;
	int head; // 1 = Right , 2 = Left
	int HP = 0;
	int th = 0;
	float width = 32, height = 32;
	sf::RectangleShape body;
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
					FISHBONE[i].set(body.getPosition().x + ((this->width - FISHBONE[i].width) / 2), body.getPosition().y+3);
					break;
				}
			}
		}
		body.setSize({ 0,0 });
		body.setPosition(-1, -1);
		stick.setPosition(-1, -1);
		stick.setTextureRect({ 0,0,0,0 });
		HP = -50;
	}
	void set(float x, float y)
	{
		if (HP == 0) { stick.setTexture(stickTexture); }
		body.setSize({ width,height });
		body.setFillColor(sf::Color::Yellow);
		body.setPosition(x, y + 0.0001);
		HP = 20;
	}
	void move() // turn left or right
	{
		if (shapeSprite.getPosition().x > body.getPosition().x)
		{
			head = 1;
			// turn left
		}
		else
		{
			head = 2;
			// turn right
		}
		if (head == 1 && th == 0)
		{
			if (body.getPosition().x - shapeSprite.getPosition().x < 1000)
			{
				stick.setTextureRect({ 0,0,16,16 });
				stick.setPosition(body.getPosition().x+width+3,body.getPosition().y+(height/2) - 10);
				sx = stick.getPosition().x;
				th = 1;
				start = clock();
			}
		}
		else if(head == 2 && th == 0)
		{
			if (body.getPosition().x - shapeSprite.getPosition().x > -1000)
			{
				stick.setTextureRect({ 0,0,16,16 });
				stick.setPosition(body.getPosition().x-stick.getScale().x+3, body.getPosition().y + (height / 2) - 10);
				sx = stick.getPosition().x;
				th = 2;
				start = clock();
			}
		}
	}
	void shot()
	{
		double dif = (double)(endt - start) / CLOCKS_PER_SEC;
		if (th == 1)
		{
			stick.move(0.25, 0);
			if (stick.getPosition().x - sx > 600)reStick();
		}
		else if (th == 2)
		{
			stick.move(-0.25, 0);
			if (stick.getPosition().x - sx < -600)reStick();
		}
		for (int i = 0; i < g; i++)
		{
			if (stick.getGlobalBounds().intersects(ground[i].getGlobalBounds()))
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

normalBear NBear[nb];
throwBear TBear[tb];
Fish FISH[f];

int main()
{
	startx = 0;
	endx = 5000;
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Test", sf::Style::Default);
	view = window.getView();

	shapeSprite.setPosition(spawn);
	setGround1();
	loadTexture();
	setSprite();
	firstTextSet();
	setMonster1();
	setFish1();

	while (window.isOpen())
	{
		setText();
		window.setView(view);
		if(state == 0||state == 2)window.draw(shapeSprite);
		window.draw(textScore);
		window.draw(textFish);
		window.draw(textFishbone);
		window.draw(textHP);
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
		for (int i = 0; i < f; i++)
		{
			if(FISH[i].state == 1)window.draw(FISH[i].body);
		}
		for (int i = 0; i < fb; i++)
		{
			if (FISHBONE[i].state == 1)window.draw(FISHBONE[i].body);
		}
		for (int i = 0; i < g; i++)
		{
			window.draw(ground[i]);
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
	gr = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && shapeSprite.getPosition().x > startx)
	{
		RH = 2;
		shapeSprite.move(-0.18f, 0.f);
		if ((view.getCenter().x - shapeSprite.getPosition().x >= -16) && view.getCenter().x - 540 > startx)view.move(-0.18, 0);
		for (int i = 0; i < g; i++)
		{
			if (shapeSprite.getGlobalBounds().intersects(ground[i].getGlobalBounds()))
			{
				if (shapeSprite.getPosition().y + 31 > ground[i].getPosition().y)
				{
					shapeSprite.move(0.18f, 0.f);
					if ((view.getCenter().x - shapeSprite.getPosition().x >= -16) && view.getCenter().x - 540 > startx)view.move(0.18, 0);
					break;
				}
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)&&shapeSprite.getPosition().x+32<endx)
	{
		RH = 1;
		shapeSprite.move(.18f, 0.f);
		if ((view.getCenter().x - shapeSprite.getPosition().x <= 16) && view.getCenter().x + 540 < endx)view.move(.18, 0);
		for (int i = 0; i < g; i++)
		{
			if (shapeSprite.getGlobalBounds().intersects(ground[i].getGlobalBounds()))
			{
				if (shapeSprite.getPosition().y + 31 > ground[i].getPosition().y)
				{
					shapeSprite.move(-0.18f, 0.f);
					if ((view.getCenter().x - shapeSprite.getPosition().x <= 16) && view.getCenter().x + 540 < endx)view.move(-18, 0);
					break;
				}
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && bullet == 0 && fishbone > 0)
	{
		fishbone--;
		BH = RH;
		bullet = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && attack == 0)
	{
		AH = RH;
		attack = 1;
		startAttack = clock();
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
		for (int i = 0; i < g; i++)
		{
			if (shapeSprite.getGlobalBounds().intersects(ground[i].getGlobalBounds()))
			{
				if (shapeSprite.getPosition().y > ground[i].getPosition().y)
				{
					shapeSprite.move(.0f, speed);
				}
			}
		}
		if (speed <= 0)up = 0;
	}
	for (int i = 0; i < g; i++)
	{
		if (shapeSprite.getGlobalBounds().intersects(ground[i].getGlobalBounds()) && !up && !down && !gr)
		{
			gr = 1;
		}
	}
	for (int i = 0; i < g; i++)
	{
		if (!shapeSprite.getGlobalBounds().intersects(ground[i].getGlobalBounds()) && !up && !down && !gr)
		{
			down = 1;
			speed = 0;
		}
	}
	if (down)
	{
		speed += 0.00085;
		shapeSprite.move(0.f, speed);
		for (int i = 0; i < g; i++)
		{
			if (shapeSprite.getGlobalBounds().intersects(ground[i].getGlobalBounds()))
			{
				if (shapeSprite.getPosition().y > ground[i].getPosition().y)
				{
					shapeSprite.move(0.f, -(shapeSprite.getPosition().y - ground[i].getPosition().y));
				}
				down = 0;
			}
		}
	}
}

void damageCal()
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
		double dif = double(endt - startt) / CLOCKS_PER_SEC;
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

void shoot()
{
	if (bullet == 1)
	{
		bullet = 2;
		if (BH == 1)
		{
			Bullet.setPosition(shapeSprite.getPosition().x+35, shapeSprite.getPosition().y+10);
			bx = shapeSprite.getPosition().x + 35;
		}
		else
		{
			Bullet.setPosition(shapeSprite.getPosition().x - 15, shapeSprite.getPosition().y + 10);
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
				NBear[i].HP-=10;
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
			for (int i = 0; i < g; i++)
			{
				if (Bullet.getGlobalBounds().intersects(ground[i].getGlobalBounds()))
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

void setText()
{
	tScore = "SCORE ";
	tScore.insert(6, changeNtoS(score, 4));
	textScore.setString(tScore);
	textScore.setPosition(view.getCenter().x - 510, 5);

	tFish = "X ";
	tFish.insert(2, changeNtoS(fish, 2));
	textFish.setString(tFish);
	textFish.setPosition(view.getCenter().x - 90 , 5);

	tFishbone = "X ";
	tFishbone.insert(2, changeNtoS(fishbone, 2));
	textFishbone.setString(tFishbone);
	textFishbone.setPosition(view.getCenter().x + 100, 5);

	tHP = "X ";
	tHP.insert(2, changeNtoS(HP,2));
	textHP.setString(tHP);
	textHP.setPosition(view.getCenter().x+290,5);
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
	double dif = double(endt - startAttack) / CLOCKS_PER_SEC;
	if (attack == 1)
	{
		attack = 2;
		if (AH == 1)
		{
			attackSprite.setPosition(shapeSprite.getPosition().x + 35 , shapeSprite.getPosition().y-24);
		}
		else
		{
			attackSprite.setPosition(shapeSprite.getPosition().x - 51, shapeSprite.getPosition().y-24);
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
					for (int j = 0; j < g; j++)
					{
						if (NBear[i].body.getGlobalBounds().intersects(ground[j].getGlobalBounds()))
						{
							onG = j;
							break;
						}
					}
					NBear[i].body.move(5, 0);
					for (int j = 0; j < g; j++)
					{
						if (NBear[i].body.getGlobalBounds().intersects(ground[j].getGlobalBounds()))
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
					for (int j = 0; j < g; j++)
					{
						if (NBear[i].body.getGlobalBounds().intersects(ground[j].getGlobalBounds()))
						{
							onG = j;
							break;
						}
					}
					NBear[i].body.move(-5, 0);
					for (int j = 0; j < g; j++)
					{
						if (NBear[i].body.getGlobalBounds().intersects(ground[j].getGlobalBounds()))
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
	if (!playerTexture.loadFromFile("sprites/spritesheet.png"))
	{
		std::cout << "spritesheet Load failed " << std::endl;
	}
	if (!fishTexture.loadFromFile("sprites/fish.png"))
	{
		std::cout << "fish Load failed " << std::endl;
	}
	if (!fishboneTexture.loadFromFile("sprites/fishbone.png"))
	{
		std::cout << "fishbone Load failed " << std::endl;
	}
	if (!attackTexture.loadFromFile("sprites/claw.png"))
	{
		std::cout << "claw Load failed " << std::endl;
	}
	if (!font.loadFromFile("fonts/#glidepath.ttf"))
	{
		std::cout << "fonts Load failed " << std::endl;
	}
	if (!stickTexture.loadFromFile("sprites/stick.png"))
	{
		std::cout << "stick Load failed " << std::endl;
	}
}

void setSprite()
{
	shapeSprite.setTexture(playerTexture);
	shapeSprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
	shapeSprite.setPosition(spawn);

	Bullet.setTexture(fishboneTexture);
	Bullet.setTextureRect(sf::IntRect(0, 0, 12, 12));

	attackSprite.setTexture(attackTexture);
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
	ground[0].setSize({ 1200.f,32.f });
	ground[0].setPosition(0.f, 600.f);
	ground[0].setFillColor(sf::Color::Green);

	ground[1].setSize({ 200.f,32.f });
	ground[1].setPosition(200.f, 400.f);
	ground[1].setFillColor(sf::Color::Green);

	ground[2].setSize({ 200,32 });
	ground[2].setPosition(900, 568);
	ground[2].setFillColor(sf::Color::Green);

	ground[3].setSize({ 1600,32 });
	ground[3].setPosition(1200, 632);
	ground[3].setFillColor(sf::Color::Green);

	ground[4].setSize({ 32,232 });
	ground[4].setPosition(2800, 432);
	ground[4].setFillColor(sf::Color::Green);

	ground[5].setSize({ 2000,32 });
	ground[5].setPosition(1500, 432);
	ground[5].setFillColor(sf::Color::Green);

	ground[6].setSize({ 100,32 });
	ground[6].setPosition(0, 568);
	ground[6].setFillColor(sf::Color::Green);
}

void setMonster1()
{
	NBear[0].set(300, 368); // g1
	NBear[1].set(200, 568); // g0
	NBear[2].set(1000, 536); // g2
	NBear[3].set(1400, 600); // g3
	NBear[4].set(2500, 600); // g3
	NBear[5].set(2000, 600); // g3
	NBear[6].set(2250, 600); // g3
	NBear[7].set(1750, 400); // g5
	NBear[8].set(2000, 400); // g5
	NBear[9].set(2500, 400); // g5
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
