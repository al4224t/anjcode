#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

#define MPU9250_ADDRESS (0x68)
#define MPU9250_REG_PWR_MGMT_1 (0x6b)
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



  // Setup Wiring Pi
  wiringPiSetup();

  // Open an I2C connection
  int fd = wiringPiI2CSetup(0x68);
  

  // Perform I2C work
  wiringPiI2CWriteReg8(fd, MPU9250_REG_PWR_MGMT_1, 0); 
  uint8_t axh,axl,ayh,ayl,azh,azl,gxh,gxl,gyh,gyl,gzh,gzl,mxh,mxl,myh,myl,mzh,mzl;
  while(1) {
    axh = wiringPiI2CReadReg8(fd, 0x3B);
    axl = wiringPiI2CReadReg8(fd, 0x3C);
    int16_t accelX = axh << 8 | axl;

    ayh = wiringPiI2CReadReg8(fd, 0x3D);
    ayl = wiringPiI2CReadReg8(fd, 0x3E);
    int16_t accelY = ayh << 8 | ayl;

    azh = wiringPiI2CReadReg8(fd, 0x3F);
    azl = wiringPiI2CReadReg8(fd, 0x40);
    int16_t accelZ = azh << 8 | azl;

    gxh = wiringPiI2CReadReg8(fd, 0x43);
    gxl = wiringPiI2CReadReg8(fd, 0x44);
    uint16_t gyroX = gxh << 8 | gxl;

    gyh = wiringPiI2CReadReg8(fd, 0x45);
    gyl = wiringPiI2CReadReg8(fd, 0x46);
    uint16_t gyroY = gyh << 8 | gyl;

    gzh = wiringPiI2CReadReg8(fd, 0x47);
    gzl = wiringPiI2CReadReg8(fd, 0x48);
    uint16_t gyroY = gzh << 8 | gzl;

    

    printf("accelX=%f, accelY=%f, accelZ=%f, gyroX=%f, gyroY=%f, gyroZ=%f\n");
    sleep(1);
  }
}
