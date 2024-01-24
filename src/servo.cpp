#include <Arduino.h>
#include <ESP32Servo.h>
#include <pins_define.h>
#include <servo.h>

Servo myservo;

void servo_begin(){
    ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
    myservo.setPeriodHertz(50); // standard 50 hz servo
	myservo.attach(servo_pin, 500, 2400); // Attach the servo after it has been detatched
    myservo.write(0);
    delay(2000);
}

int servo_ms;
bool isOpening;
unsigned long last_delay;
void servo_open(int degree, int time_ms){
    myservo.write(degree);
    isOpening = true;
    servo_ms = time_ms;
    last_delay = millis();
}
void servo_run(){
    if (((millis() - last_delay) > servo_ms) && isOpening)
    {
        myservo.write(0);
        isOpening = false;
    }
}

bool servo_opening(){
    return isOpening;
}