#include <Arduino.h>
#include <Servo.h>

#include "HACKberry.h"
#include "HbButton.h"
#include "HbSensor.h"
#include "HbI2C.h"

// Objects
HACKberry Hb;

//Global
char HbSerialNum[] = "Wireless Test";
int HbSensorVal  = 0;
int HbBatteryVal = 0;
ConnectionStatus BLEStateVal = Disconnected;
HandState HandStateVal = NotInitialized;

void setup() {

    // Object initialization
    Hb.setBoardType(Mk2RightBLE);
    Hb.setSerialNum(HbSerialNum);
    Hb.setAngleIndex( 15, 135);
    Hb.setAngleOther(100,  95);
    Hb.setAngleThumb(100, 175);
    Hb.setSpeedRange( -2, 0, 0, 4); //
    Hb.setSensorThreshold(20, 30, 60); //

    // init
    Hb.init();
    Hb.initLog();

    delay(100);

    // Sensor Calibration
    // Open Hand
    Hb.TargetAngleIndex = Hb.AngleIndexOpen;
    Hb.TargetAngleOther = Hb.AngleOtherOpen;
    Hb.TargetAngleThumb = Hb.AngleThumbOpen;
    Hb.controlServo();

    delay(1000);

    while (1) {

        if (Hb.ButtonCalib.read() == LOW) {
            Hb.calibration(3000);
            break;
        }
        if (Hb.isLogValid) {
            Serial.println("wating for calibration....");
            outputLog(&Hb);
        }
        delay(PERIOD_CONTROL_IN_MILISEC);
    }
}

void loop() {
    // Control

    // Button
    if (Hb.ButtonCalib.read() == LOW) {
        Hb.calibration(5000);
        while (Hb.ButtonCalib.read() == LOW) delay(1);
    }

    if (Hb.ButtonExtra.read() == LOW) {
        // do something here
        Hb.isSensorReversed = !Hb.isSensorReversed;
        while (Hb.ButtonExtra.read() == LOW) delay(1);
    }

    if (Hb.ButtonThumb.read() == LOW) {
        Hb.isThumbOpen = !Hb.isThumbOpen;
        while(Hb.ButtonThumb.read() == LOW) delay(1);
    }

    if (Hb.ButtonOther.read() == LOW) {
        Hb.isOtherLock = !Hb.isOtherLock;
        while(Hb.ButtonOther.read() == LOW) delay(1);
    }

    // sensor
    Hb.readSensor();
    Hb.calcControlInput();
    Hb.calcPosition();

    // calc target angle
    Hb.TargetAngleIndex = map(Hb.CurrentAngle,
                                Hb.NormalizedAngleMinPosition, Hb.NormalizedAngleMaxPosition,
                                Hb.AngleIndexOpen, Hb.AngleIndexClose);
    if ( Hb.isOtherLock ) {
        Hb.TargetAngleOther = Hb.TargetAngleOther;
    } else {
        Hb.TargetAngleOther = map(Hb.CurrentAngle,
                                    Hb.NormalizedAngleMinPosition, Hb.NormalizedAngleMaxPosition,
                                    Hb.AngleOtherOpen, Hb.AngleOtherClose);
    }
    if ( Hb.isThumbOpen ) {
        Hb.TargetAngleThumb = Hb.AngleThumbOpen;
    } else {
        Hb.TargetAngleThumb = Hb.AngleThumbClose;
    }

    // servo control
    Hb.controlServo();

    delay(PERIOD_CONTROL_IN_MILISEC);
    outputLog(&Hb);
}
