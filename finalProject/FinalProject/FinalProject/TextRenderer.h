#pragma once
#include <SDL_ttf.h>
#include <string>
#include <sstream>

using namespace std;

class TextRenderer {
public:
//Creates methods for the text renderer.
	TextRenderer(string ttfFile, int fontSize);
	virtual ~TextRenderer();

	void RenderString(SDL_Renderer* renderer, string text, int x, int y);
	void clean();

private:
//Surface, texture and font stored to so the string can be renderer to the screen.
	SDL_Surface* textSurface;
	SDL_Texture* textTexture;
	TTF_Font* font;
};
