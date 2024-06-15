#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include<stdint.h>

#include "peqcurvlib/curves.h"
#include "peqcurvlib/sdltools.h"
#include "constants.h"

SDL_Window * wind;
SDL_Renderer * rend;

void mainloop(){
	
	Curve e = createEllipse(400,200,50,100, 0.001);
	fillCurve(&e,400,200,HEIGHT,WIDTH);
	
	SDL_Event event;
	while(true){
		while(SDL_PollEvent(&event)){
			if(event.type==SDL_QUIT){
				exit(1);
			}
		}
		
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		SDL_RenderClear(rend);
		
		drawCurve(rend,e.out,e.size_out,255,0,0,255);
		drawCurve(rend,e.in,e.size_in,0,255,0,255);
		
		SDL_RenderPresent(rend);
		SDL_Delay(1000/FPS);		
		
	}
}

void init_SDL(){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		printf("Error initializing SDL: %s\n", SDL_GetError());
		exit(1);
	}
	
	wind = SDL_CreateWindow("Ellipse",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH, HEIGHT, 0);
	
	if (!wind){
		printf("Error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}
	
	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	rend = SDL_CreateRenderer(wind, -1, render_flags);
	
	if (!rend){
		printf("Error creating renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(wind);
		SDL_Quit();
		exit(1);
	}
}

void end_SDL(){
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(wind);
	SDL_Quit();
}

int main(int argc, char* argv[]){
  init_SDL();
  mainloop();
  end_SDL();
  return 0;
}