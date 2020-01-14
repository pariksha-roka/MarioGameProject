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

	// ADDING ALL THE IMAGES TO BE INCLUDED IN TITLE PAGE
	SDL_Texture* marioTitle = IMG_LoadTexture(renderer, "assets/MarioTitle.png");
	SDL_Texture* marioHero = IMG_LoadTexture(renderer, "assets/MarioHero.png");
	SDL_Texture* marioEnemy = IMG_LoadTexture(renderer, "assets/MarioEnemy.png");
	SDL_Texture* marioPowerPlant = IMG_LoadTexture(renderer, "assets/MarioPowerPlant.png");
	SDL_Texture* marioTubo = IMG_LoadTexture(renderer, "assets/MarioTubo.png");
	SDL_Texture* marioBricksCollection = IMG_LoadTexture(renderer, "assets/MarioBricksCollection.png");
	SDL_Texture* marioBricksWithCoinQues = IMG_LoadTexture(renderer, "assets/MarioBricksWithCoinQues.png");

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

	SDL_Rect marioTitleDest;
	SDL_QueryTexture(marioTitle, NULL, NULL, &marioTitleDest.w, &marioTitleDest.h);
	marioTitleDest.x = 185;
	marioTitleDest.y = 25;
	marioTitleDest.w = marioTitleDest.w*0.90;
	marioTitleDest.h = marioTitleDest.h*0.50;

	SDL_Rect marioDest;
	SDL_QueryTexture(marioHero, NULL, NULL, &marioDest.w, &marioDest.h);
	marioDest.x = 400;
	marioDest.y = 345;
	marioDest.w = marioDest.w*0.12;
	marioDest.h = marioDest.h*0.12;

	SDL_Rect marioEnemyDest;
	SDL_QueryTexture(marioEnemy, NULL, NULL, &marioEnemyDest.w, &marioEnemyDest.h);
	marioEnemyDest.x = 900;
	marioEnemyDest.y = 500;
	marioEnemyDest.w = marioEnemyDest.w*0.1;
	marioEnemyDest.h = marioEnemyDest.h*0.1;

	SDL_Rect marioPowerPlantDest;
	SDL_QueryTexture(marioPowerPlant, NULL, NULL, &marioPowerPlantDest.w, &marioPowerPlantDest.h);
	marioPowerPlantDest.x = 690;
	marioPowerPlantDest.y = 425;
	marioPowerPlantDest.w = marioPowerPlantDest.w*0.1;
	marioPowerPlantDest.h = marioPowerPlantDest.h*0.1;

	SDL_Rect marioTuboDest;
	SDL_QueryTexture(marioTubo, NULL, NULL, &marioTuboDest.w, &marioTuboDest.h);
	marioTuboDest.x = 30;
	marioTuboDest.y = 488;
	marioTuboDest.w = marioTuboDest.w*0.3;
	marioTuboDest.h = marioTuboDest.h*0.3;

	SDL_Rect marioBricksCollectionDest;
	SDL_QueryTexture(marioBricksCollection, NULL, NULL, &marioBricksCollectionDest.w, &marioBricksCollectionDest.h);
	marioBricksCollectionDest.x = 130;
	marioBricksCollectionDest.y = 490;
	marioBricksCollectionDest.w = marioBricksCollectionDest.w*0.7;
	marioBricksCollectionDest.h = marioBricksCollectionDest.h*0.7;

	SDL_Rect marioBricksWithCoinQuesDest;
	SDL_QueryTexture(marioBricksWithCoinQues, NULL, NULL, &marioBricksWithCoinQuesDest.w, &marioBricksWithCoinQuesDest.h);
	marioBricksWithCoinQuesDest.x = 650;
	marioBricksWithCoinQuesDest.y = 545;
	marioBricksWithCoinQuesDest.w = marioBricksWithCoinQuesDest.w*0.5;
	marioBricksWithCoinQuesDest.h = marioBricksWithCoinQuesDest.h*0.5;

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

	// showing all the images on the console
	SDL_RenderCopy(renderer, marioTitle, NULL, &marioTitleDest);
	SDL_RenderCopy(renderer, marioHero, NULL, &marioDest);
	SDL_RenderCopy(renderer, marioEnemy, NULL, &marioEnemyDest);
	SDL_RenderCopy(renderer, marioPowerPlant, NULL, &marioPowerPlantDest);
	SDL_RenderCopy(renderer, marioTubo, NULL, &marioTuboDest);
	SDL_RenderCopy(renderer, marioBricksCollection, NULL, &marioBricksCollectionDest);
	SDL_RenderCopy(renderer, marioBricksWithCoinQues, NULL, &marioBricksWithCoinQuesDest);
	
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