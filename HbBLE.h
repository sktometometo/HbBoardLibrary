#ifndef __HBBLE_H__
#define __HBBLE_H__

#include <Arduino.h>
#include <nRF5x_BLE_API.h>

#define BLE_BUFSIZE 20

#define ADVERTISING_INTERVAL 160
#define TICKER_TIMER         1000000

/*
 * function declaration
 */
void reverseByteOrder(const uint8_t* , uint8_t* , int);
//int strlen(const char*);

void disconnectionCallBack(const Gap::DisconnectionCallbackParams_t *);
void connectionCallBack(const Gap::ConnectionCallbackParams_t *);
void gattServerWriteCallBack(const GattWriteCallbackParams *);
void tickerBLEsender();

void hbBLEinit();

#endif
