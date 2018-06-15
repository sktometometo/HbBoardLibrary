#include "Arduino.h"
#include "Wire.h"
#include "MsTimer2.h"

#include "HACKberry.h"
#include "HbI2C.h"
#include "HbSerial.h"
#include "HbSensor.h"
//#include "HbBLE.h"

extern int HbSensorVal;
extern HACKberry Hb;

HbSensor::HbSensor()
{
    this->bus = None;
    this->pin = -1;
};

boolean HbSensor::attachBus(SensorBusType bus)
{
    switch (bus) {
        case AnalogIn:
          this->bus = bus;
          return true;
        case I2C:
          this->bus = bus;
          Wire.begin(I2C_ADDR_HAND);
          if (Hb.isLogValid) {
              Serial.println(" I2C started.");
          }
          return true;
        case SerialBus:
          this->bus = bus;
          if (Hb.isLogValid) {
              Hb.modeLog = 0; // disable if log is valid
              Hb.isLogValid = false;
          } else {
              Serial.begin(HBSERIAL_SPEED);
          }
          return true;
        case BLE:
            this->bus = bus;
  //          hbBLEInit();
            return true;
        default:
          return false;
    }

}

boolean HbSensor::setPin(int pin)
{
    if (this->bus != AnalogIn) return false;
    this->pin = pin;
    return true;
}

boolean HbSensor::init()
{
    switch(this->bus) {
        case AnalogIn:
            return true;
        case I2C:
            Wire.onRequest(requestEvent);
            Wire.onReceive(receiveEvent);
            return true;
        case SerialBus:
            MsTimer2::set(50, tickerSerial);
            MsTimer2::start();
            return true;
        case BLE:
            return true;
        default:
            return false;
    }
}

int HbSensor::read()
{
    if ( this->bus == None ||
        (this->bus == AnalogIn && this->pin == -1) ) return -1;
    int sval=0;
    switch(bus)
    {
        case AnalogIn:
            for (int i=0; i<10; i++) {
                sval += analogRead(this->pin);
            }
            sval = sval/10;
            return sval;
        case I2C:
            if (Hb.isLogValid && Hb.modeLog != 0) {
                Serial.println("read a sensor data from I2C Bus");
            }
            return HbSensorVal;
        case SerialBus:
            if (Hb.isLogValid && Hb.modeLog == 1) {
                Serial.print("read a sensor data from Serial Bus. sensor value is "); Serial.println(HbSensorVal);
            }
            return HbSensorVal;
        case BLE:
            return HbSensorVal;
        default:
            return 0;
    }
}
