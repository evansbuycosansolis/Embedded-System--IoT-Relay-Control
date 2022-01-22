
#include <ESP8266WiFi.h>

const char* ssid = "iPhone";
const char* password = "evans214";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare GPIO2
  pinMode(2, OUTPUT);
  pinMode (12, OUTPUT);
  digitalWrite(2, 0);
  digitalWrite (12, 0);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  int val;
  int val2;
  if (req.indexOf("/gpio/1") != -1){
    val = 0;
    val2=0;}
  else if (req.indexOf("/gpio/0") != -1){
    val = 1;
    val2=1;}
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  // Set Digital pin 2 according to the request
  digitalWrite(2, val);
  digitalWrite(12, val2);
  client.flush();


 client.println("HTTP/1.1 200 OK");
 client.println("Content-Type: text/html");
 client.println(""); //  do not forget this one
 client.println("<!DOCTYPE HTML>");
 client.println("<html>");
 client.println("<head>");
 client.println("<meta name='esp8266-iot-capable' content='yes' />");
 client.println("<meta name='esp8266-iot-status-bar-style' content='black-translucent' />");
 client.println("</head>");
 client.println("<body bgcolor = \"#c4c0c0\">"); 
 client.println("<hr/><hr>");
 client.println("<h4><center> Internet-Of-Things: Controlling Your Lights using NodeMCU</center></h4>");
 client.println("<hr/><hr>");
 client.println("<br><br>");
 client.println("<br><br>");
 client.println("<center>");
 client.println("Internet-of-things Light Switch");
 client.println("<br><br>");
 client.println("<a href=\"/gpio/1\"\"><button>Light On </button></a>");
 client.println("<a href=\"/gpio/0\"\"><button>Light Off </button></a><br />");  
 client.println("</center>");   
 client.println("<br><br>");
 client.println("<center>");
 client.println("<table border=\"5\">");
 client.println("<tr>");
 client.println("<br />");
 client.println("</tr>");
 client.println("</table>");
 client.println("</center>");
 client.println("</html>"); 
 delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

