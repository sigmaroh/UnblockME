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
class timer
{
private:
    int startTicks;
    int pausedTicks;
    bool paused;
    bool started;

public:
    timer();
    void start();
    void stop();
    void pause();
    void unpause();
    int get_ticks();
    bool is_started();
    bool is_paused();
};

SDL_Surface *load_image(std::string filename)
{
    SDL_Surface* loadedImage=NULL;
    SDL_Surface* optimizedImage=NULL;
    loadedImage=IMG_Load(filename.c_str());

    if (loadedImage!=NULL)
    {
        optimizedImage=SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
        if( optimizedImage != NULL )
        {

            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }
    return optimizedImage;
}
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination,SDL_Rect* clip=NULL)
{
    SDL_Rect offset;
    offset.x=x;
    offset.y=y;
    SDL_BlitSurface(source,clip,destination,&offset);
}
timer::timer()
{
    startTicks=0;
    pausedTicks=0;
    paused=false;
    started=false;
}
void timer::start()
{
    started=true;
    paused=false;
    startTicks=SDL_GetTicks();

}
void timer::stop()
{
    started=false;
    paused=false;
}
void timer::pause()
{
    if ((started==true)&&(paused==false))
    {
        paused=true;
        pausedTicks=SDL_GetTicks();
    }
}
void timer::unpause()
{
    if(paused==true)
    {
        paused=false;
        startTicks=SDL_GetTicks()-pausedTicks;
        pausedTicks=0;

    }
}
class bar1;
class bar2;
class bar3;
class bar4;
class mainbar;
class loadab;
class bar1
{
public:
    bool select;
    int xpos;
    int ypos;
    int width;
    int height;
    friend class loadab;
    template<class t1,class t2>
    friend int checkcollison(t1 a[],t2 b[]);
    bar1():select(false) {}
    void assign(int a, int b)
    {
        xpos=a;
        ypos=b;
        width=60;
        height=120;
    }
    void loadgivenbar()
    {
        apply_surface(xpos,ypos,bar60by120,screen);
    }


    ~bar1()
    {
        SDL_FreeSurface(bar60by120);
    }
};
class bar2
{
public:
    int xpos;
    int ypos;
    int width;
    int height;
    friend class loadab;
    template<class t1,class t2>
    friend int checkcollison(t1 a[],t2 b[]);
    void assign(int a, int b)
    {
        xpos=a;
        ypos=b;
        width=60;
        height=180;
    }
    void loadgivenbar()
    {

        apply_surface(xpos,ypos,bar60by180,screen);
    }

    ~bar2()
    {
        SDL_FreeSurface(bar60by180);
    }
};
class bar3
{
public:
    int xpos;
    int ypos;
    int width;
    int height;
    bool select;
    bar3():select(false){}
    friend class loadab;
    template<class t1,class t2>
    friend int checkcollison(t1 a[],t2 b[]);
    void assign(int a, int b)
    {
        xpos=a;
        ypos=b;
        width=120;
        height=60;
    }
    void loadgivenbar()
    {
        apply_surface(xpos,ypos,bar120by60,screen);
    }

    ~bar3()
    {
        SDL_FreeSurface(bar120by60);
    }
};
class bar4
{
public:
    int xpos;
    int ypos;
    int width;
    int height;
    friend class loadab;
    template<class t1,class t2>
    friend int checkcollison(t1 a[],t2[]);
    void assign(int a, int b)
    {
        xpos=a;
        ypos=b;
        width=180;
        height=60;
    }
    void loadgivenbar()
    {
        apply_surface(xpos,ypos,bar180by60,screen);
    }

    ~bar4()
    {
        SDL_FreeSurface(bar180by60);
    }
};
class mainbar
{
public:
    int xpos;
    int ypos;
    int width;
    int height;
    friend class loadab;
    template<class t1,class t2>
    friend int checkcollison(t1 a[],t2 b[]);
    void assign(int a, int b)
    {
        xpos=a;
        ypos=b;
        width=180;
        height=60;
    }
    void loadgivenbar()
    {

        apply_surface(xpos,ypos,requiredbar,screen);
    }

    ~mainbar()
    {
        SDL_FreeSurface(requiredbar);
    }
};

int timer::get_ticks()
{
    if(started==true)
    {
        if(paused==true)
        {
            return pausedTicks;
        }
        else
        {
            return SDL_GetTicks()-startTicks;
        }
    }
}
bool timer::is_started()
{
    return started;
}
bool timer::is_paused()
{
    return paused;
}
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
void loadbackground()
{
    apply_surface(0,0,background1,screen);
    apply_surface(85,12,background2,screen);
    apply_surface(125,85,playingsurface,screen);
    apply_surface(485,205,gate,screen);
}

