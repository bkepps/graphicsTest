#pragma once
#include <SDL.h>
#include <string.h>


/*
struct with all key elements of a slide selector
*/
typedef struct {
	Uint8 position;
	Uint8 numberOfPositions;
	Uint16 spaceBetweenPositions;
	SDL_Rect slideRailRectangle;			//
	SDL_Rect sliderArrowRectangle;			//
	Uint8 move;								//BOOL
} Slider;

int Slider_MoveWithMouse(SDL_Point, Slider*);

int Slider_Render(SDL_Renderer*, SDL_Texture*, SDL_Texture*, Slider*);

/*BitsNBobs_append(orgin, "to be appended")*/
const char* BitsNBobs_append(char* orgin, const char *toAppend);