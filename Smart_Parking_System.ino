#inlcude <ESP8266WiFi.h>
String apiKey = "3PFDDW63K91OJHMB";
const char *ssid= "Farrukh";
const char* pass="Farrukh12";
const char * server = "api.thingspeak.com";

int pir_sensor= 16;

WiFiClient client;

void setup()
{
  Serial.begin(115200);
  delay(10);
  pinMode(pir_sensor,INPUT);

  Serial.println("Connecting to ");
  Serial.println("ssid");

  WiFi.begin(ssid, pass);

  while (WiFi.status() !=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop()
{
  int pir_sensor = digitalRead(pir_sensor);

  if (client.connect(server,80)){
    String postStr=apiKey;
    postStr+="&fieldl";
    postStr+=String(pir);
    postStr+="\r\n\r\n";

    client.print("POST /update HTTP1.1\n");
    client.print("Host: api.thingspeak.com\n");  
    client.print("Connection: close\n");  
    client.print("X-THINGSPEAKAPIKEY: "+apiKey + "\n");  
    client.print("Content-Type: application/x-www-form-urlencoded\n"); 
    client.print("Content-Length: ");
    client.print(postStr.length()); 
    client.print("\n\n");  
    client.print(postStr);

    Serial.print("motion : ");
    Serial.print("pir");
    Serial.println(" , Send to Thingspeak.");  

  }
  client.stop();

  delay(1000);
}