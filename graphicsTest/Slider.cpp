#include "MainHead.h"

int Slider_MoveWithMouse(SDL_Point mousePos, Slider* slide) {
	int randcalc;

	randcalc = (mousePos.y - slide->slideRailRectangle.y) / slide->spaceBetweenPositions;
	if (randcalc >= 0 && randcalc < slide->numberOfPositions) {
		slide->position = randcalc;
	}
	else if (randcalc >= slide->numberOfPositions) {
		slide->position = slide->numberOfPositions - 1;
	}
	else if (randcalc < 0) {
		slide->position = 0;
	}
	/* set position of arrow on slider */
	slide->sliderArrowRectangle.y = 50 + (slide->spaceBetweenPositions * slide->position) - (.5 * slide->sliderArrowRectangle.h);
	return 0;
}

int Slider_Render(SDL_Renderer* ren, SDL_Texture* arrow, SDL_Texture* slider, Slider* slide) {

	SDL_RenderCopy(ren, slider, NULL, &(slide->slideRailRectangle));
	SDL_RenderCopy(ren, arrow, NULL, &(slide->sliderArrowRectangle));

	return 0;
}