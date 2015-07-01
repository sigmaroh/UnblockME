
#include"SDL/SDL.h"
#include "SDL/SDL_image.h"
#include"SDL/SDL_ttf.h"
#include<string>
#include<sstream>
#include<cmath>
#include<iostream>
#include<fstream>
#include<vector>
#include<cstdlib>
using namespace std;
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
