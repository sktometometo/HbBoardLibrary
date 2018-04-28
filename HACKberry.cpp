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

void HACKberry::setSerialNum(char* sn) {
    this->serialNum = sn;
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

void HACKberry::setSpeedRange(int MaxOpenSpeed, int MinOpenSpeed, int MinCloseSpeed, int MaxCloseSpeed ) {
    this->MaxOpenSpeed  = MaxOpenSpeed;
    this->MinOpenSpeed  = MinOpenSpeed;
    this->MaxCloseSpeed = MaxCloseSpeed;
    this->MinCloseSpeed = MinCloseSpeed;
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

            this->ButtonCalib.attach(A6);
            this->ButtonExtra.attach(A5);
            this->ButtonThumb.attach(A4);
            this->ButtonOther.attach(A3);

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

            this->ButtonCalib.attach(11);
            this->ButtonExtra.attach(10);
            this->ButtonThumb.attach(8);
            this->ButtonOther.attach(7);

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

            this->ButtonCalib.attach(A6);
            this->ButtonExtra.attach(A7);
            this->ButtonThumb.attach(A0);
            this->ButtonOther.attach(10);

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

            this->ButtonCalib.attach(A6);
            this->ButtonExtra.attach(A7);
            this->ButtonThumb.attach(A0);
            this->ButtonOther.attach(10);

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

            this->ButtonCalib.attach( 1);
            this->ButtonExtra.attach( 2);
            this->ButtonThumb.attach( 3);
            this->ButtonOther.attach( 0);

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

            this->ButtonCalib.attach(A6);
            this->ButtonExtra.attach(A7);
            this->ButtonThumb.attach(A0);
            this->ButtonOther.attach(10);

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
    int NormalizedSensorValue = 0;
    if ( this->isSensorReversed ) {
        NormalizedSensorValue = map(this->SensorValue, this->MinSensorValue, this->MaxSensorValue, this->NormalizedSensorMin, this->NormalizedSensorMax); 
    } else {
        NormalizedSensorValue = map(this->SensorValue, this->MinSensorValue, this->MaxSensorValue, this->NormalizedSensorMax, this->NormalizedSensorMin); 
    }
    if ( NormalizedSensorValue > this->SensorRangeSaturation ) {
        this->CurrentAngularVelocity = MaxCloseSpeed;
    } else if ( NormalizedSensorValue > this->MaxSensorRangeStop ) { // Forward
        this->CurrentAngularVelocity = map(NormalizedSensorValue, this->MaxSensorRangeStop, this->NormalizedSensorMax, MinCloseSpeed, MaxCloseSpeed);
    } else if ( NormalizedSensorValue > this->MinSensorRangeStop ) { // Stop
        this->CurrentAngularVelocity = MinCloseSpeed;
    } else { // Reverse
        this->CurrentAngularVelocity = map(NormalizedSensorValue, this->NormalizedSensorMin, this->MinSensorRangeStop, MaxOpenSpeed, MinOpenSpeed);
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
    delay(500);

    //
    (this->readSensor)();
    (this->calcControlInput)();
    this->MinSensorValue = this->SensorValue;
    this->MaxSensorValue = this->SensorValue;
    unsigned long time = millis();
    while( millis() < time + calibtime ) {
        this->readSensor();
        this->calcControlInput();
        if ( this->SensorValue < this->MinSensorValue ) {
            this->MinSensorValue = this->SensorValue;
        } else if ( this->SensorValue > this->MaxSensorValue ) {
            this->MaxSensorValue = this->SensorValue;
        }

        calcPosition();
        this->TargetAngleIndex = map(this->CurrentAngle,
                                    this->NormalizedAngleMinPosition, this->NormalizedAngleMaxPosition,
                                    this->AngleIndexOpen, this->AngleIndexClose);
        (this->controlServo)();

        if ( this->isLogValid ) {
            outputLog(this);
        }
        delay(PERIOD_CONTROL_IN_MILISEC);
    }
}

void HACKberry::initLog() {
    this->isLogValid = true;
    Serial.begin(9600);
}

void outputLog(HACKberry* hackberry) {
    if ( hackberry->isLogValid ) {
        Serial.println("== LOG ==");
        Serial.print("  "); Serial.print("Serial Number = "); Serial.println(hackberry->serialNum);
        Serial.println("=== Sensor ===");
        Serial.print("  "); Serial.print("Cur Sensor Val = "); Serial.println(hackberry->SensorValue);
        Serial.print("  "); Serial.print("Min Sensor Val = "); Serial.println(hackberry->MinSensorValue);
        Serial.print("  "); Serial.print("Max Sensor Val = "); Serial.println(hackberry->MaxSensorValue);
        Serial.println("=== Status ===");
        Serial.print("  "); Serial.print("Current Ang = "); Serial.println(hackberry->CurrentAngle);
        Serial.print("  "); Serial.print("Cuurent Vel = "); Serial.println(hackberry->CurrentAngularVelocity);
        Serial.print("  "); Serial.print("Target Ang (Index)= "); Serial.println(hackberry->TargetAngleIndex);
        Serial.print("  "); Serial.print("Target Ang (Middle)= "); Serial.println(hackberry->TargetAngleOther);
        Serial.print("  "); Serial.print("Target Ang (Thumb)= "); Serial.println(hackberry->TargetAngleThumb);
        Serial.print("  "); Serial.print("Flag Thumb Open= "); Serial.println(hackberry->isThumbOpen);
        Serial.print("  "); Serial.print("Flag Other Lock= "); Serial.println(hackberry->isOtherLock);
        Serial.print("  "); Serial.print("Flag Sensor Rev= "); Serial.println(hackberry->isSensorReversed);
    } else {
    }
}
