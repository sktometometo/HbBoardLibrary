#if defined(ARDUINO_BLE_Nano2)

#include <Arduino.h>

#include <nRF5x_BLE_API.h>

#include "HACKberry.h"
#include "HbBLE.h"

/*
 * External Gloval Variables
 */
extern char HbSerialNum[];
extern int HbSensorVal;
extern int HbBatteryVal;
extern ConnectionStatus BLEStateVal;
extern HandState HandStateVal;

extern HACKberry Hb;

/*
 * Global Objects
 */
BLE ble;
Ticker ticker;
ConnectionStatus blestate = Disconnected;

/*
 * BLE UUID
 */
static const uint8_t serviceHb_uuid[] = { 0xb4, 0x36, 0xa2, 0x15, 0xcf, 0x24, 0x4a, 0xe4, 0xb1, 0x0d, 0x3d, 0x84, 0x2f, 0xec, 0x6b, 0xd2 } ;// b436a215-cf24-4ae4-b10d-3d842fec6bd2
static const uint8_t serviceHb_characteristicSensor_uuid[] = { 0xbc, 0x25, 0xd7, 0xb5, 0xd9, 0x2f, 0x4d, 0x45, 0xbd, 0xaa, 0xcc, 0x0b, 0x04, 0xb8, 0x15, 0x11 } ;// bc25d7b5-d92f-4d45-bdaa-cc0b04b81511
static const uint8_t serviceHb_characteristicBattery_uuid[] = { 0x88, 0x26, 0x54, 0x7a, 0xeb, 0x87, 0x43, 0xec, 0x9a, 0x6c, 0x68, 0xde, 0x15, 0xc4, 0x6a, 0xd9 } ; // 8826547a-eb87-43ec-9a6c-68de15c46ad9
static const uint8_t serviceHb_characteristicHandState_uuid[] = { 0x3a, 0x87, 0x33, 0x8a, 0xc1, 0x09, 0x4f, 0xf6, 0x96, 0x94, 0x19, 0x75, 0xf3, 0x3e, 0xb6, 0x35 } ; // 3a87338a-c109-4ff6-9694-1975f33eb635
static const uint8_t Hb_base_uuid[] = { 0xc6, 0xe1, 0x04, 0x4a, 0x8f, 0x83, 0x4b, 0x85, 0x86, 0x44, 0x4f, 0xe2, 0x84, 0x74, 0xb7, 0x1d } ; // c6e1044a-8f83-4b85-8644-4fe28474b71d

/*
 * 通信用バッファ
 */
uint8_t deviceLocalName[BLE_BUFSIZE] = {0,};
uint8_t bufferSensorValue[BLE_BUFSIZE] = {0,};
uint8_t bufferBatteryValue[BLE_BUFSIZE] = {0,};
uint8_t bufferHandStateValue[BLE_BUFSIZE] = {0,};

/*
 * GattCharacteristic and Service
 */
 GattCharacteristic characteristicSensor(
     serviceHb_characteristicSensor_uuid,
     bufferSensorValue,
     1,
     BLE_BUFSIZE,
     GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_WRITE |
     GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_WRITE_WITHOUT_RESPONSE
 );
 GattCharacteristic characteristicBattery(
     serviceHb_characteristicBattery_uuid,
     bufferBatteryValue,
     1,
     BLE_BUFSIZE,
     GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_READ |
     GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY
 );
 GattCharacteristic characteristicHandState(
     serviceHb_characteristicHandState_uuid,
     bufferHandStateValue,
     1,
     BLE_BUFSIZE,
     GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_READ |
     GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY
 );
 GattCharacteristic *HbChars[] = {&characteristicSensor, &characteristicBattery, &characteristicHandState};
 GattService HbService(serviceHb_uuid, HbChars, sizeof(HbChars) / sizeof(GattCharacteristic *));

/*
 * functions definition
 */
void reverseByteOrder(const uint8_t* src, uint8_t* dst, int length)
{
    for ( int i=0; i<length; i++) {
        dst[i] = src[length - 1 - i];
    }
}

void disconnectionCallBack(const Gap::DisconnectionCallbackParams_t *params) {
    blestate = Disconnected;
    ble.startAdvertising();
}

void connectionCallBack(const Gap::ConnectionCallbackParams_t *params)
{
    blestate = Connected;
}

void gattServerWriteCallBack(const GattWriteCallbackParams *Handler)
{
    int buf = 0;

    if ( Handler->handle == characteristicSensor.getValueAttribute().getHandle() ) {
        int digitsize = Handler->len;
        for ( int i=0; i< digitsize; i++) {
            buf *= 10;
            buf += Handler->data[ i ];
        }
        if ( digitsize != 0 ) {
            HbSensorVal = buf;
        }

        return;
    } else if ( Handler->handle == characteristicBattery.getValueAttribute().getHandle() ) {
        return;
    } else if ( Handler->handle == characteristicHandState.getValueAttribute().getHandle() ) {
        return;
    }
}

void tickerBLEsender()
{
    if ( true ) {
        bufferBatteryValue[0] = 0;
        bufferBatteryValue[1] = 0;
    }
    ble.updateCharacteristicValue(
        characteristicBattery.getValueAttribute().getHandle(),
        bufferBatteryValue,
        2
    );

    if ( true ) {
        bufferHandStateValue[0] = 3;
    }
    ble.updateCharacteristicValue(
        characteristicHandState.getValueAttribute().getHandle(),
        bufferHandStateValue,
        1
    );
}

void hbBLEinit()
{
    uint8_t base_uuid_rev[16];

    reverseByteOrder(Hb_base_uuid, base_uuid_rev, 16);

    ble.init();
    ble.onDisconnection(disconnectionCallBack);
    ble.onConnection(connectionCallBack);
    ble.onDataWritten(gattServerWriteCallBack);

    ble.accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED);
    ble.accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LOCAL_NAME,
                                    (const uint8_t *)deviceLocalName, strlen((char *)deviceLocalName));
    ble.accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LIST_128BIT_SERVICE_IDS,
                                    (uint8_t *)base_uuid_rev, sizeof(Hb_base_uuid));
    ble.setAdvertisingType(GapAdvertisingParams::ADV_CONNECTABLE_UNDIRECTED);
    ble.addService(HbService);
    ble.setDeviceName((const uint8_t *)deviceLocalName);
    ble.setTxPower(4);
    ble.setAdvertisingInterval(ADVERTISING_INTERVAL);
    ble.setAdvertisingTimeout(0);
    ble.startAdvertising();

    ticker.attach(tickerBLEsender, 10);

    return;
}

#endif
