
 
#include <stdint.h> 
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h> 
#include <unistd.h>
#include <math.h>
#define MPU9250_ADDRESS (0x68)
#define MPU9250_REG_PWR_MGMT_1 (0x6B)
#define GYRO_XOUT_H (0x43)
#define GYRO_XOUT_L (0x44)
#define GYRO_YOUT_H (0x45)
#define GYRO_YOUT_L (0x46)
#define GYRO_ZOUT_H (0x47)
#define GYRO_ZOUT_L (0x48)
#define ACCEL_XOUT_H (0x3B)
#define ACCEL_XOUT_L (0x3C)
#define ACCEL_YOUT_H (0x3D)
#define ACCECL_YOUT_L (0x3E)
#define ACCEL_ZOUT_H (0x3F)
#define ACCEL_ZOUT_L (0x40)
//#define A_SCALE (16384.0)
//#define ANG_SCALE (131.0)
void checkRC(int rc, char *text) {
if (rc<0) {
printf("Error: %s - %d\n");
exit(-1);
  }
}
int main(int argc, char *argv[]) { 
  // Setup Wiring Pi
int  wiringPiSetup();

  // Open an I2C connection
int  fd = wiringPiI2CSetup(0x68);
  

  // Perform I2C work
 // wiringPiI2CWriteReg8(fd,(0X6B), 0);
  wiringPiI2CWriteReg8(fd,(0x35), 8);
  wiringPiI2CWriteReg8(fd,(0x35), 10);
  wiringPiI2CWriteReg8(fd, (0x35), 20);
  wiringPiI2CWriteReg8(fd, (0x35), 40); 
  int8_t axh,axl,ayh,ayl,azh,azl,gxh,gxl,gyh,gyl,gzh,gzl,mxh,mxl,myh,myl,mzh,mzl;
  
    axh = wiringPiI2CReadReg8(fd, 0x35);
    axl = wiringPiI2CReadReg8(fd, 0x35);
    int16_t accelX = axh << 8 | axl;

    ayh = wiringPiI2CReadReg8(fd, 0x3D);
    ayl = wiringPiI2CReadReg8(fd, 0x3E);
    int16_t accelY = ayh << 8 | ayl;

    azh = wiringPiI2CReadReg8(fd, 0x3F);
    azl = wiringPiI2CReadReg8(fd, 0x40);
    int16_t accelZ = azh << 8 | azl;

    gxh = wiringPiI2CReadReg8(fd, 0x43);
    gxl = wiringPiI2CReadReg8(fd, 0x44);
    int16_t gyroX = gxh << 8 | gxl;

    gyh = wiringPiI2CReadReg8(fd, 0x45);
    gyl = wiringPiI2CReadReg8(fd, 0x46);
    int16_t gyroY = gyh << 8 | gyl;

    gzh = wiringPiI2CReadReg8(fd, 0x47);
    gzl = wiringPiI2CReadReg8(fd, 0x48);
    int16_t gyroZ = gzh << 8 | gzl;

    

    printf("accelX=%i\n", accelX);
    printf("accelY=%i\n", accelY); 
    printf("accelZ=%i\n", accelZ);
    printf("gyroX=%i\n", gyroX);
    printf("gyroY = %i\n", gyroY);
    printf("gyroZ = %i\n", gyroZ); 
    float pitch = atan2(accelY , (sqrt((accelX * accelX) + (accelZ * accelZ)))); 
    float roll = atan2(-accelX , (sqrt((accelY * accelY) + (accelZ * accelZ)))); 

       printf("%f\n", pitch);
       printf("%f\n", roll);   
       
  }

