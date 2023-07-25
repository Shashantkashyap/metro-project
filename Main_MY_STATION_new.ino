#include <ThingSpeak.h>
#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#include <Ultrasonic.h>


char ssid[]="Riya Saini";
char password[]="qwerty28";
String op1;
String op2;
char auth[] = "911b77ed9b074ca6ac6ddbb21bda4e22";
char ServerAdd[]="api.thingspeak.com";;
unsigned long ChannelID=797857;
int Field1=1;
int Field2=2;
int Field3=3;
int Field4=4;
int Field5=5;
int Field6=6;
int Field7=7;
int Field8=8;
//int Field9=9;
//int Field10=10;
char ReadAPIKey[]="J80G2QW6CEQNH8W2";
int s1,s2,s3,s4,s5,timemillis1,timemillis2,timemillis3,timemillis4,timemillis5;

WiFiClient client;

int timegap=120000;
int ind;
int my_station=1;
int k;
int arr2[3]={5,4,3};//denotes metro konse station pe hai
int arr3[3];//jaha se metro shuru huyi vaha se mujhse kitni door thi
float arr4[4];//Times left for every metro in order
int iind;
//int mil[4];

void setup() {
   Serial.begin(115200);
   WiFiconnect();
}

void loop() {   
  
  // put your main code here, to run repeatedly:
  s1=readTSdata(ChannelID,Field1);
  s2=readTSdata(ChannelID,Field2);
  s3=readTSdata(ChannelID,Field3);
  s4=readTSdata(ChannelID,Field4);
  //s5=readTSdata(ChannelID,Field5);
  timemillis1=readTSdata(ChannelID,Field5);
  timemillis2=readTSdata(ChannelID,Field6);
  timemillis3=readTSdata(ChannelID,Field7);
  timemillis4=readTSdata(ChannelID,Field8);
  //timemillis5=readTSdata(ChannelID,Field10);
 int mil[4]={timemillis4,timemillis3,timemillis2,timemillis1};

  
 
 int arr[4]={s1,s2,s3,s4};
  k=2;
   for(ind=0;ind<4;ind++){
    if(arr[ind]<50){
      arr2[k]=4-ind;
      k--;
      }
  }
 
  for(ind=0;ind<3;ind++){  
    arr3[ind]=(arr2[ind]-my_station)*timegap;
    }

  ind=0;
  for(ind=0;ind<3;ind++){
    iind=arr2[ind]-1;
  arr4[ind] = float(arr3[ind]-mil[iind])/60000;
  }

  /*
   for(ind=0;ind<4;ind++){Serial.print(String(arr[ind]));}
   Serial.println();
   for(ind=0;ind<3;ind++){Serial.print(String(arr2[ind]));}
   Serial.println();
   /*for(ind=0;ind<2;ind++){Serial.print(String(arr3[ind]));}
   Serial.println();
   for(ind=0;ind<2;ind++){Serial.print(String(arr4[ind]));}
   Serial.println();
   */
  

  Serial.println("------------------------------------");
  Serial.println("------------------------------------");
  
  for(ind=0;ind<3;ind++){
    Serial.println("Metro number " + String(ind+1) + " : \n Last Left stn = " + String(arr2[ind]) + " ||| Time left = " + String(arr4[ind]) + " minutes away." );
    Serial.println("------------------------------------");
  }
  
  Serial.println("------------------------------------");
  Serial.println("------------------------------------");
  
 Serial.println(String(s1)+" " +String(s2)+" " +String(s3)+ " " +String(s4)+" READ FROM SERVER.");
delay(20000);
  
}


float readTSdata(unsigned long ChannelID,int Field1){
  float a=ThingSpeak.readFloatField(ChannelID,Field1,ReadAPIKey);
  //Serial.println(String(a,9)+ " read from server.");
  return a;
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

