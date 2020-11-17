#include "TextRenderer.h"

TextRenderer::TextRenderer(string ttfFile, int fontSize)
{
	if (TTF_Init() < 0) 
	{
		printf("TTF could not be initialised!", SDL_GetError());
	}
	
	font = TTF_OpenFont(ttfFile.c_str(), fontSize);

	if (font == NULL) 
	{
		printf("Unable to load the font %s! SDL Error %s\n", "arial.ttf", SDL_GetError());
	}
}

TextRenderer::~TextRenderer()
{
	SDL_FreeSurface(textSurface);
}

void TextRenderer::RenderString(SDL_Renderer* renderer, string text, int x, int y)
{
	SDL_Color textColor = { 255, 0, 0 };
	textSurface = TTF_RenderText_Solid(font, text.c_str() , textColor);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = 120;
	rect.h = 32;
	SDL_RenderCopy(renderer, textTexture, NULL, &rect);
}

