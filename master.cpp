#include "mbed.h"
#define F446
//master
/*intからcharへの分解
   分解の際
   dat1 = data % 256;
   dat2 = data / 256;
   復元の際
   data = dat2 * 256 + dat1;
   参考元：https://oshiete.goo.ne.jp/qa/6219385.html
 */
#ifdef F446
Serial pc(USBTX,USBRX);
RawSerial device(NC,D9);
DigitalOut Uart(D3);
DigitalOut led(LED1);
Timer timer;
struct {
        char highbyte;
        char lowbyte;
        short intdat;
} data;

int read() //読み込む関数
{
        Uart = 1;//ピン変化割り込みするためにHIGHに
        //wait_ms(100);
        while (device.readable() != 1) ;
        char c = device.getc();
        if(c != 'H') {
                Uart =0;
                return 0;
        }
        while (device.readable() != 1) ;
        data.lowbyte = device.getc();
        while (device.readable() != 1) ;
        data.highbyte = device.getc();
        Uart = 0;//元に戻す
        data.intdat = data.highbyte*256+data.lowbyte;//復元
        //wait_ms(1000);
        pc.printf("Re %d\n",data.intdat);
        //pc.printf("HELLO\n" );
}

int main() {
        device.baud(230400);
        led = 1;
        wait_ms(1000);
        led = 0;
        data.intdat = 100;
        data.lowbyte = 0;
        data.highbyte = 0;
        while(1) {
                led =!led;
                Uart =!Uart;
                read();
        }
}

#else

   RawSerial pc(USBTX,USBRX);
   RawSerial device(D5,D4);
   DigitalOut Uart(D8);
   DigitalOut led(LED1);
   Timer timer;
   struct {
        char highbyte;
        char lowbyte;
        short intdat;
   } data;

   inline int read() //読み込む関数
   {
        Uart = 1;//ピン変化割り込みするためにHIGHに
        //wait_ms(100);
        while (device.readable() != 1) ;
        char c = device.getc();
        if(c != 'H') {
                Uart = 0;
                return 0;
        }
        while (device.readable() != 1) ;
        data.lowbyte = device.getc();
        while (device.readable() != 1) ;
        data.highbyte = device.getc();
        Uart = 0;//元に戻す
        data.intdat = data.highbyte*256+data.lowbyte;//復元
        pc.printf("Re %d\r\n",data.intdat);
   }

   int main() {
        device.baud(9600);
        led = 1;
        wait_ms(1000);
        led = 0;
        while(1) {
                led =!led;
                read();
                wait_ms(0);

        }
   }
#endif
