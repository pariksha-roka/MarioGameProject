#pragma once
#include <SDL.h>

class Animation
{
public:

	// basic animation information
	int numberOfFrames;
	int frameWidth, frameHeight;
	float frameDuration; /* how long a frame should animate for
							1 = 1 second, 	0.5 = half second */
	SDL_Texture* spriteSheet;
	SDL_Renderer* renderer;

	// current state of animation
	int currentFrame;
	float frameTimer;

	void update(float dt);
	void draw(int x, int y);

	Animation();
	~Animation();
};

