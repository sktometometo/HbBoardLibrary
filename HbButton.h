#ifndef __HBBUTTON_H__
#define __HBBUTTON_H__

#define HBBUTTON_MAX_COUNT 10
#define HBBUTTON_TIME_READ_IN_USEC 500 //[micro seconds]

#include "Arduino.h"

class HbButton
{
private:
    int pin;

public:
    HbButton(int );
    HbButton();
    void    init();
    void    attach(int );
    boolean read();
    boolean readraw();
};

#endif
