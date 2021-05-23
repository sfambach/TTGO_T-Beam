#ifndef MY_MQTT_H
#define MY_MQTT_H
#include "debug.h"
#include "credentials.h"
#include <PubSubClient.h>
#include "mywifi.h"
PubSubClient mqttClient(espClient);

void receivedCallback(char* topic, byte* payload, unsigned int length) 
{
  DEBUG_PRINT("[MQTT] Message received: ");
  DEBUG_PRINTLN(topic);

  DEBUG_PRINT("[MQTT] payload: ");
  for (int i = 0; i < length; i++) DEBUG_PRINT((char)payload[i]);
  DEBUG_PRINTLN();
}

void mqttSetup()
{
  /* configure the MQTT server with IPaddress and port */
  mqttClient.setServer(BROKER, BRPORT);
  /* this receivedCallback function will be invoked 
  when client received subscribed topic */
  mqttClient.setCallback(receivedCallback);
}

boolean mqttConnected(){
  boolean con = mqttClient.connected();
 // DEBUG_PRINTLN(String(" Connected=")+String(con?"TRUE":"FALSE"));
  return con;
}

void mqttConnect() {
  DEBUG_PRINT("[MQTT] Check connection ...");
  /* Loop until reconnected */
  while (!mqttConnected()) {
    DEBUG_PRINT("connecting ...");
    mqttSetup();
    mqttClient.disconnect();
    
    /* connect now */
    if (mqttClient.connect(CLIENTID, BRUSER, BRPWD)) {
      DEBUG_PRINT(mqttClient.state());
      DEBUG_PRINTLN("connected");
      break;
    } else {
      DEBUG_PRINT(" failed, status code =");
      DEBUG_PRINTLN(mqttClient.state());
      DEBUG_PRINTLN("[MQTT] failed try again in 5 seconds");
      /* Wait 5 seconds before retrying */
      delay(5000);
    }
  }

  DEBUG_PRINTLN("[MQTT] Doing things");
}

void mqttPublish(const char* topic, const char* content){
  DEBUG_PRINT("[MQTT] send str   message  \t");
  DEBUG_PRINT("Topic: ");
  DEBUG_PRINT(topic);
  DEBUG_PRINT(" Value: ");
  DEBUG_PRINTLN(content);
  
  mqttClient.publish(topic, content);  
}
void mqttPublish(const char* topic, int32_t content){
  DEBUG_PRINT("[MQTT] send int   message  \t");
  DEBUG_PRINT("Topic: ");
  DEBUG_PRINT(topic);
  DEBUG_PRINT(" Value: ");
  DEBUG_PRINTLN(content);
  mqttClient.publish(topic, String(content).c_str());  
}


void mqttPublish(const char* topic, float content){
  DEBUG_PRINT("[MQTT] send float message \t");
  DEBUG_PRINT("Topic: ");
  DEBUG_PRINT(topic);
  DEBUG_PRINT(" Value: ");
  DEBUG_PRINTLN(content);
  mqttClient.publish(topic, String(content).c_str());  
}


void mqttDisconnect(){
  DEBUG_PRINTLN("[MQTT] Disconnect");
  mqttClient.disconnect();
}

void mqttLoop(){
  if(!mqttConnected()){
    mqttConnect();
  }
  mqttClient.loop();
}
#endif // #define MY_MQTT_H
