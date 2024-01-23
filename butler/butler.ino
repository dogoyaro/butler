#include <Servo.h>


Servo dooropener;
const int DOOROPENER_pin = 9;
int openerposition = 0;



void setup() {
    Serial.begin(9600);
    initDoorOpener();
}

void loop() {
    openDoor();
}


void initDoorOpener() {
    dooropener.attach(DOOROPENER_pin);
}

void openDoor() {
    for (openerposition = 0; openerposition <= 180; openerposition += 1) {
        dooropener.write(openerposition);
        delay(15);
    }

    for (openerposition = 180; openerposition >= 0; openerposition -= 1) {
        dooropener.write(openerposition);
        delay(15);
    }
}





void listenForDoorBell() {}

void sendNotification() {}

void listenForMessages() {}