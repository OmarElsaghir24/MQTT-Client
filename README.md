# MQTT-Client
Developed an MQTT Client using the TM4C123GH6PM microcontroller that is able to publish, subscribe, and unsubscribe to topics on the mosquitto MQTT broker. Used an ENC28J60 ethernet module to establish communication between microcontroller and MQTT broker.

   
         ![MQTT Cient](https://github.com/user-attachments/assets/ba05377b-7490-497d-89ee-7563b4d11a41)




# Hardware Components
|                         |
|-------------------------|
| TM4C123GH6PM Tiva Board |
| ENC28J60 Ethernet Module|
| Ethernet cable          |

# Peripherals Used
|               |
|---------------|
| EEPROM        |
| UART          |
| SPI           |
| TIMERS        |

# Software Features
 * `reboot`: This command restarts the microcontroller.
 * `ip`:  status: This command displays the IP and MQTT address, the MQTT connection state, and the TCP FSM state.
 * `set IP w.x.y.z`: This command sets the IP address  and stores this address persistently in EEPROM.
 * `set MQTT w.x.y.z`: This command sets the IP address of the MQTT broker and stores this address persistently in EEPROM.
 * `publish TOPIC DATA`: This command publishes a topic and associated data to the MQTT broker.
 * `subscribe TOPIC`: This command subscribes to a topic.
 * `unsubscribe TOPIC`: This command unsubscribes from a topic.
 * `connect`: This command sends a connect message to the MQTT broker.
 * `disconnect`: The command disconnects from the MQTT broker.
 
