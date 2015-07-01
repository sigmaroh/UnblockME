#include"SDL/SDL.h"
#include "SDL/SDL_image.h"
#include"SDL/SDL_ttf.h"
#include<string>
#include<sstream>
#include<cmath>
#include<iostream>
using namespace std;
const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;
const int SCREEN_BPP=32;
const int FRAMES_PER_SECOND=20;
      int movess=0;
int i1=125, j11=85, i2=185, j2=85, k1=305, l1=85,k2=365, l2=85, k3=425, l3=85,m1=125, n1=325,o1=305,p1=265,q1=125, r1=205;
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
SDL_Surface *moves=NULL;
SDL_Surface *message=NULL;

SDL_Event event;
TTF_Font *font;
SDL_Color textColor={0,0,0};
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

char* tostring(int count)
{
   char c[3];
   sprintf(c,"%d",count);
    return c;
}
SDL_Surface *surf(char* a)
{

    return TTF_RenderText_Solid( font,a, textColor);
}
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

class StringInput
{
    private:
    //The storage string
    std::string str;

    //The text surface
    SDL_Surface *text;

    public:

    //Initializes variables
    StringInput();

    //Does clean up
    ~StringInput();

    //Handles input
    void handle_input();

    //Shows the message on screen
    void show_centered(int,int);
    void showname(int i,int j)
    {
        apply_surface(i,j,text,screen);
    }
};
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
StringInput::StringInput()
{
    //Initialize the string
    str = "";

    //Initialize the surface
    text = NULL;

    //Enable Unicode
    SDL_EnableUNICODE( SDL_ENABLE );
}

StringInput::~StringInput()
{
    //Free text surface
    SDL_FreeSurface( text );

    //Disable Unicode
    SDL_EnableUNICODE( SDL_DISABLE );
}

void StringInput::handle_input()
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Keep a copy of the current version of the string
        std::string temp = str;

        //If the string less than maximum size
        if( str.length() <= 16 )
        {
            //If the key is a space
            if( event.key.keysym.unicode == (Uint16)' ' )
            {
                //Append the character
                str += (char)event.key.keysym.unicode;
            }
            //If the key is a number
            else if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) )
            {
                //Append the character
                str += (char)event.key.keysym.unicode;
            }
            //If the key is a uppercase letter
            else if( ( event.key.keysym.unicode >= (Uint16)'A' ) && ( event.key.keysym.unicode <= (Uint16)'Z' ) )
            {
                //Append the character
                str += (char)event.key.keysym.unicode;
            }
            //If the key is a lowercase letter
            else if( ( event.key.keysym.unicode >= (Uint16)'a' ) && ( event.key.keysym.unicode <= (Uint16)'z' ) )
            {
                //Append the character
                str += (char)event.key.keysym.unicode;
            }
        }

        //If backspace was pressed and the string isn't blank
        if( ( event.key.keysym.sym == SDLK_BACKSPACE ) && ( str.length() != 0 ) )
        {
            //Remove a character from the end
            str.erase( str.length() - 1 );
        }

        //If the string was changed
        if( str != temp )
        {
            //Free the old surface
            SDL_FreeSurface( text );

            //Render a new text surface
            text = TTF_RenderText_Solid( font, str.c_str(), textColor );
        }
    }
}

void StringInput::show_centered(int x,int y)
{
    //If the surface isn't blank
    if( text != NULL )
    {
        //Show the name
        apply_surface( x, y, text, screen );
    }
}

