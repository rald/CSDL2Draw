#include <stdlib.h>
#include <stdbool.h>
#include <time.h>



#define GRAPHICS_IMPLEMENTATION
#include "graphics.h"



#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 256

#define P_MAX 4



SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

SDL_Texture *texture;



bool quit = false;



int px[P_MAX],py[P_MAX];
int pxi[P_MAX],pyi[P_MAX];



int main(void) {

	srand(time(NULL));

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow( "SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);


	texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);



	for(size_t i=0;i<P_MAX;i++) {
		px[i]=rand()%SCREEN_WIDTH;
		py[i]=rand()%SCREEN_HEIGHT;		
		pxi[i]=(rand()%2?1:-1)*(rand()%5+1);
		pyi[i]=(rand()%2?1:-1)*(rand()%5+1);
	}





	while( !quit ) {

		while( SDL_PollEvent( &event ) != 0 ) {
			if( event.type == SDL_QUIT ) {
				quit = true;
			}
		}

		SDL_SetRenderTarget(renderer,texture);

		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0x08 );

		SDL_RenderFillRect(renderer,&(SDL_Rect){0,0,SCREEN_WIDTH,SCREEN_HEIGHT});

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

		SDL_RenderDrawPoly(renderer,px,py,P_MAX); 

		
		for(size_t i=0;i<P_MAX;i++) {
			px[i]+=pxi[i];
			py[i]+=pyi[i];

			if(px[i]<0) { px[i]=0; pxi[i]=rand()%5+1; }
			if(py[i]<0) { py[i]=0; pyi[i]=rand()%5+1; }

			if(px[i]>=SCREEN_WIDTH) { px[i]=SCREEN_WIDTH-1; pxi[i]=-(rand()%5+1); }		

			if(py[i]>=SCREEN_HEIGHT) { py[i]=SCREEN_HEIGHT-1; pyi[i]=-(rand()%5+1); }		

		}


		SDL_SetRenderTarget(renderer,NULL);

		SDL_RenderCopy(renderer,texture,NULL,NULL);		

		SDL_RenderPresent( renderer );

	}



	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;



	SDL_Quit();

	return 0;
}


