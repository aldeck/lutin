/*
 * Copyright 2010, Alexandre Deckner. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 * 		Alexandre Deckner <alex@zappotek.com>
 */

#include <Alert.h>

#include "App.h"
#include "MainWindow.h"


App::App()
	:
	BApplication("application/x-vnd.Haiku-Lutin"),
	fMainWindow(NULL)
{
}


App::~App()
{
}


void
App::ReadyToRun()
{
	BRect frame(50, 50, 640 + 50, 480 + 50);
	const char* title = "Lutin";
	fMainWindow = new MainWindow(frame, title);
	fMainWindow->Show();
}


void
App::AboutRequested()
{
	BAlert* alert;
	alert = new BAlert("About", "A little sprite demo", "OK");
	alert->Go(NULL);
}


bool
App::QuitRequested()
{
	return true;
}


int
main(int argc, char** argv)
{
	App app;
	app.Run();
	return 0;
}
