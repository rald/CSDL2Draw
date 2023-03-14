#ifndef GRAPHICS_H
#define GRAPHICS_H



#include <SDL2/SDL.h>



void SDL_RenderDrawCircle(SDL_Renderer *renderer,int x0,int y0,int r);

void SDL_RenderFillCircle(SDL_Renderer *renderer,int x0,int y0,int r);

void SDL_RenderDrawPoly(SDL_Renderer *renderer,int *x,int *y,size_t n);



#ifdef GRAPHICS_IMPLEMENTATION



void SDL_RenderDrawCircle(SDL_Renderer *renderer,int x0,int y0,int r) {
    int f=1-r;
    int ddfx=0;
    int ddfy=-2*r;
    int x=0;
    int y=r;

    SDL_RenderDrawPoint(renderer,x0,y0+r);
    SDL_RenderDrawPoint(renderer,x0,y0-r);
    SDL_RenderDrawPoint(renderer,x0+r,y0);
    SDL_RenderDrawPoint(renderer,x0-r,y0);

    while(x<y) {
        if(f>=0) {
            y--;
            ddfy+=2;
            f+=ddfy;
        }
        x+=1;
        ddfx+=2;
        f+=ddfx+1;

        SDL_RenderDrawPoint(renderer,x0+x,y0+y);
        SDL_RenderDrawPoint(renderer,x0-x,y0+y);
        SDL_RenderDrawPoint(renderer,x0+x,y0-y);
        SDL_RenderDrawPoint(renderer,x0-x,y0-y);
        SDL_RenderDrawPoint(renderer,x0+y,y0+x);
        SDL_RenderDrawPoint(renderer,x0-y,y0+x);
        SDL_RenderDrawPoint(renderer,x0+y,y0-x);
        SDL_RenderDrawPoint(renderer,x0-y,y0-x);
    }
}



void SDL_RenderFillCircle(SDL_Renderer *renderer,int x0,int y0,int r) {
    int f=1-r;
    int ddfx=0;
    int ddfy=-2*r;
    int x=0;
    int y=r;

    SDL_RenderDrawLine(renderer,x0,y0+r,x0,y0-r);
    SDL_RenderDrawLine(renderer,x0,y0-r,x0,y0+r);
    SDL_RenderDrawLine(renderer,x0+r,y0,x0-r,y0);
    SDL_RenderDrawLine(renderer,x0-r,y0,x0+r,y0);
    SDL_RenderDrawLine(renderer,x0-r,y0,x0+r,y0);

    while(x<y) {
        if(f>=0) {
            y--;
            ddfy+=2;
            f+=ddfy;
        }
        x+=1;
        ddfx+=2;
        f+=ddfx+1;

        SDL_RenderDrawLine(renderer,x0+x,y0+y,x0-x,y0+y);
        SDL_RenderDrawLine(renderer,x0-x,y0+y,x0+x,y0+y);
        SDL_RenderDrawLine(renderer,x0+x,y0-y,x0-x,y0-y);
        SDL_RenderDrawLine(renderer,x0-x,y0-y,x0+x,y0-y);
        SDL_RenderDrawLine(renderer,x0+y,y0+x,x0-y,y0+x);
        SDL_RenderDrawLine(renderer,x0-y,y0+x,x0+y,y0+x);
        SDL_RenderDrawLine(renderer,x0+y,y0-x,x0-y,y0-x);
        SDL_RenderDrawLine(renderer,x0-y,y0-x,x0+y,y0-x);
    }
}



void SDL_RenderDrawPoly(SDL_Renderer *renderer,int *x,int *y,size_t n) {
	for(size_t i=0;i<n-1;i++) {
		SDL_RenderDrawLine(renderer,x[i],y[i],x[i+1],y[i+1]);
	}
	SDL_RenderDrawLine(renderer,x[n-1],y[n-1],x[0],y[0]);
}



#endif /* GRAPHICS_IMPLEMENTATION */



#endif /* GRAPHICS_H */


