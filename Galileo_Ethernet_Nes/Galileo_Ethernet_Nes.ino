#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {  0x98, 0x4F, 0xEE, 0x00, 0x0A, 0x89 };
char server[] = "www.dinorobotics.net"; // Server

EthernetClient client;

char incomingByte;  // incoming data
int  LED = 7;      // LED pin

String snapToString = "";

int counter = 0;
unsigned char snapshot = 0;
unsigned char data = 8;
unsigned char nesClock = 9;
unsigned char latch = 10;

unsigned char onStandby = 1;
//orange: VCC

//white: GND

//black: data (8)

//blue: CLK (9)

//yellow: latch (10)

void GetNESControllerData() {
  digitalWrite(latch, HIGH);
  digitalWrite(latch, LOW);
  snapshot = 0x00;

  for (unsigned char i = 0; i <= 7; ++i) {
    snapshot = (~digitalRead(data) & 0x01) << i | snapshot;
    digitalWrite(nesClock, HIGH);
    digitalWrite(nesClock, LOW);
    
  }
  
  //delay(100); //////////////////////////////// Delay Here
}

void NESControllerTick() {

// 	NES_A       B00000001
// 	NES_B       B00000010
//      NES_SELECT  B00000100
// 	NES_START   B00001000
// 	NES_UP      B00010000
// 	NES_DOWN    B00100000
// 	NES_LEFT    B01000000
// 	NES_RIGHT   B10000000

  GetNESControllerData();
  
  if(snapshot == 0 && onStandby){
    snapToString = String(snapshot);
    sendData(snapToString);
  }
  else if(snapshot == 0 && !onStandby){
    onStandby = 1;
    snapToString = String(snapshot);
    sendData(snapToString);
    //delay(50);
    //sendData(snapToString);
    Serial.println(snapshot);
  }
  else{
    onStandby = 0;
    snapToString = String(snapshot);
    sendData(snapToString);  
    Serial.println(snapshot);
  }
  delay(50);
  snapshot = 0;
}
 
void setup() {
  Serial.begin(9600); // initialization
  pinMode(LED, OUTPUT);
  pinMode(data, INPUT);
  pinMode(nesClock, OUTPUT);
  pinMode(latch, OUTPUT);
  
  Serial.println("connecting...");
  system("ifup eth0");
  delay(5000);

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /commands.php?command=0 HTTP/1.1");
    client.print( "Host: " );
    client.println( "dinorobotics.net" );
    client.println();
    client.println();
    client.stop();
  } 
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void sendData(String command){
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.print("GET /commands.php?command=");
    client.print(command);
    client.println(" HTTP/1.1");
    client.print( "Host: " );
    client.println( "dinorobotics.net" );
    client.println();
    client.println();
    client.stop();
  } 
  
  
}
 
void loop() {
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  NESControllerTick();
  
}
