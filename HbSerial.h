#ifndef __HBSERIAL_H
#define __HBSERIAL_H


/*
 * ---------- Serial Communication Protocol ----------
 *
 * |-----------------|-----------|----------------------------|-----------------------|------------------|-------------------------------|
 * | CMD (bin) 1byte | TXRX Flag | Data Type Flag (bin) 1byte | Data Size (bin) 1byte | Data (bin/ascii) | end of data (1byte) 0x00 = 0  |
 * |-----------------|-----------|----------------------------|-----------------------|------------------|-------------------------------|
 *
 * In Data Section, you cannnot use 0x00 = 0, because it signs the end of a data.
 * CMD       : defined
 * Send/receive flag : 1 (send) / 2 (receive)
 * Data Flag : 1 (Byte), 2 (Ascii)
 * Data Size : i must be begger than 0
 *
 */
#define HBSERIAL_SPEED 9600
#define HBSERIAL_BUFLEN 40
#define HBSERIAL_CMDLEN 1
#define HBSERIAL_DATLEN 2

#define HBSERIAL_CMD_SEND_SENSOR            's' //0x01
#define HBSERIAL_CMD_SEND_SENSOR_DATSIZE    4
#define HBSERIAL_CMD_SEND_BLESTATE          'b' //0x02
#define HBSERIAL_CMD_SEND_BLESTATE_DATSIZE  1
#define HBSERIAL_CMD_READ_SN                'n' //0x10
#define HBSERIAL_CMD_READ_SN_DATSIZE        20
#define HBSERIAL_CMD_READ_STATE             't' //0x11
#define HBSERIAL_CMD_READ_STATE_DATSIZE     1
#define HBSERIAL_CMD_READ_BAT               'a' //0x12
#define HBSERIAL_CMD_READ_BAT_DATSIZE       4

#define HBSERIAL_TXRXFLAG_TX 't'
#define HBSERIAL_TXRXFLAG_RX 'r'

#define HBSERIAL_DATATYPEFLAG_BIN 'b'
#define HBSERIAL_DATATYPEFLAG_ASCII 'a'

#define HBSERIAL_ENDFLAG '\n'

void tickerSerial();
int readCommandFromSerial(char*);
int commandParser();
int readSensorFromSerial(char *);
int readBLEStateFromSerial(char *);
int sendSerialNumToSerial();
int sendHandStateToSerial();
int sendBatteryToSerial();

#endif
