#include "mbed.h"
RawSerial pc(USBTX,USBRX);
RawSerial device(D5,D4);
InterruptIn Uart(D8);
DigitalOut led(LED1);
struct {
        char highbyte;
        char lowbyte;
        short intdat = 0;
} data;

void sendTomaster(){
        data.intdat++;
        data.highbyte = data.intdat%256;
        data.lowbyte = data.intdat/256;
        device.putc('H');
        device.putc(data.highbyte);
        device.putc(data.lowbyte);
        pc.printf("riseing!\r\n");
}

int main() {

        led = 0;
        Uart.rise(&sendTomaster);
        device.baud(230400);
        while(1) {
                wait_ms(650);
                led =!led;
        }
}
