#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <vector>

enum class Font {
	// Update getAllFonts and getPath when updating this
	MENU 
};

class Text {
private:
	static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> fonts;
	static std::vector<Font> getAllFonts();

public:
	static void initFonts();
	static std::string getPath(Font font);

private:
	std::unique_ptr<SDL_Texture*> mTexture;
	std::string mText;
	std::shared_ptr<TTF_Font> fontUsing;
	SDL_Rect mDstRect;
	SDL_Color mColor;

private:
	void free();

public:
	Text();
	~Text();

	void setFont(Font font);
	void setText(std::string text);
	void setDstRect(SDL_Rect dstRect);
	void setColor(SDL_Color color);
	void loadText();
	void render() const;
};

