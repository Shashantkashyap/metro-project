#include <Ultrasonic.h>

#include <ThingSpeak.h>

#include<ESP8266WiFi.h>

char ssid[] = "Riya Saini";
char password[] = "qwerty28";
char ServerAdd[] = "api.thingspeak.com";;
unsigned long ChannelID = 797857;
int Field1 = 2;
int Field4 = 5;
char WriteAPIKey[] = "LXZA8Y8EXOKI5P0A";
Ultrasonic ultrasonic (D6, D7);
int mil = 0;
int prevcount = 0;

WiFiClient client;
void setup() {
  Serial.begin(115200);
  WiFiconnect();
}

void loop() {
  int a = ultrasonic.read();
  Serial.println(String(a) + "read from MCU.");
  //  writeTSdata(ChannelID, a, Field1);

    if (millis() - prevcount >= 120000) {
      prevcount = millis();
    }
    mil = millis() - prevcount;
    if(a<50){mil=0;
    prevcount=millis();}
    writeTSdata(ChannelID, a, mil, Field1, Field4);
  
  delay(20000);
}


int writeTSdata2(unsigned long ChannelID,int a, int Field1){
  int writesuccess=ThingSpeak.writeField(ChannelID,Field1,a,WriteAPIKey);
  Serial.println(String(a)+" written to F1.");
  return writesuccess;
}



int writeTSdata(unsigned long ChannelID, int data, int a, int Field1, int Field2) {
  ThingSpeak.setField(Field1, data);
  ThingSpeak.setField(Field2, a);
  int writesuccess = ThingSpeak.writeFields(ChannelID, WriteAPIKey);
  Serial.println(String(data) + " & " + String(a) + " written to." + String(Field1) + "&" + String(Field2));
  return writesuccess;
}

int WiFiconnect() {
  WiFi.begin(ssid, password);
  Serial.println("Connecting."); 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected.");
  ThingSpeak.begin(client);
}

