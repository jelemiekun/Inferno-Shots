#include "Text.h"
#include "Game.h"

std::vector<Font> Text::getAllFonts() {
	return {
		Font::MENU
	};
}

void Text::initFonts() {
	std::vector<Font> itFonts = getAllFonts();

	for (auto& font : itFonts) {
		std::string path = getPath(font);
		std::shared_ptr<TTF_Font> font = std::make_shared<TTF_Font>(TTF_OpenFont(path.c_str(), 28));

		fonts[path] = font;
	}
}

std::string Text::getPath(Font font) {
	std::string path = " ";

	switch (font) {
	case Font::MENU: path = "//TODO"; break;
	default:
		break;
	}

	return path;
}

void Text::free() {
	if (!(mTexture.get())) {
		SDL_DestroyTexture(*mTexture.get());
		mTexture = nullptr;
	}
}

Text::Text() {}

Text::~Text() {
	SDL_DestroyTexture(*mTexture.get());
}

void Text::setFont(Font font) {
	std::string fontPath = Text::getPath(font);
	fontUsing = fonts[fontPath];
}

void Text::setText(std::string text) {
	mText = text;
}

void Text::setDstRect(SDL_Rect dstRect) {
	mDstRect = dstRect;
}

void Text::setColor(SDL_Color color) {
	mColor = color;
}

void Text::loadText() {
	free();

	SDL_Surface* surface = TTF_RenderText_Solid(fontUsing.get(), mText.c_str(), mColor);
	
	if (!surface) {
		std::cout << "Failed to render text: " << TTF_GetError() << '\n';
	} else {
		*mTexture.get() = SDL_CreateTextureFromSurface(Game::getInstance()->getRenderer(), surface);

		if (!mTexture.get()) {
			std::cout << "Failed to create texture from surface: " << SDL_GetError() << '\n';
		}
	}

	SDL_FreeSurface(surface);
}

void Text::render() const {
	SDL_RenderCopy(Game::getInstance()->getRenderer(), *mTexture.get(), nullptr, &mDstRect);
}