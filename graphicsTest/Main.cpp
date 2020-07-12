#include "MainHead.h"
#include "Cleanup.h"

int updateGraph(SDL_Renderer *ren, SDL_Texture *grph, Uint32* width, Uint32* height, Uint32* ctrlWidth) {
	SDL_Rect GraphWinSize;					//set size of scope screen
	GraphWinSize.x = 5;						//render to top left corner
	GraphWinSize.y = 5;						//with 5px padding

	if ((*width - *ctrlWidth) * .8 > (*height - 10)) {
		GraphWinSize.h = *height - 10;
		GraphWinSize.w = GraphWinSize.h * 1.25;
	}
	else {
		GraphWinSize.w = *width - *ctrlWidth;			//size of graph window
		GraphWinSize.h = GraphWinSize.w * .8;			//
	}

									//render scope screen
	SDL_RenderCopy(ren, grph, NULL, &GraphWinSize);
	

	return 0;
}

int main(int argc, char* argv[])
{
	const char* title = "Oscilloscope V0.0.0005";
	Uint32* width = new Uint32 (900);
	Uint32* height = new Uint32 (500);
	Uint32* ctrlWidth = new Uint32(300);
	bool* quit = new bool (false);
	int randcalc;
	char* basePath = SDL_GetBasePath();		//get file path for .exe


	const char* returnedFilePath = NULL;


	int* tSlidepos = new int (0);
	int tSlidenop = 15;
	bool tArrowmove = false;

	int tdistbtwnPos = 200 / tSlidenop;

	SDL_Point mousePos;

	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *win = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, *width, *height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	Uint32* windowID = new Uint32 (SDL_GetWindowID(win));
		
	returnedFilePath = BitsNBobs_append(basePath, "Resources\\OscopeGraph.bmp");//load scope background &
	SDL_Surface *grphsurf = SDL_LoadBMP(returnedFilePath);						//create texture from it
	free((void*)returnedFilePath);
	SDL_Texture *grph = SDL_CreateTextureFromSurface(ren, grphsurf);			//
	SDL_FreeSurface(grphsurf);													//

	returnedFilePath = BitsNBobs_append(basePath, "Resources\\SliderArrow.bmp");			//load arrow for sliders to texture
	SDL_Surface *sliderArrowsurf = SDL_LoadBMP(returnedFilePath);
	free((void*)returnedFilePath);
	SDL_Texture *sliderArrow = SDL_CreateTextureFromSurface(ren, sliderArrowsurf);
	SDL_FreeSurface(sliderArrowsurf);

	returnedFilePath = BitsNBobs_append(basePath, "Resources\\SliderRail.bmp");				//load rail arrow slides on
	SDL_Surface *sliderRailsurf = SDL_LoadBMP(returnedFilePath);
	free((void*)returnedFilePath);
	SDL_Texture *sliderRail = SDL_CreateTextureFromSurface(ren, sliderRailsurf);
	SDL_FreeSurface(sliderRailsurf);

	SDL_SetRenderDrawColor(ren, 235, 235, 235, 255);
	SDL_RenderClear(ren);

	updateGraph(ren, grph, width, height, ctrlWidth);

	Slider* timeScaleSelect = new Slider;
	timeScaleSelect->position = 0;
	timeScaleSelect->numberOfPositions = 15;
	timeScaleSelect->spaceBetweenPositions = 200 / timeScaleSelect->numberOfPositions;
	timeScaleSelect->slideRailRectangle.x = *width - 52;
	timeScaleSelect->slideRailRectangle.y = 50;
	timeScaleSelect->slideRailRectangle.w = 8;
	timeScaleSelect->slideRailRectangle.h = (timeScaleSelect->numberOfPositions - 1) * timeScaleSelect->spaceBetweenPositions;
	timeScaleSelect->sliderArrowRectangle.w = 20;
	timeScaleSelect->sliderArrowRectangle.h = 15;
	timeScaleSelect->sliderArrowRectangle.x = timeScaleSelect->slideRailRectangle.x - 9;
	timeScaleSelect->sliderArrowRectangle.y = 50 + (timeScaleSelect->spaceBetweenPositions * timeScaleSelect->position) - (.5 * timeScaleSelect->sliderArrowRectangle.h);

	timeScaleSelect->move = false;

	while(!*quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				*quit = true;
				break;
			case SDL_WINDOWEVENT:
				switch (event.window.event) {
				case SDL_WINDOWEVENT_SIZE_CHANGED:
					*width = event.window.data1;
					*height = event.window.data2;

					/* update all elements who's position is changed by a window resize */

					timeScaleSelect->slideRailRectangle.x = *width - 50;
					timeScaleSelect->sliderArrowRectangle.x = timeScaleSelect->slideRailRectangle.x - 9;
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					SDL_GetMouseState(&mousePos.x, &mousePos.y);
					if (SDL_PointInRect(&mousePos, &timeScaleSelect->slideRailRectangle) || SDL_PointInRect(&mousePos, &timeScaleSelect->sliderArrowRectangle))
						timeScaleSelect->move = true;
				}

				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT) {
					SDL_GetMouseState(&mousePos.x, &mousePos.y);
					if (timeScaleSelect->move) {
						timeScaleSelect->move = false;
						Slider_MoveWithMouse(mousePos, timeScaleSelect);
					}
						
				}
				
				break;
			case SDL_MOUSEMOTION:
				mousePos.y = event.motion.y;
				if (timeScaleSelect->move)
					Slider_MoveWithMouse(mousePos, timeScaleSelect);
				break;
			}
		}
		SDL_RenderClear(ren);
		updateGraph(ren, grph, width, height, ctrlWidth);
		Slider_Render(ren, sliderArrow, sliderRail, timeScaleSelect);
		SDL_RenderPresent(ren);
	}
	cleanup(ren, win);
	SDL_Quit();

	return 0;
}