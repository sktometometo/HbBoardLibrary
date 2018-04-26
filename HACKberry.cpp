#include "Arduino.h"
#include "HACKberry.h"

HACKberry::HACKberry() {
    this->board = NONE;
}

HACKberry::HACKberry(BoardType board) {
    this->board = board;
}

void HACKberry::setBoardType(BoardType board) {
    this->board = board;
}

void HACKberry::setAngleIndex(int MinAngle, int MaxAngle) {
    this->AngleIndexMin = MinAngle;
    this->AngleIndexMax = MaxAngle;
}

void HACKberry::setAngleOther(int MinAngle, int MaxAngle) {
    this->AngleOtherMin = MinAngle;
    this->AngleOtherMax = MaxAngle;
}

void HACKberry::setAngleThumb(int MinAngle, int MaxAngle) {
    this->AngleThumbMin = MinAngle;
    this->AngleThumbMax = MaxAngle;
}

void HACKberry::setSpeedRange(int MaxReverseSpeed, int MinReverseSpeed, int MinForwardSpeed, int MaxForwardSpeed ) {
    this->MaxForwardSpeed = MaxForwardSpeed;
    this->MinForwardSpeed = MinForwardSpeed;
    this->MaxReverseSpeed = MaxReverseSpeed;
    this->MinReverseSpeed = MinReverseSpeed;
}

// set Range of Sensor Value For Zero speed (0~100)
void HACKberry::setSensorThreshold(int Min, int Middle, int Max) {
    this->MinSensorRangeStop = Min;
    this->MaxSensorRangeStop = Middle;
    this->SensorRangeSaturation = Max;
}

void HACKberry::setCalibCallBack(void (*func_cb)(void*)) {
    this->CalibCB = func_cb;
}

void HACKberry::setExtraCallBack(void (*func_cb)(void*)) {
    this->ExtraCB = func_cb;
}

void HACKberry::setThumbCallBack(void (*func_cb)(void*)) {
    this->ThumbCB = func_cb;
}

void HACKberry::setOtherCallBack(void (*func_cb)(void*)) {
    this->OtherCB = func_cb;
}

