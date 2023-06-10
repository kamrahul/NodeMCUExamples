
# MQTT example 

This example demonstates how led can be controlled using mqtt
Here we are using free broker emqx to send and receive mqtt messages

# How to try this example 

- Provide your wifi credentials in the SSID and password section.
- Provide mQTT details.
- Flash the device using Arduino interface
- When program starts it will connect to wifi and then to emqx mqtt connection.
- The current topic to which NodeMCU listens is <b> esp8266/123yougofree</b>.
- Not using MQTTX desktop client send messge to topic Eg . turn_on and turn_off to control the led provided in the board.
