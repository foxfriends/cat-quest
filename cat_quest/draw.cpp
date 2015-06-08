#include "draw.h"

SDL_Color Draw::c_color = {0,0,0,255};

void Draw::setColor(int r, int g, int b, int a) {
	c_color.r = r;
	c_color.g = g;
	c_color.b = b;
	c_color.a = a;
	SDL_SetRenderDrawColor(Gamebase::getRenderer(), r, g, b, a);
}
void Draw::setColor(SDL_Color color) {
	c_color.r = color.r;
	c_color.g = color.g;
	c_color.b = color.b;
	c_color.a = color.a;
	SDL_SetRenderDrawColor(Gamebase::getRenderer(), c_color.r, c_color.g, c_color.b, c_color.a);
}

void Draw::sprite_sheet(Sprite* spr, int x, int y, int w, int h) {
	SDL_Rect* dest = NULL;
	if(w != -1) {
		dest = new SDL_Rect();
		dest->x = x;
		dest->y = y;
		dest->w = w;
		dest->h = h;
	}
	SDL_RenderCopy(Gamebase::getRenderer(), spr->getTexture(), NULL, dest);
	delete dest;
}
void Draw::sprite(Sprite* spr, int n, int x, int y, int w, int h, double angle) {
	SDL_Rect* dest = new SDL_Rect(*spr->getFrame(n));
	dest->x = x - spr->getOrigin()->x;
	dest->y = y - spr->getOrigin()->y;
	if(w != -1) {
		dest->w = w;
		dest->h = h;
	}

	SDL_Rect * view = new SDL_Rect();
	int v = Gamebase::currentView();
	view->w = 0;
	view->h = 0;
	if(v != -1) {
		view->x = Gamebase::getView(v)->getView()->x;
		view->y = Gamebase::getView(v)->getView()->y;
	} else {
		view->x = 0;
		view->y = 0;
	}
	SDL_RenderCopyEx(Gamebase::getRenderer(), spr->getTexture(), spr->getFrame(n), &((*dest) - (*view)), angle, spr->getOrigin(), SDL_FLIP_NONE);
	delete dest;
}

void Draw::rect(int x, int y, int w, int h, bool fill) {
	SDL_Rect rect = {x, y, w, h};
	if(fill) {
		SDL_RenderFillRect(Gamebase::getRenderer(), &rect);
	} else {
		SDL_RenderDrawRect(Gamebase::getRenderer(), &rect);
	}
}
void Draw::rect(SDL_Rect rect, bool fill) {
	if(fill) {
		SDL_RenderFillRect(Gamebase::getRenderer(), &rect);
	} else {
		SDL_RenderDrawRect(Gamebase::getRenderer(), &rect);
	}
}
void Draw::line(int x1, int y1, int x2, int y2) {
	SDL_RenderDrawLine(Gamebase::getRenderer(), x1, y1, x2, y2);
}
void Draw::point(int x, int y) {
	SDL_RenderDrawPoint(Gamebase::getRenderer(), x, y);
}
void Draw::text(int x, int y, char* str, Font* font) {
	SDL_Surface* ts = TTF_RenderText_Solid(font->getFont(), str, c_color);
	if(ts == NULL) { 
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	} else {
		if (Gamebase::getRenderer() != NULL) {
			SDL_Texture *tt = SDL_CreateTextureFromSurface(Gamebase::getRenderer(), ts);
			SDL_Rect *dest = NULL;
			if (tt == NULL) {
				printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			}
			else {
				dest = new SDL_Rect();
				dest->x = x;
				dest->y = y;
				dest->w = ts->w;
				dest->h = ts->h;
			}
			if (ts != NULL) {
				SDL_FreeSurface(ts);
				ts = NULL;
			}
			SDL_RenderCopy(Gamebase::getRenderer(), tt, NULL, dest);
			SDL_DestroyTexture(tt);
			tt = NULL;
			delete dest;
		}
	}
}

void Draw::clear(int r, int g, int b) {
	SDL_SetRenderDrawColor(Gamebase::getRenderer(), r, g, b, 255);
	SDL_RenderClear(Gamebase::getRenderer());
	setColor(c_color);
}