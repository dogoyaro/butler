#include <Servo.h>
#include <IRremote.h>


const int DOOROPENER_pin = 9;
const int RECEIVER_pin = 11;

enum ButlerCommand {
    OPENDOOR,
    TURNOFFLIGHTS,
    IGNORE
};

Servo dooropener;
IRrecv irrecv(RECEIVER_pin);
decode_results message;

int openerposition = 0;

void setup() {
    Serial.begin(9600);
    initDoorOpener();
    initIRReceiver();
}

void initIRReceiver() {
    IrReceiver.begin(RECEIVER_pin, ENABLE_LED_FEEDBACK);
}

void loop() {
    listenForDoorBell();
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

ButlerCommand IRReceiverAdapter(unsigned long code) {
    switch (code) {
        case 0xBA45FF00:
            return OPENDOOR;
        default:
            return IGNORE;
    }
}

void listenForDoorBell() {
    if (IrReceiver.decode()) {
      // USE NEW 3.x FUNCTIONS
      IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
      IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
        // openDoor();

        ButlerCommand command = IRReceiverAdapter(IrReceiver.decodedIRData.decodedRawData);
        switch (command) {
            case OPENDOOR:
                openDoor();
                break;
            default:
                break;
        }
        irrecv.resume();
    }
}

void listenForMessages() {}