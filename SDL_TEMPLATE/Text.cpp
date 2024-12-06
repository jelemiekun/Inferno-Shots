#include "Text.h"
#include "Game.h"

std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Text::fonts;

std::vector<Font> Text::getAllFonts() {
	return {
		Font::MOTION_CONTROL_BOLD,
		Font::MOTION_CONTROL_ITALLIC
	};
}

void Text::initFonts() {
	std::vector<Font> itFonts = getAllFonts();

	for (const auto& font : itFonts) {
		std::string path = getPath(font);

		std::shared_ptr<TTF_Font> fontPtr(
			TTF_OpenFont(path.c_str(), 28),
			[](TTF_Font* font) {
				if (font) TTF_CloseFont(font);
			}
		);

		if (!fontPtr) {
			std::cerr << "Failed to load font: " << path << ": " << TTF_GetError() << "\n";
			continue;
		} else {
			std::cout << "Font " << path << " loaded." << '\n';
		}

		fonts[path] = fontPtr;
	}
}

std::string Text::getPath(Font font) {
	std::string path = " ";

	switch (font) {
	case Font::MOTION_CONTROL_BOLD: path = "assets/fonts/MotionControl-Bold.otf"; break;
	case Font::MOTION_CONTROL_ITALLIC: path = "assets/fonts/MotionControl-Italic.otf"; break;
	default: path = ""; break;
	}

	return path;
}

Text::Text() {}

Text::~Text() {}

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
	mTexture.reset();

	if (!fontUsing) {
		std::cerr << "No font selected for rendering text!\n";
		return;
	}

	SDL_Surface* surface = TTF_RenderText_Solid(fontUsing.get(), mText.c_str(), mColor);
	if (!surface) {
		std::cerr << "Failed to render text surface: " << TTF_GetError() << '\n';
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::getInstance()->getRenderer(), surface);
	SDL_FreeSurface(surface);

	if (!texture) {
		std::cerr << "Failed to create texture from surface: " << SDL_GetError() << '\n';
		return;
	}

	mTexture.reset(texture);
}


void Text::render() const {
	if (!mTexture) {
		std::cerr << "No texture to render!\n";
		return;
	}

	SDL_RenderCopy(Game::getInstance()->getRenderer(), mTexture.get(), nullptr, &mDstRect);
}