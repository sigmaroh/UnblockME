#ifndef LOAD_FROM_FILE_H_INCLUDED
#define LOAD_FROM_FILE_H_INCLUDED
#include<iostream>
#include<fstream>
using namespace std;
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
        ifstream F("Level 10.txt");
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
#endif