bool checkcollison(int xoffsetofA, int yoffsetofA, int widthofA, int heightofA,int xoffsetofB, int yoffsetofB, int widthofB, int heightofB )
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA =  xoffsetofA;
    rightA = xoffsetofA+widthofA;
    topA = yoffsetofA;
    bottomA =yoffsetofA+heightofA;

    leftB = xoffsetofB;
    rightB = xoffsetofB+widthofB;
    topB = yoffsetofB;
    bottomB =yoffsetofB+heightofB;

    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    return true;
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
void handlethebars()
{
    int x,y;
    int top=85;

    if( SDL_PollEvent( &event ) )
    {

    if(event.type == (SDL_MOUSEMOTION))
    {

        if(event.button.button==SDL_BUTTON_LEFT)//while
        {
        x = event.motion.x;
        y = event.motion.y;


        if(checkcollison(x,y+50,0,0,i1,j11,60,120)==true)
        {

                j11=y;
                if(checkcollison(i1,j11,60,120,m1,n1,120,60)==true)
                   {
                        if(y<n1-120)
                        j11=y;
                        if(y>n1-120)
                        {
                            j11=85+120;
                        }
                    }
                if(checkcollison(i1,j11,60,120,q1,r1,120,60)==true)
                   {
                        if(j11<=r1)
                        {
                            if(y<r1-120)
                            j11=y;
                            if(y>r1-120)
                            {
                                j11=85;
                            }
                        }

                    if(j11>=r1+60)
                    {
                        if(y<r1+60)
                        j11=r1+60;
                        if(y>r1+60)
                        j11=y;
                    }
                    }
                if(checkcollison(i1,j11,60,120,o1,p1,180,60)==true)
                   {
                        if(y<o1-120)
                        j11=y;
                        if(y>o1-120)
                        {
                            j11=125+20;
                        }
                    }
                if(checkcollison(i1,j11,60,120,120,80,370,5)==true)
                    {
                        if(y<85)
                        j11=85;
                        if(y>85)
                        j11=y;
                    }
                if(checkcollison(i1,j11,60,120,120,385+60,370,5)==true)
                    {
                        if(y<385+60-120)
                        j11=y;
                        if(y>385+60-120)
                        j11=385+60-120;
                    }
        }
        else if(checkcollison(x,y+50,0,0,i2,j2,60,120)==true)
        {
                j2=y;
                if(checkcollison(i2,j2,60,120,m1,n1,120,60)==true)
                   {
                        if(y<n1-120)
                        j2=y;
                        if(y>n1-120)
                        {
                            j2=125+80;
                        }
                }
            if(checkcollison(i2,j2,60,120,q1,r1,120,60)==true)
                   {
                        if(y<r1-120)
                        j2=y;
                        if(y>r1-120)
                        {
                            j2=85;
                        }
                }
            if(checkcollison(i2,j2,60,120,o1,p1,180,60)==true)
                   {
                        if(y<o1-120)
                        j2=y;
                        if(y>o1-120)
                        {
                            j2=125+20;
                        }
                    }

            if(checkcollison(i2,j2,60,120,120,80,370,5)==true)
                    {
                        if(y<85)
                        j2=85;
                        if(y>85)
                        j2=y;
                    }
            if(checkcollison(i2,j2,60,120,120,385+60,370,5)==true)
                    {
                        if(y<385+60-120)
                        j2=y;
                        if(y>385+60-120)
                        j2=385+60-120;
                    }
        }
        else if(checkcollison(x,y+50,0,0,k1,l1,60,180)==true)
        {
        l1=y;
            if(checkcollison(k1,l1,60,180,m1,n1,120,60)==true)
                   {
                        if(y<n1-180)
                        l1=y;
                        if(y>n1-180)
                        {
                            l1=n1-180;
                        }
                    }
            if(checkcollison(k1,l1,60,180,q1,r1,120,60)==true)
                   {
                        if(y<r1-180)
                        l1=y;
                        if(y>r1-180)
                        {
                            l1=r1-180;
                        }
                    }
                if(checkcollison(k1,l1,60,180,o1,p1,180,60)==true)
                   {
                        if(y<p1-180)
                        l1=y;
                        if(y>p1-180)
                        {
                            l1=p1-180;
                        }
                    }

                if(checkcollison(k1,l1,60,180,120,80,370,5)==true)
                    {
                        if(y<85)
                        l1=85;
                        if(y>85)
                        l1=y;
                    }
                if(checkcollison(k1,l1,60,180,120,385+60,370,5)==true)
                    {
                        if(y<385+60-180)
                        l1=y;
                        if(y>385+60-180)
                        l1=385+60-180;
                    }
        }
        else if(checkcollison(x,y+50,0,0,k2,l2,60,180)==true)
        {
        l2=y;
        if(checkcollison(k2,l2,60,180,m1,n1,120,60)==true)
                   {
                        if(y<n1-180)
                        l2=y;
                        if(y>n1-180)
                        {
                            l2=n1-180;
                        }
                    }
        if(checkcollison(k2,l2,60,180,q1,r1,120,60)==true)
                   {
                        if(y<r1-180)
                        l2=y;
                        if(y>r1-180)
                        {
                            l2=r1-180;
                        }
                    }
                if(checkcollison(k2,l2,60,180,o1,p1,180,60)==true)
                   {
                        if(y<p1-180)
                        l2=y;
                        if(y>p1-180)
                        {
                            l2=p1-180;
                        }
                    }
                if(checkcollison(k2,l2,60,180,120,80,370,5)==true)
                    {
                        if(y<85)
                        l2=85;
                        if(y>85)
                        l2=y;
                    }
            if(checkcollison(k2,l2,60,180,120,385+60,370,5)==true)
                    {
                        if(y<385+60-180)
                        l2=y;
                        if(y>385+60-180)
                        l2=385+60-180;
                    }
        }
        else if(checkcollison(x,y+50,0,0,k3,l3,60,180)==true)
        {
        l3=y;
            if(checkcollison(k3,l3,60,180,m1,n1,120,60)==true)
                   {
                        if(y<n1-180)
                        l3=y;
                        if(y>n1-180)
                        {
                            l3=n1-180;
                        }
                    }
                    if(checkcollison(k3,l3,60,180,q1,r1,120,60)==true)
                   {
                        if(y<r1-180)
                        l3=y;
                        if(y>r1-180)
                        {

                            l3=r1-180;
                        }
                    }
            if(checkcollison(k3,l3,60,180,q1,r1,120,60)==true)
                   {
                        if(y<r1-180)
                        l3=y;
                        if(y>r1-180)
                        {
                            l3=r1-180;
                        }
                    }
                if(checkcollison(k3,l3,60,180,o1,p1,180,60)==true)
                   {
                        if(y<p1-180)
                        l3=y;
                        if(y>p1-180)
                        {
                            l3=p1-180;
                        }
                    }

            if(checkcollison(k3,l3,60,180,120,80,370,5)==true)
                    {
                        if(y<85)
                        l3=85;
                        if(y>85)
                        l3=y;
                    }
            if(checkcollison(k3,l3,60,180,120,385+60,370,5)==true)
                    {
                        if(y<385+60-180)
                        l3=y;
                        if(y>385+60-180)
                        l3=385+60-180;
                    }

        }
        else if(checkcollison(x+50,y,0,0,m1,n1,120,60)==true)
        {
        m1=x;
            if(checkcollison(m1,n1,120,60,i1,j11,60,120)==true)
            {
                if(x<i1+60)
                m1=i1+60;
                if(x>m1+60)
                m1=x;
            }
            if(checkcollison(m1,n1,120,60,i2,j2,60,120)==true)
            {
                if(x<i2+60)
                m1=i2+60;
                if(x>i2+60)
                m1=x;
            }
            if(checkcollison(m1,n1,120,60,k1,l1,60,180)==true)
            {
                if(x>k1-120)
                m1=k1-120;
                if(x<k1-120)
                m1=x;
            }
            if(checkcollison(m1,n1,120,60,k2,l2,60,180)==true)
            {
                if(x>k2-120)
                m1=k2-120;
                if(x<k2-120)
                m1=x;
            }
            if(checkcollison(m1,n1,120,60,k3,l3,60,180)==true)
            {
                if(x>k3-120)
                m1=k3-120;
                if(x<k3-120)
                m1=x;
            }
            if(checkcollison(m1,n1,120,60,485,80,5,310+60)==true)
            {
                if(x+120>310+55)
                m1=310+55;
                if(x+120<310+55)
                m1=x;
            }

            if(checkcollison(m1,n1,120,60,120,80,5,310+60)==true)
            {
                if(x<125)
                m1=125;
                if(x>125)
                m1=x;
            }
        }
        else if(checkcollison(x+50,y,0,0,q1,r1,120,60)==true)
        {
        q1=x;
            if(checkcollison(q1,r1,120,60,i1,j11,60,120)==true)
            {
                if(x<i1+60)
                q1=i1+60;
                if(x>m1+60)
                q1=x;
            }
            if(checkcollison(q1,r1,120,60,i2,j2,60,120)==true)
            {
                if(x<i2+60)
                q1=i2+60;
                if(x>i2+60)
                q1=x;
            }
            if(checkcollison(q1,r1,120,60,k1,l1,60,180)==true)
            {
                if(x>k1-120)
                q1=k1-120;
                if(x<k1-120)
                q1=x;
            }
            if(checkcollison(q1,r1,120,60,k2,l2,60,180)==true)
            {
                if(x>k2-120)
                q1=k2-120;
                if(x<k2-120)
                q1=x;
            }
            if(checkcollison(q1,r1,120,60,k3,l3,60,180)==true)
            {
                if(x>k3-120)
                q1=k3-120;
                if(x<k3-120)
                q1=x;
            }
            if(checkcollison(q1,r1,120,60,485,80,5,310+60)==true)
            {
                if(x+120>310+55)
                q1=310+55;
                if(x+120<310+55)
                q1=x;
            }

            if(checkcollison(q1,r1,120,60,120,80,5,310+60)==true)
            {
                if(x<125)
                q1=125;
                if(x>125)
                q1=x;
            }
        }

        else if(checkcollison(x+50,y,0,0,o1,p1,180,60)==true)
        {
        o1=x;
            if(checkcollison(o1,p1,180,60,i1,j11,60,120)==true)
            {
                if(x<i1+60)
                o1=i1+60;
                if(x>o1+60)
                o1=x;
            }
            if(checkcollison(o1,p1,180,60,i2,j2,60,120)==true)
            {
                if(x<i2+60)
                o1=i2+60;
                if(x>i2+60)
                o1=x;
            }
            if(checkcollison(o1,p1,180,60,k1,l1,60,180)==true)
            {
                if(x>k1-180)
                o1=k1-180;
                if(x<k1-180)
                o1=x;
            }
            if(checkcollison(o1,p1,180,60,k2,l2,60,180)==true)
            {
                if(x>k2-180)
                o1=k2-180;
                if(x<k2-180)
                o1=x;
            }
            if(checkcollison(o1,p1,180,60,k3,l3,60,180)==true)
            {
                if(x>k3-180)
                o1=k3-180;
                if(x<k3-180)
                o1=x;
            }
            if(checkcollison(o1,p1,180,60,485,80,5,310+60)==true)
            {
                if(x+180<310+55)
                o1=x;
                else
                o1=310-5;
            }
            if(checkcollison(o1,p1,180,60,120,80,5,310+60)==true)
            {
                if(x<125)
                o1=125;
                if(x>125)
                o1=x;
            }
        }
        }
    }

if( event.type == SDL_MOUSEBUTTONUP )
    {
        if( event.button.button == SDL_BUTTON_LEFT )
            {

                x = event.button.x;
                y = event.button.y;

                {
                    if((j11-85)%60<=30)
                    {
                        j11=j11-((j11-85)%60);
                    }
                    if((j11-85)%60>30)
                    {
                        j11=j11+(60-((j11-85)%60));
                    }
                    if((j2-85)%60<=30)
                    {
                        j2=j2-((j2-85)%60);
                    }
                    if((j2-85)%60>30)
                    {
                        j2=j2+(60-((j2-85)%60));
                    }
                    if((l1-85)%60>30)
                    {
                        l1=l1+(60-((l1-85)%60));
                    }
                    if((l2-85)%60>30)
                    {
                        l2=l2+(60-((l2-85)%60));
                    }
                    if((l3-85)%60>30)
                    {
                        l3=l3+(60-((l3-85)%60));
                    }
                    if((l1-85)%60<=30)
                    {
                        l1=l1-((l1-85)%60);
                    }
                    if((l2-85)%60<=30)
                    {
                        l2=l2-((l2-85)%60);
                    }
                    if((l3-85)%60<=30)
                    {
                        l3=l3-((l3-85)%60);
                    }
                    if((m1-125)%60>30)
                    {
                        m1=m1+(60-((m1-125)%60));
                    }
                    if((q1-125)%60>30)
                    {
                        q1=q1+(60-((q1-125)%60));
                    }
                    if((o1-125)%60>30)
                    {
                        o1=o1+(60-((o1-125)%60));
                    }
                    if((m1-125)%60<=30)
                    {
                        m1=m1-((m1-125)%60);
                    }
                    if((q1-125)%60<=30)
                    {
                        q1=q1-((q1-125)%60);
                    }
                    if((o1-125)%60<=30)
                    {
                        o1=o1-((o1-125)%60);
                    }
                }
                movess++;

            }

        }
    }

    apply_surface(590,40,surf(tostring(movess)),screen);
               // SDL_Flip(screen);
}
void loadbar60by120()
{

    bar60by120=load_image("bar60by120.png");
    apply_surface(i1,j11,bar60by120,screen);
    apply_surface(i2,j2,bar60by120,screen);

}
void loadbar60by180()
{

    bar60by180=load_image("bar60by180.png");
    apply_surface(k1,l1,bar60by180,screen);
    apply_surface(k2,l2,bar60by180,screen);
    apply_surface(k3,l3,bar60by180,screen);
}
void loadbar120by60()
{


    bar120by60=load_image("bar120by60.png");
    apply_surface(m1,n1,bar120by60,screen);
}
void loadbar180by60()
{
    bar180by60=load_image("bar180by60.png");
    apply_surface(o1,p1,bar180by60,screen);
}
void playingbar()
{
    requiredbar=load_image("requiredbar.png");
    apply_surface(q1,r1,requiredbar,screen);
}
void loadbackground()
{
    background1=load_image("background1.png");
    background2=load_image("background2.png");
    gate=load_image("gate.png");
    playingsurface=load_image("playingsurface.png");
    apply_surface(0,0,background1,screen);
    apply_surface(85,12,background2,screen);
    loadwall();
    apply_surface(125,85,playingsurface,screen);
    apply_surface(485,205,gate,screen);
     moves = TTF_RenderText_Solid( font, "Moves", textColor );
    apply_surface(550,17,moves,screen);

}
int main(int argc, char* args[])
{

    timer fps;
    timer update;
    bool quit=false;
    bool nameEntered = false;
    bool jpt=false;
    SDL_Init(SDL_INIT_EVERYTHING);
    screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);
    TTF_Init();
    font = TTF_OpenFont( "LSANSD.TTF", 26);

    SDL_WM_SetCaption("PROJECT UNBLOCKME",NULL);
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 255, 255, 255 ) );

    StringInput name;
    message = TTF_RenderText_Solid( font, "Enter Name:", textColor );

    //While the user hasn't quit
    while( quit == false )
    {
       // while( jpt == false )
            {
                if(nameEntered == false)
               {

                 apply_surface( ( SCREEN_WIDTH - message->w ) / 2, ( ( SCREEN_HEIGHT / 2 ) - message->h ) / 2, message, screen );
                name.handle_input();

               if  ( event.key.keysym.sym == SDLK_RETURN )
               {nameEntered = true;
               }
    name.show_centered(250,150);


               }
               SDL_Flip(screen);
            }
    //if(nameEntered==true)
    //{
    fps.start();
    loadbackground();
    loadbar60by120();
    loadbar60by180();
    loadbar120by60();
    loadbar180by60();
    playingbar();
    handlethebars();
    name.showname(530,100);

    SDL_FreeSurface(bar60by120);
    SDL_FreeSurface(bar60by180);
    SDL_FreeSurface(bar120by60);
    SDL_FreeSurface(bar180by60);
    SDL_FreeSurface(background1);
    SDL_FreeSurface(background2);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(gate);
    if(fps.get_ticks()<1000/FRAMES_PER_SECOND)
        {
            //SDL_Delay((1000/FRAMES_PER_SECOND)-fps.get_ticks());
        }
    }
    SDL_Quit();
    return 0;

}