void HACKberry::init() {

    switch (board) {
        case Mk1Right:

            this->ButtonCalib.attach(A6,true,true);
            this->ButtonExtra.attach(A5,true,true);
            this->ButtonThumb.attach(A4,true,true);
            this->ButtonOther.attach(A3,true,true);

            this->ServoIndex.attach(3);
            this->ServoOther.attach(5);
            this->ServoThumb.attach(6);

            this->Sensor.attachBus(AnalogIn);
            this->Sensor.setPin(A0);
            this->Sensor.init();

            this->AngleThumbOpen  = this->AngleThumbMax;
            this->AngleThumbClose = this->AngleThumbMin;
            this->AngleIndexOpen  = this->AngleIndexMax;
            this->AngleIndexClose = this->AngleIndexMin;
            this->AngleOtherOpen  = this->AngleOtherMax;
            this->AngleOtherClose = this->AngleOtherMin;
            break;

        case Mk1Left:

            this->ButtonCalib.attach(11,true,true);
            this->ButtonExtra.attach(10,true,true);
            this->ButtonThumb.attach(8,true,true);
            this->ButtonOther.attach(7,true,true);

            this->ServoIndex.attach(3);
            this->ServoOther.attach(5);
            this->ServoThumb.attach(6);

            this->Sensor.attachBus(AnalogIn);
            this->Sensor.setPin(A0);
            this->Sensor.init();

            this->AngleThumbOpen  = this->AngleThumbMin;
            this->AngleThumbClose = this->AngleThumbMax;
            this->AngleIndexOpen  = this->AngleIndexMin;
            this->AngleIndexClose = this->AngleIndexMax;
            this->AngleOtherOpen  = this->AngleOtherMin;
            this->AngleOtherClose = this->AngleOtherMax;
            break;

        case Mk2Right:

            this->ButtonCalib.attach(A6,false,true);
            this->ButtonExtra.attach(A7,false,true);
            this->ButtonThumb.attach(A0,false,true);
            this->ButtonOther.attach(10,true,true);

            this->ServoIndex.attach(5);
            this->ServoOther.attach(6);
            this->ServoThumb.attach(9);

            this->Sensor.attachBus(AnalogIn);
            this->Sensor.setPin(A1);
            this->Sensor.init();

            this->AngleThumbOpen  = this->AngleThumbMax;
            this->AngleThumbClose = this->AngleThumbMin;
            this->AngleIndexOpen  = this->AngleIndexMax;
            this->AngleIndexClose = this->AngleIndexMin;
            this->AngleOtherOpen  = this->AngleOtherMax;
            this->AngleOtherClose = this->AngleOtherMin;
            break;

        case Mk2Left:

            this->ButtonCalib.attach(A6,false,true);
            this->ButtonExtra.attach(A7,false,true);
            this->ButtonThumb.attach(A0,false,true);
            this->ButtonOther.attach(10,true,true);

            this->ServoIndex.attach(5);
            this->ServoOther.attach(6);
            this->ServoThumb.attach(9);

            this->Sensor.attachBus(AnalogIn);
            this->Sensor.setPin(A1);
            this->Sensor.init();

            this->AngleThumbOpen  = this->AngleThumbMin;
            this->AngleThumbClose = this->AngleThumbMax;
            this->AngleIndexOpen  = this->AngleIndexMin;
            this->AngleIndexClose = this->AngleIndexMax;
            this->AngleOtherOpen  = this->AngleOtherMin;
            this->AngleOtherClose = this->AngleOtherMax;
            break;

        case SizeSRight:
            break;

        case SizeSLeft:

            this->ButtonCalib.attach( 1, true, true);
            this->ButtonExtra.attach( 2, true, true);
            this->ButtonThumb.attach( 3, true, true);
            this->ButtonOther.attach( 0, true, true);

            this->ServoIndex.attach(9);
            this->ServoOther.attach(6);
            this->ServoThumb.attach(5);

            this->Sensor.attachBus(AnalogIn);
            this->Sensor.setPin(A0);
            this->Sensor.init();

            this->AngleThumbOpen  = this->AngleThumbMin;
            this->AngleThumbClose = this->AngleThumbMax;
            this->AngleIndexOpen  = this->AngleIndexMin;
            this->AngleIndexClose = this->AngleIndexMax;
            this->AngleOtherOpen  = this->AngleOtherMin;
            this->AngleOtherClose = this->AngleOtherMax;
            break;

        case Mk2RightBLE:

            this->ButtonCalib.attach(A6,false,true);
            this->ButtonExtra.attach(A7,false,true);
            this->ButtonThumb.attach(A0,false,true);
            this->ButtonOther.attach(10,true,true);

            this->ServoIndex.attach(5);
            this->ServoOther.attach(6);
            this->ServoThumb.attach(9);

            this->Sensor.attachBus(I2C);
            this->Sensor.init();

            this->AngleThumbOpen  = this->AngleThumbMax;
            this->AngleThumbClose = this->AngleThumbMin;
            this->AngleIndexOpen  = this->AngleIndexMax;
            this->AngleIndexClose = this->AngleIndexMin;
            this->AngleOtherOpen  = this->AngleOtherMax;
            this->AngleOtherClose = this->AngleOtherMin;
            break;

        default:
            break;
    }
}

void HACKberry::readSensor() {
    this->SensorValue = (this->Sensor).read();
}

void HACKberry::calcControlInput() {
    this->ControlInput = this->SensorValue;
}

