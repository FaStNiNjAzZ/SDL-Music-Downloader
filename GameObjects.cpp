// ======================================================= 
// Libraries / Headers to include 
#include "GameObjects.h"

// ======================================================= 
GameObject::GameObject()
{	// default Constructor; 
}

void GameObject::Loadtexture(const char* spriteFileName)
{
	// Load Image from File to create the sprite
	SDL_Surface* tempSurface = IMG_Load(spriteFileName);
	spriteTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	if (spriteTexture == NULL) printf(" Image Load Error  - SDL Error: %s\n", SDL_GetError());
	SDL_FreeSurface(tempSurface);

}//---



// ======================================================= 
void GameObject::update()
{	// update the display Rectangle Position
	destRect.x = (int)x;
	destRect.y = (int)y;
}//---

// ======================================================= 

// ======================================================= 
void GameObject::render()
{
	// add the Sprite to the Render Image
	SDL_RenderCopy(Game::renderer, spriteTexture, &srcRect, &destRect);
}//---