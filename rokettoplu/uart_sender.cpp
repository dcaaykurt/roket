#include "uart_sender.h"
void uart_init(long br){
	Serial.begin(br);
}

//	@arg void
//	paketin içini boşaltır
//	@return NONE	
void set_package(void){
	PACKAGE = "";
}

//	@arg device: roket = 1, diger = 0
//	@arg altitude: yukseklik degeri
//	@arg speed: hiz
//	@arg gpsLat: gps enlem
//	@arg gpsLong: gps boylam
//	@return NONE
void make_package(String device, int altitude, int speed, float gpsLat, float gpsLong){
	PACKAGE = (device == "roket") ? "1" : "0";
	PACKAGE += "/";
	PACKAGE += String(altitude);
	PACKAGE += "/";
	PACKAGE += String(speed);
	PACKAGE += "/";
	PACKAGE += String(gpsLat, FLOAT_PRECISION);
	PACKAGE += "/";
	PACKAGE += String(gpsLong, FLOAT_PRECISION);

}

//	@arg void
//	paketi postalar
//	@return NONE
void post_package(void){
	Serial.println(PACKAGE);
	//set_package();
}

void setup() {
	uart_init(115200);
	set_package();
}

void loop() {
	/*make_package("roket", 250, 25, 25.565484, 22.484512);
	post_package();
	delay(20);*/
	make_package("yuk", 251, 23, 25.325654, 22.411523);
	post_package();
	delay(50);
}
