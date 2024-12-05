#pragma once
#include <SDL.h>

namespace Border {
	inline void bRenderBorder(SDL_Renderer*& renderer, 
		const SDL_Rect& dstRect, 
		const int& borderThick, const 
		SDL_Color& borderColor) 
	{
		for (int borderCount = 0; borderCount < borderThick; borderCount++) {
			SDL_Rect border = {
				dstRect.x - borderCount,
				dstRect.y - borderCount,
				dstRect.w + (borderCount * 2),
				dstRect.h + (borderCount * 2)
			};

			SDL_SetRenderDrawColor(renderer, 
				borderColor.r,
				borderColor.g, 
				borderColor.b, 
				borderColor.a
			);

			SDL_RenderDrawRect(renderer, &border);
		}
	}
}