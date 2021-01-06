#include "TextRenderer.h"

//Initialises the TTF, if it cannot be initialised an error message is shown in the console.
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

//The deconstructor releases the text surface to free memory.
TextRenderer::~TextRenderer()
{
	SDL_FreeSurface(textSurface);
}

//Renderers string to the window at the position given.
//A colour is set and then a textSurface is created using the strong given in the parameter, this is then used to create a texture and is copied to the renderer.
void TextRenderer::RenderString(SDL_Renderer* renderer, string text, int x, int y)
{
	SDL_Color textColor = { 255, 0, 0 };
	textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = 120;
	rect.h = 32;
	SDL_RenderCopy(renderer, textTexture, NULL, &rect);
	SDL_DestroyTexture(textTexture);
}

//Destroys texture to free memory.
void TextRenderer::clean()
{
	SDL_DestroyTexture(textTexture);
}

