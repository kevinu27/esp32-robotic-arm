
#include <WiFi.h>
#include <WebServer.h>

#define STEP_PIN_HOMBRO 18
#define DIR_PIN_HOMBRO 19
#define ENABLE_PIN_HOMBRO 21  // opcional

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
        
        String motor1 = receivedData.substring(0, firstSep);
        String motor2 = receivedData.substring(firstSep + 1, secondSep);
        String motor3 = receivedData.substring(secondSep + 1);


        int firstSepMotor1 = motor1.indexOf('-');
        int secondSepMotor1  = motor1.indexOf('-', firstSepMotor1 + 1);
        String motor1Dir = motor1.substring(0, firstSepMotor1);
        String motor1Angle = motor1.substring(firstSepMotor1 + 1, secondSepMotor1);
        String motor1Stepping = motor1.substring(secondSepMotor1 + 1);
        
      // // Print the split values
      // Serial.println("First two characters: " + firstTwoChars);
      // Serial.println("Rest of string: " + restOfString);

      Serial.println("motor1: " + motor1);
      Serial.println("motor2: " + motor2);
      Serial.println("motor3: " + motor3);
      Serial.println("motor1Dir: " + motor1Dir);
      Serial.println("motor1Angle: " + motor1Angle);
      Serial.println("motor1Stepping: " + motor1Stepping);
      // if(restOfString == "der"){
      //   moverMotor(true);
      // }
      //  if(restOfString == "izq"){
      //   moverMotor(false);
      //  }
      
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

void moverMotor(bool direccion) {
  digitalWrite(DIR_PIN_HOMBRO, direccion ? HIGH : LOW);

  for (int i = 0; i < steps_por_10_grados_hombro; i++) {
     Serial.println("lopp ");
    digitalWrite(STEP_PIN_HOMBRO, HIGH);
    delay(100); // velocidad del motor
    digitalWrite(STEP_PIN_HOMBRO, LOW);
    delay(100);
  }

  Serial.println("Motor movido ");
  Serial.println(grados_a_mover);
  Serial.println(" grados hacia " + String(direccion ? "derecha" : "izquierda"));
}
