// Libraries / Headers to include 
#include "Game.h"
#include "GameObjects.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <Mmsystem.h>
#include <mciapi.h>
#include <stdlib.h>
#pragma comment(lib, "Urlmon.lib")
#pragma comment(lib, "Winmm.lib")


#include "VariableConversion.h"
#include "MPAD.h"
using namespace vc;
using namespace mpad;

// ======================================================= 
// SDL Variables
SDL_Renderer* Game::renderer = nullptr;;
SDL_Event Game::playerInputEvent;
GameInput playerInput;

// Game Objects


TTF_Font* font = nullptr;
TTF_Font* font2 = nullptr;
SDL_Color textColour = { 255, 255, 255 };
SDL_Surface* textSurface = nullptr;
SDL_Texture* textTexture = nullptr;

int level = 1;
int points = 0;
int pointIncrement = 100;
int finalScore = 0;
int speed = 256;

void MusicPlayer(std::string songIDInputGlobal);
Mix_Music* music = NULL;

std::string text = "";
std::string statusText = "";
int currentStatus;




// ======================================================= 
void Game::createGameObjects()
{
	printf("\nCreating Game Objects");
	music = Mix_LoadMUS("downloads/DDLoop1.wav");

	// Create Background
	// Create Game Objects - filename , x and y pos, initial angle

}//----

void Game::update(float frameTime)
{
	// Ensure Frame rate is at the delay speed and convert to deltaTime
	frameTime = static_cast<float>(1) / FPS;
	if (frameTime < 1000 * (float)1 / FPS) frameTime = (float)1 / FPS;
}//---

void Game::updateGUI()
{
	SDL_Rect textRect = { 64,8,0,0 }; // start position of the text
	std::string  screenText;
	std::string screenText2;

	// text to be on screen
	screenText = text;
	screenText2 = "\n" +statusText;



	// render the text to screen
	textSurface = TTF_RenderText_Blended_Wrapped(font2, screenText.c_str(), textColour, 0);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

	textSurface = TTF_RenderText_Blended_Wrapped(font2, screenText2.c_str(), textColour, 0);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

	// Clear the memory
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

}//--

// ======================================================= 
void Game::render()
{
	SDL_RenderClear(renderer);


	// Render
	updateGUI();

	SDL_RenderPresent(renderer); 	// Update the screen
}//---



// ======================================================= 
void Game::handleEvents()
{
	MPAD mpad;
	// Reset Inputs
	playerInput.keyPressed = NULL;
	playerInput.mouseL = false;
	playerInput.mouseR = false;

	//Check for Events
	SDL_PollEvent(&playerInputEvent);

	switch (playerInputEvent.type)
	{
	case SDL_QUIT:
		gameRunning = false;
		break;

	//case SDL_KEYDOWN:
	//	playerInput.keyPressed = playerInputEvent.key.keysym.sym;
	//	break;

	case SDL_TEXTINPUT:
		//system("cls");
		if (text.size() < 30) 
		{
			text += playerInputEvent.text.text;
			/*for (int i = 0; i < text.length(); i++) {
				if (isdigit(text[i]) == false) {
					text.pop_back();
					break;
				}
			}*/
			
		}
		//std::cout << text << endl;
		break;
	case SDL_KEYDOWN:
		switch (playerInputEvent.key.keysym.scancode) {
		case SDL_SCANCODE_BACKSPACE:
			if (text.size() > 0) 
			{
				text.pop_back();
			}
			break;
		case SDL_SCANCODE_DELETE:
			text = "";
			break;
		case SDL_SCANCODE_SPACE:
			statusText = "Downloading...";
			currentStatus = mpad.MusicDownloader(text);
			if (currentStatus == 0) { statusText = "Downloaded Successfully..."; }
			else { statusText = "Download Failed..."; }
			MusicPlayer(text);
			break;
		}

		break;
	default:
		break;
	}
}//---

// ======================================================= 
void Game::startSDL(const char* title)
{
	
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)
	{
		std::cout << "Dylan Love - CI517 - 2023 - 24";
		std::cout << "\nSDL Initialised  \n";
		gameWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		if (gameWindow) printf("\nGame Window Created ");
		renderer = SDL_CreateRenderer(gameWindow, -1, 0);
		if (renderer) printf("\nRenderer Created \n");
		
		gameRunning = true;

		Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

		TTF_Init();
		font = TTF_OpenFont("assets/fonts/arial.ttf", 22);
		font2 = TTF_OpenFont("assets/fonts/PressStart2P-Regular.ttf", 22);
	}
	else
	{
		std::cout << "SDL_INIT_EVERYTHING FALIED! Code: " << SDL_Init(SDL_INIT_AUDIO) << std::endl;

		gameRunning = false;
	}
}//---

void MusicPlayer(std::string songIDInputGlobal)
{
	
	VariableConversion vc;
	std::string baseMusicLocation = "downloads/" + songIDInputGlobal + ".mp3";



	const char* songLocationChar = vc.stringToChar(baseMusicLocation);
	//music = Mix_LoadMUS("downloads/DDLoop1.wav");
	std::cout << "\nSongID:" << baseMusicLocation << std::endl;
	std::cout << baseMusicLocation << " | " << music << " | " << std::endl;
	Mix_PlayMusic(music, 1);
	std::cout << Mix_PlayingMusic() << std::endl;
}

// ======================================================= 

void Game::welcomeScreen()
{
	SDL_RenderPresent(renderer);
	SDL_Delay(500);

}//---


void Game::endScreen()
{
	SDL_RenderPresent(renderer);
	SDL_Delay(2000);
	closeSDL();
}//---

// ======================================================= 
void Game::exitScreen()
{
	printf("\n\n ----- Thank you for playing -----");
	SDL_Delay(1000);
}//---

// ======================================================= 
void Game::closeSDL() // Clear Memory and exit SDL
{
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(renderer);
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	SDL_Quit();
	std::cout << "\nSDL Closed \n";
}//---

// ======================================================= 
Game::Game() // Constructor
{
	printf(" \n\n ----- Game Started ------ \n");
}

// ======================================================= 