
#include <PubSubClient.h>
#include <Ethernet.h>
#include <stdio.h>
#include <iostream>
using namespace std;


// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(172, 16, 0, 100);
IPAddress server(172, 16, 0, 2);

void callback(char* topic, byte* payload, unsigned int length) {
 cout<< "Message arrived [" << endl;
 cout<< topic << endl;
   cout<< "] " << endl;
  for (int i=0;i<length;i++) {
      cout<<((char)payload[i] )<< endl;
  }
}

EthernetClient ethClient;
PubSubClient client(ethClient);

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    cout<< "Attempting MQTT connection..." << endl;
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      cout <<"connected" <<endl;
      // Once connected, publish an announcement...
      client.publish("outTopic","hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      
       cout <<"failed, rc=" <<endl;
       cout <<client.state() <<endl;
       cout <<"try again"<<endl;
 
      // Wait 5 seconds before retrying
  
    }
  }
}

int main(void)
{

  client.setServer(server, 1883);
  client.setCallback(callback);
while(true)
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

  return 0;
}


