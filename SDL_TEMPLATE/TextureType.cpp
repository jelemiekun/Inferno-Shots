#include "TextureType.h"
#include "SDL_image.h"
#include "Game.h"

void TextureType::checkTextureIfLoaded(const std::string& path) {
	if (texture) {
		std::cout << "Texture with path " << path << " loaded." << '\n';
		fetchTextureDimension();
	} else {
		std::cout << "Texture " << path << " failed to load: " << IMG_GetError() << '\n';
	}
}

void TextureType::fetchTextureDimension() {
	SDL_QueryTexture(texture, nullptr, nullptr, &dimension.x, &dimension.y);
}

TextureType::TextureType(Prototype_Type type) {
	std::string path = getProtoType_Type_Path(type);

	texture = IMG_LoadTexture(Game::getInstance()->getRenderer(), path.c_str());

	checkTextureIfLoaded(path);
}

TextureType::~TextureType() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
}