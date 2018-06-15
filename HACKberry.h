#ifndef __HACKBERRY_H__
#define __HACKBERRY_H__

#define PERIOD_CONTROL_IN_MILISEC 50

#include <Arduino.h>
#include <Servo.h>

#include "HbButton.h"
#include "HbSensor.h"

typedef enum {
    NONE,
    Mk1Right,
    Mk1Left,
    Mk2Right,
    Mk2Left,
    SizeSRight,
    SizeSLeft,
    SizeMRight,
    SizeMLeft,
    Mk2RightBLE,
    Mk2LeftBLE
} BoardType;

class HACKberry {
public:

// member values
    // Objects
    BoardType board;
    HbButton  ButtonCalib;
    HbButton  ButtonExtra;
    HbButton  ButtonThumb;
    HbButton  ButtonOther;
    HbSensor  Sensor;
    Servo     ServoIndex;
    Servo     ServoOther;
    Servo     ServoThumb;

    // Serial Number
    String serialNum = "HACKberry";

    // Status
    // TBI: init them in init();
    boolean isThumbOpen=true;
    boolean isOtherLock=false;
    boolean isSensorReversed=false;

    // Log
    boolean isLogValid=false;
    int modeLog = 0;

    // status variables
    int ControlInput;
    int CurrentAngle;
    int CurrentAngularVelocity;
    int PreAngle;
    int PreAngularVelocity; // Not In Use
    int TargetAngleThumb;
    int TargetAngleIndex;
    int TargetAngleOther;
    int TargetAngularVelocityThumb; // Not In Use
    int TargetAngularVelocityIndex; // Not In Use
    int TargetAngularVelocityOther; // Not In Use

    //
    int BLEStateVal;

    // for Sensor
    int SensorValue;

    // constatnt
    const int NormalizedAngleMaxPosition = 100;
    const int NormalizedAngleMinPosition = 0;
    const int NormalizedSensorMax = 100;
    const int NormalizedSensorMin = 0;

    // Parameters for Sensor
    int MinSensorRangeStop; // Minimum Value of Range for finger not moving
    int MaxSensorRangeStop;
    int SensorRangeSaturation;
    int MinSensorValue;
    int MaxSensorValue;

    // Parameters for Servo Control
    // MinReverseSpeed < MaxReverseSpeed < MinForwardSpeed < MaxForwardSpeed
    int MaxOpenSpeed;
    int MinOpenSpeed;
    int MaxCloseSpeed;
    int MinCloseSpeed;

    int AngleThumbMin;
    int AngleThumbMax;
    int AngleIndexMin;
    int AngleIndexMax;
    int AngleOtherMin;
    int AngleOtherMax;

    int AngleThumbOpen;
    int AngleThumbClose;
    int AngleIndexOpen;
    int AngleIndexClose;
    int AngleOtherOpen;
    int AngleOtherClose;

    // Callback functions for switch
    // Not In Use
    void (*CalibCB)();
    void (*ExtraCB)();
    void (*ThumbCB)();
    void (*OtherCB)();

    // functions
    HACKberry();
    HACKberry(BoardType);

    void setSerialNum(char*);
    void setSerialNum(String);
    void setBoardType(BoardType);
    void setAngleIndex(int , int );
    void setAngleOther(int , int );
    void setAngleThumb(int , int );
    void setSpeedRange(int , int , int , int );
    void setSensorThreshold(int , int , int);

    void init();
    void readSensor();
    void calcControlInput();
    void calcPosition();
    void controlServo();
    void calibration(unsigned long);

    void initLog(int);

};

void outputLog(HACKberry *);

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
