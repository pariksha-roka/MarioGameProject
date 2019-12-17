#include <iostream> // for input and output files
#include <SDL.h> // to include all SDL files
#include <string> // to use the string data type variables
#include <SDL_image.h> // to include different types of images such as png and jpg



using namespace std;

/* we need this for SDL to work, need old 'main' signature 
, not void main() */
int main(int argc, char **argv)
{
	// initialise SDL and its subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL Fail initialized!!!\n";
		// diplaying the error
		cout << "ERROR Message: " << SDL_GetError() << endl;
		system("pause");
		return -1; // exit program early
	}
	else
	{
		cout << "SDL initialized sucess!!!\n";
	}

	// params or parameters:
	// window title, x and y pos, width, height, flags for creation
	SDL_Window* window = SDL_CreateWindow("My Mario Game",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1024, 720, SDL_WINDOW_SHOWN); // similar to SDL_WINDOW_FULLSCREEN

	if (window != NULL) {
		cout << "window is created!!!" << endl;
	}
	else
	{
		// diplaying the error
		cout << "ERROR Message: " << SDL_GetError() << endl;
		system("pause");
		SDL_Quit(); // to cleanup SDL memory
		return -1; // exit the program
	}

	// creating renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL) {
		cout << "ERROR Message: " << SDL_GetError() << endl;
		system("pause");
		SDL_Quit(); // cleanup SDL memory
		return -1; // exit the program
	}

	// LOADING UP ASSETS TO DRAW
	/* Loading up image up as a surface. Surfaces are stored in RAM so we
	can acess their pixel data from code*/
	// surfaces used for software rendering is not as fast as hardware
	SDL_Surface* marioBackgroundSurface = IMG_Load("assets/BaseMarioBackground.png"); // CHANGE
	
	// CONVERTING SURFACE TO TEXTURE
	/* Textures are stored in gfx cards vram and is used for Hardware 
	rendering */
	// we cannot access the pixel data of a texture directly
	SDL_Texture* marioBackgroundTexture = SDL_CreateTextureFromSurface(renderer, marioBackgroundSurface); // CHANGE
	// we don't need surface anymore, so let's free up memory
	SDL_FreeSurface(marioBackgroundSurface); // CHANGE

	/* which is destination rectangle and which is source rectangle
	in the console window? */

	// NOW knight rectangle to help the draw to the screen // CHANGE
	SDL_Rect sourceRectangle;
	/* getting width and height from texture and storing them to our 
	source rectangle 
	parameters: texture to query, format pointer, access pointer, width pointer
	            height pointer
	*/
	SDL_QueryTexture(marioBackgroundTexture, NULL, NULL, &sourceRectangle.w, &sourceRectangle.h); // CHANGE
	sourceRectangle.x = 0;
	sourceRectangle.y = 0;

	// destination rectangle
	SDL_Rect destinationRectangle;
	destinationRectangle.x = 0;
	destinationRectangle.y = 0;
	destinationRectangle.w = 1024;
	destinationRectangle.h = 720;


	// setting draw color of render with RBGA value (i.e value between 0-255)
	SDL_SetRenderDrawColor(renderer, 255, 0, 168, 255); // CHANGE
	// now clearing the screen with current draw color
	SDL_RenderClear(renderer);

	/* Why renderer has 2 different colors?*/

	// changing render draw color
	SDL_SetRenderDrawColor(renderer, 0, 228, 255, 255); // CHANGE
	
	// making rectangle to draw to the screen (x, y, w, h)
	SDL_Rect rectangle = { 100, 50, 300, 240 }; // CHANGE

	//drawing rectangle to screen with current draw color
	SDL_RenderFillRect(renderer, &rectangle);

	// drawing knight image // CHANGE
	SDL_RenderCopy(renderer, marioBackgroundTexture, &sourceRectangle, &destinationRectangle); // CHANGE

	// swaping the buffers and showing our current frame that we have been drawing
	SDL_RenderPresent(renderer);

	// to wait for 5 seconds i.e 5000ms
	SDL_Delay(5000);

	// cleaning up renderer and window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// cleaning up SDL memory
	SDL_Quit();

	system("pause");
	return 0;
}