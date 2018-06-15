#include <Arduino.h>

#include "Wire.h"
#include "HACKberry.h"
#include "HbI2C.h"

extern char HbSerialNum[];
extern int HbSensorVal;
extern int HbBatteryVal;
extern ConnectionStatus BLEStateVal;
extern HandState HandStateVal;
extern HACKberry Hb;

// I2C Buffer
uint8_t bufrx[I2C_BUFSIZE];
uint8_t buftx[I2C_BUFSIZE];

// cmd and state
int cmd; // if -1, received data is cmd;

void requestEvent() {
    if (Hb.isLogValid) {
        Serial.println(" I2C Request");
    }
    if (cmd == -1) {
        // if this section is excuted,
        // something go wrong
        Serial.println(" I2C error");
    } else {
        switch (cmd) {
            case I2C_CMD_READ_SN:
                HbI2C_transceiveSerialNumber(HbSerialNum);
                break;
            case I2C_CMD_READ_STATE:
                HbI2C_transceiveState(HandStateVal);
                break;
            case I2C_CMD_READ_BAT:
                HbI2C_transceiveBattery(HbBatteryVal);
                break;
        }
        cmd = -1;
    }
}

void receiveEvent() {
    if (Hb.isLogValid) {
        Serial.println(" I2C data received.");
    }
    for (int i=0; i<I2C_BUFSIZE || Wire.available(); i++) {
        bufrx[i] = Wire.read();
    }

    if (cmd == -1) {
        cmd = (bufrx[0] << 8) + bufrx[1];
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

void HbI2C_transceiveSerialNumber(char *sn) {
    Wire.write(sn);
}

void HbI2C_transceiveState(uint8_t val) {
    // TBD
    // TODO: bufdata繧�1繝舌う繝医〒縺､縺上ｋ
    buftx[0] = val;
    Wire.write(buftx, 1);
}

void HbI2C_transceiveBattery(uint16_t val) {
    // TBD
    // TODO: bufdata繧�2繝舌う繝医〒縺､縺上ｋ
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



