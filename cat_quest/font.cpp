#include "font.h"

Font::Font(char* url, int size) {
	font = NULL;
	change(url, size);
}
Font::~Font() {
	free();
}

void Font::free() {
	if(font != NULL) {
		TTF_CloseFont(font);
		font = NULL;
	}
}

void Font::change(char* url, int size) {
	free();
	font = TTF_OpenFont(url, size);
	if(font == NULL) {
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		ok = false;
	} else {
		ok = true;
	}
}

TTF_Font* Font::getFont() {
	return font;
}