
#include <WiFi.h>
#include <WebServer.h>

#define STEP_PIN_BASE 15
#define DIR_PIN_BASE 16
#define ENABLE_PIN_BASE 17  // opcional

#define STEP_PIN_HOMBRO 18
#define DIR_PIN_HOMBRO 19
#define ENABLE_PIN_HOMBRO 21  // opcional

#define STEP_PIN_CODO 12
#define DIR_PIN_CODO 13
#define ENABLE_PIN_CODO 24  // opcional

        int firstSepMotor2 ;
        int secondSepMotor2 ;
        String motor2Dir;
        int motor2Angle ;
        int motor2Stepping ;
        bool motor1BaseInTarget = false;
        bool motor2HomrboInTarget = false;
        bool motor3CodoInTarget = false;
        int relacionTrasmisionMotor2Hombro = 4;

const int steps_per_rev_hombro = 200;  // 1.8° por paso
const float grados_a_mover = 40.0;
const int steps_por_10_grados_hombro = 50;

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

  digitalWrite(ENABLE_PIN_HOMBRO, HIGH); 
  digitalWrite(DIR_PIN_HOMBRO, LOW); 

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
        String motor1Dir = motor1Base.substring(0, firstSepMotor1);
        String motor1Angle = motor1Base.substring(firstSepMotor1 + 1, secondSepMotor1);
        String motor1Stepping = motor1Base.substring(secondSepMotor1 + 1);
        

        firstSepMotor2 = motor2Hombro.indexOf('-');
      secondSepMotor2  = motor2Hombro.indexOf('-', firstSepMotor2 + 1);
        motor2Dir = motor2Hombro.substring(0, firstSepMotor2);
      motor2Angle = motor2Hombro.substring(firstSepMotor2 + 1, secondSepMotor2).toInt();
      motor2Stepping = motor2Hombro.substring(secondSepMotor2 + 1).toInt();


        int firstSepMotor3 = motor3Codo.indexOf('-');
        int secondSepMotor3  = motor3Codo.indexOf('-', firstSepMotor3 + 1);
        String motor3Dir = motor3Codo.substring(0, firstSepMotor3);
        String motor3Angle = motor3Codo.substring(firstSepMotor3 + 1, secondSepMotor3);
        String motor3Stepping = motor3Codo.substring(secondSepMotor3 + 1);

      // // Print the split values
      // Serial.println("First two characters: " + firstTwoChars);
      // Serial.println("Rest of string: " + restOfString);

      Serial.println("motor1Base: " + motor1Base);
      Serial.println("otor2Hombro: " + motor2Hombro);
      Serial.println("motor3Codo: " + motor3Codo);
      Serial.println("motor2Dir: " + motor2Dir);
      Serial.println("motor2Angle: " + motor2Angle);
      Serial.println("motor2Stepping: " + motor2Stepping);
      
       if(motor2Angle != 0 or motor1Angle != 0 or motor3Angle != 0 ){
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
  if(motor2Dir == "0"){
    Serial.println("en el if de (motor2Dir == 1): " );
    digitalWrite(DIR_PIN_HOMBRO, LOW); 
    }
   if(motor2Dir == "1"){
      Serial.println("en el if de (motor2Dir == 0): " );
      digitalWrite(DIR_PIN_HOMBRO, HIGH); 
      }
 

  for (int i = 0; i < motor2Angle; i++) {
     Serial.println("lopp ");
    digitalWrite(STEP_PIN_HOMBRO, HIGH);
    delayMicroseconds(100); // velocidad del motor
    digitalWrite(STEP_PIN_HOMBRO, LOW);
    delayMicroseconds(100);
  }

  Serial.println("Motor movido ");
  Serial.println(grados_a_mover);

}
