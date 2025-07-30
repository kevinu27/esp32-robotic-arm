
#include <WiFi.h>
#include <WebServer.h>
#define LIMIT_SWITCH_CODO_PIN 4
#define LIMIT_SWITCH_HOMBRO_PIN 5

#define STEP_PIN_BASE 15
#define DIR_PIN_BASE 16
#define ENABLE_PIN_BASE 17  // opcional

#define STEP_PIN_HOMBRO 18
#define DIR_PIN_HOMBRO 19
#define ENABLE_PIN_HOMBRO 21  // opcional

#define STEP_PIN_CODO 12
#define DIR_PIN_CODO 13
#define ENABLE_PIN_CODO 22  // opcional

        int firstSepMotor1Base;
        int secondSepMotor1Base;
        int firstSepMotor2;
        int secondSepMotor2;
        int firstSepMotor3Codo;
        int secondSepMotor3Codo;

        String motor1Dir;
        String motor1Angle;
        int motor1SteppingInt;
        String motor2Dir;
        String motor2Angle;
        int motor2SteppingInt;
        String motor3Dir;
        String motor3Angle ;
        int motor3SteppingInt;

        bool motor1BaseInTarget = false;
        bool motor2HomrboInTarget = false;
        bool motor3CodoInTarget = false;

        int relacionTrasmisionMotor1Base = 2;
        int motor1AngleInt = 0;
        int stepsToMove1 = 0;
        int stepsToMoveWithTRansmision1Base = 1;
        int stepsToMoveWithTRansmision1BaseRemaining = 0;

        int relacionTrasmisionMotor2Hombro = 5;
        int motor2AngleInt = 0;
        int stepsToMove = 0;
        int stepsToMoveWithTRansmision = 1;
        int stepsToMoveWithTRansmisionRemaining = 0;
        
        int relacionTrasmisionMotor3Codo = 5;
        int motor3AngleInt = 0;
        int stepsToMove3 = 0;
        int stepsToMoveWithTRansmision3Codo = 1;
        int stepsToMoveWithTRansmision3CodoRemaining = 0;

// WiFi credentials
const char* ssid = "MIWIFI_EXtU";
const char* password = "4GFCfAfR";

// Create web server on port 80
WebServer server(80);

// Variables to store the split values
String firstTwoChars = "";
String restOfString = "";

void setup() {
  Serial.begin(115200);
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  // Enable CORS for all routes
  server.enableCORS(true);
  // Route to handle data reception
  server.on("/sendData", HTTP_POST, handleDataReceived);
  // Route to handle preflight requests
  server.on("/sendData", HTTP_OPTIONS, handleOptions);
  // Start server
  server.begin();
  Serial.println("Server started");

  //motor
  pinMode(STEP_PIN_HOMBRO, OUTPUT);
  pinMode(DIR_PIN_HOMBRO, OUTPUT);
  pinMode(ENABLE_PIN_HOMBRO, OUTPUT);
  pinMode(STEP_PIN_BASE, OUTPUT);
  pinMode(DIR_PIN_BASE, OUTPUT);
  pinMode(ENABLE_PIN_BASE, OUTPUT);
  pinMode(STEP_PIN_CODO, OUTPUT);
  pinMode(DIR_PIN_CODO, OUTPUT);
  pinMode(ENABLE_PIN_CODO, OUTPUT);

  digitalWrite(ENABLE_PIN_BASE, HIGH); 
  digitalWrite(ENABLE_PIN_HOMBRO, HIGH); 
  digitalWrite(ENABLE_PIN_CODO, HIGH); 

  digitalWrite(DIR_PIN_BASE, LOW);
  digitalWrite(DIR_PIN_HOMBRO, LOW);
  digitalWrite(DIR_PIN_CODO, LOW);

  pinMode(LIMIT_SWITCH_CODO_PIN, INPUT_PULLUP); 
  pinMode(LIMIT_SWITCH_HOMBRO_PIN, INPUT_PULLUP); 
}

void loop() {
  server.handleClient();
    if (digitalRead(LIMIT_SWITCH_HOMBRO_PIN) == LOW) {
    Serial.println("BASE activado");
  } else {
    Serial.println("BASE inactivo");
  }
  delay(500);
}

void handleOptions() {
  Serial.print("handleOptions");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "POST, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  server.send(200, "text/plain", "");
  Serial.print("handleOptions end");
}

