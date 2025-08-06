
#include <WiFi.h>
#include <WebServer.h>
#define LIMIT_SWITCH_CODO_PIN 4
#define LIMIT_SWITCH_HOMBRO_PIN 5
#define LIMIT_SWITCH_BASE_PIN 14

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
        float baseDiffAngle;
        float hombroDiffAngle;
        float codoDiffAngle;

float baseAngle ;
float hombroAngle ;
float codoAngle ;


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

  server.on("/homing", HTTP_POST, homing);

  server.on("/movetoposition", HTTP_POST, moveToPosition);
  server.on("/movetoposition", HTTP_OPTIONS, handleOptions);


  
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
  pinMode(LIMIT_SWITCH_BASE_PIN, INPUT_PULLUP); 
}

void loop() {
  server.handleClient();

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
  Serial.print("handleDataReceived end del handleDataReceived");
}

void moveToPosition() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "POST, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  Serial.println("moveToPosition");
  String response = "";
  
  if (server.hasArg("data")) {
    String receivedData = server.arg("data");
    
    Serial.println("Received data en el moveToPosition-----: " + receivedData);
    
    receivedData.trim();

   if (receivedData.length() >= 5 && receivedData.indexOf('/') > 0) {
      Serial.println("Entró al if correctamente");

      int firstSlash = receivedData.indexOf('/');
      int secondSlash = receivedData.indexOf('/', firstSlash + 1);

      int baseGlobalTargetAngle = receivedData.substring(0, firstSlash).toInt();
      int hombroGlobalTargetAngle = receivedData.substring(firstSlash + 1, secondSlash).toInt();
      int codoGlobalTargetAngle = receivedData.substring(secondSlash + 1).toInt();

      if(baseGlobalTargetAngle < 500){
        baseDiffAngle = baseGlobalTargetAngle - baseAngle;
        // llama a la funcion que mueve  el motor los angulos que toca
        Serial.println("baseDiffAngle");
        Serial.println(baseDiffAngle);
        motorToAngle(1, baseDiffAngle);
      }

      if(hombroGlobalTargetAngle < 500){
        hombroDiffAngle = hombroGlobalTargetAngle - hombroAngle;
        // llama a la funcion que mueve  el motor los angulos que toca
        Serial.println("hombroDiffAngle");
        Serial.println(hombroDiffAngle);
        motorToAngle(2, hombroDiffAngle);

      }

      if(codoGlobalTargetAngle < 500){
        codoDiffAngle = codoGlobalTargetAngle - codoAngle;
        // llama a la funcion que mueve  el motor los angulos que toca
        Serial.println("codoDiffAngle");
        Serial.println(codoDiffAngle);
        motorToAngle(3, codoDiffAngle);

      }
       
      float codoDiffAngle = codoGlobalTargetAngle - codoAngle;

      Serial.println("baseGlobalTargetAngle: " + String(baseGlobalTargetAngle));
      Serial.println("hombroGlobalTargetAngle: " + String(hombroGlobalTargetAngle));
      Serial.println("codoGlobalTargetAngle: " + String(codoGlobalTargetAngle));

      response = "{\"status\":\"success\",\"message\":\"Data processed successfully\"}";
      server.send(200, "application/json", response);
    }else {
      // Error: string too short
      Serial.println("Error: String too short (less than 2 characters)");
      response = "{\"status\":\"error\",\"message\":\"String must have at least 2 characters\"}";
      server.send(400, "application/json", response);
    }
  } else {
    // Error: no data received
    Serial.println("Error: No data received moveToPosition");
    response = "{\"status\":\"error\",\"message\":\"No data received\"}";
    server.send(400, "application/json", response);
  }
  Serial.println(" end del moveToPosition");
}
void motorToAngle(int motorid, float motorAngle) {

  if(motorid == 1){
    Serial.println("if(motorid == 1){");
    Serial.println(motorid);
    
    // for (int i = 0; i <= 255; i++) {
    //     analogWrite(PWMpin, i);
    //     delay(10);
    //   }

    // for (int i = 0; i <= 255; i++) {
    //   if(digitalRead(LIMIT_SWITCH_BASE_PIN) == LOW){
    //     motor1BaseInTarget = true;
    //     baseAngle = 90.0;
    //     break;
    //   }
    //   digitalWrite(STEP_PIN_BASE, HIGH);
    //   delayMicroseconds(100); 
    //   digitalWrite(STEP_PIN_BASE, LOW);
    //   delayMicroseconds(100);
    // }
  }

  if(motorid == 2){
    Serial.println("if(motorid == 2){");
    Serial.println(motorid);
    
    // for (int i = 0; i <= 255; i++){
    //   if(digitalRead(LIMIT_SWITCH_HOMBRO_PIN) == LOW ){
    //     motor2HomrboInTarget = true;
    //     hombroAngle = 180.0;
    //     break;
    //   }
    //   digitalWrite(STEP_PIN_HOMBRO, HIGH);
    //   delayMicroseconds(200); 
    //   digitalWrite(STEP_PIN_HOMBRO, LOW);
    //   delayMicroseconds(200);
    // }
  }

  if(motorid == 3){
    Serial.println("if(motorid == 3){");
    Serial.println(motorid);

    // for (int i = 0; i <= 255; i++) {
    //   if(digitalRead(LIMIT_SWITCH_CODO_PIN) == HIGH ){
    //     motor3CodoInTarget = true;
    //     codoAngle =100.0;
    //     break;
    //   }
    //   digitalWrite(STEP_PIN_CODO, HIGH);
    //   delayMicroseconds(200);
    //   digitalWrite(STEP_PIN_CODO, LOW);
    //   delayMicroseconds(200);
    // }
  }

}

