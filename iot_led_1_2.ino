#include <ESP8266WiFi.h>
#define LED A0
#define led 
const char* ssid = "AndroidAP";
const char* password = "udhaya123";
unsigned char status_led=0;
WiFiServer server(80);

void setup() {
Serial.begin(115200);
pinMode(A0,OUTPUT);
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED )
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
server.begin();
Serial.println("Server started");
Serial.println(WiFi.localIP());
}

void loop() {
WiFiClient client = server.available();
if (!client) {
return;
}

Serial.println("new client");
while(!client.available())
{
delay(1);
}
String req = client.readStringUntil('\r');
Serial.println(req);
client.flush();
if (req.indexOf("/ledoff") != -1)
{
status_led=0;
analogWrite(A0,0);
Serial.println("LED OFF");
}
else if(req.indexOf("/ledlow") != -1)
{
status_led=1;
analogWrite(A0,64);
Serial.println("LED ON");
}

  if (req.indexOf("/ledmedium") != -1)
{
status_led=0;
analogWrite(A0,128);
Serial.println("LED ON");
}
else if(req.indexOf("/ledHIGH") != -1)
{
status_led=1;
analogWrite(A0,192);
Serial.println("LED ON");
}
else if(req.indexOf("/ledveryhigh") !=-1)
{
  status_led=1;
analogWrite(A0,255);
Serial.println("LED ON");
}
String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
web += "<html>\r\n";
web += "<body>\r\n";
web += "<h1>LED Status</h1>\r\n";
web += "<p>\r\n";

if(status_led==1)
web += "LED On\r\n";
else
web += "LED Off\r\n";
web += "</p>\r\n";
web += "</p>\r\n";
web += "<a href=\"/ledoff\">\r\n";
web += "<button>LED Off</button >\r\n";
web += "</a>\r\n";
web += "</p>\r\n";

web += "<a href=\"/ledlow\">\r\n";
web += "<button>LED low</button >\r\n";
web += "</a>\r\n";

if(status_led==1)
web += "LED On\r\n";
else
web += "LED Off\r\n";
web += "</p>\r\n";
web += "</p>\r\n";
web += "<a href=\"/ledmedium\">\r\n";
web += "<button>LED medium</button >\r\n";
web += "</a>\r\n";
web += "</p>\r\n";

web += "<a href=\"/ledHIGH\">\r\n";
web += "<button>LED high</button >\r\n";
web += "</a>\r\n";

web += "</body>\r\n";
web += "</html>\r\n";

client.print(web);
}
