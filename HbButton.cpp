#include "Arduino.h"
#include "HbButton.h"

HbButton::HbButton() {
}

HbButton::HbButton(int pin)
{
    this->pin = pin;
    this->init();
}

void HbButton::init()
{
    pinMode( this->pin, INPUT_PULLUP);
}

void HbButton::attach(int pin)
{
    this->pin = pin;
    pinMode( this->pin, INPUT_PULLUP);
}

boolean HbButton::read()
{
    int count = 0;
    int time_delay = HBBUTTON_TIME_READ_IN_USEC / HBBUTTON_MAX_COUNT;

    for (int i=0; i<HBBUTTON_MAX_COUNT; i++) {
        if ( this->readraw() == LOW ) count++;
        delayMicroseconds(time_delay);
    }
    
    if (count == HBBUTTON_MAX_COUNT) return LOW;
    else return HIGH;
}

boolean HbButton::readraw()
{
    if ( digitalPinToPort(pin) == NOT_A_PIN ) {
        return analogRead(this->pin) > 512 ? HIGH : LOW;
    } else {
        return digitalRead(this->pin);
    }
}
