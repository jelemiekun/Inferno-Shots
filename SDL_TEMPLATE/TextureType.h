#pragma once
#include <SDL.h>
#include "GameEnums.h"

using Dimension = SDL_Point;

class TextureType {
private:
	void checkTextureIfLoaded(const std::string& path);
	void fetchTextureDimension();

public:
	SDL_Texture* texture;
	Dimension dimension;

	TextureType(Prototype_Type type);
	~TextureType();
};

