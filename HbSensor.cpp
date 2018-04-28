#include "Arduino.h"
#include "Wire.h"

#include "Arduino.h"
#include "HbI2C.h"
#include "HbSensor.h"

int HbSensorVal;

HbSensor::HbSensor()
{
    this->bus = None;
    this->pin = -1;
};

boolean HbSensor::attachBus(SensorBusType bus)
{
    if ( bus == AnalogIn ) {
        this->bus = bus;
        return true;
    } else if ( bus == I2C ) {
        // work as slave
        this->bus = bus;
        Wire.begin(I2C_ADDR_HAND);
        return true;
    } else {
        return false;
    }
}

boolean HbSensor::setPin(int pin)
{
    if (this->bus != AnalogIn) return false;
    // TODO: pinが正しい範囲にあることを判定する
    this->pin = pin;
    return true;
}

boolean HbSensor::init()
{
    switch(this->bus)
    {
        case AnalogIn:
            return true;
        case I2C:
            Wire.onRequest(requestEvent);
            Wire.onReceive(receiveEvent);
            return true;
        default:
            return false;
    }
}

int HbSensor::read()
{
    if ( this->bus == None ||
        (this->bus == AnalogIn && this->pin == -1) ) return -1;

    int i, sval;
    switch(bus)
    {
        case AnalogIn:
            for (i=0; i<10; i++) {
                sval += analogRead(this->pin);
            }
            sval = sval/10;
            return sval;
        case I2C:
            return HbSensorVal;
    }
}