void HACKberry::calcPosition() {

    // Calc Speed
    int NormalizedSensorValue = map(this->ControlInput, this->MinSensorValue, this->MaxSensorValue, this->NormalizedSensorMin, this->NormalizedSensorMax);
    if ( NormalizedSensorValue > this->SensorRangeSaturation ) {
        this->CurrentAngularVelocity = MaxForwardSpeed
    } else if ( NormalizedSensorValue > this->MaxSensorRangeStop ) { // Forward
        this->CurrentAngularVelocity = map(NormalizedSensorValue, this->MaxSensorRangeStop, this->NormalizedSensorMax, MinForwardSpeed, MaxForwardSpeed);
    } else if ( NormalizedSensorValue > this->MinSensorRangeStop ) { // Stop
        this->CurrentAngularVelocity = MinForwardSpeed;
    } else { // Reverse
        this->CurrentAngularVelocity = map(NormalizedSensorValue, this->NormalizedSensorMin, this->MinSensorRangeStop, ManReverseSpeed, MinReverseSpeed);
    }

    // Calc Target Position
    this->CurrentAngle = this->PreAngle + this->CurrentAngularVelocity;
    if ( this->CurrentAngle > this->NormalizedAngleMaxPosition ) {
        this->CurrentAngle = this->NormalizedAngleMaxPosition;
    }
    if ( this->CurrentAngle < this->NormalizedAngleMinPosition ) {
        this->CurrentAngle = this->NormalizedAngleMinPosition;
    }
    this->PreAngle = this->CurrentAngle;
}

void HACKberry::controlServo() {
    this->ServoIndex.write(this->TargetAngleIndex);
    this->ServoThumb.write(this->TargetAngleThumb);
    this->ServoOther.write(this->TargetAngleOther);
}

// calibration
void HACKberry::calibration( unsigned long calibtime = 5000 ) {

    // init position
    this->TargetAngleIndex = this->AngleIndexOpen;
    this->TargetAngleOther = this->AngleOtherClose;
    this->TargetAngleThumb = this->AngleThumbOpen;
    (this->controlServo)();

    //
    this->readSensor();
    this->MinSensorValue = this->SensorValue;
    this->MaxSensorValue = this->SensorValue;
    unsigned long time = millis();
    while( millis() < time + calibtime ) {
        this->readSensor();
        if ( this->SensorValue < this->MinSensorValue ) {
            this->MinSensorValue = this->SensorValue;
        } else if ( this->SensorValue > this->MaxSensorValue ) {
            this->MaxSensorValue = this->SensorValue;
        }

        calcPosition();
        this->TargetAngleIndex = map(this->CurrentAngle,
                                    this->NormalizedAngleMinPosition, this->NormalizedAngleMaxPosition,
                                    this->AngleIndexClose, this->AngleIndexOpen);
        (this->controlServo)();

        delay(PERIOD_CONTROL_IN_MILISEC);
    }
}

void HACKberry::initLog() {
    this->isLogValid = true;
    Serial.begin(9600);
}

void HACKberry::outputLog() {
    if ( this->isLogValid ) {
        Serial.print("== LOG ==");
        Serial.print("=== Sensor ===");
        Serial.print("  "); Serial.print("Cur Sensor Val ="); Serial.print(this->SensorValue);
        Serial.print("  "); Serial.print("Min Sensor Val ="); Serial.print(this->MinSensorValue);
        Serial.print("  "); Serial.print("Max Sensor Val ="); Serial.print(this->MaxSensorValue);
        Serial.print("=== Status ===");
        Serial.print("  "); Serial.print("Current Ang ="); Serial.print(this->CurrentAngle);
        Serial.print("  "); Serial.print("Cuurent Vel ="); Serial.print(this->CurrentAngularVelocity);
        Serial.print("  "); Serial.print("Target Ang (Index)="); Serial.print(this->TargetAngleIndex);
        Serial.print("  "); Serial.print("Target Ang (Middle)="); Serial.print(this->TargetAngleMiddle);
        Serial.print("  "); Serial.print("Target Ang (Thumb)="); Serial.print(this->TargetAngleThumb);
        Serial.print("  "); Serial.print("Flag Thumb Open="); Serial.print(this->isThumbOpen);
        Serial.print("  "); Serial.print("Flag Other Lock="); Serial.print(this->isOtherLock);
    } else {
    }
}
