#include <wiringPi.h>
#include <wiringPiI2C.h>

int main (void) {
    int fd;
    int i, cnt;
    int a2dChannel = 1; // analog channel AIN1, thermistor sensor
    int prev, a2dVal;
    int threshold = 200;
    printf("[ADC/DAC(YL-40) Module testing..........]\n");
    if((fd = wiringPiI2CSetupInterface("/dev/i2c-1", 0x48))<0) {
        printf("wiringPiI2CSetupInterface failed:\n");
    }
    cnt = 0;
    while(1) {
        wiringPiI2CWrite(fd, 0x00 | a2dChannel); // 0000_0001
        prev = wiringPiI2CRead(fd); // Previously byte, garvage
        a2dVal = wiringPiI2CRead(fd);
        printf("[%d] prev = %d, ", cnt, prev);
        printf("a2dVal = %d, ", a2dVal);
        if(a2dVal > threshold)
            printf("Hot!!\n");
        else
            printf("Normal!!\n");
        delay(1000);
        cnt++;
    }
}