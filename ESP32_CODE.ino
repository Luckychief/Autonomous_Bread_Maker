#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output4State = "off";
String output5State = "off";
String output6State = "off";
String output7State = "off";



// Assign output variables to GPIO pins
const int output4 = 4;
const int output5 = 5;
const int output6 = 6;
const int output7 = 7;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output6, OUTPUT);
  pinMode(output7, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output5, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output4, LOW);
  digitalWrite(output5, LOW);
  digitalWrite(output6, LOW);
  digitalWrite(output7, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
            } else if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(output5, LOW);
            }else if (header.indexOf("GET /6/on") >= 0) {
              Serial.println("GPIO 6 on");
              output6State = "on";
              digitalWrite(output6, HIGH);
            } else if (header.indexOf("GET /6/off") >= 0) {
              Serial.println("GPIO 6 off");
              output6State = "off";
              digitalWrite(output6, LOW);
            } else if (header.indexOf("GET /7/on") >= 0) {
              Serial.println("GPIO 7 on");
              output7State = "on";
              digitalWrite(output7, HIGH);
            } else if (header.indexOf("GET /7/off") >= 0) {
              Serial.println("GPIO 7 off");
              output7State = "off";
              digitalWrite(output7, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #FFA500; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Select Desired Option</h1>");

            // Display current state, and ON/OFF buttons for GPIO 4 
            
            // If the output4State is off, it displays the ON button       
            if (output4State=="off" && output5State=="off" && output6State=="off" && output7State=="off") {
              client.println("<p>Light, Small Batch</p>");
              client.println("<p><a href=\"/4/on\"><button class=\"button\">START</button></a></p>");
            } else if (output4State=="on") {
              client.println("<p>Light, Small Batch</p>");
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">CANCEL</button></a></p>");
              
            } 

            // Display current state, and ON/OFF buttons for GPIO 5 
            
            // If the output5State is off, it displays the ON button       
            if (output4State=="off" && output5State=="off" && output6State=="off" && output7State=="off") {
              client.println("<p>Light, Large Batch</p>");
              client.println("<p><a href=\"/5/on\"><button class=\"button\">START</button></a></p>");
            } else if (output5State=="on") {
              client.println("<p>Light, Large Batch</p>");
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">CANCEL</button></a></p>");
            } 
            
            // Display current state, and ON/OFF buttons for GPIO 6  
            
            // If the output6State is off, it displays the ON button       
            if (output4State=="off" && output5State=="off" && output6State=="off" && output7State=="off") {
              client.println("<p>Dark, Small Batch</p>");
              client.println("<p><a href=\"/6/on\"><button class=\"button\">START</button></a></p>");
            } else if (output6State=="on") {
              client.println("<p>Dark, Small Batch</p>");
              client.println("<p><a href=\"/6/off\"><button class=\"button button2\">CANCEL</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 7  
            
            // If the output7State is off, it displays the ON button       
            if (output4State=="off" && output5State=="off" && output6State=="off" && output7State=="off") {
              client.println("<p>Dark, Large Batch</p>");
              client.println("<p><a href=\"/7/on\"><button class=\"button\">START</button></a></p>");
            } else if (output7State=="on") {
              client.println("<p>Dark, Large Batch</p>");
              client.println("<p><a href=\"/7/off\"><button class=\"button button2\">CANCEL</button></a></p>");
            }
            //client.println("</body></html>");

            //ADDITIONAL CODE FOR STEPPER MOTOR
            //client.println("<p>GPIO 15</p>");
            //if (output7State=="off") {
              //client.println("<p><a href=\"/15/on\"><button class=\"button\">ON</button></a></p>");
            //} else {
              //client.println("<p><a href=\"/15/off\"><button class=\"button button2\">OFF</button></a></p>");
            //}

            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
