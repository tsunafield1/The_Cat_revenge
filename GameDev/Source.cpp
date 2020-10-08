#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>

bool gr = 0; // is sprite on the ground?  
int RH = 1,H; // recent head of main character
int bullet = 0; // bullet status
sf::Vector2f spawn = { 20, 300 }; // spawn point
const int g = 3, nb = 1; // number of ground , number of normal bear
sf::Sprite shapeSprite; // main character
sf::RectangleShape ground[g]; // ground
sf::Sprite Bullet;
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
			body.move(0.065f, .0f);
			for (int i = 0; i < g; i++)
			{
				if (body.getGlobalBounds().intersects(ground[i].getGlobalBounds()))
				{
					on = i;
					if (body.getPosition().y + 31 > ground[i].getPosition().y)
					{
						body.move(-0.065f, 0.f);
						head = 2;
						break;
					}
				}
				if (i == g - 1)
				{
					body.move(width, 0);
					if (!body.getGlobalBounds().intersects(ground[on].getGlobalBounds()))
					{
						body.move(-0.065f, 0.f);
						head = 2;
					}
					body.move(-width, 0.f);
				}
			}
		}
		else if (head == 2)
		{
			body.move(-0.065f, .0f);
			for (int i = 0; i < g; i++)
			{
				if (body.getGlobalBounds().intersects(ground[i].getGlobalBounds()))
				{
					on = i;
					if (body.getPosition().y + 31 > ground[i].getPosition().y)
					{
						body.move(0.065f, 0.f);
						head = 1;
						break;
					}
				}
				if (i == g - 1)
				{
					body.move(-width, 0.f);
					if (!body.getGlobalBounds().intersects(ground[on].getGlobalBounds()))
					{
						body.move(0.065f, 0.f);
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

normalBear NBear[nb];
int main()
{
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Test");
	
	NBear[0].set(300, 268);

	ground[0].setSize({ 2000.f,32.f });
	ground[0].setPosition(0.f, 500.f);
	ground[0].setFillColor(sf::Color::Green);

	ground[1].setSize({ 200.f,32.f });
	ground[1].setPosition(200.f, 300.f);
	ground[1].setFillColor(sf::Color::Green);

	ground[2].setSize({ 0.1,500 });
	ground[2].setPosition(0, 0);
	ground[2].setFillColor(sf::Color::Green);

	////// Circle
	sf::CircleShape collision(50.f);
	collision.setPosition({ 200.f, 200.f });
	collision.setFillColor(sf::Color::Red);

	////// Texture
	sf::Texture playerTexture,fishbone;
	if (!playerTexture.loadFromFile("spritesheet.png"))
	{
		std::cout << "1 Load failed " << std::endl;
	}
	if (!fishbone.loadFromFile("fishbone.png"))
	{
		std::cout << "2 Load failed " << std::endl;
	}

	////// Sprite
	shapeSprite.setTexture(playerTexture);
	shapeSprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
	shapeSprite.setPosition(spawn);
	Bullet.setTexture(fishbone);
	Bullet.setTextureRect(sf::IntRect(0, 0, 12, 12));
	while (window.isOpen())
	{
		window.draw(shapeSprite);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		RH = 2;
		shapeSprite.move(-0.2f, 0.f);
		for (int i = 0; i < g; i++)
		{
			if (shapeSprite.getGlobalBounds().intersects(ground[i].getGlobalBounds()))
			{
				if (shapeSprite.getPosition().y + 31 > ground[i].getPosition().y)
				{
					shapeSprite.move(0.2f, 0.f);
					break;
				}
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		RH = 1;
		shapeSprite.move(.2f, 0.f);
		for (int i = 0; i < g; i++)
		{
			if (shapeSprite.getGlobalBounds().intersects(ground[i].getGlobalBounds()))
			{
				if (shapeSprite.getPosition().y + 31 > ground[i].getPosition().y)
				{
					shapeSprite.move(-0.2f, 0.f);
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
	for (int i = 0; i < nb; i++)
	{
		if (shapeSprite.getGlobalBounds().intersects(NBear[i].body.getGlobalBounds()))
		{
			shapeSprite.setPosition(spawn);
			NBear[i].HP -= 5;
			break;
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
		}
		else
		{
			Bullet.setPosition(shapeSprite.getPosition().x - 15, shapeSprite.getPosition().y + 10);
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
			}
		}
	}
	if (Bullet.getPosition().x - shapeSprite.getPosition().x > 600 || Bullet.getPosition().x - shapeSprite.getPosition().x < -600)
	{
		bullet = 0;
		Bullet.setPosition(-1, -1);
	}
}
