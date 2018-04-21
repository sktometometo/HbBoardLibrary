#include <Arduino.h>

#include "Wire.h"

extern int HbSensorVal;

// I2C Buffer
uint8_t bufcmd[I2C_BUFSIZE];
uint8_t bufdata[I2C_BUFSIZE];

void requestEvent() {

    for (int i=0; i<I2C_BUFSIZE || Wire.avilable(); i++) {
        bufcmd[i] = Wire.read();
    }
    int cmd = (bufcmd[0] << 8) + bufcmd[1];

    switch (cmd) {
        case I2C_CMD_READ_STATE:
            HbI2C_transceiveState();
            break;
        case I2C_CMD_READ_BAT:
            HbI2C_transceiveBattery();
            break;
    }
}

void receiveEvent() {
    for (int i=0; i<I2C_BUFSIZE || Wire.avilable(); i++) {
        bufcmd[i] = Wire.read();
    }
    for (int i=0; i<I2C_BUFSIZE || Wire.available(); i++) {
        bufdata[i] = Wire.read();
    }

    int cmd = (bufcmd[0] << 8) + bufcmd[1];

    switch (cmd) {
        case I2C_CMD_SEND_SENSOR:
            HbI2C_receiveSensor( (bufdata[0] << 8) + bufdata[1] );
            break;
        case I2C_CMD_SEND_BLESTATE:
            HbI2C_receiveBLEState( bufdata[0] );
            break;
    }
}

void HbI2C_transceiveState() {
    // TBD
}

void HbI2C_transceiveBattery() {
    // TBD
}

void HbI2C_receiveSensor(int val) {
    HbSensorVal = val;
}

void HbI2C_receiveBLEState(int ) {
    // TBD
}
