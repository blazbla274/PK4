#pragma once
class Ghost :public sf::Drawable, protected virtual Guardian
{
public:
	Ghost(float x, float y, Map* m, Game* g, Packman* p, int timeToresp);
	Ghost() = default;
	~Ghost() = default;
	void update();
	void updateVelocity();
	bool capture{ false };
	void reset();
	void resetControler(int x);
	int resetCounter{ 0 };
protected:
	sf::Vector2i pacmanPosition;
	sf::Vector2i gohstPosition; 
	sf::Vector2i movementDirection{ 0, 0 };
	Packman * pacman;
	float velocity;
	float velocityHunt;
	float velocityRunOut;
	Vector2f velocityVectorLeft{ -velocity , 0 };
	Vector2f velocityVectorRight{ velocity , 0 };
	Vector2f velocityVectorTop{ 0 , -velocity };
	Vector2f velocityVectorBottom{ 0 , velocity };
	Texture fearTexture;
	int bestDirection();
	void colisionDetection();
	void fearDetection(); //zmienia texturê je¿eli duszki siê boj¹
	sf::Vector2i sugestedDirection();
	void respawn(); 
	bool resp{ true };
	int timeToRespawn{ 50 };
	int timeToRespawnSetter{ 50 };
	float respX, respY;
	void draw(RenderTarget& target, RenderStates state) const override;
};

