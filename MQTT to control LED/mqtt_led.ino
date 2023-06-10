#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <string.h>



// WiFi
const char *ssid = "ABC"; // Enter your WiFi name
const char *password = "ABC";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "broker.emqx.io"; // broker address
const char *topic = "esp8266/123yougofree"; // define topic 
const char *mqtt_username = "emqx"; // username for authentication
const char *mqtt_password = "public"; // password for authentication
const int mqtt_port = 1883; // port of MQTT over TCP


const int ledPin =  2;  // LEd pin


WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // Set software serial baud to 115200;
  Serial.begin(115200);
  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
      String client_id = "esp8266-client-";
      client_id += String(WiFi.macAddress());
      Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
      if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
          Serial.println("Public emqx mqtt broker connected");
      } else {
          Serial.print("failed with state ");
          Serial.print(client.state());
          delay(2000);
      }
  }
  // publish and subscribe
  client.publish(topic, "hello emqx"); // publish to the topic
  client.subscribe(topic); // subscribe from the topic

  // initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  //Serial.print("Message:");
  char command_params[] = "";
  
 
  for (int i = 0; i < length; i++) {
      //Serial.print((char) payload[i]);
      //command_params[i] += (unsigned char) payload[i];
      //command_params[i] += (char) payload[i];
      //Serial.println(command_params);
      char test = (char) payload[i];
      strncat(command_params,&test,1);
  }
  Serial.println(command_params);
  Serial.println("-----------------------");

  if (strcmp(command_params, "turn_on")==0){
      // turn LED on
    Serial.println(" TURNED ON ");
    digitalWrite(ledPin, LOW);
    delay(1000);
  }
  else if (strcmp(command_params, "turn_off")==0){

     Serial.println(" TURNED OFF ");

    digitalWrite(ledPin, HIGH);

  }

  

}

void loop() {
  client.loop();
}
