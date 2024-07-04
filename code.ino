/* https://arduino.esp8266.com/stable/package_esp8266com_index.json
 * ESP8266 as Web Server using WiFi Access Point (AP) mode
 * Connect to AP "Robot Wifi", password = "87654321"
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;


//#include <ESP8266WiFi.h>
//#include <BlynkSimpleEsp8266.h>

//SSID and Password to your ESP Access Point
char ssid[] = "Robot Wifi";  // type your wifi name
char password[] = "87654321";  // type your wifi password

#define ENA   4     // Enable/speed motors Right    GPIO4(D2)
#define IN_1  0     // L298N in1 motors Right       GPIO0(D3)
#define IN_2  2     // L298N in2 motors Right       GPIO2(D4)
#define IN_3  12    // L298N in3 motors Left        GPIO12(D6)
#define IN_4  13    // L298N in4 motors Left        GPIO13(D7)
#define ENB   15    // Enable/speed motors Left     GPIO15(D8)

#define Light  16 // Light  GPIO16(D0)

String command;             //String to store app command state.
int speedCar = 150; // 0 to 255
int speed_low = 60;

Servo myservo1, myservo2, myservo3, myservo4;
ESP8266WebServer server(80);



void setup() {
 
  Serial.begin(115200);

  motor1.attach(1, 500, 2400); // NodeMCU TX pin
  motor1.write(0); //up-down
  
  motor2.attach(3, 500, 2400); // NodeMCU RX pin
  motor2.write(100); //Left-Center-Right

   motor3.attach(14, 500, 2400); // NodeMCU D5 pin
  motor3.write(40); //Forward-Center-Backward

  motor4.attach(5, 500, 2400); // NodeMCU D1 pin
  motor4.write(0); //Grab-Release

 pinMode(ENA, OUTPUT); 
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT);
 pinMode(ENB, OUTPUT); 

 pinMode(Light, OUTPUT); 
 
  
// Connecting WiFi

  WiFi.mode(WIFI_AP);           //Only Access point
  WiFi.softAP(ssid, password);  //Start HOTspot removing password will disable security

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void loop() {
  
      server.handleClient();
    
      command = server.arg("State");
      if (command == "F") Forword();
      else if (command == "B") Back();
      else if (command == "L") Left();
      else if (command == "R") Right();

      
      else if (command == "HOn") digitalWrite(Light, HIGH);
      else if (command == "BOn") digitalWrite(Light, HIGH);
      else if (command == "Off") digitalWrite(Light, LOW);
      else if (command == "Off") digitalWrite(Light, LOW);

      
      else if (command == "0") speedCar = 100;
      else if (command == "1") speedCar = 120;
      else if (command == "2") speedCar = 140;
      else if (command == "3") speedCar = 160;
      else if (command == "4") speedCar = 180;
      else if (command == "5") speedCar = 200;
      else if (command == "6") speedCar = 215;
      else if (command == "7") speedCar = 230;
      else if (command == "8") speedCar = 240;
      else if (command == "9") speedCar = 255;
      else if (command == "S") stopRobot();
      

      else if (command == "Up") up();
      else if (command == "Down") down();
      else if (command == "AL") ArmLeft();
      else if (command == "AC") ArmCenter();
      else if (command == "AR") ArmRight();
      else if (command == "AB") ArmBack();
      else if (command == "ARC") ARC();
      else if (command == "AF") ArmForward();
      else if (command == "G") Grab();
      else if (command == "R2") Release();
      

}


void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}

void Forword(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }

void Back(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void Right(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }

void Left(){

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void stopRobot(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
 }


int srv1=0;
void down(){ 
  
      while(srv1>=0)
      {
        srv1=srv1-5;
        motor1.write(srv1);
      }
  }

void up(){ 
  
  while(srv1<=50)
  {
    srv1=srv1+5;
    motor1.write(srv1);
  }
}




int srv2=100;
void ArmLeft(){ 
  
      while(srv2<=180)
      {
        srv2=srv2+8;
        motor2.write(srv2);
//          digitalWrite(LED_BUILTIN, HIGH);
//          delay(30);
      }
  }

void ArmCenter(){ 
  
  while(srv2!=100)
  {
    if (srv2>100){
      srv2=srv2-8;
      motor2.write(srv2);
//      delay(30);
    }

    if (srv2<100){
      srv2=srv2+8;
      motor2.write(srv2);
//      delay(30);
    }
//          digitalWrite(LED_BUILTIN, HIGH);
          
  }
}

void ArmRight(){ 
  
      while(srv2>=0)
      {
        srv2=srv2-8;
        motor2.write(srv2);
//          digitalWrite(LED_BUILTIN, HIGH);
//          delay(30);
      }
  }

int srv3=40;
void ArmForward(){ 
  
      while(srv3>=20)
      {
        srv3=srv3-5;
        motor3.write(srv3);
//        delay(50);
      }
  }

void ARC(){ 
  
      while(srv3!=20)
      {
        if (srv3>40){
          srv3=srv3-5;
          motor3.write(srv3);
//          delay(50);  
        }


        if (srv3<40){
          srv3=srv3+5;
          motor3.write(srv3);  
//          delay(50);
        }
      }
  }

void ArmBack(){ 
  
      while(srv3<=55)
      {
        srv3=srv3+5;
        motor3.write(srv3);
//        delay(50);
      }
  }

int srv4=0;
void Grab(){
  while(srv4>=0)
      {
        srv4=srv4-5;
        motor4.write(srv4);
      }
}

void Release(){
  while(srv4<=50)
      {  
        srv4=srv4+5;
        motor4.write(srv4);
      }
}
