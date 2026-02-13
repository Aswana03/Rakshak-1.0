#include <SPI.h>
#include <LoRa.h>

#define SS   5
#define RST  27
#define DIO0 26

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println("Starting TX");

  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH);

  SPI.begin(18, 19, 23, SS);
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa failed");
    while (1);
  }

  // Lock parameters
  LoRa.setSpreadingFactor(7);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);
  LoRa.setSyncWord(0x12);

  Serial.println("LoRa ready");
}

void loop() {
  Serial.println("Inside loop");

  LoRa.beginPacket();
  LoRa.print("HELLO");
  LoRa.endPacket(true);   // 🔥 FIX

  Serial.println("Packet sent");
  delay(3000);
}
