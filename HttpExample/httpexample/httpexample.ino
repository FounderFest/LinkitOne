#include <LGPRS.h> 
#include <LGPRSClient.h> 
#include <LWiFi.h> 
#include <LWiFiClient.h> 

#include "HttpClient.h"

//Replace with your information
const char GPRS_APN[] =  "XXXX.XXXX.XX";
const char GPRS_USER[] = "XXXX";
const char GPRS_PASS[] = "XXXX";

//Replace with your configuration
const char SSID[] = "SSDI";
const char PASS[] = "PASS";

const char kHostname[] = "YOURDOMAIN.net";
const char kPath[] = "/";

const int kNetworkTimeout = 30*1000;
const int kNetworkDelay = 1000;

void wifiStatus() {
  switch(LWiFi.status()) {
    case LWIFI_STATUS_DISABLED:
      Serial.println("Modulo apagado");
      break;
    case LWIFI_STATUS_DISCONNECTED:
      Serial.println("Modulo no conectado a ninguna red");
      break;
    case LWIFI_STATUS_CONNECTED:
      Serial.println("Conectado!!!");
      break;
    default:
      break;
  }
}

void setupGPRS() {
  Serial.println(LGPRS.attachGPRS(GPRS_APN,GPRS_USER,GPRS_PASS));
}

void setupWiFi() {
  LWiFi.begin();
  LWiFi.connectWPA(SSID, PASS);
  wifiStatus();
}

void setup() {
  Serial.begin(9600);
  setupWiFi();
  //setupGPRS();
}

void loop() {
  int err = 0;
  LWiFiClient c;
  //LGPRSClient c;
  HttpClient http(c);
  err = http.get(kHostname, kPath);
  if(err == 0) {
    Serial.println("Inicio la petición");
    err = http.responseStatusCode();
    if(err >= 0) {
      Serial.println("Se obtuvo código de estatus:");
      Serial.println(err);

      err = http.skipResponseHeaders();
      if(err >= 0) {
        int bodyLen = http.contentLength();
        int i = 0;
        char body[bodyLen + 1];
        Serial.println("Longitud del contenido");
        Serial.println(bodyLen);
        Serial.println();
        Serial.println("Cuerpo de la respuesta");

        unsigned long timeoutStart = millis();
        //char c;
        while((http.connected() || http.available()) &&
                (millis() - timeoutStart) < kNetworkTimeout){
          if(http.available()) {
            body[i] = http.read();
            //Serial.println(c);
            bodyLen--;
            i++;
            timeoutStart = millis();  
          }
          else {
            delay(kNetworkDelay);
          }
        }
        body[i] = '\0';
        Serial.println(body);
      }
      else {
        Serial.println("Fallo al recibir las cabeceras:");
        Serial.println(err);
      }
    }
    else {
      Serial.println("Fallo al recibir respuesta:");
      Serial.println(err);  
    }
  }
  else {
    Serial.println("Fallo la conexión");
    Serial.println(err);
  }
  http.stop();

  //In to stop making requests
  delay(6000);
}

