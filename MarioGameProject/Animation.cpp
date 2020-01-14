#include "Animation.h"


void Animation::update(float dt)
{
	frameTimer += dt; // increment frame timer

	if (frameTimer >= frameDuration) { // if it meets our frame duration time
		frameTimer = 0; // reset timer
		currentFrame++; // increment frame
		
		if (currentFrame >= numberOfFrames) // if current frame gone past our number of frames
			currentFrame = 0; // reset animation back to first frame
	}
}

void Animation::draw(int x, int y)
{
	// set up clip region to get current frame in animation
	SDL_Rect clip;

	clip.x = currentFrame * frameWidth;
	clip.y = 0;
	clip.w = frameWidth;
	clip.h = frameHeight;

	// set up render destination
	SDL_Rect destRender = { x, y, frameWidth, frameHeight };
	// render
	SDL_RenderCopy(renderer, spriteSheet, &clip, &destRender); 
}

Animation::Animation()
{
}


Animation::~Animation()
{
}
