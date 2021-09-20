// Precompiled headers
#include "stdafx.h"

// Game core
#include "Game.h"

int main()
{
	// Creating random seed
	srand(static_cast<unsigned int>(time(NULL)));

	// Hiding Console window
//	HWND console_window = GetConsoleWindow();
//	ShowWindow(console_window, SW_HIDE);

	Game game;	

	game.run();

	// Showing Console window - IT'S IMPORTANT
//	ShowWindow(console_window, SW_SHOW);
//	SetForegroundWindow(console_window);

	return 0;
}