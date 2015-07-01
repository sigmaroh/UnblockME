#ifndef DECLARE_H_INCLUDED
#define DECLARE_H_INCLUDED
#include"declare.h"
#include<iostream>
#include"load_func.h"
const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;
const int SCREEN_BPP=32;
const int FRAMES_PER_SECOND=20;
SDL_Surface *message=NULL;
SDL_Surface *screen=NULL;
SDL_Surface *dot=NULL;
SDL_Surface *background1=NULL;
SDL_Surface *background2=NULL;
SDL_Surface *gate=NULL;
SDL_Surface *playingsurface=NULL;
SDL_Surface *bar60by120=NULL;
SDL_Surface *bar60by180=NULL;
SDL_Surface *bar120by60=NULL;
SDL_Surface *bar180by60=NULL;
SDL_Surface *requiredbar=NULL;
SDL_Event event;
SDL_Color textColor= {0,0,0};
SDL_Rect wall1;
SDL_Rect wall2;
SDL_Rect wall3;
SDL_Rect wall4;

void init()
{
    background1=load_image("background1.png");
    background2=load_image("background2.png");
    gate=load_image("gate.png");
    playingsurface=load_image("playingsurface.png");
    bar60by120=load_image("bar60by120.png");
    requiredbar=load_image("requiredbar.png");
    bar60by180=load_image("bar60by180.png");
    bar120by60=load_image("bar120by60.png");
    bar180by60=load_image("bar180by60.png");
}

#endif
