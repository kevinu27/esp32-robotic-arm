
#include <WiFi.h>
#include <WebServer.h>

#define STEP_PIN 18
#define DIR_PIN 19
#define ENABLE_PIN 21  // opcional

const int steps_per_rev = 200;  // 1.8° por paso
const float grados_a_mover = 40.0;
const int steps_por_10_grados = 50;

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
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

  digitalWrite(ENABLE_PIN, HIGH); 
  digitalWrite(DIR_PIN, LOW); 

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
      // Split the string
      firstTwoChars = receivedData.substring(0, 2);
      restOfString = receivedData.substring(2);
      
      // Print the split values
      Serial.println("First two characters: " + firstTwoChars);
      Serial.println("Rest of string: " + restOfString);
      if(restOfString == "der"){
        moverMotor(true);
      }
       if(restOfString == "izq"){
        moverMotor(false);
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

void moverMotor(bool direccion) {
  digitalWrite(DIR_PIN, direccion ? HIGH : LOW);

  for (int i = 0; i < steps_por_10_grados; i++) {
     Serial.println("lopp ");
    digitalWrite(STEP_PIN, HIGH);
    delay(100); // velocidad del motor
    digitalWrite(STEP_PIN, LOW);
    delay(100);
  }

  Serial.println("Motor movido ");
  Serial.println(grados_a_mover);
  Serial.println(" grados hacia " + String(direccion ? "derecha" : "izquierda"));
}
