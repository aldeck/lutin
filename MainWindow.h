/*
 * Copyright 2010, Alexandre Deckner. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 * 		Alexandre Deckner <alex@zappotek.com>
 */
#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <DirectWindow.h>

class RenderView;

class MainWindow: public BWindow {
public:
					MainWindow(BRect frame, const char* title);
					~MainWindow();

	virtual bool	QuitRequested();
	virtual void	MessageReceived(BMessage* message);

protected:
	RenderView*		fRenderView;
};

#endif /* _MAINWINDOW_H */
