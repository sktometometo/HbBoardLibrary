#ifndef __HBI2C_H__
#define __HBI2C_H__

#define I2C_ADDR_HAND 0xA0
#define I2C_ADDR_RECIEVER 0xA1

#define I2C_CMD_SEND_SENSOR 0x01 // Master縺後そ繝ｳ繧ｵ繝ｼ縺ｮ蛟､繧痴end縺吶ｋ
#define I2C_CMD_SEND_BLESTATE 0x02 // Master縺沓LE縺ｮ迥ｶ諷九ｒsend縺吶ｋ TBD
#define I2C_CMD_READ_SN 0x10
#define I2C_CMD_READ_STATE 0x11 // Master縺敬and縺ｮ迥ｶ諷九ｒread縺吶ｋ    TBD
#define I2C_CMD_READ_BAT 0x12 // Master縺恵attery縺ｮ迥ｶ諷九ｒread縺吶ｋ  TBD

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

#endif