void handleDataReceived() {
  // Add CORS headers
   Serial.print("handleDataReceived");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "POST, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  
  String response = "";
  
  if (server.hasArg("data")) {
    String receivedData = server.arg("data");
    
    Serial.println("Received data: " + receivedData);
    
    // Check if string has at least 2 characters
    if (receivedData.length() >= 2) {
    
        int firstSep = receivedData.indexOf('/');
        int secondSep  = receivedData.indexOf('/', firstSep + 1);
        
        String motor1Base = receivedData.substring(0, firstSep);
        String motor2Hombro = receivedData.substring(firstSep + 1, secondSep);
        String motor3Codo = receivedData.substring(secondSep + 1);


        int firstSepMotor1 = motor1Base.indexOf('-');
        int secondSepMotor1  = motor1Base.indexOf('-', firstSepMotor1 + 1);
         motor1Dir = motor1Base.substring(0, firstSepMotor1);
         motor1Angle = motor1Base.substring(firstSepMotor1 + 1, secondSepMotor1);
         motor1SteppingInt = motor1Base.substring(secondSepMotor1 + 1).toInt();
        motor1AngleInt = motor1Angle.toInt();
        Serial.print("motor1AngleInt: " );
        Serial.println(motor1AngleInt);
        motor1SteppingInt = motor1Base.substring(secondSepMotor1 + 1).toInt();
        Serial.print("motor1SteppingInt: " );
        Serial.println(motor1SteppingInt);
        stepsToMove1 = (motor1AngleInt * motor1SteppingInt) / 360;
        stepsToMoveWithTRansmision1Base = stepsToMove1 * relacionTrasmisionMotor1Base ;
        stepsToMoveWithTRansmision1BaseRemaining = stepsToMoveWithTRansmision1Base;

        firstSepMotor2 = motor2Hombro.indexOf('-');
        secondSepMotor2  = motor2Hombro.indexOf('-', firstSepMotor2 + 1);
        motor2Dir = motor2Hombro.substring(0, firstSepMotor2);
        motor2Angle = motor2Hombro.substring(firstSepMotor2 + 1, secondSepMotor2);
        motor2AngleInt = motor2Angle.toInt();
        Serial.print("motor2AngleInt: " );
        Serial.println(motor2AngleInt);
        motor2SteppingInt = motor2Hombro.substring(secondSepMotor2 + 1).toInt();
        Serial.print("motor2SteppingInt: " );
        Serial.println(motor2SteppingInt);
        stepsToMove = (motor2AngleInt * motor2SteppingInt) / 360;
        stepsToMoveWithTRansmision = stepsToMove * relacionTrasmisionMotor2Hombro ;
        stepsToMoveWithTRansmisionRemaining = stepsToMoveWithTRansmision;
        
        int firstSepMotor3 = motor3Codo.indexOf('-');
        int secondSepMotor3  = motor3Codo.indexOf('-', firstSepMotor3 + 1);
         motor3Dir = motor3Codo.substring(0, firstSepMotor3);
         motor3Angle = motor3Codo.substring(firstSepMotor3 + 1, secondSepMotor3);
         motor3SteppingInt = motor3Codo.substring(secondSepMotor3 + 1).toInt();
         motor3AngleInt = motor3Angle.toInt();
        Serial.print("dir///" + motor3Dir );
        Serial.println(motor3Dir);
        Serial.print("motor3SteppingInt: " );
        Serial.println(motor3SteppingInt);
        stepsToMove3 = (motor3AngleInt * motor3SteppingInt) / 360;
        stepsToMoveWithTRansmision3Codo = stepsToMove3 * relacionTrasmisionMotor3Codo ;
        stepsToMoveWithTRansmision3CodoRemaining = stepsToMoveWithTRansmision3Codo;
        Serial.println("stepsToMoveWithTRansmision3Codo" + stepsToMoveWithTRansmision3Codo);
        Serial.println("stepsToMoveWithTRansmision3CodoRemaining" + stepsToMoveWithTRansmision3CodoRemaining);
        Serial.println("stepsToMove" + stepsToMove);

        Serial.println("motor1Base: " + motor1Base);
        Serial.println("otor2Hombro: " + motor2Hombro);
        Serial.println("motor3Codo: " + motor3Codo);
        Serial.println("motor2Dir: " + motor2Dir);
        Serial.println("motor2Angle: " + motor2Angle);
        Serial.println("motor2SteppingInt: " + motor2SteppingInt);
      
        if(motor1AngleInt < 1){
          Serial.println(" en el if de motor1AngleInt < 1");
          Serial.print("motor1AngleInt: " );
          Serial.println(motor1AngleInt);
          motor1BaseInTarget = true;
        }else{
          motor1BaseInTarget = false;
          }
          
        if(motor2AngleInt < 1){
          Serial.println(" en el if de motor2AngleInt < 1");
          Serial.print("motor2AngleInt: " );
          Serial.println(motor2AngleInt);
          motor2HomrboInTarget = true;
        }else{
          motor2HomrboInTarget = false;
          }
          Serial.print("motor3AngleInt: ---------------" );
          Serial.println(motor3AngleInt);
        if(motor3AngleInt < 1){
          Serial.println(" en el if de motor3AngleInt < 1");
          Serial.print("motor3AngleInt: " );
          Serial.println(motor3AngleInt);
          motor3CodoInTarget = true;
        }else{
          motor3CodoInTarget = false;
          }

       if(motor1AngleInt > 0 || motor2AngleInt > 0 || motor3AngleInt > 0){
        Serial.println(" en el if de motor1AngleInt > 0 || motor2AngleInt > 0 || motor3AngleInt > 0 < 1 ");
         moverMotor();
       }       


      // Create success response
      response = "{\"status\":\"success\",\"message\":\"Data processed successfully\",\"firstTwo\":\"" + firstTwoChars + "\",\"rest\":\"" + restOfString + "\"}";
      
      server.send(200, "application/json", response);
    } else {
      // Error: string too short
      Serial.println("Error: String too short (less than 2 characters)");
      response = "{\"status\":\"error\",\"message\":\"String must have at least 2 characters\"}";
      server.send(400, "application/json", response);
    }
  } else {
    // Error: no data received
    Serial.println("Error: No data received");
    response = "{\"status\":\"error\",\"message\":\"No data received\"}";
    server.send(400, "application/json", response);
  }
  Serial.print("handleDataReceived end");
}

