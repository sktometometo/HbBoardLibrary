#ifndef __HBI2C_H__
#define __HBI2C_H__

#define I2C_ADDR_HAND 0xA0
#define I2C_ADDR_RECIEVER 0xA1

#define I2C_CMD_SEND_SENSOR 0x01 // Masterがセンサーの値をsendする
#define I2C_CMD_SEND_BLESTATE 0x02　// MasterがBLEの状態をsendする TBD
#define I2C_CMD_READ_STATE 0x11 // Masterがhandの状態をreadする    TBD
#define I2C_CMD_READ_BAT 0x12　// Masterがbatteryの状態をreadする  TBD

#define I2C_BUFSIZE 4

void requestEvent();
void receiveEvent();

void HbI2C_transceiveState();
void HbI2C_transceiveBattery();
void HbI2C_receiveSensor(int);
void HbI2C_receiveBLEState(int);

#endif
