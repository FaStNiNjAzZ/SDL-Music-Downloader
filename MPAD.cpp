#include <cstdio>
#include <iostream>
#include <string>
#include <SDL_mixer.h>
#include <windows.h>
#include <Mmsystem.h>
#include <mciapi.h>
#include "MPAD.h"
#include "VariableConversion.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

using namespace vc;
using namespace mpad;


std::string songIDInputGlobal;


int MPAD::MusicDownloader(std::string songIDInputGlobal)
{
	VariableConversion variableConversion;
	printf("How To Download Songs:\n");
	printf("1. Go to newgrounds.com/audio.\n");
	printf("2. Take the song ID from the end of the URL. For example https://www.newgrounds.com/audio/listen/739991, the 739991 is the song ID.\n");
	printf("3. Paste the song ID below.\n");



	// the URL to download from 

	wchar_t srcURL[44] = L"https://www.newgrounds.com/audio/download/";
	wchar_t idURL[2] = L"1";
	const wchar_t* finalURL = wcscat(srcURL, variableConversion.stringToConstChar_t(songIDInputGlobal));

	//const wchar_t* srcURL = L"https://www.newgrounds.com/audio/download/";

	// the destination file 
	wchar_t folder[24] = L"downloads/";
	wchar_t fileExtension[6] = L".mp3";
	wchar_t* filePath = wcscat(folder, variableConversion.stringToConstChar_t(songIDInputGlobal));
	const wchar_t* destFile = wcscat(filePath, fileExtension);
	printf("Downloading...\n");

	// URLDownloadToFile returns S_OK on success 
	if (S_OK == URLDownloadToFile(NULL, finalURL, destFile, 0, NULL))
	{
		printf("Saved to ");
		std::cout << variableConversion.constChar_tToString(destFile) << std::endl;
		//MusicPlayer(songIDInputGlobal);
		return 0;
	}

	else
	{
		printf("Failed");
		return -1;
	}
}

void MPAD:: MusicPlayer(std::string songIDInputGlobal)
{
	Mix_Music* music = NULL;
	VariableConversion vc;
	std::string baseMusicLocation = "downloads/" + songIDInputGlobal + ".mp3";



	const char* songLocationChar = vc.stringToChar(baseMusicLocation);
	music = Mix_LoadMUS(songLocationChar);
	std::cout << "\nSongID:" << baseMusicLocation << std::endl;
	std::cout << baseMusicLocation << " | " << music << " | " << std::endl;
	Mix_PlayMusic(music, -1);
	std::cout << Mix_PlayingMusic() << std::endl;
}
