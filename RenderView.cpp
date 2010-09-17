/*
 * Copyright 2010, Alexandre Deckner. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 * 		Alexandre Deckner <alex@zappotek.com>
 */


#include "RenderView.h"

#include <Bitmap.h>
#include <Region.h>
#include <Window.h>

#include <stdio.h>


RenderView::RenderView(BRect frame)
	:
	BView(frame, "renderView", B_FOLLOW_ALL, B_WILL_DRAW),
	fRenderThread(-1),
	fStopRendering(false),
	fRes(0, 0),
	fNextRes(0, 0),
	fLastFrameTime(0)
{
	fBitmap = new BBitmap(Bounds(), B_RGB32, true, false);
	fOffscreenView = new BView(Bounds(), "offscreenView", 0, 0);
	
	fBitmap->Lock();
	fBitmap->AddChild(fOffscreenView);
	fBitmap->Unlock();
}


RenderView::~RenderView()
{
	_DeleteScene();
	
	delete fBitmap;
}


void
RenderView::AttachedToWindow()
{
	BView::AttachedToWindow();
	
	_CreateScene();
	
	if (_CreateRenderThread() != B_OK)
		printf("Error trying to start the render thread!\n");
}


uint32
RenderView::_CreateRenderThread()
{
	fRenderThread = spawn_thread(RenderView::_RenderThreadEntry, "renderThread",
		B_NORMAL_PRIORITY, this);

	if (fRenderThread < 0)
		return fRenderThread;

	return resume_thread(fRenderThread);
}


void
RenderView::StopRenderThread()
{
	if (Window()->Lock()) {
		fStopRendering = true;
		Window()->Unlock();
	}
	
	if (fRenderThread >= 0)
		wait_for_thread(fRenderThread, NULL);
}


int32
RenderView::_RenderThreadEntry(void* pointer)
{
	return reinterpret_cast<RenderView*>(pointer)->_RenderLoop();
}


int32
RenderView::_RenderLoop()
{
	fLastFrameTime = system_time();

	while (_Render()) {
		snooze(100);
	}
	return B_OK;
}


void
RenderView::_CreateScene()
{
	for (int i = 0; i < 64; i++) { 
		Sprite* lutin = new Sprite(fOffscreenView, BPoint(320 , 240), (60.0 / 130.0) * (float) i);
		fSprites.push_back(lutin);
	}
}


void
RenderView::_DeleteScene()
{
	SpriteList::iterator it = fSprites.begin();
	for (; it != fSprites.end(); it++) {
		delete (*it);
	}
	fSprites.clear();
}


bool
RenderView::_Render()
{
	bigtime_t time = system_time();
	float deltaTime = 0.000001 * (float)(time - fLastFrameTime);
	fLastFrameTime = time;

	if (LockLooper()) {
		if (fStopRendering) {
			UnlockLooper();
			return false;
		}
		
		if (fBitmap->Lock()) {			
			fOffscreenView->SetHighColor(0, 0, 0);
			fOffscreenView->FillRect(Bounds());			
		
			SpriteList::iterator it = fSprites.begin();
			for (; it != fSprites.end(); it++) {
				(*it)->Update(deltaTime);
				(*it)->Render();
			}
			
			fOffscreenView->Sync();
			fBitmap->Unlock();		
	
			DrawBitmap(fBitmap, B_ORIGIN);
		}

		UnlockLooper();
	}

	return true;
}


void
RenderView::FrameResized(float width, float height)
{
	BView::FrameResized(width, height);
}

