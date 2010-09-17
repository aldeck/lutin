/*
 * Copyright 2010, Alexandre Deckner. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 * 		Alexandre Deckner <alex@zappotek.com>
 */
#ifndef _RENDERVIEW_H
#define _RENDERVIEW_H

#include <View.h>

#include "Sprite.h"

#include <vector>

class BBitmap;


class RenderView : public BView {
public:
					RenderView(BRect frame);
					~RenderView();

	virtual void	AttachedToWindow();
	virtual void	FrameResized(float width, float height);
	void			StopRenderThread();

protected:

	bool			_Render();
	uint32			_CreateRenderThread();
	
	static int32	_RenderThreadEntry(void* pointer);
	int32			_RenderLoop();
	
	void			_CreateScene();
	void			_DeleteScene();
	
	BBitmap*		fBitmap;
	BView*			fOffscreenView;

	typedef std::vector<Sprite*> SpriteList;
	SpriteList		fSprites;

	thread_id		fRenderThread;
	bool			fStopRendering;

	BPoint			fRes, fNextRes;
	bigtime_t		fLastFrameTime;
};

#endif /* _RENDERVIEW_H */
