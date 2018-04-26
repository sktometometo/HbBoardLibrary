#include <Arduino.h>

#include "Wire.h"

extern int HbSensorVal;

// I2C Buffer
uint8_t bufrx[I2C_BUFSIZE];
uint8_t buftx[I2C_BUFSIZE];

// cmd and state
int cmd; // if -1, received data is cmd;

// state value
int BLEStateVal;

void requestEvent() {
    if (cmd == -1) {
        // if this section is excuted,
        // something go wrong
    } else {
        switch (cmd) {
            case I2C_CMD_READ_STATE:
                HbI2C_transceiveState(0);
                break;
            case I2C_CMD_READ_BAT:
                HbI2C_transceiveBattery(0);
                break;
        }
        cmd = -1;
    }
}

void receiveEvent() {
    for (int i=0; i<I2C_BUFSIZE || Wire.avilable(); i++) {
        bufrx[i] = Wire.read();
    }

    if (cmd == -1) {
        cmd = (bufcmd[0] << 8) + bufcmd[1];
    } else {
        switch (cmd) {
            case I2C_CMD_SEND_SENSOR:
                HbI2C_receiveSensor( (bufrx[0] << 8) + bufrx[1] );
                break;
            case I2C_CMD_SEND_BLESTATE:
                HbI2C_receiveBLEState( bufrx[0] );
                break;
        }
        cmd = -1;
    }
}

void HbI2C_transceiveState(uint8_t val) {
    // TBD
    // TODO: bufdataを1バイトでつくる
    buftx[0] = val
    Wire.write(buftx, 1);
}

void HbI2C_transceiveBattery(uint16_t val) {
    // TBD
    // TODO: bufdataを2バイトでつくる
    buftx[0] = val >> 8;
    buftx[1] = val;
    Wire.write(buftx, 2);
}

void HbI2C_receiveSensor(int val) {
    HbSensorVal = val;
}

void HbI2C_receiveBLEState(int val) {
    // TBD
    BLEStateVal = val;
}
