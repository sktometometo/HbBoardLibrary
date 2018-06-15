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
    if ( isPinPort(pin) ) pinMode( this->pin, INPUT_PULLUP);
}

void HbButton::attach(int pin)
{
    this->pin = pin;
    if ( isPinPort(pin) ) pinMode( this->pin, INPUT_PULLUP);
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
    if ( !isPinPort(pin) ) {
        return analogRead(this->pin) > 512 ? HIGH : LOW;
    } else {
        return digitalRead(this->pin);
    }
}

boolean isPinPort(int pin)
{
#if defined(ARDUINO_AVR_NANO) // for mk2
    return (pin != A6) && (pin != A7) ? true : false;
#elif defined(ARDUINO_AVR_A_STAR_32U4) // for Size S and M.  leonard compatible?
    return (pin >= 0) ? true : false;
#endif
    return true;
}

