#include"SDL/SDL.h"
#include "SDL/SDL_image.h"
#include"SDL/SDL_ttf.h"
#include"declare.h"
#include"load.h"
#include"bar_declaration.h"
#include"load_func.h"
#include"load_from_file.h"
#include"check_collison.h"
#include<string>
#include<sstream>
#include<cmath>
#include<iostream>
#include<fstream>
#include<vector>
#include<cstdlib>
using namespace std;
int dummyi=praj.i;
int dummyj=praj.j;
int dummyk=praj.k;
int dummyl=praj.l;
int dummym=praj.m;
int x,y;

void doEveryThingForBara1()
{
    while(i<dummyi)
        {


            int x1,y1;

            if (event.type == SDL_MOUSEBUTTONDOWN)
            {

                {
                    if(x>a1[i].xpos&&x<(a1[i].xpos+a1[i].width)&&y>a1[i].ypos&&y<(a1[i].ypos+a1[i].height))
                        a1[i].select = true;
                    if(y<a3[k].ypos-a1[i].height)
                    {
                        selected=true;
                        fromUp=true;
                        fromDown=false;
                    }
                    else if(y>a3[k].ypos+a3[k].height)
                    {
                        fromDown=true;
                        fromUp=false;
                    }
                }
            }

            {
                x = event.motion.x;
                y = event.motion.y;

                if(event.button.button==(SDL_BUTTON_LEFT) )
                {
                    {
                        x1=event.motion.x;
                        y1=event.motion.y;
                        for(int k1=0; k1<dummyk; k1++)
                        {
                            if (! a1[i].select) continue;

                            {
                                //if(fromUp==true and fromDown==false and y1<a3[k].ypos-a1[i].height )
                                //{   if(checkcollison(a1[i],a3[k])==false)
                                {
                                    if(fromUp==true and fromDown==false and checkcollison(a1[i],a3[k])==false )
                                    {
                                        if(y1>(a3[k].ypos))
                                        {
                                            if(checkcollison(a1[i],a3[k])==false)
                                                selected=false;

                                        }
                                        //else if(y1<(a3[k].ypos))
                                        //{
                                        //  if(checkcollison(a1[i],a3[k])==false)
                                        //selected=true;
                                        //}
                                        if(selected==true)
                                            a1[i].assign(a1[i].xpos,y1);
                                    }
                                    else if(fromDown==true and fromUp==false and checkcollison(a1[i],a3[k])==false)
                                    {
                                        a1[i].assign(a1[i].xpos,y1);
                                    }


                                }
                                //a1[i].assign(a1[i].xpos,y1);
                                //if(checkcollison(a1[i],a3[k])==true)
                                //{
                                //  y1=a3[k].ypos-a1[i].height;
                                //a1[i].assign(a1[i].xpos,y1);
                                //}
                                //}
                                // else if(fromUp==false and fromDown==true and y1>a3[k].ypos+a3[k].height )
                                //a1[i].assign(a1[i].xpos,y1);
                            }
                        }
                        for(int k1=0; k1<dummyk; k1++)
                        {
                            if(checkcollison(a1[i],a3[k1])==true)
                            {
                                {
                                    if(returnstateofcollison(a1[i],a3[k1])==6)
                                    {
                                        if(y1<a3[k1].ypos+a3[k].height)
                                        {
                                            if(fromUp==false and fromDown==true)

                                            {

                                                y1=a3[k].ypos+a3[k].height;
                                                a1[i].assign(a1[i].xpos,y1);
                                                a[i].cantmoveup=true;
                                            }
                                        }

                                    }
                                    if(returnstateofcollison(a1[i],a3[k1])==5)
                                    {




                                        if(y1>a3[k1].ypos-a1[i].height)
                                        {
                                            if(fromUp==true and fromDown==false)
                                            {

                                                y1=a3[k1].ypos-a1[i].height;
                                                a1[i].assign(a1[i].xpos,y1);
                                                a[i].cantmovedown=true;
                                            }

                                        }
                                    }
                                }
                            }

                        }

                    }

                }
            }





            a1[i].loadgivenbar();
            i++;
        }
}
