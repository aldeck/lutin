/*
 * Copyright 2010 Alexandre Deckner. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 * 		Alexandre Deckner <alex@zappotek.com>
 */


#include "Sprite.h"

#include <View.h>

#include "MathUtils.h"

#include <stdlib.h>


Sprite::Sprite(BView* parentView, const BPoint& position, float animOffset)
	:
	fParentView(parentView),
	fPosition(position),
	fScale(1.0f),
	fTime(0.0f),
	fAnimOffset(animOffset)
{
	fOrigin = fPosition;
	fSpeed.x = -50.0 + 100.0 * (float)rand() / ((float)RAND_MAX + 1);
	fSpeed.y = -50.0 + 100.0 * (float)rand() / ((float)RAND_MAX + 1);
	
	float a = 360.0 * (float)rand() / ((float)RAND_MAX + 1);	
	fColor = hsvToRGB(a, 1.0f, 1.0f);
}


Sprite::~Sprite()
{
}


void
Sprite::Update(float dt)
{
	BRect borders(0, 50, 640 - 60, 480);
	
	fPosition.x += 4.0 * dt * fSpeed.x;
	fPosition.y += 4.0 * dt * fSpeed.y;
	
	if (fPosition.x > borders.right) {
		fPosition.x = borders.right;
		fSpeed.x = -fSpeed.x;	
	} else if (fPosition.x < borders.left) {
		fPosition.x = borders.left;
		fSpeed.x = -fSpeed.x;	
	}
	
	if (fPosition.y > borders.bottom) {
		fPosition.y = borders.bottom;
		fSpeed.y = -fSpeed.y;	
	} else if (fPosition.y < borders.top) {
		fPosition.y = borders.top;
		fSpeed.y = -fSpeed.y;	
	}
}


void
Sprite::Render()
{
	/*BPoint begin(fPosition);
	begin.x -= 25;
	begin.y -= 25;
	BPoint end(fPosition);
	end.x += 25;
	end.y += 25;
	fParentView->SetHighColor(*(rgb_color*)(&fColor));
	fParentView->StrokeRect(BRect(begin, end));*/
	
	static const float body[98] = {
		0, 1,
		0, 4,
		1, 4,
		1, 5,
		2, 5,
		2, 6,
		3, 6,
		3, 7,
		2, 7,
		2, 8,
		3, 8,
		3, 7,
		4, 7,
		4, 6,
		7, 6,
		7, 7,
		8, 7,
		8, 8,
		9, 8,
		9, 7,
		8, 7,
		8, 6,
		9, 6,
		9, 5,
		10, 5,
		10, 4,
		11, 4,
		11, 1,
		10, 1,
		10, 3,
		9, 3,
		9, 1,
		8, 1,
		8, 0,
		6, 0,
		6, 1,
		8, 1,
		8, 2,
		3, 2,
		3, 1,
		5, 1,
		5, 0,
		3, 0,
		3, 1,
		2, 1,
		2, 3,
		1, 3,
		1, 1,
		0, 1 
	};
	
	static const float lefteye[10] = {
		3, 4,
		4, 4,
		4, 5,
		3, 5,
		3, 4
	};
	
	static const float righteye[10] = {
		7, 4,
		8, 4,
		8, 5,
		7, 5,
		7, 4
	};
	
	
	float scale = 6.0;
	
	fParentView->BeginLineArray(48 + 4 + 4);
	for (int i = 0; i < 49 - 1; i++) {
		BPoint p1(scale * body[i * 2], -scale * body[i * 2 + 1]);		
		BPoint p2(scale * body[i * 2 + 2], -scale * body[i * 2 + 3]);		
		fParentView->AddLine(p1 + fPosition, p2 + fPosition, *(rgb_color*)(&fColor)) ;
	}
	
	for (int i = 0; i < 5 - 1; i++) {
		BPoint p1(scale * lefteye[i * 2], -scale * lefteye[i * 2 + 1]);		
		BPoint p2(scale * lefteye[i * 2 + 2], -scale * lefteye[i * 2 + 3]);		
		fParentView->AddLine(p1 + fPosition, p2 + fPosition, *(rgb_color*)(&fColor)) ;
	}
	
	for (int i = 0; i < 5 - 1; i++) {
		BPoint p1(scale * righteye[i * 2], -scale * righteye[i * 2 + 1]);		
		BPoint p2(scale * righteye[i * 2 + 2], -scale * righteye[i * 2 + 3]);		
		fParentView->AddLine(p1 + fPosition, p2 + fPosition, *(rgb_color*)(&fColor)) ;
	}
	
	fParentView->EndLineArray();	
}
