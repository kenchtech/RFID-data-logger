
//Certified to work
/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
  Edited by KENCH_TECH 
*********/
//The esp8266 acts as a client and is controlled a webpage  whose ip addreess is that of the Wifi module
// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include <MFRC522.h>
#include <SPI.h>
MFRC522 mfrc522(10, 9); // MFRC522 mfrc522(SS_PIN, RST_PIN)
String tagUID = "39 D1 E6 00";  // String to store UID of tag. Change it with your tag's UID
const int LED =2;
const int LED2=0;
unsigned  char led_status=0;
unsigned char led2_status=0;

// Replace with your network credentials
const char* ssid     = "AndroidAPP";
const char* password = "1234567*";

// Set web server port number to 80
WiFiServer server(80);



void setup() {
  Serial.begin(9600); 
    SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  // Initialize the output variables as outputs
  pinMode(LED, OUTPUT);
pinMode (LED2,OUTPUT);
 
  // Set outputs to LOW
  digitalWrite(LED, LOW);
  digitalWrite(LED2, LOW);
  delay(50);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  server.begin();
  Serial.println("MINI SERVER STARTS AT: ");
  Serial.println(WiFi.localIP());
  
}

void loop(){
 void rfid_start ()
  WiFiClient client = server.available();   // Listen for incoming clients

  if (!client) {  return;        // If a new client connects,
  }
  Serial.println("CLIENT FOUND");
  while (!client.available())
  {
    delay(1);
  }
  String req= client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  //*********Control statement for first load(led1)
  if(req.indexOf("/lightoff")>=0) {
   led_status=0;
    digitalWrite(LED,LOW);
    Serial.println("LED OFF");
    delay(50);
  }
  else if(req.indexOf("/lighton")>=0)
  {
    led_status=1;
    digitalWrite(LED,HIGH);
    Serial.println("LED ON");
    delay(50);
  }
  //*******Control statements for second load(led2)
  if(req.indexOf("/light2off")>=0) {
   led2_status=0;
    digitalWrite(LED2,LOW);
    Serial.println("LED2 OFF");
    delay(50);
  }
  else if(req.indexOf("/light2on")>=0)
  {
    led2_status=1;
    digitalWrite(LED2,HIGH);
    Serial.println("LED2 ON");
    delay(50);
  }
    
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println("");
            
            // Display the HTML web page
            client.println("<!DOCTYPE html>");
            client.println("<html>");
            client.println("<head>");
            client.println("<title>IOT</title>");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
            client.println("</head>");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<body style=\"height:100%;margin:0;background:#f6f6f6\">");
            client.println("<div style=\"height:6%;text-align:center;padding:3px;background:#4caf50;color:white;\">");
            
            // Web Page Heading
            client.println("<h1>NIMI IOT</h1>");
            client.println("</div>");
            client.println("<br/>");
            if(led_status==1)
            client.println("<div style=\"color:#f57c00;text_align:center;font-size:20px;font-weight:bold;\">LIGHT ON</div>");
            
            else
             client.println("<div style=\"color:#f57c00;text_align:center;font-size:20px;font-weight:bold;\">LIGHT OFF</div>");

              client.println("<div style=\"color:#212121;text-align:center;\">status</div>");
             client.println("<br/>");
             client.println("<br/>");
             client.println("<div style=\"text-align:center;\">");
             client.println("<a href=\"/lighton\"\"style=\"color:white;background:#607d8b;padding;10px;border-radius:10px;text-decoration:none;\">LIGHT ON</a>");
             client.println("</div>");
             
             client.println("<br/>");
             client.println("<br/>");
             client.println("<div style=\"color:#212121;text-align:center;\">status</div>");
             client.println("<div style=\"text-align:center;\">");
             client.println("<a href=\"/lightoff\"\"style=\"color:white;background:#607d8b;padding;10px;border-radius:10px;text-decoration:none;\">LIGHT OFF</a>");
             client.println("</div>");
             client.println("</body>");
             client.println("</html>");

client.println("<br/>");
//******************This section is for the second load to be controlled
if(led2_status==1)
            client.println("<div style=\"color:#f57c00;text_align:center;font-size:20px;font-weight:bold;\">LIGHT2 ON</div>");
            
            else
             client.println("<div style=\"color:#f57c00;text_align:center;font-size:20px;font-weight:bold;\">LIGHT2 OFF</div>");
             
client.println("<br/>");
  client.println("<div style=\"color:#212121;text-align:center;\">status2</div>");
             client.println("<br/>");
             client.println("<br/>");
             client.println("<div style=\"text-align:center;\">");
             client.println("<a href=\"/light2on\"\"style=\"color:white;background:#607d8b;padding;10px;border-radius:10px;text-decoration:none;\">LIGHT2 ON</a>");
             client.println("</div>");
             
             client.println("<br/>");
             client.println("<br/>");
             client.println("<div style=\"color:#212121;text-align:center;\">status2</div>");
             client.println("<div style=\"text-align:center;\">");
             client.println("<a href=\"/light2off\"\"style=\"color:white;background:#607d8b;padding;10px;border-radius:10px;text-decoration:none;\">LIGHT2 OFF</a>");
             client.println("</div>");
             client.println("</body>");
             client.println("</html>");


             delay(1);
             Serial. println("RESPONSE SENT");
             Serial.println("");
}


void rfid_start(){
  Serial.println(" Show Your Tag ");
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  //Reading from the card
  String tag = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    tag.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  tag.toUpperCase();
  //Checking the card
  if (tag.substring(1) == tagUID) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Access Granted");
  
    delay(3000);
  }
  else
  {
    Serial.println("Wrong Tag Shown");
    Serial.println("Access Denied");
    delay(3000);
   
  }
}

////////////////////////////////////////////////////////////
void(){
if (tag.substring(1)==tagUID)
{
  Serial.printl
}




}







            
