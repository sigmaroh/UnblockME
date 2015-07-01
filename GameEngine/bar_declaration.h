#ifndef BAR_DECLARATION_H
#define BAR_DECLARATION_H
#include<iostream>
class bar1
{
public:
    bool select;
    int xpos;
    int ypos;
    int width;
    int height;
    friend class loadab;
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
    }
};
class bar2
{
public:
    int xpos;
    int ypos;
    int width;
    int height;
    bool select;
    friend class loadab;
    bar2():select(false){}
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
    }
};
class bar4
{
public:
    int xpos;
    int ypos;
    int width;
    int height;
    bool select;
    friend class loadab;
    bar4():select(false){}
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
    }
};
class mainbar
{
public:
    int xpos;
    int ypos;
    int width;
    int height;
    bool select;
    bool cantmoveup;
    bool cantmovedown;
    friend class loadab;
    mainbar():select(false) {}
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
    }
};
#endif
