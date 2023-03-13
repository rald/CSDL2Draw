#include <SDL2/SDL.h>

#include <stdbool.h>



#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 256

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

bool quit = false;



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

int main(void) {

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow( "SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );



	while( !quit ) {

		while( SDL_PollEvent( &event ) != 0 ) {
			if( event.type == SDL_QUIT ) {
				quit = true;
			}
		}

		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

		SDL_RenderClear( renderer );

		SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );



		int x=4,y=4,size=32,gap=4;

		SDL_RenderDrawPoint(renderer,x+size/2,y+size/2);

		x+=size+gap;

		SDL_RenderDrawLine(renderer,x,y,x+size,y+size);

		x+=size+gap;

		{
			SDL_Rect rect= {x,y,size,size};
			SDL_RenderDrawRect(renderer,&rect);
		}

		x+=size+gap;

		{
			SDL_Rect rect= {x,y,size,size};
			SDL_RenderFillRect(renderer,&rect);
		}

		x+=size+gap;
		SDL_RenderDrawCircle(renderer,x+size/2,y+size/2,size/2);

		x+=size+gap;
		SDL_RenderFillCircle(renderer,x+size/2,y+size/2,size/2);

		SDL_RenderPresent( renderer );

	}

	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	SDL_Quit();

	return 0;
}


