#ifndef __GAMEBASE_H__
#define __GAMEBASE_H__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <vector>
#include <typeinfo>
#include "gameobject.h"
#include "sprite.h"
#include "view.h"
#include "sound.h"
#include "font.h"
#include "object.h"
#include "sdlx.h"
#include "const.h"

class Gamebase : public GameObject {
	static SDL_Window* window;
	static SDL_Surface* screenSurface;
	static SDL_Renderer* renderer;
	SDL_Event evt;
	static int screen_width;
	static int screen_height;
	static int c_view;

	int mouse_x;
	int mouse_y;
	int mouse_button;
	static const Uint8* keys;
	static Uint8* keys_p;

	static std::vector<View*> views;
	static std::vector<Sprite*> sprites;
	static std::vector<Object*> objects;
	static std::vector<Font*> fonts;
	static std::vector<Sound*> sounds;
	static std::vector<Music*> musics;

	static bool ok;
	static Object* paused;
public:
	Gamebase(int w = 640, int h = 480);
	~Gamebase();

	static SDL_Surface* getSurface();
	static SDL_Renderer* getRenderer();
	static bool checkKey(int);
	static bool checkKeyPressed(int);
	static bool checkKeyReleased(int);
	static void clearInput();
	template<class T>
	static bool checkCollision(Object*, SDL_Point, T* = NULL, bool = false);
	template<class T>
	static bool checkCollision(Object*, bool = false);
	template<class T>
	static T* instCollision(Object*, SDL_Point, T* = NULL, bool = false);
	template<class T>
	static T* instCollision(Object*, bool = false);
	
	static Sprite* addSprite(char*, int = 0, int = 0);
	static void changeSprite(int, char*);
	static void removeSprite(int);
	static Sprite* getSprite(int);

	static Font* addFont(char*, int);
	static void changeFont(int, char*, int);
	static void removeFont(int);
	static Font* getFont(int);
	
	template<class T>
	static T* addObject(int, int, Sprite* = NULL);
	static void removeObject(int);
	static void removeObject(Object*);
	static void clearObjects();
	static Object* getObject(int);
	template<class T>
	static std::vector<T*> getObjects();
	
	static View* addView(int, int, int, int);
	static void removeView(int);
	static View* getView(int);
	static void useView(int);
	static int currentView();
	static void moveView(int, int, int);

	static Sound* addSound(char*);
	static void changeSound(int, char*);
	static void removeSound(int);
	static Sound* getSound(int);

	static Music* addMusic(char*);
	static void changeMusic(int, char*);
	static void removeMusic(int);
	static Music* getMusic(int);

	static bool on_screen(Object*, int extra = 0);
	
	static void roomStart();
	void events();
	void runObjects();
	void draw();
	void refresh();
	static void end();

	bool isOK();
	static void pause();
};

template<class T>
T* Gamebase::addObject(int x, int y, Sprite* n) {
	T* o;
	if(n == NULL) {
		o = new T(x, y);
	} else {
		o = new T(x, y, n);
	}
	if(o->isOK()) {
		objects.push_back(o);
		return o;
	}
	return NULL;
}

template<class T>
std::vector<T*> Gamebase::getObjects() {
	std::vector<T*> o;
	for(unsigned int i = 0; i < objects.size(); i++) {
		if(typeid(*objects[i]) == typeid(T)) {
			o.push_back((T*)objects[i]);
		}
	}
	return o;
}

template<class T>
bool Gamebase::checkCollision(Object* me, bool include_offscreen) {
	SDL_Point off = {0,0};
	return checkCollision<T>(me, off, NULL, include_offscreen);
}

template<class T>
bool Gamebase::checkCollision(Object* me, SDL_Point offset, T* them, bool include_offscreen)  {
	if(them == NULL) {
		for(unsigned int i = 0; i < objects.size(); i++) {
			if(typeid(*objects[i]) == typeid(T)) {
				if (on_screen(objects[i], 64) || include_offscreen) {
					if (checkCollision<T>(me, offset, dynamic_cast<T*>(objects[i]))) {
						return true;
					}
				}
			}
		}
		return false;
	} else {
		SDL_Rect m = me->get_bbox() * me->get_image_scale() + me->get_pos() + offset - *me->getSprite()->getOrigin();
		SDL_Rect t = them->get_bbox() * them->get_image_scale() + them->get_pos() - *them->getSprite()->getOrigin();
		if(m.x + m.w <= t.x) {
			return false;
		} else if(m.x >= t.x + t.w) {
			return false;
		} else if(m.y + m.h <= t.y) {
			return false;
		} else if(m.y >= t.y + t.h) {
			return false;
		}
		return true;
	}
}

template<class T>
T* Gamebase::instCollision(Object* me, bool include_offscreen) {
	SDL_Point off = {0,0};
	return instCollision<T>(me, off, NULL, include_offscreen);
}

template<class T>
T* Gamebase::instCollision(Object* me, SDL_Point offset, T* them, bool include_offscreen)  {
	if(them == NULL) {
		for(unsigned int i = 0; i < objects.size(); i++) {
			if(typeid(*objects[i]) == typeid(T)) {
				if (on_screen(objects[i], 64) || include_offscreen) {
					if (checkCollision<T>(me, offset, dynamic_cast<T*>(objects[i]))) {
						return dynamic_cast<T*>(objects[i]);
					}
				}
			}
		}
		return NULL;
	} else {
		SDL_Rect m = me->get_bbox() * me->get_image_scale() + me->get_pos() + offset - *me->getSprite()->getOrigin();
		SDL_Rect t = them->get_bbox() * them->get_image_scale() + them->get_pos() - *them->getSprite()->getOrigin();
		if(m.x + m.w < t.x) {
			return NULL;
		} else if(m.x > t.x + t.w) {
			return NULL;
		} else if(m.y + m.h < t.y) {
			return NULL;
		} else if(m.y > t.y + t.h) {
			return NULL;
		}
		return them;
	}
}

#endif