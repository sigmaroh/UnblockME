#ifndef LOAD_H_INCLUDED
#define LOAD_H_INCLUDED

#include"declare.h"
#include<iostream>
#include"load_func.h"
void loadwall()
{
    wall1.x=120;
    wall1.y=80;
    wall1.h=5;
    wall1.w=370;

    wall2.x=120;
    wall2.y=80;
    wall2.h=310+60;
    wall2.w=5;

    wall3.x=485;
    wall3.y=80;
    wall3.h=310+60;
    wall3.w=5;

    wall4.x=120;
    wall4.y=385+60;
    wall4.h=5;
    wall4.w=370;

    SDL_FillRect( screen, &wall4, SDL_MapRGB( screen->format, 110,160,50 ) );
    SDL_FillRect( screen, &wall3, SDL_MapRGB( screen->format, 110,160,50 ) );
    SDL_FillRect( screen, &wall2, SDL_MapRGB( screen->format, 110,160,50 ) );
    SDL_FillRect( screen, &wall1, SDL_MapRGB( screen->format, 110,160,50 ) );
}
void loadbackground()
{
    apply_surface(0,0,background1,screen);
    apply_surface(85,12,background2,screen);
    apply_surface(125,85,playingsurface,screen);
    apply_surface(485,205,gate,screen);
}
#endif
