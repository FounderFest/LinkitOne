#include <LGPS.h>
#define LATITUDE_DATA 2
#define LONGITUDE_DATA 4
#define DATA_LENGTH 20

/*struct GPSLocation{
  char latitude[DATA_LENGTH];
  char longitude[DATA_LENGTH];  
};*/

gpsSentenceInfoStruct info;


void setup() {
  Serial.begin(9600);
  LGPS.powerOn();
  Serial.println("GPS prendido!!!");
  delay(500);
}

void loop() {
  char *GPGGA;
  //struct GPSLocation coordenates;
  Serial.println("Obteniendo Información");
  LGPS.getData(&info);
  delay(2000);
  GPGGA = (char *)info.GPGGA;
  //strcpy(GPGGA,(char *)info.GPGGA);
  Serial.println("Se obtuvo información!!!");
  Serial.print("GPGGA: ");
  Serial.println(GPGGA);
  /*coordenates = getCoordenates(GPGGA);
  Serial.print("Latitud: ");
  Serial.println(coordenates.latitude);
  Serial.print("Longitud: ");
  Serial.println(coordenates.longitude);*/
  //while(1);
}