class loadab
{
public:
    int i,j,k,l,m;
    loadab()
    {
        i=0;
        j=0;
        k=0;
        l=0;
        m=0;
    }
    void load(bar1 a1[],bar2 a2[],bar3 a3[],bar4 a4[],mainbar a[])
    {
        int posx,posy,id;
        ifstream F("Level 1.txt");
        while(F)
        {
            F>>posx>>posy>>id;
            if(id==0)

            {
                a1[i].assign(posx,posy);
                a1[i].loadgivenbar();
                i++;
            }

            if(id==1)

            {

                a2[j].assign(posx,posy);
                a2[j].loadgivenbar();
                j++;
            }

            if(id==2)

            {

                a3[k].assign(posx,posy);
                a3[k].loadgivenbar();
                k++;
            }

            if(id==3)

            {
                a4[l].assign(posx,posy);
                a4[l].loadgivenbar();
                l++;

            }

            if(id==4)

            {
                a[m].assign(posx,posy);
                a[m].loadgivenbar();
                m++;
            }
        }

    }
};
template<class t1, class t2>
int checkcollison(t1 a,t2 b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA =  a.xpos;
    rightA = a.xpos+a.width;
    topA = a.ypos;
    bottomA =a.ypos+a.height;

    leftB = b.xpos;
    rightB = b.xpos+b.width;
    topB = b.ypos;
    bottomB =b.ypos+b.height;

    if( bottomA >= topB )
    {
        return 1;
    }

    if( topA <= bottomB )
    {
        return 2;
    }

    if( rightA >= leftB )
    {
        return 3;
    }

    if( leftA <= rightB )
    {
        return 4;
    }

    return 0;
}
int main(int argc, char* args[])
{

    bar1 a1[10];
    bar2 a2[10];
    bar3 a3[10];
    bar4 a4[10];
    mainbar a[10];
    timer fps;
    int i=0,j=0,k=0,l=0,m=0;
    timer update;
    int quit=0;
    SDL_Init(SDL_INIT_EVERYTHING);
    screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);
    TTF_Init();
    SDL_WM_SetCaption("GameEngine",NULL);
    loadab praj;
    praj.load(a1,a2,a3,a4,a);
    int dummyi=praj.i;
    int dummyj=praj.j;
    int dummyk=praj.k;
    int dummyl=praj.l;
    int dummym=praj.m;
    int x,y;
    init();
    int exit=0;
    int exit1=0;
    while(quit==0)
    {

        loadbackground();
        loadwall();

        i=0;
        j=0;
        k=0;
        l=0;
        m=0;
        while(i<dummyi)
        {

            a1[i].loadgivenbar();

            while( SDL_PollEvent( &event ) );
            {
                if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                        if(x>a1[i].xpos&&x<(a1[i].xpos+a1[i].width)&&y>a1[i].ypos&&y<(a1[i].ypos+a1[i].height))
                            a1[i].select = true;

                }

                if(event.type == (SDL_MOUSEMOTION))
                {
                    x = event.motion.x;
                    y = event.motion.y;

//                    if(event.button.button==(SDL_BUTTON_LEFT) )
//                    {
//
//                    }
                    if(event.type==(SDL_MOUSEMOTION) && a1[i].select)
                    {
                        int x1=event.motion.x;
                        int y1=event.motion.y;
                        a1[i].assign(a1[i].xpos,y1);
                    }
                }
                    if(event.type==(SDL_MOUSEBUTTONUP))
                    {
                        a1[i].select = false;
                    }


            }


            i++;
        }
        while(j<dummyj)
        {
            a2[j].loadgivenbar();
            j++;
        }
        while(k<dummyk)
        {
            a3[k].loadgivenbar();

            while( SDL_PollEvent( &event ) );
            {
                if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                        if(x>a3[k].xpos&&x<(a3[k].xpos+a3[k].width)&&y>a3[k].ypos&&y<(a3[k].ypos+a3[k].height))
                            a3[k].select = true;

                }

                if(event.type == (SDL_MOUSEMOTION))
                {
                    x = event.motion.x;
                    y = event.motion.y;

//                    if(event.button.button==(SDL_BUTTON_LEFT) )
//                    {
//
//                    }
                    if(event.type==(SDL_MOUSEMOTION) && a3[k].select)
                    {
                        int x1=event.motion.x;
                        int y1=event.motion.y;
                        a3[k].assign(x1,a3[k].ypos);
                    }
                }
                    if(event.type==(SDL_MOUSEBUTTONUP))
                    {
                        a3[k].select = false;
                    }
            }

            k++;
        }
        while(l<dummyl)
        {
            a4[l].loadgivenbar();
            l++;
        }
        while(m<dummym)
        {
            a[m].loadgivenbar();
            m++;
        }
        SDL_Flip(screen);
    }
    SDL_FreeSurface(screen);
    SDL_FreeSurface(message);
    SDL_FreeSurface(screen);
    SDL_Quit();
    return 0;

}

