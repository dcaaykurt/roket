// BMP180
#include <SFE_BMP180.h> 
#include <Wire.h> 
SFE_BMP180 pressure;
double baseline,a,P;

//GPS
#include <TinyGPS++.h>
TinyGPSPlus gps;


//UART
#define FLOAT_PRECISION 6
static String PACKAGE;


//SWSERİAL
//#include <SoftwareSerial.h>
//SoftwareSerial yeniSeriPort(2, 3); //RX-TX





double getPressure(){

char status;
double T,P,p0,a;
 

status = pressure.startTemperature();
if (status != 0) 
{
delay(status); 
status = pressure.getTemperature(T); 
if (status != 0) 
{
status = pressure.startPressure(3);
if (status != 0)
{

 
delay(status);
 

 
status = pressure.getPressure(P,T); //Tamamlanan basınç ölçümü Al :
if (status != 0) //sıfıra eşit değilse
{
return(P); // Ölçüm birimi P saklanır
}

}
}
}
}


void uart_init(long br){
  Serial.begin(br);
}

//  @arg void
//  paketin içini boşaltır
//  @return NONE  
void set_package(void){
  PACKAGE = "";
}

//  @arg device: roket = 1, diger = 0
//  @arg altitude: yukseklik degeri
//  @arg speed: hiz
//  @arg gpsLat: gps enlem
//  @arg gpsLong: gps boylam
//  @return NONE
void make_package(String device, float aaltitude, float sspeed, float gpsLat, float gpsLong){
  PACKAGE = (device == "roket") ? "1" : "0";
  PACKAGE += "/";
  PACKAGE += String(aaltitude,FLOAT_PRECISION);
  PACKAGE += "/";
  PACKAGE += String(sspeed,FLOAT_PRECISION);
  PACKAGE += "/";
  PACKAGE += String(gpsLat, FLOAT_PRECISION);
  PACKAGE += "/";
  PACKAGE += String(gpsLong, FLOAT_PRECISION);

}

//  @arg void
//  paketi postalar
//  @return NONE
void post_package(void){
  Serial.println(PACKAGE);
  //set_package();
}












void setup() {
  
  pressure.begin();
  //yeniSeriPort.begin(9600); megaan uno ya geçersen gps buna bagla
  Serial3.begin(9600);
  baseline = getPressure();
  while(Serial3.available()){
    gps.encode(Serial3.read());
  }
  uart_init(115200);
  set_package();
}

void loop() {
  P = getPressure();
  a = pressure.altitude(P,baseline);
  make_package("yuk",a, 25, gps.location.lat(), gps.location.lng());
  post_package();
  
  
  delay(500);

}
