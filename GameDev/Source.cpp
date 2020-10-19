#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

clock_t startt, endt;
int state = 0; // 1 = after recieve damage
std::string tHP, tScore , tFish , tFishbone; // String of HP , Score , Fish , Fishbone
const int g = 3, nb = 2; // number of ground , number of normal bear
int HP = 3; // Hit point
int score = 0; 
int fish = 0; // Fish
int fishbone = 3; // Ammo
bool gr = 0; // is sprite on the ground?  
int RH = 1,H; // recent head of main character
int bullet = 0; // bullet status
int bx,endx,startx;
sf::Text textHP,textScore,textFish,textFishbone;
sf::Font font;
sf::Vector2f spawn = { 20, 300 }; // spawn point
sf::Sprite shapeSprite; // main character
sf::RectangleShape ground[g]; // ground
sf::Sprite Bullet;
sf::View view;
float speed = 0; // use when jumping or falling
bool down = 0, up = 0; // state of jumping

class normalBear 
{
public:

	int head = 2;  // 1 = Right , 2 = Left
	int HP = 20;
	float width = 32, height = 32;
	int on;  // which ground that body stay

	sf::RectangleShape body;
	void set(float x, float y)
	{
		body.setSize({ width,height });
		body.setFillColor(sf::Color::Red);
		body.setPosition(x, y+0.0001);
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

void mainCharacter();
void damageCal();
void shoot();
void setText();
void showText();
std::string changeNtoS(int ,int);

normalBear NBear[nb];

int main()
{
	startx = 0;
	endx = 5000;
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Test");
	view = window.getView();
	///// Monster /////
	NBear[0].set(300, 368);
	NBear[1].set(200, 568);
	///// Monster /////

	///// Ground /////
	ground[0].setSize({ 1200.f,32.f });
	ground[0].setPosition(0.f, 600.f);
	ground[0].setFillColor(sf::Color::Green);

	ground[1].setSize({ 200.f,32.f });
	ground[1].setPosition(200.f, 400.f);
	ground[1].setFillColor(sf::Color::Green);

	ground[2].setSize({ 200,32 });
	ground[2].setPosition(900, 568);
	ground[2].setFillColor(sf::Color::Green);
	///// Ground /////

	////// Texture /////
	sf::Texture playerTexture,fishbone;
	if (!playerTexture.loadFromFile("spritesheet.png"))
	{
		std::cout << "spritesheet Load failed " << std::endl;
	}
	if (!fishbone.loadFromFile("fishbone.png"))
	{
		std::cout << "fishbone Load failed " << std::endl;
	}
	if (!font.loadFromFile("fonts/#glidepath.ttf"))
	{
		std::cout << "fonts Load failed " << std::endl;
	}
	////// Texture /////

	////// Sprite /////
	shapeSprite.setTexture(playerTexture);
	shapeSprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
	shapeSprite.setPosition(spawn);

	Bullet.setTexture(fishbone);
	Bullet.setTextureRect(sf::IntRect(0, 0, 12, 12));
	////// Sprite /////

	////// Text /////
	textScore.setFont(font);
	textScore.setFillColor(sf::Color::White);
	textScore.setOutlineColor(sf::Color::Black);
	textScore.setCharacterSize(45);
	textScore.setStyle(sf::Text::Bold);

	textFish.setFont(font);
	textFish.setFillColor(sf::Color::White);
	textFish.setOutlineColor(sf::Color::Black);
	textFish.setCharacterSize(45);
	textFish.setStyle(sf::Text::Bold);

	textFishbone.setFont(font);
	textFishbone.setFillColor(sf::Color::White);
	textFishbone.setOutlineColor(sf::Color::Black);
	textFishbone.setCharacterSize(45);
	textFishbone.setStyle(sf::Text::Bold);

	textHP.setFont(font);
	textHP.setFillColor(sf::Color::White);
	textHP.setOutlineColor(sf::Color::Black);
	textHP.setCharacterSize(45);
	textHP.setStyle(sf::Text::Bold);
	////// Text /////

	while (window.isOpen())
	{
		setText();
		window.setView(view);
		if(state == 0||state == 2)window.draw(shapeSprite);
		window.draw(textHP);
		window.draw(textScore);
		for (int i = 0; i < g; i++)
		{
			window.draw(ground[i]);
		}
		mainCharacter();
		if (bullet > 0)
		{
			shoot();
			if(bullet < 3) window.draw(Bullet);
		}
		for (int i = 0; i < nb; i++)
		{
			if (NBear[i].HP > 0)
			{
				window.draw(NBear[i].body);
				NBear[i].move();
			}
			else
			{
				NBear[i].set(-1, -1);
			}
		}
		damageCal();
		window.display();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && bullet == 0)
	{
		H = RH;
		bullet = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
	{

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
	}
	else
	{
		endt = clock();
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
		if (H == 1)
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
	if (H == 1)
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

	/*tFish = "X ";
	tFish.insert(2, changeNtoS(fish, 2));
	textFish.setString(tFish);
	textFish.setPosition(view.getCenter().x + 280, 5);

	tFishbone = "X ";
	tFishbone.insert(2, changeNtoS(fishbone, 2));
	textFishbone.setString(tFishbone);
	textFishbone.setPosition(view.getCenter().x + 280, 5);*/

	tHP = "X ";
	tHP.insert(2, changeNtoS(HP,2));
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
