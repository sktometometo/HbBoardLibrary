#include <Arduino.h>

#include "HACKberry.h"
#include "HbSerial.h"

extern char HbSerialNum[];
extern int HbSensorVal;
extern int HbBatteryVal;
extern ConnectionStatus BLEStateVal;
extern HandState HandStateVal;

extern HACKberry Hb;

char num2ascii(uint8_t val)
{
    return '0' + val;
}

int ascii2num(char val)
{
    return val - '0';
}

int readSensorFromSerial(char *buf)
{
    char cmd = buf[0];
    char txrxFlag = buf[1];
    char datasize = buf[2];
    char *data = buf + 3;

    HbSensorVal = ascii2num(data[0]) * 1000 + ascii2num(data[1]) * 100 + ascii2num(data[2]) * 10 + ascii2num(data[3]);

    if( Hb.isLogValid && Hb.modeLog != 0 ) {
        Serial.print("Serial > Sensor data received."); Serial.println(HbSensorVal);
    }

    return 0;
}

int readBLEStateFromSerial(char *buf)
{
    char cmd = buf[0];
    char txrxFlag = buf[1];
    char dataTypeFlag = buf[2];
    char *data = buf + 3;

    BLEStateVal = (ConnectionStatus)ascii2num(data[0]);
    return 0;
}

int sendSerialNumToSerial()
{
    Serial.write(HBSERIAL_CMD_READ_SN);
    Serial.write(HBSERIAL_TXRXFLAG_RX);
    Serial.write(strlen(HbSerialNum)+1);
    Serial.write(HbSerialNum, strlen(HbSerialNum)+1);
    Serial.write(HBSERIAL_ENDFLAG);

    return 0;
}

int sendHandStateToSerial()
{
    Serial.write(HBSERIAL_CMD_READ_STATE);
    Serial.write(HBSERIAL_TXRXFLAG_RX);
    Serial.write(HBSERIAL_CMD_READ_STATE_DATSIZE);
    Serial.write((char)HandStateVal);
    Serial.write(HBSERIAL_ENDFLAG);

    return 0;
}

int sendBatteryToSerial()
{
    uint8_t buf[HBSERIAL_CMD_READ_BAT_DATSIZE];

    buf[0] = (HbBatteryVal / 1000) + '0';
    buf[1] = ((HbBatteryVal % 1000) / 100) + '0';
    buf[2] = ((HbBatteryVal % 100 ) / 10)  + '0';
    buf[3] = ((HbBatteryVal % 10)) + '0';

    Serial.write(HBSERIAL_CMD_READ_BAT);
    Serial.write(HBSERIAL_TXRXFLAG_RX);
    Serial.write(HBSERIAL_CMD_READ_BAT_DATSIZE);
    Serial.write(buf, HBSERIAL_CMD_READ_BAT_DATSIZE);
    Serial.write(HBSERIAL_ENDFLAG);

    return 0;
}

int readCommandFromSerial(char *buf)
{
    char c;
    int ind=0;
    if ( Serial.available()<=0 ) return 0;
    do {
        c = Serial.read();
        buf[ind++] = c;
    } while( c != HBSERIAL_ENDFLAG && (Serial.available() > 0) );
    
    if ( Hb.isLogValid && Hb.modeLog != 0 )
        Serial.println("received a command");
    return ind;
}

int commandParser(char *buf)
{
    switch (buf[0]) {
        case HBSERIAL_CMD_SEND_SENSOR:
            return readSensorFromSerial(buf);

        case HBSERIAL_CMD_SEND_BLESTATE:
            return readBLEStateFromSerial(buf);

        case HBSERIAL_CMD_READ_SN:
            return sendSerialNumToSerial();

        case HBSERIAL_CMD_READ_STATE:
            return sendHandStateToSerial();

        case HBSERIAL_CMD_READ_BAT:
            return sendBatteryToSerial();
 
        default:
            return 0;
    }
}

void tickerSerial()
{
    char bufser[HBSERIAL_BUFLEN];
    int buflen = 0;

    if ( (buflen = readCommandFromSerial(bufser)) == 0 )
        return;
    commandParser(bufser);
}
