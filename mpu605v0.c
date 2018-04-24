

#
  
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
#define A_SCALE (16384.0)
#define ANG_SCALE (131.0)
#define ACCEL_CONFIG (0x1C)
#define ACCEL_CONFIG2 (0x1D)
#define GYRO_CONFIG (0x1B)
#define AK8963_ST1 (0x02)
#define AK8963_MAGNET_OUT (0x03)
#define AK8963_YOUT_L (0x5H)
#define AK9863_YOUT_H (0x6H)
#define AK8963_ZOUT_L (0x7H)
#define AK9863_ZOUT_H (0x8H)
#define AK9863_CNTL (0x0A)
#define I2C_SLV1_CTRL (0X2A)
#define I2C_SLV1_ADDR (0x25)
#define INT_PIN_CFG (0x37)
#define EXT_SENS_DATA (0x49)
#define INT_PIN_CONFIG (0x37)
#define  USER_CTRL (0x6A)
#define ST2 (0x09)


void checkRC(int rc, char *text) {   //check if wiringPi okay
if (rc<0) {
printf("Error: %s - %d\n");
exit(-1);
  }
}
int main(int argc, char *argv[]) { 
  // Setup Wiring Pi
int  wiringPiSetup();

  // Open an I2C connection
int  fd = wiringPiI2CSetup(0x68);  //for mpu9250 gyro + accel
//int magno = wiringPiI2CSetup(0xC); // for magno address
  

  // Perform I2C work
  wiringPiI2CWriteReg8(fd,(0X6C), 0x00);//power on
  wiringPiI2CWriteReg8(fd, (0x1C), 0);//write to accelorometer
  wiringPiI2CWriteReg8(fd, (0x1B), 0);//write to gyro
  wiringPiI2CWriteReg8(fd , (0x37), 0b00000010); //enable auxillary pins to SDA and SCL
  wiringPiI2CWriteReg8(fd, (0x6A), 0b00000000);  //disable auxillary pins
 
//wiringPiI2CWriteReg8(fd, 0x0A, 0x02); //enable i2c magneto continous ranging mode

float accelscale = 16384.0; //16384 counts/g
  float gyroscale = 131.0; //131 counts/g


  delay(100);
 
  int8_t axh,axl,ayh,ayl,azh,azl,gxh,gxl,gyh,gyl,gzh,gzl,mxh,mxl,myh,myl,mzh,mzl;
  while(1) {  
    axh = wiringPiI2CReadReg8(fd, 0x3B); //high accelerometer high byte
    axl = wiringPiI2CReadReg8(fd, 0x3C); //low accelerometer low byte
    int16_t accelX = axh << 8 | axl;
    float actualaccelXvalue = accelX/accelscale;

    ayh = wiringPiI2CReadReg8(fd, 0x3D);  //high  accelerometer y byte
    ayl = wiringPiI2CReadReg8(fd, 0x3E);   //low  accelerometer y byte
    int16_t accelY = ayh << 8 | ayl;
    float actualaccelYvalue = accelY/accelscale;
   
    azh = wiringPiI2CReadReg8(fd, 0x3F);  //high  accelerometer z byte
    azl = wiringPiI2CReadReg8(fd, 0x40);   //low  accelerometer z byte
    int16_t accelZ = azh << 8 | azl;
    float actualaccelZvalue = accelZ/accelscale;

    gxh = wiringPiI2CReadReg8(fd, 0x43);   //high  gyro x byte
    gxl = wiringPiI2CReadReg8(fd, 0x44);    //low gyro x byte
    int16_t gyroX = gxh << 8 | gxl;
    float actualgyroXvalue = gyroX/gyroscale;
    
   
    gyh = wiringPiI2CReadReg8(fd, 0x45);  //high  gyro y byte
    gyl = wiringPiI2CReadReg8(fd, 0x46);   //low  gyro y byte
    int16_t gyroY = gyh << 8 | gyl;
    float actualgyroYvalue = gyroY/gyroscale;
   
    gzh = wiringPiI2CReadReg8(fd, 0x47);  //high  gyro z byte
    gzl = wiringPiI2CReadReg8(fd, 0x48);  //low  gyro z byte
    int16_t gyroZ = gzh << 8 | gzl;
    float actualgyroZvalue = gyroZ/gyroscale;
 
printf("actualaccelXvalue = %f\n", actualaccelXvalue);
printf("actualaccelYvalue = %f\n", actualaccelYvalue);
printf("actualaccelZvalue  = %f\n",actualaccelZvalue);
printf("actualgyroXvalue =  %f\n", actualgyroXvalue);
printf("actualgyroYvalue = %f\n" , actualgyroYvalue);
printf("actualgyroZvalue = %f\n" , actualgyroZvalue);
pitch = 180 * atan (actualaccelXvalue/sqrt(actualaccelYvalue*actualaccelYvalue + actualaccelZvalue*actualaccelZvalue))/M_PI;
roll = 180 * atan (actualaccelYvalue/sqrt(actualaccelXvalue*actualaccelXvalue + actualaccelZvalue*actualaccelZvalue))/M_PI;
    printf("%f\n", pitch);
    printf("%f\n", roll);
    
pitch = 180 * atan (actualaccelXvalue/sqrt(actualaccelYvalue*actualaccelYvalue + actualaccelZvalue*actualaccelZvalue))/M_PI;
roll = 180 * atan (actualaccelYvalue/sqrt(actualaccelXvalue*actualaccelXvalue + actualaccelZvalue*actualaccelZvalue))/M_PI;
    printf("%f\n", pitch);
    printf("%f\n", roll);
 
    
    
    
    
    
    /*
    //a = τ/(τ + Δt)   
    //(Gyroscope Angle) = (last measured filterd angle) + ω×Δt
  // Filtered Angle = α × (Gyroscope Angle) + (1 − α) × (Accelerometer Angle)   


    
     //  int drdy = wiringPiI2CReadReg8(magno, 0x02);
    //while (drdy & 0x01){
    // mxh = wiringPiI2CReadReg8(magno, 0x03);
    // mxl = wiringPiI2CReadReg8(magno, 0x04);
    //int16_t magnoX = mxh << 8 | mxl;
    //printf("magnoX = %i\n", magnoX);

   int count=0;
   int county=0;
  int countz=0;
 int dataxl[count];
   int dataxh[count];
   int datayl[count];
  int datayh[count];
 int datazl[count];
int datazh[count];   
   int  drdy = wiringPiI2CReadReg8(magno, 0x02);
 while  (drdy & 0x01){
  // datax[count] = wiringPiI2CReadReg8(magno, 0x03);
  // datay[count] = wiringPiI2CReadReg8(magno, 0x05);
 // dataz[count] = wiringPiI2CReadReg8(magno,0x07);
   
 for (count=0; count<7; count++){
//      printf("hello world");
   //    if (drdy & 0x01){
       dataxl[0] = wiringPiI2CReadReg8(magno, 0x03);
       dataxh[1] = wiringPiI2CReadReg8(magno,0x04);
       datayl[2] = wiringPiI2CReadReg8(magno, 0X05);
       datayh[3] = wiringPiI2CReadReg8(magno, 0x06); 
       datazl[4] = wiringPiI2CReadReg8(magno, 0x07); 
        datazh[5] = wiringPiI2CReadReg8(magno, 0x08);
   // printf("hello world");
 }
}
  //  if (data[6] & 0x08!=0x08){
  int16_t magnoX = dataxl[1] << 8| dataxh[0];
   printf("magnoX = %i\n", magnoX);
//}  
//  int16_t magnoYY = ((int16_t) datax[3] << 8) | datax[2];
  // printf("magnoYY = %i\n", magnoYY);
  // int16_t magnoZZ =((int16_t) datax[5] << 8) | datax[4];
  // printf("magnoZZ =%i\n", magnoZZ);

int16_t magnoY = datayl[3] <<8 | datayh[2];
  printf( "magnoY=%i\n", magnoY); 

int16_t magnoZ = datazl[5] <<8 | datazh[4];
printf("magnoZ=%i\n", magnoZ);
//printf("hello world");
//}

  

  
 //   printf("magnoX = %i\n", magnoX);
   // printf("magnoY = %i\n", magnoY);
   // printf("magnoZ = %i\n", magnoZ);
  
 */
sleep(1);   
      } 
}