void moverMotor() {
  if(motor1Dir == "0"){
    Serial.println("en el if de (motor1Dir == 0): " );
    digitalWrite(DIR_PIN_BASE, HIGH); 
    }
  if(motor1Dir == "1"){
      Serial.println("en el if de (motor1Dir == 1): " );
      digitalWrite(DIR_PIN_BASE, LOW); 
    }

  if(motor2Dir == "0"){
    Serial.println("en el if de (motor2Dir == 0): " );
    digitalWrite(DIR_PIN_HOMBRO, LOW); 
    }
  if(motor2Dir == "1"){
      Serial.println("en el if de (motor2Dir == 1): " );
      digitalWrite(DIR_PIN_HOMBRO, HIGH); 
    }

  if(motor3Dir == "0"){
    Serial.println("en el if de (motor3Dir == 0): " );
    digitalWrite(DIR_PIN_CODO, LOW); 
    }
  if(motor3Dir == "1"){
      Serial.println("en el if de (motor3Dir == 1): " );
      digitalWrite(DIR_PIN_CODO, HIGH); 
    }

  while (motor1BaseInTarget == false || motor2HomrboInTarget == false || motor3CodoInTarget == false) {
    Serial.println("lopp ");

    if(motor1BaseInTarget == false){
      digitalWrite(STEP_PIN_BASE, HIGH);
      delayMicroseconds(100); // velocidad del motor
      digitalWrite(STEP_PIN_BASE, LOW);
      delayMicroseconds(100);
      stepsToMoveWithTRansmision1BaseRemaining = stepsToMoveWithTRansmision1BaseRemaining - 1;
      if(stepsToMoveWithTRansmision1BaseRemaining < 1){
        motor1BaseInTarget = true;
      }
    }

    if(motor2HomrboInTarget == false){
      digitalWrite(STEP_PIN_HOMBRO, HIGH);
      delayMicroseconds(100); // velocidad del motor
      digitalWrite(STEP_PIN_HOMBRO, LOW);
      delayMicroseconds(100);
      stepsToMoveWithTRansmisionRemaining =stepsToMoveWithTRansmisionRemaining - 1;
      if(stepsToMoveWithTRansmisionRemaining < 1){
        motor2HomrboInTarget = true;
      }
    }

    if(motor3CodoInTarget == false){
      digitalWrite(STEP_PIN_CODO, HIGH);
      delayMicroseconds(100); // velocidad del motor
      digitalWrite(STEP_PIN_CODO, LOW);
      delayMicroseconds(100);
      stepsToMoveWithTRansmision3CodoRemaining =stepsToMoveWithTRansmision3CodoRemaining - 1;
      if(stepsToMoveWithTRansmision3CodoRemaining < 1){
        Serial.print("******" + stepsToMoveWithTRansmision3CodoRemaining );
        motor3CodoInTarget = true;
      }
    }
  }

  // for (int i = 0; i < stepsToMoveWithTRansmision; i++) {
  //    Serial.println("lopp ");
  //   digitalWrite(STEP_PIN_HOMBRO, HIGH);
  //   delayMicroseconds(100); // velocidad del motor
  //   digitalWrite(STEP_PIN_HOMBRO, LOW);
  //   delayMicroseconds(100);
  // }

  Serial.println("Motor movido ");


}
