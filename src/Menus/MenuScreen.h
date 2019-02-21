#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "State.h"
#include <iostream>
#include <SDL_ttf.h>


class MenuScreen : State
{
public:
	MenuScreen(GameState * state, SDL_Renderer * renderer, TTF_Font* Font, SDL_GameController* controller);
	~MenuScreen();

	void update(SDL_Window *window);
	void render(SDL_Renderer* renderer);

	SDL_Texture* loadFromFile(std::string path, SDL_Renderer* gRenderer);
	void freeTexture();

	SDL_Texture* init(TTF_Font* Font, std::string & text, SDL_Texture* texture, SDL_Rect & quad, int x, int y);
private:
	GameState * m_currentGameState;

	std::string play_text = "(A) Play";
	std::string online_text = "(X) Online";
	std::string options_text = "(Y) Options";
	std::string exit_text = "(B) Exit";

	std::string title_text = "UnPlayabe";
	SDL_Renderer *m_renderer;

	SDL_Texture* playtexture;
	SDL_Texture* onlinetexture;
	SDL_Texture* optiontexture;
	SDL_Texture* exittexture;

	SDL_Texture* titletexture;

	SDL_Rect playRenderQuad;
	SDL_Rect onlineRenderQuad;
	SDL_Rect optionRenderQuad;
	SDL_Rect exitRenderQuad;

	SDL_Rect titleRenderQuad;

	SDL_Texture* m_texture;
	SDL_Texture* m_texture2;
	SDL_Texture* m_drawTexture;
	int m_width;
	int m_height;
	SDL_Rect* m_sRect;
	SDL_Rect* m_dRect;

	SDL_GameController* gGameController = NULL;

	bool firstTime = true;

	int buttonTimer = 0;
	int setSecondTime = 60;
};

