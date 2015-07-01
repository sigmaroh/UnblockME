#ifndef CHECK_COLLISON_H_INCLUDED
#define CHECK_COLLISON_H_INCLUDED

template<class t1, class t2>
bool checkcollison(t1 a,t2 b)
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
template<class t2>
bool checkcollisonforwall(SDL_Rect a,t2 b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA =  a.x;
    rightA = a.x+a.w;
    topA = a.y;
    bottomA =a.y+a.h;

    leftB = b.xpos;
    rightB = b.xpos+b.width;
    topB = b.ypos;
    bottomB =b.ypos+b.height;
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

template<class t1, class t2>
int returnstateofcollison(t1 a,t2 b)
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

    if( bottomA >= topB &&  topA<topB  )
    {
        return 5;
    }

    if( topA <= bottomB )
    {
        return 6;
    }

    if( rightA > leftB )
    {
        return 7;
    }

    if( leftA < rightB )
    {
        return 8;
    }
}

#endif
