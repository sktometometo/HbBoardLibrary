#ifndef __HBI2C_H__
#define __HBI2C_H__

#define I2C_ADDR_HAND 0xA0
#define I2C_ADDR_RECIEVER 0xA1

#define I2C_CMD_SEND_SENSOR 0x01 // Masterがセンサーの値をsendする
#define I2C_CMD_SEND_BLESTATE 0x02 // MasterがBLEの状態をsendする TBD
#define I2C_CMD_READ_SN 0x10
#define I2C_CMD_READ_STATE 0x11 // Masterがhandの状態をreadする    TBD
#define I2C_CMD_READ_BAT 0x12 // Masterがbatteryの状態をreadする  TBD

#define I2C_BUFSIZE 4

/*
 *
 * ---------- functions for I2C ----------
 *
 */
void requestEvent();
void receiveEvent();

void HbI2C_transceiveState(uint8_t);
void HbI2C_transceiveBattery(uint16_t);
void HbI2C_transceiveSerialNumber(char*);
void HbI2C_receiveSensor(int);
void HbI2C_receiveBLEState(int);

/*
 *
 * ---------- Type Declarations ----------
 *
 */
typedef enum
{
    Disconnected = 0,
    Connected    = 1,
    Connecting   = 2,
    Unknown      = 3
} ConnectionStatus;

typedef enum {
    NotInitialized = 0,
    Calibrating    = 1,
    WorkingWell    = 2,
    SomethingWrong = 3
} HandState;

#endif
