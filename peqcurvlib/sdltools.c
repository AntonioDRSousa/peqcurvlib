#include<stdint.h>
#include <SDL2/SDL.h>

void drawCurve(SDL_Renderer* rend, uint16_t curve[], int size, int c1, int c2, int c3, int trans) {
	register int i;
	SDL_SetRenderDrawColor(rend, c1, c2, c3, trans);
    for(i = 0; i < size; i+=2) {
        SDL_RenderDrawPoint(rend, curve[i], curve[i+1]);
    }
}