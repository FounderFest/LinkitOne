#include <LGPS.h>
#define LATITUDE_DATA 1
#define LONGITUDE_DATA 3
#define DATA_LENGTH 20

struct GPSLocation{
  char latitude[DATA_LENGTH];
  char longitude[DATA_LENGTH];  
};

gpsSentenceInfoStruct info;

struct GPSLocation getCoordenates(char* GPGGA){
  GPSLocation coordenates;
  int i = 0;
  int dataCounter = 0;
  int length = strlen(GPGGA);
  while(dataCounter <= LONGITUDE_DATA && i < length) {
    Serial.print(GPGGA[i]);
    if(GPGGA[i] == ','){
      if(dataCounter == LATITUDE_DATA || dataCounter == LONGITUDE_DATA) {
        char *buffer = dataCounter == LATITUDE_DATA ? coordenates.latitude : coordenates.longitude;
        bool bndTerminate = true;
        int j;
        i++;
        for(j = 0; bndTerminate; j++) {
          buffer[j] = GPGGA[i++];
          if(GPGGA[i] == ',') {
            buffer[++j] = GPGGA[++i];
            buffer[++j] = '\0';
            bndTerminate = false;
            dataCounter++;
          }
        }
      }
      dataCounter++; 
    }
    i++;
  }
  Serial.println();
  return coordenates;
}

void setup() {
  Serial.begin(9600);
  LGPS.powerOn();
  Serial.println("GPS prendido!!!");
  delay(500);
}

void loop() {
  char *GPGGA;
  struct GPSLocation coordenates;
  Serial.println("Obteniendo Información");
  LGPS.getData(&info);
  delay(2000);
  GPGGA = (char *)info.GPGGA;
  Serial.println("Se obtuvo información!!!");
  Serial.print("GPGGA: ");
  Serial.println(GPGGA);
  coordenates = getCoordenates(GPGGA);
  Serial.print("Latitud: ");
  Serial.println(coordenates.latitude);
  Serial.print("Longitud: ");
  Serial.println(coordenates.longitude);
}
