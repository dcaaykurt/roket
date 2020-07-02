// BMP180

#include "SFE_BMP180.h" 
#include <Wire.h> 
#include "uart_sender.h"
#include "oneDimensionalKalman.h"

SFE_BMP180 pressure;
double baseline,a,P;

//GPS
#include "TinyGPS++.h"
TinyGPSPlus gps;
// denemeler

//SWSERİAL
//#include <SoftwareSerial.h>
//SoftwareSerial yeniSeriPort(2, 3); //RX-TX

double getPressure(){

char status;
double T,P,p0,a;

status = pressure.startTemperature();

if (status != 0){
	delay(status); 
	status = pressure.getTemperature(T); 
if (status != 0){
	status = pressure.startPressure(3);
if (status != 0){
	delay(status);
	status = pressure.getPressure(P,T); //Tamamlanan basınç ölçümü Al :
if (status != 0){ //sıfıra eşit değilse
	return(P); // Ölçüm birimi P saklanır
				}
			}
		}
	}
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
  //make_package("yuk",a, 25, gps.location.lat(), gps.location.lng());
  double ok = gps.location.lat();
  Serial.println(ok);
  post_package();
  delay(500);
}