void homing() {
  Serial.println("Homing");

  
  bool motor1BaseInTarget = false;
  bool motor3CodoInTarget = false;
  bool motor2HomrboInTarget = false;
  
  bool pinBase = digitalRead(LIMIT_SWITCH_BASE_PIN);
  bool pinCodo = digitalRead(LIMIT_SWITCH_CODO_PIN);
  bool pinHombro = digitalRead(LIMIT_SWITCH_HOMBRO_PIN);
  
Serial.println("pinBase");
Serial.println( pinBase);
Serial.println("pinCodo");
Serial.println( pinCodo);
Serial.println("pinHombro");
Serial.println(pinHombro);
  
  if(digitalRead(LIMIT_SWITCH_BASE_PIN) == LOW){
    Serial.print("entro en el if de la base");
    motor1BaseInTarget = true;
    baseAngle = 90.0;

  }
  if(digitalRead(LIMIT_SWITCH_CODO_PIN) == HIGH ){
    Serial.print("entro en el if de la codo");
    motor3CodoInTarget = true;
    codoAngle =100.0;

  }
  if(digitalRead(LIMIT_SWITCH_HOMBRO_PIN) == LOW ){
    Serial.print("entro en el if de la hombro");
    hombroAngle = 180.0;
    motor2HomrboInTarget = true;
  }
  
  digitalWrite(DIR_PIN_BASE, LOW);
  digitalWrite(DIR_PIN_HOMBRO, HIGH); 
  digitalWrite(DIR_PIN_CODO, HIGH); 

  while (motor1BaseInTarget == false ) {
    if(digitalRead(LIMIT_SWITCH_BASE_PIN) == LOW){
      motor1BaseInTarget = true;
      baseAngle = 90.0;
      break;
    }
    digitalWrite(STEP_PIN_BASE, HIGH);
    delayMicroseconds(200); 
    digitalWrite(STEP_PIN_BASE, LOW);
    delayMicroseconds(200);
  }

  while (motor3CodoInTarget == false ) {
      if(digitalRead(LIMIT_SWITCH_CODO_PIN) == HIGH ){
        motor3CodoInTarget = true;
        codoAngle =100.0;
        break;
      }
      digitalWrite(STEP_PIN_CODO, HIGH);
      delayMicroseconds(200);
      digitalWrite(STEP_PIN_CODO, LOW);
      delayMicroseconds(200);
  }

    while (motor2HomrboInTarget == false ) {
       if(digitalRead(LIMIT_SWITCH_HOMBRO_PIN) == LOW ){
        motor2HomrboInTarget = true;
        hombroAngle = 180.0;
        break;
      }
      digitalWrite(STEP_PIN_HOMBRO, HIGH);
      delayMicroseconds(200); 
      digitalWrite(STEP_PIN_HOMBRO, LOW);
      delayMicroseconds(200);
  }

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
Serial.println("motor1BaseInTarget "  );
Serial.println(motor1BaseInTarget);
Serial.println("motor2HomrboInTarget ");
Serial.println(motor2HomrboInTarget);
Serial.println("motor3CodoInTarget "  );
Serial.println( motor3CodoInTarget  );
  while (motor1BaseInTarget == false || motor2HomrboInTarget == false || motor3CodoInTarget == false) {
    Serial.println("lopp ");

    if(motor1BaseInTarget == false ){
      digitalWrite(STEP_PIN_BASE, HIGH);
      delayMicroseconds(100); 
      digitalWrite(STEP_PIN_BASE, LOW);
      delayMicroseconds(100);
      stepsToMoveWithTRansmision1BaseRemaining = stepsToMoveWithTRansmision1BaseRemaining - 1;
      if(stepsToMoveWithTRansmision1BaseRemaining < 1){
        motor1BaseInTarget = true;
        if(baseAngle >0){
          baseAngle = baseAngle + motor1AngleInt;
        }
      }
      if(digitalRead(LIMIT_SWITCH_BASE_PIN) == LOW && motor1Dir == "1"){
        motor1BaseInTarget = true;
        baseAngle = 90.0;
      }
    }

    if(motor2HomrboInTarget == false ){
      digitalWrite(STEP_PIN_HOMBRO, HIGH);
      delayMicroseconds(100); 
      digitalWrite(STEP_PIN_HOMBRO, LOW);
      delayMicroseconds(100);
      stepsToMoveWithTRansmisionRemaining =stepsToMoveWithTRansmisionRemaining - 1;
      if(stepsToMoveWithTRansmisionRemaining < 1){
        motor2HomrboInTarget = true;
        if( hombroAngle> 0){
          hombroAngle = hombroAngle + motor2AngleInt;
        }
      }
      if(digitalRead(LIMIT_SWITCH_HOMBRO_PIN) == LOW && motor2Dir == "1"){
        motor2HomrboInTarget = true;
        hombroAngle = 180.0;
      }
    }

    if(motor3CodoInTarget == false ){
      digitalWrite(STEP_PIN_CODO, HIGH);
      delayMicroseconds(100);
      digitalWrite(STEP_PIN_CODO, LOW);
      delayMicroseconds(100);
      stepsToMoveWithTRansmision3CodoRemaining =stepsToMoveWithTRansmision3CodoRemaining - 1;
      if(stepsToMoveWithTRansmision3CodoRemaining < 1){
        Serial.print("******" + stepsToMoveWithTRansmision3CodoRemaining );
        motor3CodoInTarget = true;
      }
      if(codoAngle < 0){
        codoAngle = codoAngle + motor3AngleInt;
      }
      if(digitalRead(LIMIT_SWITCH_CODO_PIN) == HIGH && motor3Dir == "1"){
        Serial.print("******");
        motor3CodoInTarget = true;
        codoAngle =100.0;
      }
    }
  }

  Serial.println("Motor movido ");


}
