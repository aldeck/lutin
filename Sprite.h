/*
 * Copyright 2010 Alexandre Deckner. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 * 		Alexandre Deckner <alex@zappotek.com>
 */
#ifndef _SPRITE_H
#define _SPRITE_H


#include <Point.h>


class BView;


class Sprite {
public:
				Sprite(BView* parentView, const BPoint& position, float animOffset);
				~Sprite();

	void		Update(float dt);
	void		Render();

protected:
	BView*		fParentView;
	
	BPoint		fOrigin;
	BPoint		fPosition;
	BPoint 		fSpeed;
	uint32		fColor;
	float		fScale;	

	// TODO: manage the animation externally
	float		fTime;
	float		fAnimOffset;	
};

#endif /* _SPRITE_H */
