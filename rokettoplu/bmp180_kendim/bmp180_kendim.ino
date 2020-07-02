#include <SFE_BMP180.h> 
#include <Wire.h> 

#include <TinyGPS++.h>
TinyGPSPlus gps;
 
SFE_BMP180 pressure; 
 
 // Basınç değeri



#define bobin 6

float ilkkonum;
unsigned long eskizaman=0;
unsigned long yenizaman;
boolean ivme = false; 
double bulundugunkonumsifirkabul,P,denizseviyesiyukseklik;










void ivmefonk(){
  
  yenizaman=millis();
  if(yenizaman-eskizaman<300){
    ilkkonum=bulundugunkonumsifirkabul;
    
    
  }
  if(yenizaman-eskizaman>3000){
    if(bulundugunkonumsifirkabul-ilkkonum<0){
      ivme=true;
      eskizaman=yenizaman;
    }
    if(bulundugunkonumsifirkabul-ilkkonum>0){
      ivme=false;
      eskizaman=yenizaman;
    }
  }
}




double baseline;

void setup()
{
  Serial3.begin(9600);
  Serial.begin(115200);
  digitalWrite(bobin,LOW);
  
  pressure.begin();
  
/*  
if (bmp.begin()){
}
}
//Serial.println("BMP180 Bağlanıldı");
else
{
//Serial.println("BMP180 Bağlanılamadı\n\n");
while(1);
}
*/
baseline = getPressure();
 
Serial.print("Basınç: ");
Serial.print(baseline);
Serial.println(" mb");
pinMode(bobin,OUTPUT);
}

void loop() {
 while (Serial3.available())
      gps.encode(Serial3.read()); 
  
double a,P;

P = getPressure();
bulundugunkonumsifirkabul = pressure.altitude(P,baseline);
denizseviyesiyukseklik = (1013.25-P)*30/3.28083;
 
Serial.print("Yükseklik: ");

Serial.print(bulundugunkonumsifirkabul,1);
Serial.print(" metre, ");

Serial.print(bulundugunkonumsifirkabul*3.28084,0);
Serial.println(" feet");

Serial.print("Deniz Seviyesi Yükseklik: ");

Serial.print(denizseviyesiyukseklik,1);
Serial.print(" metre, ");

Serial.print(denizseviyesiyukseklik*3.28084,0);

Serial.println(" feet");

Serial.print("LAT:");
  Serial.println(gps.location.lat(),6);
  Serial.print("LNG:");
  Serial.println(gps.location.lng(),6);


delay(500);

if(ivme==true){
  if(bulundugunkonumsifirkabul>9 && bulundugunkonumsifirkabul<13){
  digitalWrite(bobin,HIGH);
}
else{
  digitalWrite(bobin,LOW);
}
  
}

ivmefonk();

 

}

double getPressure()
{
char status;
double T,P,p0,a;
 
// Önce bir basınç okuma gerçekleştirmek için bir sıcaklık ölçümünü almak gerekir.
// Ölçüm birimi T saklanır
// Kullan 'T' işlevine T adresini sağlamak.
// Fonksiyon döner başarılı olursa 1, başarısızlık ise 0.
status = pressure.startTemperature();//Bir sıcaklık ölçümü başlatılır
if (status != 0) //
{
delay(status); // Ölçüm tamamlanması için bekle
status = pressure.getTemperature(T); // T değerini ölç
if (status != 0) //Sıfırdan faklı ise
{
status = pressure.startPressure(3);//Basınç ölçümünü başlat
if (status != 0)
{
// Parametre 0 ila 3 örnekleme ayarı, (en yüksek res, uzun bekleme) 'dir.
// Istek başarılı olursa beklemek ms sayısı döndürülür.
// Istek başarısız olursa 0 döndürülür.
 
delay(status);// Ölçümünü tamamlanmasını bekle
 
// 'P' adresi sağlamak için
// Not ayrıca işlev önceki sıcaklık ölçümü (T) gerektirir.
// (Sıcaklık kararlı ise, basınç ölçümleri bir dizi için tek ısı ölçümü yapabilirsiniz.)
// Fonksiyon döner başarılı olursa 1 , başarısızlık ise 0
 
status = pressure.getPressure(P,T); //Tamamlanan basınç ölçümü Al :
if (status != 0) //sıfıra eşit değilse
{
return(P); // Ölçüm birimi P saklanır
}
// P sıfıra eşitse
else Serial.println("Basınç ölçümünde hata alındı\n");
}
// P sıfıra eşitse
else Serial.println("Basınç Ölçümü başlatılamadı\n");
}
// T sıfıra eşitse
else Serial.println("Sıcaklık değeri alınamadı\n");
}
// T sıfıra eşitse
else Serial.println("Sıcaklık ölçümü başlatılamadı\n");
}
