#include "LWiFi.h"
#include "LWiFiClient.h"

LWiFiClient cliente;

void setup() {
  // put your setup code here, to run once:
  // networkSSID = "Mitef";
  Serial.begin(9600);
}

void loop() {
  char* response;
  int t_size;
  // put your main code here, to run repeatedly:
  LWiFi.begin();
  Serial.println("Escaneando Redes...");
  int numeroRedes = LWiFi.scanNetworks();
  // Serial.print("Numero de redes... ");  Serial.println(nearbyAccessPointCount);

  for (int i = 0; i != numeroRedes; i++)
  {
    Serial.println(LWiFi.SSID(i));
  }

  Serial.println("Conectando a Mitef...");

  LWiFi.connectWPA("Mitef", "mitef2015");

  Serial.println(LWiFi.status());
  Serial.println("");

  if (LWiFi.status() == 2) {
    cliente.connect("kreelcarlos.cloudapp.net/tinshar/mails", 80);
    cliente.read(response, t_size);
    Serial.println(response);
    cliente.stop();
  }

  LWiFi.end();

  delay(1000);
}
